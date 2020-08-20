#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <visualization_msgs/Marker.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PointStamped.h>
// PCL specific includes
#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl_ros/transforms.h>
// PCL Filtering
#include <pcl/filters/voxel_grid.h>
// PCL Plane Segmentation
#include <pcl/ModelCoefficients.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/extract_indices.h>
// PCL Clustering
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/kdtree/kdtree_flann.h>
// PCL Visualizer
#include <pcl_visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>


// Parameters (TODO: Create a yaml file and move params to the param server)
#define MAX_PERSON_HEIGHT 2
#define MIN_PERSON_HEIGHT 0.5
#define MAX_PERSON_WIDTH 1
#define MIN_PERSON_WIDTH 0.2
#define MAX_PERSON_CLUSTER_SIZE 20000
#define MIN_PERSON_CLUSTER_SIZE 100
#define PERSON_CLUSTER_TOLERANCE 0.2 //0.1
#define LEAF_SIZE 0.05 //0.01 - Downsampled grid size

ros::Publisher pub;
ros::Publisher pub_plane;
ros::Publisher pub_cluster;
ros::Publisher cluster_marker;
ros::Publisher detections_pub;
tf::TransformListener *tf_listener;
pcl::ModelCoefficients::Ptr plane_coefficients (new pcl::ModelCoefficients);

// Visualization Marker for Point Cloud Cluster

void publishClusterMarker(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster, std::string ns ,int id, float r, float g, float b)
{
  // Tranform cloud to base_link
   pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ>);
   (*cloud_cluster).header.frame_id = "openni_depth_optical_frame";
 //  tf_listener->waitForTransform("openni_depth_optical_frame","base_link",ros::Time::now(),ros::Duration(3.0));
   pcl_ros::transformPointCloud("base_link",*cloud_cluster,*transformed_cloud, *tf_listener);

 // transformed_cloud = cloud_cluster;

  Eigen::Vector4f centroid;
  Eigen::Vector4f min;
  Eigen::Vector4f max;

  pcl::compute3DCentroid (*transformed_cloud, centroid);
  pcl::getMinMax3D (*transformed_cloud, min, max);

  uint32_t shape = visualization_msgs::Marker::CUBE;
  visualization_msgs::Marker marker;
  marker.header.frame_id = "base_link";
  marker.header.stamp = ros::Time::now();

  marker.ns = ns;
  marker.id = id;
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.x = centroid[0];
  marker.pose.position.y = centroid[1];
  marker.pose.position.z = centroid[2];
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  marker.scale.x = (max[0]-min[0]);
  marker.scale.y = (max[1]-min[1]);
  marker.scale.z = (max[2]-min[2]);

  if (marker.scale.x ==0)
    marker.scale.x=0.1;

  if (marker.scale.y ==0)
    marker.scale.y=0.1;

  if (marker.scale.z ==0)
    marker.scale.z=0.1;

  marker.color.r = r;
  marker.color.g = g;
  marker.color.b = b;
  marker.color.a = 0.5;

  marker.lifetime = ros::Duration();
  //   marker.lifetime = ros::Duration(0.5);
  cluster_marker.publish(marker); 
  return;
} 

//------------------------------------------------------------------------------------------------------------------------------------------------
bool  evaluateCluster(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster) 
{

  // Tranform cloud to base_link
  pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ>);
  (*cloud_cluster).header.frame_id = "openni_depth_optical_frame";
 // tf_listener->waitForTransform("openni_depth_optical_frame","base_link",ros::Time::now(),ros::Duration(3.0));
  pcl_ros::transformPointCloud("base_link",*cloud_cluster,*transformed_cloud, *tf_listener);

 // transformed_cloud = cloud_cluster;
  Eigen::Vector4f centroid;
  Eigen::Vector4f min;
  Eigen::Vector4f max;

  pcl::compute3DCentroid (*transformed_cloud, centroid);
  pcl::getMinMax3D (*transformed_cloud, min, max);


  // All human beings must be shorter than 2m and taller than 1m.
  if(!((max[2]-min[2]>MIN_PERSON_HEIGHT)&&(max[2]-min[1]<MAX_PERSON_HEIGHT)))
    return false;
  // Human beings cannot be wider than 1m
  if((max[1]-min[1]>MAX_PERSON_WIDTH)||(max[0]-min[0]>MAX_PERSON_WIDTH))
    return false;
  if((max[1]-min[1]<MIN_PERSON_WIDTH)||(max[0]-min[0]<MIN_PERSON_WIDTH))
    return false;

  ROS_INFO("Person Location (x,y,z) %f %f %f\n",centroid[0],centroid[1],centroid[2]);

  geometry_msgs::PointStamped cluster_centroid;
  cluster_centroid.header.frame_id = "base_link";
  cluster_centroid.header.stamp = ros::Time::now();
  cluster_centroid.point.x = centroid[0];
  cluster_centroid.point.y = centroid[1];
  cluster_centroid.point.z = centroid[2];
  detections_pub.publish(cluster_centroid);

  return true;
} 

//------------------------------------------------------------------------------------------------------------------------------------------------

// Get Ground Plane Coefficients from Point Cloud using Sample Consensus
pcl::ModelCoefficients::Ptr getPlaneCoefficients(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{

  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_temp (new pcl::PointCloud<pcl::PointXYZ>);
  cloud_temp = cloud;

  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);;
  // Create the segmentation object
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  // Optional
  seg.setOptimizeCoefficients (true);
  // Mandatory
  seg.setModelType (pcl::SACMODEL_PLANE);
  seg.setMethodType (pcl::SAC_RANSAC);
  seg.setDistanceThreshold (0.3); //0.01
  seg.setInputCloud (cloud_temp->makeShared ());
  seg.segment (*inliers, *coefficients);

  // Publish the model coefficients
  pub_plane.publish (*coefficients);
  //std::cerr << "Model coefficients: " << coefficients->values[0] << " " 
   // << coefficients->values[1] << " "
  //  << coefficients->values[2] << " " 
   // << coefficients->values[3] << std::endl;
  return coefficients;

}
//------------------------------------------------------------------------------------------------------------------------------------------------
// Remove Ground Plane from Point Cloud
pcl::PointCloud<pcl::PointXYZ>::Ptr removeGroundPlane(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::ModelCoefficients::Ptr coefficients)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr ground_removed_pcd (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
  // Create the segmentation object
  pcl::SACSegmentation<pcl::PointXYZ> seg;
  // Optional
  seg.setOptimizeCoefficients (false);
  // Mandatory
  seg.setModelType (pcl::SACMODEL_PLANE);
  // seg.setModelType (pcl::SACMODEL_PARALLEL_PLANE);
  //seg.setAxis (Eigen::Vector3f (0.0, 0.0, 1.0));
  //seg.setEpsAngle (15*3.14/180);
  seg.setMethodType (pcl::SAC_RANSAC);
  seg.setDistanceThreshold (0.1); //0.01
  seg.setInputCloud (cloud->makeShared ());
  seg.segment (*inliers, *coefficients);
 // std::cerr << "Model coefficients: " << coefficients->values[0] << " " 
   // << coefficients->values[1] << " "
   // << coefficients->values[2] << " " 
   // << coefficients->values[3] << std::endl;

  // Remove the planar inliers from the input cloud
  pcl::ExtractIndices<pcl::PointXYZ> extract;
  extract.setInputCloud (cloud);
  extract.setIndices (inliers);
  extract.setNegative (true);
  extract.filter(*ground_removed_pcd);
  return ground_removed_pcd;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
// Euclidean Clustering
pcl::PointCloud<pcl::PointXYZ>::Ptr doEuclideanClustering(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cluster_pcd (new pcl::PointCloud<pcl::PointXYZ>);

  // Creating the KdTree object for the search method of the extraction
  pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr tree (new pcl::KdTreeFLANN<pcl::PointXYZ>);
  tree->setInputCloud (cloud);

  std::vector<pcl::PointIndices> cluster_indices;
  pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
  ec.setClusterTolerance (PERSON_CLUSTER_TOLERANCE); // 2cm
  ec.setMinClusterSize (MIN_PERSON_CLUSTER_SIZE); //100
  ec.setMaxClusterSize (MAX_PERSON_CLUSTER_SIZE);
  ec.setSearchMethod (tree);
  ec.setInputCloud (cloud);
  ec.extract (cluster_indices);

  int j = 0;
  bool human_flag = true;
  for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
  {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZ>);
    for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++)
      cloud_cluster->points.push_back (cloud->points[*pit]); //*

    cloud_cluster->width = cloud_cluster->points.size ();
    cloud_cluster->height = 1;
    cloud_cluster->is_dense = true;
    cloud_cluster->sensor_origin_ = cloud->sensor_origin_;
    cloud_cluster->sensor_orientation_ = cloud->sensor_orientation_;
    //printf("Size: %d\n",(int)cloud_cluster->points.size ());


    // Publish the cluster marker
       human_flag = evaluateCluster(cloud_cluster);
    if(human_flag == true){
   
      float r = 1, g = 0, b = 0;
    std::string ns = "base_link";
    publishClusterMarker(cloud_cluster,ns,1,r,g,b);
    
    // Publish the data
      sensor_msgs::PointCloud2 output_cloud; 
      pcl::toROSMsg(*cloud_cluster,output_cloud);
      output_cloud.header.frame_id = "openni_depth_optical_frame";
      pub_cluster.publish (output_cloud);
      // return cloud_cluster;
    }
    j++;

  }
  return cluster_pcd;

}
//------------------------------------------------------------------------------------------------------------------------------------------------
// Callback for ROS Subscriber
  void 
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& cloud)
{

  // Input PCD Point Cloud
  pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromROSMsg (*cloud, *input_cloud);

  // Output Sensor MSG point cloud
  sensor_msgs::PointCloud2 output_cloud;

  // Processing 
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  // One time processing
  static int i = 1;
  if(i==1)
  {
    plane_coefficients = getPlaneCoefficients(input_cloud);
    i = 0;
  } 

  // Perform the actual filtering
  pcl::VoxelGrid<pcl::PointXYZ> sor;
  sor.setInputCloud (input_cloud);
  sor.setLeafSize (LEAF_SIZE,LEAF_SIZE,LEAF_SIZE);
  sor.filter (*cloud_filtered);

  // Plane Segmentation 
  cloud_filtered = removeGroundPlane(cloud_filtered,plane_coefficients);

  //Euclidean Clustering
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZ>);
  cloud_cluster = doEuclideanClustering(cloud_filtered);

  // Publish the data
  pcl::toROSMsg(*cloud_filtered,output_cloud);
  pub.publish (output_cloud); 
}
//------------------------------------------------------------------------------------------------------------------------------------------------
  int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "pcdtest");
  ros::NodeHandle nh;
  tf_listener = new tf::TransformListener();

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("openni/depth_registered/points", 1, cloud_cb);

  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("base_link/filtered_cloud", 1);
  // Create a ROS publisher for the detections
  detections_pub = nh.advertise<geometry_msgs::PointStamped>("kinect_tracker/detections",1);
  // Create a ROS publisher for the output segmented plane
  pub_plane = nh.advertise<pcl::ModelCoefficients> ("base_link/plane", 1);
  // Create a ROS publisher for the clusters
  pub_cluster = nh.advertise<sensor_msgs::PointCloud2> ("base_link/cluster_cloud", 1);
  // Create a ROS publisher for the cluster markers
  cluster_marker = nh.advertise<visualization_msgs::Marker> ("base_link/cluster_marker", 1);


  // Spin
  ros::spin ();
}

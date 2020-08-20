#include "ROSThread.h"


extern pRBCORE_SHM_COMMAND     sharedCMD;
extern pRBCORE_SHM_REFERENCE   sharedREF;
extern pRBCORE_SHM_SENSOR      sharedSEN;
extern pUSER_SHM               sharedUSER;
extern pROS_SHM                sharedROS;

extern int     __IS_GAZEBO;


ROSThread::ROSThread()
{
}

void ROSThread::run(){

    ROSWorker worker;
    QTimer fastTimer;
    QTimer timerPODO2ROS, timerROS2PODO;

    if(__IS_GAZEBO){
        worker.timePeriod = 0.005; // 50ms period for sending
        worker.timePrev = worker.timeCur = sharedSEN->Sim_Time_sec + sharedSEN->Sim_Time_nsec/1000000000.0;

        connect(&fastTimer, SIGNAL(timeout()), &worker, SLOT(onFastTimer()));
        fastTimer.start(1);
    }else{
        worker.timePeriod = 0.005;
        connect(&timerPODO2ROS, SIGNAL(timeout()), &worker, SLOT(onPODO2ROS()));
        connect(&timerROS2PODO, SIGNAL(timeout()), &worker, SLOT(onROS2PODO()));

        timerPODO2ROS.start(5);
        timerROS2PODO.start(5);
    }
    exec();
}


ROSWorker::ROSWorker(){
    serverPODOROS = new PODO_ROS_Server();
    serverPODOROS->RBServerOpen(QHostAddress::AnyIPv4, 5000);
    if(__IS_GAZEBO){
        connect(serverPODOROS, SIGNAL(SIG_NewConnection()), this, SLOT(onNewConnection()));
    }

    connect(serverPODOROS, SIGNAL(SIG_DisConnected()),this,SLOT(onDisconnect()));
    serverJOINTREF = new Ref_Receive_Server();
    serverJOINTREF->RBServerOpen(QHostAddress::AnyIPv4, 7000);
}

void ROSWorker::onNewConnection(){
    timePrev = timeCur = sharedSEN->Sim_Time_sec + sharedSEN->Sim_Time_nsec/1000000000.0;
}

void ROSWorker::onDisconnect()
{
    printf("ROS disconnected\n");
    sharedROS->COMMAND.CMD_GRIPPER = GRIPPER_STOP;
    sharedROS->COMMAND.CMD_JOINT = MODE_E_STOP;
    sharedROS->COMMAND.CMD_WHEEL = WHEEL_MOVE_STOP;
}

void ROSWorker::onFastTimer(){
    // read data from ROS
    onROS2PODO();

    // send data to ROS
    timeCur = sharedSEN->Sim_Time_sec + sharedSEN->Sim_Time_nsec/1000000000.0;
    if(timeCur - timePrev >= timePeriod){
        timePrev = timeCur;
        onPODO2ROS();
    }else if(timeCur < timePrev-0.001){
        FILE_LOG(logERROR) << "SimTime Reversed..";
        FILE_LOG(logERROR) << "Probably New Gazebo is turned on..";
        FILE_LOG(logERROR) << "Reset the local timer..";

        timePrev = timeCur = sharedSEN->Sim_Time_sec + sharedSEN->Sim_Time_nsec/1000000000.0;
    }
}


void ROSWorker::SendtoROS(){
    static int index = 0;
    for(int i=0; i<NO_OF_JOINTS; i++){
        TXData.JointReference[i] = sharedSEN->ENCODER[MC_GetID(i)][MC_GetCH(i)].CurrentReference;
        TXData.JointEncoder[i]   = sharedSEN->ENCODER[MC_GetID(i)][MC_GetCH(i)].CurrentPosition;
    }
    TXData.odom_x = sharedUSER->odom_data[0];
    TXData.odom_y = sharedUSER->odom_data[1];
    TXData.odom_theta = sharedUSER->odom_data[2];
    TXData.vx = sharedUSER->odom_data[3];
    TXData.vy = sharedUSER->odom_data[4];
    TXData.vth = sharedUSER->odom_data[5];

    //write sensor
    for(int i=0; i<NUM_JOINTS; i++)
    {
        TXData.podo2ros_data.sensor.ENCODER[i] = sharedSEN->ENCODER[ROS_MC_Pairs[i].id][ROS_MC_Pairs[i].ch];
    }
    TXData.podo2ros_data.sensor.FT[WRIST_LEFT] = sharedSEN->FT[3];
    TXData.podo2ros_data.sensor.FT[WRIST_RIGHT] = sharedSEN->FT[2];

    //write feedback
    TXData.podo2ros_data.Arm_feedback = sharedROS->Arm_feedback;
    TXData.podo2ros_data.Base_feedback = sharedROS->Base_feedback;
    TXData.podo2ros_data.Gripper_feedback = sharedROS->Gripper_feedback;

//    printf("%f\n",TXData.podo2ros_data.Arm_feedback.joint[rosREB].reference);
//    sharedROS->joint_before[rosWST].reference = TXData.podo2ros_data.Arm_feedback.wbik[WAIST].Goal_angle;
//    sharedROS->joint_before[rosREB].reference = TXData.podo2ros_data.sensor.ENCODER[rosWST].CurrentReference;

//    static int cnt = 0;
//    sharedROS->ROSindex = cnt;
//    cnt++;
    //write state
    TXData.podo2ros_data.state_arm = sharedROS->state_arm;
    TXData.podo2ros_data.state_base = sharedROS->state_base;
    TXData.podo2ros_data.index = index;

    memcpy(&(TXData.cmd), &(sharedUSER->G2M.ros_cmd), sizeof(LAN_GENERAL_COMMAND));
    sharedUSER->G2M.ros_cmd.cmd = 0;

    //FILE_LOG(logWARNING) << "Send to ROS: " << sizeof(LAN_PODO2ROS);
    QByteArray SendData = QByteArray::fromRawData((char*)&TXData, sizeof(LAN_PODO2ROS));
    serverPODOROS->RBSendData(SendData);

    index++;
}

void ROSWorker::SendtoJOINTREF(){
    static int index = 0;

    QByteArray SendData = QByteArray::fromRawData((char*)&index, sizeof(int));
    serverJOINTREF->RBSendData(SendData);

    index++;
}

void ROSWorker::ReadfromROS(){
    printf("Read From ROS\n");
    QByteArray tempData = serverPODOROS->dataReceived[0];
    serverPODOROS->dataReceived.pop_front();

    memcpy(&RXData, tempData.data(), sizeof(RXData));

    sharedUSER->vel_cmd[0] = RXData.vx;
    sharedUSER->vel_cmd[1] = RXData.vth;

    //read action
    sharedROS->Arm_action = RXData.ros2podo_data.Arm_action;
    sharedROS->Base_action = RXData.ros2podo_data.Base_action;
    printf("%f\n",RXData.ros2podo_data.Base_action.wheel.VelX);
    sharedROS->Gripper_action.side = RXData.ros2podo_data.Gripper_action.side;
    sharedROS->Gripper_action.desired_mm = RXData.ros2podo_data.Gripper_action.desired_mm;
    sharedROS->ROSindex = RXData.ros2podo_data.index;
    //read command
    sharedROS->COMMAND.CMD_GRIPPER = RXData.ros2podo_data.CMD_GRIPPER;
    sharedROS->COMMAND.CMD_WHEEL = RXData.ros2podo_data.CMD_WHEEL;
    sharedROS->COMMAND.CMD_JOINT = RXData.ros2podo_data.CMD_JOINT;
    printf("CMD = %d, %d, %d\n",RXData.ros2podo_data.CMD_JOINT,RXData.ros2podo_data.CMD_GRIPPER,RXData.ros2podo_data.CMD_WHEEL);
//    printf("ref WST = %f\n",RXData.ros2podo_data.Arm_action.joint[rosWST].reference);
    //here!
//    usleep(20*1000);
}

void ROSWorker::ReadfromROS_JOINTREF()
{
    static int i=0;
    while(serverJOINTREF->dataReceived.size()>0)
    {
        QByteArray tempData = serverJOINTREF->dataReceived[0];
        serverJOINTREF->dataReceived.pop_front();

        ROS_JOINTREF tempDATA;
        memcpy(&tempDATA, tempData, sizeof(ROS_JOINTREF));

        if(tempDATA.StartFlag == true)
        {
            printf("StartFlag\n");
            i=0;
            memset(&sharedROS->refarray, 0, sizeof(ROS_JOINTREF)*200);
        }

        sharedROS->ref = tempDATA;
        sharedROS->refarray[i] = tempDATA;
        sharedROS->DoneFlag = tempDATA.DoneFlag;
        i++;

        if(tempDATA.DoneFlag == true)
            printf("DoneFlag\n");
    }

//    sharedROS->refsIter = sharedROS->refs->begin();

    if(sharedROS->DoneFlag == true)
    {
        printf("DoneFlag true\n");
        sharedROS->refsLen = i;//sharedROS->refs->size();
        i=0;

        for(int i=0;i<NUM_JOINTS;i++)
        {
            sharedROS->refsGoalTime[i] = 0.;
        }

        //print
        for(int j=0;j<sharedROS->refsLen;j++)
        {
            for(int i=0;i<NUM_JOINTS;i++)
            {
                //if(sharedROS->refsIter[j].ref[i].ONOFF_control == true)
                if(sharedROS->refarray[j].ref[i].ONOFF_control == true)
                {
                    printf("%d|%d   ON : %d     REF : %f        TIME : %f\n",j,i,sharedROS->refarray[j].ref[i].ONOFF_control,sharedROS->refarray[j].ref[i].reference,sharedROS->refarray[j].ref[i].GoalmsTime);
                    sharedROS->refsGoalTime[i] += sharedROS->refarray[j].ref[i].GoalmsTime;
                }
            }
        }
        printf("print done in rosthread\n");
    }

}

void ROSWorker::onPODO2ROS(){
    if(serverPODOROS->RBConnectionState == RBLAN_CS_CONNECTED){
        SendtoROS();
    }
    if(serverJOINTREF->RBConnectionState == RBLAN_CS_CONNECTED)
    {
        SendtoJOINTREF();
    }
}

void ROSWorker::onROS2PODO(){
    if(serverPODOROS->dataReceived.size() > 0){
        ReadfromROS();
    }
    if(serverJOINTREF->dataReceived.size() > 0)
    {
        printf("read start\n");
        ReadfromROS_JOINTREF();
    }
}


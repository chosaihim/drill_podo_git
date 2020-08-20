#ifndef MAINHEADER_H
#define MAINHEADER_H
#include <QCoreApplication>

#include <alchemy/task.h>
#include "../../../share/Headers/ROS_COMMUNICATION.h"
#include "../../../share/Headers/Command.h"
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <Eigen/Dense>
#include "BasicFiles/ManualCAN.h"

#include "BasicFiles/joint.h"
#include "BasicFiles/taskmotion.h"
#include "BasicFiles/BasicMatrix.h"

#include "JoyStick/joystickclass.h"
#include "JoyStick/joystickvariable.h"

#ifndef PI
#define PI			3.141592653589793
#endif
#ifndef D2R
#define D2R			1.745329251994330e-2
#endif
#ifndef R2D
#define R2D			5.729577951308232e1
#endif

#include "OMNImove.h"
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

/* Debug data */
FILE *fp;
#define ROW 50000
#define COL 100
int     Save_Index;
double  Save_Data[COL][ROW];

///* RT task handler for control */
//TaskMotion      *WBmotion;

// TOOL_MOTION Supervisor
int     WaitMode     = 0;
int     WaitCount    =       0;
double  WaitTime     = 0.;


enum{
    PUB_DONE = 0, PUB_START, PUB_onlyRIGHT, PUB_onlyLEFT, PUB_onlyWHEEL, PUB_TRAJECTORY
};

const int TransNum[NUM_JOINTS] = {
    RSP, RSR, RSY, REB, RWY, RWP, RWY2,
    LSP, LSR, LSY, LEB, LWY, LWP, LWY2,
    WST, RWH, LWH, BWH
};

enum PODO_WORKING_STATE{
    STATE_SLEEP = 0, STATE_JOINT_PUBLISH, STATE_JOINT_MOVING, STATE_WBIK_MOVING
};

OMNIMOVE OMNImove;

typedef struct _ref200_
{
    QVector<double> p;
}ref200;

typedef struct _isonoff_
{
    QVector<int>   s;
}isonoff;

isonoff IsONOFF[NUM_JOINTS];
ref200 Pt[NUM_JOINTS];
ref200 dPt[NUM_JOINTS];
ref200 ddPt[NUM_JOINTS];

double curPt[NUM_JOINTS];
double curdPt[NUM_JOINTS];
double curddPt[NUM_JOINTS];

int MAX_GRIPPER_CNT = 300;

int isTerminated;
int PODO_NO;
int PODO_NO_DAEMON  = 0;
int __IS_WORKING    = false;
int __IS_GAZEBO     = false;
int WB_FLAG         = false;

int FLAG_JointPublish   = false;
int STATE_JointPublish  = PUB_DONE;
int FLAG_Gripper        = false;
int MODE_RGripper       = 0;
int MODE_LGripper       = 0;
int MODE_Gripper        = 0;
int SIDE_Gripper        = 0;
double LIMIT_Gripper    = 0.;
double DESIRED_Gripper  = 0.;
int FLAG_trajectory     = false;

int  CheckMotionOwned();
void CatchSignals(int _signal);
int  HasAnyOwnership();
void Write_Feedback();
void Calculate_FK();
void RBTaskThread(void *);
void RBFlagThread(void *);
int  RBInitialize(void);
void save();
void JOY_TH();
void ReadJoy();
void CalculateLIMITGripper();
void ToolTask_Supervisor();


// Move Function //
void StartWBIKmotion(int _mode);
void ROS_Joint_Publish();
void ROS_Move_Joint();
void ROS_Move_WBIK();
void PushJointReference();
void PushJointTrajectory();
void SetMoveJoint();
void SetWBIK();
void GripperTH();
int CheckRobotState_ARM();
int CheckRobotState_BASE();
int IsReadyTrajectory200Hz();

// GUI Function //
void GotoHomePos();
void GotoWalkReadyPos();
void SetOriHand(doubles &target, double _pitch, double _yaw);
void SetOriHand_YP(doubles &target, double _pitch, double _yaw);

// TOOL motion //
void SetWaitTime(int mode, double time);
int  Mode_TOOL = false;
int  Mode_cont = false;

//Joystick
enum{
    MANUAL_STOP = 0, MANUAL_WHEEL, MANUAL_RHAND, MANUAL_LHAND, MANUAL_TWOHAND
};
/* Joystick Move Variables */
doubles RWHList(120);
doubles LWHList(120);
doubles BWHList(120);
double RWHnow, LWHnow, BWHnow;
double RWHvel, LWHvel, BWHvel;

float Kspeed = 0.3;

bool  _isFirst_both_R = true;
bool  _isFirst_both_L = true;
float  Move_X = 0.;
float  Move_Y = 0.;
float  Move_R = 0.;
double VelX = 0.;
double VelY = 0.;
double VelT = 0.;
double VelX_before = 0.;
double VelY_before = 0.;
double VelT_before = 0.;
float  MotorSpeed[3] = {0.0, };

/* Joystick Move */
void MoveWheelVelocity();
void CalculateMovingEverage(void);
void ManualMoveRHand();
void ManualMoveLHand();
void ChangeManualMode();
void ManualMoveHand();
int FLAG_JOYStart = false;
int Mode_Manual = MANUAL_STOP;

RBJoystick          *joystick;
char GL_JOY_LT, GL_JOY_LB;
int  GL_JOY_LJOG_RL, GL_JOY_LJOG_UD;
int  GL_JOY_AROW_RL, GL_JOY_AROW_UD;
char GL_JOY_LJOG_PUSH;
char GL_JOY_RT, GL_JOY_RB;
int  GL_JOY_RJOG_RL, GL_JOY_RJOG_UD;
char GL_JOY_A, GL_JOY_B, GL_JOY_X, GL_JOY_Y;
char GL_JOY_RJOG_PUSH;
char GL_JOY_BACK, GL_JOY_START, GL_JOY_LOGITECH;

bool _isFirst = true;
bool RIGHT_isFirst = true;
bool LEFT_isFirst = false;
bool Joystick_flag = false;
void ResetJOY();
void CheckArguments(int argc, char *argv[]){
    int opt = 0;
    int podoNum = -1;
    while((opt = getopt(argc, argv, "g:p:")) != -1){
        switch(opt){
        case 'g':
            if(strcmp(optarg, "true")==0 || strcmp(optarg, "TRUE")==0){
                __IS_GAZEBO = true;
            }else if(strcmp(optarg, "false")==0 || strcmp(optarg, "FALSE")==0){
                __IS_GAZEBO = false;
            }else{
                FILE_LOG(logERROR) << optarg;
                FILE_LOG(logERROR) << "Invalid option for Gazebo";
                FILE_LOG(logERROR) << "Valid options are \"true\", \"TRUE\", \"false\", \"FALSE\"";
                FILE_LOG(logERROR) << "Use default value";
            }
            break;
        case 'p':
            podoNum = atoi(optarg);
            if(podoNum == 0){
                FILE_LOG(logERROR) << optarg;
                FILE_LOG(logERROR) << "Invalid option for AL";
                FILE_LOG(logERROR) << "Valid options are \"true\", \"TRUE\", \"false\", \"FALSE\"";
                FILE_LOG(logERROR) << "Use default value";
            }else{
                PODO_NO = podoNum;
            }
            break;
        case '?':
            if(optopt == 'g'){
                FILE_LOG(logERROR) << "Option for Gazebo";
                FILE_LOG(logERROR) << "Valid options are \"true\", \"TRUE\", \"false\", \"FALSE\"";
            }else if(optopt == 'p'){
                FILE_LOG(logERROR) << "Option for AL";
                FILE_LOG(logERROR) << "Valid options are \"Integer Values\"";
            }
        }
    }


    cout << endl;
    FILE_LOG(logERROR) << "===========AL Setting============";
    FILE_LOG(logWARNING) << argv[0];
    if(__IS_GAZEBO)     FILE_LOG(logWARNING) << "AL for Gazebo";
    else                FILE_LOG(logWARNING) << "AL for Robot";
    FILE_LOG(logWARNING) << "AL Number: " << PODO_NO;
    FILE_LOG(logERROR) << "=================================";
    cout << endl;
}


typedef struct{

    //GUI_DRILL_HOLD_OPEN
    double hold_Handx       =  0.393229;
    double hold_Handy       = -0.246403;
    double hold_Handz       =  0.298698;
    double hold_time        =  2.0;

    //GUI_DRILL_HOLD_GRASP
    double hold_grasp_Handx =  0.393229;
    double hold_grasp_Handy = -0.246403;
    double hold_grasp_Handz =  0.298698;
    double hold_grasp_time  =  2.0;

    //GUI_DRILL_WKRD
    double WKRD_Handx       =  0.293229;
    double WKRD_Handy       = -0.246403;
    double WKRD_Handz       =  0.248698;
    double WKRD_time        =  2.0;

    //GUI_DRILL_BRING
    double bring_Handx      =  0.293229;
    double bring_Handy      = -0.246403;
    double bring_Handz      =  0.248698;
    double bring_time       =  2.0;

    //GUI_DRILL_READY
    double ready_Handx      =  0.4;
    double ready_Handy      = -0.246403;
    double ready_Handz      = -0.1;
    double ready_time       =  2.0;

    //GUI_DRILL_APPROACH
    double approach_Handx   =  0.4;
    double approach_Handy   = -0.246403;
    double approach_Handz   = -0.1 - 0.02;
    double approach_time    =  2.0;

    //GUI_DRILL_DRILLING
    double drilling_Handx   =  0.4;
    double drilling_Handy   = -0.246403;
    double drilling_Handz   = -0.1 -0.1;
    double drilling_time    =  16.0;

    //GUI_DRILL_FINISH
    double finish_Handx     =  0.4;
    double finish_Handy     = -0.246403;
    double finish_Handz     = -0.1;
    double finish_time      =  5.0;

    //GUI_DRILL_LIFT
    double lift_Handx       =  0.293229;
    double lift_Handy       = -0.246403;
    double lift_Handz       =  0.248698;
    double lift_time        =  2.0;

    //GUI_DRILL_PUT
    double put_Handx        =  0.393229;
    double put_Handy        = -0.246403;
    double put_Handz        =  0.298698;
    double put_time         =  2.0;

}drill_motion;
drill_motion drill_in;

#endif

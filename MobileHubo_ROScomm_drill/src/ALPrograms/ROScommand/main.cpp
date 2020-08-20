/*
 *	This program is generated from drc-podoal-template.
 *
 *	This AL-Process will activated by "PODO_Daemon" with appropriate "AL-Number".
 *	The AL-Number is determined at Core_config.db file at Share folder.
 *	And the AL-Process needs this AL-Number as an input parameter.
 *	So trying to open the AL-Process without any input parameter will terminate the process.
 *
 *	Please check your PODO_AL_NAME and Core_Config.db file.
 *	Actually the PODO_AL_NAME is used for recognizing the certain process and making it unique.
 *	So the same name of file with different path is allowed if the PODO_AL_NAMEs are different.
 *	But we recommend you that gather all of your build file in one folder (check the Core_Config.db file).
 *
 *	You can change the period of real-time thread by changing "RT_TIMER_PERIOD_MS" as another value in "rt_task_set_periodic".
 *	Please do not change "RT_TIMER_PERIOD_MS" value in "typedef.h".
 *	You can also change the priority of the thread by changing 4th parameter of "rt_task_create".
 *	In this function you need to care about the name of thread (the name should be unique).
 *
 *	Please do not change the "RBInitialize" function and fore code of main().
 *	You may express your idea in while loop of main & real-time thread.
 *
 *	Each AL-Process has its own command structure in Shared Memory.
 *	So, it can have its own command set.
 *	Make sure that the command set of each AL-process start from over than 100.
 *	Under the 100 is reserved for common command set.
 *
 *	Now, you can do everything what you want..!!
 *	If you have any question about PODO, feel free to contact us.
 *	Thank you.
 *
 *
 *
 *	Jungho Lee		: jungho77@rainbow.re.kr
 *	Jeongsoo Lim	: yjs0497@kaist.ac.kr
 *	Okkee Sim		: sim2040@kaist.ac.kr
 *
 *	Copy Right 2014 @ Rainbow Co., HuboLab of KAIST
 *
 */

#include "MainHeader.h"
#define PODO_AL_NAME       "ROScommand"

using namespace std;
inline void pushData(doubles &tar, double var){
    tar.push_back(var);
    tar.pop_front();
}

pRBCORE_SHM_COMMAND     sharedCMD;
pRBCORE_SHM_REFERENCE   sharedREF;
pRBCORE_SHM_SENSOR      sharedSEN;
pUSER_SHM               userData;
pROS_SHM                sharedROS;

RT_TASK rtTaskCon;
RT_TASK rtFlagCon;
RT_TASK rtJoystickCon;

JointControlClass *joint;
TaskMotion        *WBmotion;

double  RHpos[3]  = {0.,};
double  LHpos[3]  = {0.,};
doubles RHori(4);
doubles LHori(4);
double  wait_time = 0.;

//r2p sharedROS->r2p;
void JoystickThread(void *){
    while(1){
        static unsigned int Joy_counter = 0;
        if(Joystick_flag == true){
            if(joystick->isConnected() == false){
                printf("JoyStick connection failure...!!!\n");
                Joystick_flag = false;
            } else
            {
                //printf("Joy connect\n");
            }

            // Button Data
            GL_JOY_X  = joystick->JoyButton[2];
            GL_JOY_A  = joystick->JoyButton[0];
            GL_JOY_B  = joystick->JoyButton[1];
            GL_JOY_Y  = joystick->JoyButton[3];
            GL_JOY_LB = joystick->JoyButton[4];
            GL_JOY_RB = joystick->JoyButton[5];
            GL_JOY_LT = joystick->JoyAxis[2];
            GL_JOY_RT = joystick->JoyAxis[5];

            if((int)(GL_JOY_LT) == -1){
                GL_JOY_LT = 1;
            }
            else{
                GL_JOY_LT = 0;
            }
            if((int)(GL_JOY_RT) == -1){
                GL_JOY_RT = 1;
            }
            else{
                GL_JOY_RT = 0;
            }

            GL_JOY_BACK = joystick->JoyButton[6];
            GL_JOY_START = joystick->JoyButton[7];
            GL_JOY_LOGITECH = joystick->JoyButton[8];
            GL_JOY_LJOG_PUSH = joystick->JoyButton[9];
            GL_JOY_RJOG_PUSH = joystick->JoyButton[10];

            // AXIS Data
            GL_JOY_LJOG_RL = -joystick->JoyAxis[0];
            if(GL_JOY_LJOG_RL > 30000) GL_JOY_LJOG_RL = 32767;
            else if(GL_JOY_LJOG_RL < -30000) GL_JOY_LJOG_RL = -32767;
            else if(GL_JOY_LJOG_RL > -3000 && GL_JOY_LJOG_RL < 3000) GL_JOY_LJOG_RL = 0;

            GL_JOY_LJOG_UD = -joystick->JoyAxis[1];
            if(GL_JOY_LJOG_UD > 30000) GL_JOY_LJOG_UD = 32767;
            else if(GL_JOY_LJOG_UD < -30000) GL_JOY_LJOG_UD = -32767;
            else if(GL_JOY_LJOG_UD > -3000 && GL_JOY_LJOG_UD < 3000) GL_JOY_LJOG_UD = 0;


            GL_JOY_RJOG_RL = -joystick->JoyAxis[3];
            if(GL_JOY_RJOG_RL > 30000) GL_JOY_RJOG_RL = 32767;
            else if(GL_JOY_RJOG_RL < -30000) GL_JOY_RJOG_RL = -32767;
            else if(GL_JOY_RJOG_RL > -3000 && GL_JOY_RJOG_RL < 3000) GL_JOY_RJOG_RL = 0;

            GL_JOY_RJOG_UD = -joystick->JoyAxis[4];
            if(GL_JOY_RJOG_UD > 30000) GL_JOY_RJOG_UD = 32767;
            else if(GL_JOY_RJOG_UD < -30000) GL_JOY_RJOG_UD = -32767;
            else if(GL_JOY_RJOG_UD > -3000 && GL_JOY_RJOG_UD < 3000) GL_JOY_RJOG_UD = 0;

            GL_JOY_AROW_RL = joystick->JoyAxis[6];
            GL_JOY_AROW_UD = -joystick->JoyAxis[7];


            if(Joy_counter == 30){
                if(GL_JOY_X==0 && GL_JOY_A==0 && GL_JOY_B==0 && GL_JOY_Y==0 && GL_JOY_LB==0 &&
                        GL_JOY_RB==0 && GL_JOY_LT==0 && GL_JOY_RT==0 && GL_JOY_BACK==0 &&
                        GL_JOY_START==0 && GL_JOY_LJOG_PUSH==0 && GL_JOY_RJOG_PUSH==0 &&
                        GL_JOY_LJOG_RL==0 && GL_JOY_LJOG_UD==0 && GL_JOY_RJOG_RL==0 &&
                        GL_JOY_RJOG_UD==0 && GL_JOY_AROW_RL==0 && GL_JOY_AROW_UD==0){
                }
                else{
                    cout<<"Manual mode not Ready!"<<endl;
                }
                Joy_counter = 0;
            }
        }
        else{
            GL_JOY_LT=0;
            GL_JOY_LB=0;
            GL_JOY_LJOG_RL=0;
            GL_JOY_LJOG_UD=0;
            GL_JOY_AROW_RL=0;
            GL_JOY_AROW_UD=0;
            GL_JOY_LJOG_PUSH=0;

            GL_JOY_RT=0;
            GL_JOY_RB=0;
            GL_JOY_RJOG_RL=0;
            GL_JOY_RJOG_UD=0;
            GL_JOY_A=0;
            GL_JOY_B=0;
            GL_JOY_X=0;
            GL_JOY_Y=0;
            GL_JOY_RJOG_PUSH=0;

            GL_JOY_BACK=0;
            GL_JOY_START=0;

            if(Joy_counter == 30){
                Joy_counter = 0;
            }
        }
        Joy_counter++;

        userData->joy.JOY_A = GL_JOY_A;
        userData->joy.JOY_B = GL_JOY_B;
        userData->joy.JOY_X = GL_JOY_X;
        userData->joy.JOY_Y = GL_JOY_Y;

        userData->joy.JOY_LB = GL_JOY_LB;
        userData->joy.JOY_RB = GL_JOY_RB;
        userData->joy.JOY_LT = GL_JOY_LT;
        userData->joy.JOY_RT = GL_JOY_RT;


        userData->joy.JOY_AROW_RL = GL_JOY_AROW_RL;
        userData->joy.JOY_AROW_UD = GL_JOY_AROW_UD;
        userData->joy.JOY_RJOG_UD = GL_JOY_RJOG_UD;
        userData->joy.JOY_LJOG_UD = GL_JOY_LJOG_UD;
        userData->joy.JOY_RJOG_RL = GL_JOY_RJOG_RL;
        userData->joy.JOY_LJOG_RL = GL_JOY_LJOG_RL;


        userData->joy.JOY_BACK = GL_JOY_BACK;
        userData->joy.JOY_START = GL_JOY_START;
        userData->joy.JOY_LJOG_PUSH = GL_JOY_LJOG_PUSH;
        userData->joy.JOY_RJOG_PUSH = GL_JOY_RJOG_PUSH;
        userData->joy.JOY_LOGITECH = GL_JOY_LOGITECH;
        usleep(20*1000);
    }
}

int main(int argc, char *argv[])
{
    // Termination signal ---------------------------------
    signal(SIGTERM, CatchSignals);   // "kill" from shell
    signal(SIGINT,  CatchSignals);    // Ctrl-c
    signal(SIGHUP,  CatchSignals);    // shell termination
    signal(SIGKILL, CatchSignals);
    signal(SIGSEGV, CatchSignals);

    // Block memory swapping ------------------------------
    mlockall(MCL_CURRENT|MCL_FUTURE);

    CheckArguments(argc, argv);
    if(PODO_NO == -1){
        FILE_LOG(logERROR) << "Please check the AL Number";
        FILE_LOG(logERROR) << "Terminate this AL..";
        return 0;
    }

    // Initialize RBCore -----------------------------------
    if( RBInitialize() == -1 )
        isTerminated = -1;

    sharedROS->state_arm = ROBOT_NOT_MOVE;
    sharedROS->state_base = BASE_NOT_MOVE;
    sharedROS->COMMAND.CMD_WHEEL = WHEEL_BREAK;
    usleep(500*1000);

    // WBIK Initialize--------------------------------------
    WBmotion = new TaskMotion(sharedREF, sharedSEN, sharedCMD, sharedROS, joint);

    // Joystick
    joystick = new RBJoystick();
    joystick->ConnectJoy();

    // User command cheking --------------------------------
    while(isTerminated == 0)
    {

        switch(sharedROS->COMMAND.CMD_JOINT)
        {
            case MODE_JOINT_PUBLISH:
            {
                if(FLAG_JointPublish == true)
                {
                    sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                    break;
                }
                sharedROS->state_arm = ROBOT_JOINT_PUBLISHED;
                FLAG_JointPublish = true;
                break;
            }
            case MODE_MOVE_JOINT:
            {
                printf("mainsen REB = %f\n",sharedSEN->ENCODER[MC_ID_CH_Pairs[REB].id][MC_ID_CH_Pairs[REB].ch].CurrentReference);

                if(FLAG_JointPublish == true)
                {
                    FILE_LOG(logERROR) << "Joint Publishing. Disregard command and reference";
                    for(int i=0;i<NUM_JOINTS;i++)
                        sharedROS->Arm_action.joint[i] = sharedROS->joint_before[i];
                    sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                    break;
                } else if(CheckRobotState_ARM()==false)
                {
                    sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                    break;
                }
                joint->RefreshToCurrentReference(ARMonly);
                usleep(20*1000);
                joint->SetAllMotionOwner();
                SetMoveJoint();
                sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                break;
            }
            case MODE_SET_WBIK:
            {
                if(CheckRobotState_ARM()==false)
                {
                    sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                    break;
                }
                sharedROS->state_arm = ROBOT_MOVING_WBIK;

                joint->RefreshToCurrentReference(ARMonly);
                StartWBIKmotion(0);
                usleep(20*1000);
                joint->SetAllMotionOwner();
                SetWBIK();
                sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                break;
            }
            case MODE_E_STOP:
            {
                FILE_LOG(logWARNING) << "ROS CMD :: E_STOP";
                WBmotion->StopAll();
                WB_FLAG = false;
                FLAG_JointPublish = false;

                for(int i=0;i<NO_OF_JOINTS;i++)
                {
                    joint->RefreshToCurrentReference();
                }
                sharedROS->state_arm = ROBOT_NOT_MOVE;
                sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                break;
            }
            case MODE_SAVE:
            {
                FILE_LOG(logSUCCESS) << "NEW COMMAND :: DATA SAVE11";
                fp = fopen("/home/yujin/Desktop/dataPODO.txt","w");
                for(int i=0;i<Save_Index;i++)
                {
                    for(int j=0;j<COL;j++)fprintf(fp,"%g\t", Save_Data[j][i]);
                    fprintf(fp,"\n");
                }
                fclose(fp);
                FILE_LOG(logSUCCESS) << "Data Save Complete";

                sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                break;
            }
            case MODE_TRAJECTORY:
            {
    //            printf("Mode_Trajectory come\n");
                static int FLAG = false;
                if(FLAG == false)
                {
                    if(sharedROS->DoneFlag == false)
                        break;

                    FLAG = true;
                    if(IsReadyTrajectory200Hz())
                    {
                        printf("It is ready trajectory\n");
                        if(FLAG_JointPublish == true)
                        {
                            sharedROS->state_arm = ROBOT_NOT_MOVE;
                            sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                            break;
                        }
                        FLAG = false;
                        printf("Ready and Start Trajectory Mode\n");
                        sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                        sharedROS->state_arm = ROBOT_JOINT_TRAJECTORY;
                        FLAG_JointPublish = true;
                        break;
                    }
                    else
                    {
                        printf("Error make trajectory\n");
                        FLAG = false;
                        sharedROS->DoneFlag = false;
                        sharedROS->state_arm = ROBOT_NOT_MOVE;
                        sharedROS->COMMAND.CMD_JOINT = MODE_BREAK;
                        break;
                    }
                }

                break;
            }
        }

        if(sharedROS->COMMAND.CMD_GRIPPER != GRIPPER_BREAK)
        {
            if(FLAG_Gripper != true)
            {
                joint->RefreshToCurrentReference(GRIPPERonly);
                usleep(50*1000);
                joint->SetAllMotionOwner();
                FLAG_Gripper = true;
                MODE_Gripper = sharedROS->COMMAND.CMD_GRIPPER;
                SIDE_Gripper = sharedROS->Gripper_action.side;
                if(SIDE_Gripper == GRIPPER_RIGHT)
                {
                    MODE_RGripper = MODE_Gripper;
                }else if(SIDE_Gripper == GRIPPER_LEFT)
                {
                    MODE_LGripper = MODE_Gripper;
                }else
                {
                    MODE_RGripper = MODE_Gripper;
                    MODE_LGripper = MODE_Gripper;
                }
                DESIRED_Gripper = sharedROS->Gripper_action.desired_mm;

                CalculateLIMITGripper();
                sharedROS->COMMAND.CMD_GRIPPER = GRIPPER_BREAK;
            }else
            {
                FILE_LOG(logERROR) << "Duplicate Gripper Commands";
                sharedROS->COMMAND.CMD_GRIPPER = GRIPPER_BREAK;
            }
        }

        switch(sharedROS->COMMAND.CMD_WHEEL)
        {
            case WHEEL_MOVE_STOP:
            {
                OMNImove.InitWheelInfo();
                sharedROS->COMMAND.CMD_WHEEL = WHEEL_BREAK;
                sharedROS->state_base = BASE_NOT_MOVE;
                break;
            }
            case WHEEL_MOVE_START:
            {
                if(CheckRobotState_BASE() == false)
                {
                    sharedROS->COMMAND.CMD_WHEEL = WHEEL_BREAK;
                    break;
                }
                sharedROS->state_base = BASE_MOVING;
                FILE_LOG(logSUCCESS) << "Start Wheel Move" << sharedROS->Base_action.wheel.MoveX ;
                joint->RefreshToCurrentReference(WHEELonly);
                usleep(20*1000);
                joint->SetAllMotionOwnerWHEEL();
                OMNImove.StartOMNImove(sharedROS->Base_action.wheel.MoveX,sharedROS->Base_action.wheel.MoveY,sharedROS->Base_action.wheel.ThetaDeg);
                sharedROS->COMMAND.CMD_WHEEL = WHEEL_BREAK;
                break;
            }
            case WHEEL_MOVE_VELOCITY:
            {
                if(sharedROS->state_base == BASE_VEL_MOVING)
                {
                    MoveWheelVelocity();
                    break;
                }
                else{
                    if(CheckRobotState_BASE() == false)
                    {
                        sharedROS->COMMAND.CMD_WHEEL = WHEEL_BREAK;
                        break;
                    }
                    sharedROS->state_base = BASE_VEL_MOVING;
                    sharedROS->Base_action.wheel.VelTheta = 0.;
                    sharedROS->Base_action.wheel.VelX = 0.;
                    sharedROS->Base_action.wheel.VelY = 0.;
                    OMNImove.InitWheelInfo();
                    joint->RefreshToCurrentReference(WHEELonly);
                    usleep(20*1000);
                    joint->SetAllMotionOwnerWHEEL();
                    MoveWheelVelocity();
                    break;
                }
            }
        }

        switch(sharedCMD->COMMAND[PODO_NO].USER_COMMAND)
        {
            case BASICCMD_HOMEPOS:
            {
                cout << ">>> COMMAND: WALKREADY_GO_HOMEPOS" << endl;

                joint->RefreshToCurrentReference();
                joint->SetAllMotionOwner();
                GotoHomePos();
                sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                break;
            }
            case BASICCMD_WALKREADY:
            {
//                cout << ">>> COMMAND: WALKREADY_GO_WALKREADYPOS" << endl;
                FILE_LOG(logSUCCESS) << ">>> WALKREADY_GO_WALKREADYPOS" ;

                sharedCMD->CommandAccept[PODO_NO] = true;

                usleep(500*1000);
                joint->RefreshToCurrentReference();
                joint->SetAllMotionOwner();
                GotoWalkReadyPos();
                usleep(4000*1000);
                sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                break;
            }
            case BASICCMD_GRIPPER:
            {
                if(FLAG_Gripper != true)
                {
                    joint->RefreshToCurrentReference(GRIPPERonly);
                    usleep(50*1000);
                    joint->SetAllMotionOwner();
                    FLAG_Gripper = true;
                    MODE_Gripper = sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0];
                    SIDE_Gripper = sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[1];
                    if(SIDE_Gripper == GRIPPER_RIGHT)
                    {
                        MODE_RGripper = MODE_Gripper;
                    }else if(SIDE_Gripper == GRIPPER_LEFT)
                    {
                        MODE_LGripper = MODE_Gripper;
                    }else
                    {
                        MODE_RGripper = MODE_Gripper;
                        MODE_LGripper = MODE_Gripper;
                    }
                    DESIRED_Gripper = sharedCMD->COMMAND[PODO_NO].USER_PARA_DOUBLE[0];

                    CalculateLIMITGripper();
                    sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                }else
                {
                    FILE_LOG(logERROR) << "Duplicate Gripper Commands";
                    sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                }
                break;
            }
            case BASICCMD_SAVE:
            {
                if(sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0] == 0)
                {
                    FILE_LOG(logSUCCESS) << "NEW COMMAND :: DATA RESET";
                    Save_Index = 0;
                    memset(&Save_Data,0,sizeof(double)*COL*ROW);
                }
                else
                {
                    FILE_LOG(logSUCCESS) << "NEW COMMAND :: DATA SAVE";
                    fp = fopen("/home/yujin/Desktop/dataPODO.txt","w");
                    for(int i=0;i<Save_Index;i++)
                    {
                        for(int j=0;j<COL;j++)fprintf(fp,"%g\t", Save_Data[j][i]);
                        fprintf(fp,"\n");
                    }
                    fclose(fp);
                    FILE_LOG(logSUCCESS) << "Data Save Complete";
                }
                sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                break;
            }
            case MANUALCMD_JOYON:
            {
                if(sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0] == JOY_ON)
                {
                    cout << ">>> COMMAND: JOYSTICK THREAD ON" << endl;
                    joint->RefreshToCurrentReference();
                    ResetJOY();
                    _isFirst = true;
    //                FLAG_JOYStart = true;
                    usleep(20*1000);
                    Joystick_flag = true;

                }else
                {
                    cout << ">>> COMMAND: JOYSTICK THREAD OFF" << endl;
                    Joystick_flag = false;
                }
                sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                break;
            }
            case MANUALCMD_JOYMOVE:
            {
                if(sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0] == JOY_START)
                {
                    cout << ">>> COMMAND: JOYSTICK MOVE START" << endl;
                    OMNImove.InitWheelInfo();
                    ResetJOY();
                    joint->RefreshToCurrentReference();
                    joint->SetAllMotionOwner();
                    StartWBIKmotion(0);
                    usleep(20*1000);
                    WB_FLAG = true;
                    Mode_Manual = MANUAL_WHEEL;
                    _isFirst = true;
                    FLAG_JOYStart = true;
                }
                else if(sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0] == JOY_STOP)
                {
                    cout << ">>> COMMAND: JOYSTICK MOVE STOP" << endl;
                    ResetJOY();
                    WB_FLAG = false;
                    FLAG_JOYStart = false;
                    Mode_Manual = MANUAL_STOP;
                }
                sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                break;
            }
            case BASICCMD_DRILL:
            {
//                FILE_LOG(logSUCCESS) << "BASICCMD_DRILL";

                sharedCMD->CommandAccept[PODO_NO] = true;
                WB_FLAG = false;

                joint->RefreshToCurrentReference();
                joint->SetAllMotionOwner();
                StartWBIKmotion(0);
//                StartWBIKmotion(-1);
                WBmotion->RefreshToCurrentReference();
                usleep(20*1000);
                WB_FLAG = true;

                Mode_TOOL = sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0];

                if(Mode_TOOL == DRILL_HOLD || Mode_TOOL == DRILL_DRILL || Mode_TOOL == DRILL_PUT)
                {
                    Mode_cont = Mode_TOOL;
                    Mode_TOOL += 1;
                }
                else
                    Mode_cont = false;

                sharedCMD->COMMAND[PODO_NO].USER_COMMAND = COMMAND_BREAK;
                break;
            }
        }
    }
    cout << ">>> Process ROScommand is terminated..!!" << endl;
    return 0;
}

/**********************************************************************************/
void RBTaskThread(void *)
{
    while(isTerminated == 0)
    {
        ROS_Joint_Publish();
        GripperTH();
        JOY_TH();
        OMNImove.OMNIThread();
        ToolTask_Supervisor();

        Write_Feedback();
        save();

        if(OMNImove.IsMovingWheel())
        {
            joint->SetMoveJoint(LWH, OMNImove.LWHinfo.Reference, OMNImove.OMNIinfo.TickSec*1000, MOVE_ABSOLUTE);
            joint->SetMoveJoint(RWH, OMNImove.RWHinfo.Reference, OMNImove.OMNIinfo.TickSec*1000, MOVE_ABSOLUTE);
            joint->SetMoveJoint(BWH, OMNImove.BWHinfo.Reference, OMNImove.OMNIinfo.TickSec*1000, MOVE_ABSOLUTE);
        }

        if(WB_FLAG == true)
        {
            // Global whole body model
            WBmotion->updateAll();
            WBmotion->WBIK_UB();

            if(WBmotion->isDoneMove() == true)
            {
                sharedROS->state_arm = ROBOT_NOT_MOVE;
            }

            for(int i=RHY; i<=LAR; i++)
            {
                if(i!=BWH)
                    joint->SetJointRefAngle(i, WBmotion->Q_filt_34x1[idRHY+i-RHY]*R2D);
            }

            joint->SetJointRefAngle(WST, WBmotion->Q_filt_34x1[idWST]*R2D);

            joint->SetJointRefAngle(RSP,  WBmotion->Q_filt_34x1[idRSP]*R2D);
            joint->SetJointRefAngle(RSR,  WBmotion->Q_filt_34x1[idRSR]*R2D - OFFSET_RSR);
            joint->SetJointRefAngle(RSY,  WBmotion->Q_filt_34x1[idRSY]*R2D);
            joint->SetJointRefAngle(REB,  WBmotion->Q_filt_34x1[idREB]*R2D - OFFSET_ELB);
            joint->SetJointRefAngle(RWY,  WBmotion->Q_filt_34x1[idRWY]*R2D);
            joint->SetJointRefAngle(RWP,  WBmotion->Q_filt_34x1[idRWP]*R2D);
            joint->SetJointRefAngle(RWY2, WBmotion->Q_filt_34x1[idRWY2]*R2D);

            joint->SetJointRefAngle(LSP,  WBmotion->Q_filt_34x1[idLSP]*R2D);
            joint->SetJointRefAngle(LSR,  WBmotion->Q_filt_34x1[idLSR]*R2D - OFFSET_LSR);
            joint->SetJointRefAngle(LSY,  WBmotion->Q_filt_34x1[idLSY]*R2D);
            joint->SetJointRefAngle(LEB,  WBmotion->Q_filt_34x1[idLEB]*R2D - OFFSET_ELB);
            joint->SetJointRefAngle(LWY,  WBmotion->Q_filt_34x1[idLWY]*R2D);
            joint->SetJointRefAngle(LWP,  WBmotion->Q_filt_34x1[idLWP]*R2D);
            joint->SetJointRefAngle(LWY2, WBmotion->Q_filt_34x1[idLWY2]*R2D);

            if(!CheckMotionOwned())
                WB_FLAG = false;
        }

        joint->MoveAllJoint();

        if(sharedROS->state_arm == ROBOT_MOVING_JOINT && joint->IsMovingAnyJoint() == ENABLE)
        {
            printf("move done\n");
            sharedROS->state_arm = ROBOT_NOT_MOVE;
        }
        rt_task_suspend(&rtTaskCon);
    }
}

void RBFlagThread(void *)
{
    rt_task_set_periodic(NULL, TM_NOW, 300*1000);        // 300 usec

    while(isTerminated == 0)
    {
        rt_task_wait_period(NULL);

//        if(HasAnyOwnership())
        {
            if(sharedCMD->SYNC_SIGNAL[PODO_NO] == true){
                joint->JointUpdate();
                rt_task_resume(&rtTaskCon);
            }
        }
    }
}

void JOY_TH()
{
    //ReadJoy();
    switch(Mode_Manual)
    {
        case MANUAL_STOP:
        {
            break;
        }
        case MANUAL_WHEEL:
        {
            if(FLAG_JOYStart == true)
            {
                if(GL_JOY_RJOG_RL == 0 && GL_JOY_LJOG_RL == 0 && GL_JOY_LJOG_UD == 0)
                {
                    FLAG_JOYStart = false;
                    printf("OK JOY is zero now\n");
                }
                else
                {
                    printf("JOY Not Zero!!! %d, %d, %d\n",GL_JOY_RJOG_RL, GL_JOY_LJOG_RL, GL_JOY_LJOG_UD);
                }

            } else
            {
                if(fabs(GL_JOY_RJOG_RL) >35000) GL_JOY_RJOG_RL = 0;
                if(fabs(GL_JOY_LJOG_RL) >35000) GL_JOY_LJOG_RL = 0;
                if(fabs(GL_JOY_LJOG_UD) >35000) GL_JOY_LJOG_UD = 0;

                static int tempcnt = 0;
                if(GL_JOY_LJOG_RL == 0 && GL_JOY_LJOG_UD == 0 && GL_JOY_RJOG_RL == 0 && tempcnt > 20){
                    tempcnt++;
                    pushData(RWHList, 0.0);
                    pushData(LWHList, 0.0);
                    pushData(BWHList, 0.0);
                } else
                {
                    Kspeed = 2.5;
                    tempcnt = 0;
                    Move_X = ((float)GL_JOY_LJOG_UD/-32767.f)*Kspeed;
                    Move_Y = ((float)GL_JOY_LJOG_RL/32767.f)*Kspeed;
                    Move_R = ((float)GL_JOY_RJOG_RL/32767.f)*Kspeed*0.8;


                    MotorSpeed[0] = (0.866)*Move_X - (-0.5)*Move_Y + Move_R;
                    MotorSpeed[1] = (-0.866)*Move_X - (-0.5)*Move_Y + Move_R;
                    MotorSpeed[2] = -Move_Y + Move_R;

                    pushData(LWHList, MotorSpeed[0]);
                    pushData(RWHList, MotorSpeed[1]);
                    pushData(BWHList, MotorSpeed[2]);
                    if(Move_X != 0 || Move_Y != 0 || Move_R != 0)
                    {
                        printf("X = %f, Y = %f, Move_R = %f\n",Move_X, Move_Y, Move_R);
                    }
                }
                CalculateMovingEverage();

                OMNImove.RWHinfo.MoveDistance_m += OMNImove.RWHinfo.WheelVel_ms;
                OMNImove.LWHinfo.MoveDistance_m += OMNImove.LWHinfo.WheelVel_ms;
                OMNImove.BWHinfo.MoveDistance_m += OMNImove.BWHinfo.WheelVel_ms;

                printf("Init = %f\n",OMNImove.RWHinfo.InitRef_Deg);
                joint->SetMoveJoint(RWH, OMNImove.RWHinfo.InitRef_Deg + OMNImove.RWHinfo.MoveDistance_m, 5, MOVE_ABSOLUTE);
                joint->SetMoveJoint(BWH, OMNImove.BWHinfo.InitRef_Deg + OMNImove.BWHinfo.MoveDistance_m, 5, MOVE_ABSOLUTE);
                joint->SetMoveJoint(LWH, OMNImove.LWHinfo.InitRef_Deg + OMNImove.LWHinfo.MoveDistance_m, 5, MOVE_ABSOLUTE);
            }
            break;
        }
        case MANUAL_RHAND:
        {
            ManualMoveHand();
            break;
        }
        case MANUAL_LHAND:
        {
            ManualMoveHand();
            break;
        }
        case MANUAL_TWOHAND:
        {
            ManualMoveRHand();
            ManualMoveLHand();
            break;
        }
    }
    ChangeManualMode();
}


//*******************************************************************
void ToolTask_Supervisor()
{
    switch(Mode_TOOL)
    {
        case DRILL_WAIT:
        {
            WaitCount++;

            if(WaitCount > WaitTime*200)
            {
                switch(WaitMode)
                {
                    case DRILL_HOLD_APPROACH:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_HOLD_APPROACH OK";
                        Mode_TOOL = DRILL_HOLD_GRASP;
                        break;
                    }
                    case DRILL_HOLD_GRASP:
                    {
                        FILE_LOG(logSUCCESS) << "GUI_DRILL_HOLD_GRASP OK";
                        Mode_TOOL = DRILL_HOLD_GRASP_CLOSE;
                        break;
                    }
                    case DRILL_HOLD_GRASP_CLOSE:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_HOLD_GRASP_CLOSE OK";
                        Mode_TOOL = DRILL_HOLD_BRING;
                        break;
                    }
                    case DRILL_DRILL_READY:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_DRILL_READY OK";
                        Mode_TOOL = DRILL_DRILL_APPROACH;
                        break;
                    }
                    case DRILL_DRILL_APPROACH:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_DRILL_APPROACH OK";
                        Mode_TOOL = DRILL_DRILL_DOWN;
                        break;
                    }
                    case DRILL_DRILL_DOWN:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_DRILL_DOWN OK";
                        Mode_TOOL = DRILL_DRILL_UP;
                        break;
                    }
                    case DRILL_PUT_LIFT:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_PUT_LIFT OK";
                        Mode_TOOL = DRILL_PUT_PUT;
                        break;
                    }
                    case DRILL_PUT_PUT:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_PUT_PUT OK";
                        Mode_TOOL = DRILL_PUT_PUT_OPEN;
                        break;
                    }
                    case DRILL_PUT_PUT_OPEN:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_PUT_PUT_OPEN OK";
                        Mode_TOOL = DRILL_PUT_PRE_WKRD;
                        break;
                    }
                    case DRILL_PUT_PRE_WKRD:
                    {
                        FILE_LOG(logSUCCESS) << "DRILL_PUT_PRE_WKRD OK";
                        Mode_TOOL = DRILL_PUT_WKRD;
                        break;
                    }
                }
                WaitCount = 0;
            }
            break;
        }
        case DRILL_HOLD_APPROACH:
        {
            FILE_LOG(logSUCCESS) << "HOLD_OPEN";

            RHpos[0] = drill_in.hold_Handx;// 0.393229;
            RHpos[1] = drill_in.hold_Handy;//-0.246403;
            RHpos[2] = drill_in.hold_Handz;// 0.298698;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.hold_time);

            SetOriHand_YP(RHori,-90.0,-90.0);
            WBmotion->addRHOriInfo(RHori, drill_in.hold_time);

            //GRIPPER OPEN
            if(FLAG_Gripper != true)
            {
                //joint->RefreshToCurrentReference(GRIPPERonly);
                //usleep(50*1000);
                FLAG_Gripper = true;
                MODE_Gripper = GUI_GRIPPER_OPEN;
                SIDE_Gripper = GUI_GRIPPER_RIGHT;

                MODE_RGripper = GUI_GRIPPER_OPEN;

                DESIRED_Gripper = 0.;

                CalculateLIMITGripper();
            }

            if(Mode_cont == DRILL_HOLD)
                SetWaitTime(DRILL_HOLD_APPROACH, drill_in.hold_time);
            else
                Mode_TOOL = DRILL_NOTHING;

            break;
        }
        case DRILL_HOLD_GRASP:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_HOLD_GRASP";

            RHpos[0] = drill_in.hold_Handx + 0.1;
            RHpos[1] = drill_in.hold_Handy;
            RHpos[2] = drill_in.hold_Handz;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.hold_grasp_time);

            SetWaitTime(DRILL_HOLD_GRASP, drill_in.hold_grasp_time);
//            Mode_TOOL = DRILL_NOTHING;
            break;
        }
        case DRILL_HOLD_GRASP_CLOSE:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_HOLD_GRASP";

            //GRIPPER CLOSE
            if(FLAG_Gripper != true)
            {
                FLAG_Gripper = true;
                MODE_Gripper = GUI_GRIPPER_CLOSE;
                SIDE_Gripper = GUI_GRIPPER_RIGHT;

                MODE_RGripper = GUI_GRIPPER_CLOSE;

                DESIRED_Gripper = 0.;

                CalculateLIMITGripper();
            }


            if(Mode_cont == DRILL_HOLD)
                SetWaitTime(DRILL_HOLD_GRASP_CLOSE, 3.0);
            else
                Mode_TOOL = DRILL_NOTHING;

            break;
        }
        case DRILL_HOLD_BRING:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_BRING";

            RHpos[0] = drill_in.bring_Handx;
            RHpos[1] = drill_in.bring_Handy;
            RHpos[2] = drill_in.bring_Handz;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.bring_time);

            Mode_TOOL = DRILL_NOTHING;
            break;
        }
        case DRILL_DRILL_READY:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_READY";

            RHpos[0] = drill_in.ready_Handx;
            RHpos[1] = drill_in.ready_Handy;
            RHpos[2] = drill_in.ready_Handz;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.ready_time);

            SetOriHand_YP(RHori,0.0,-90.0);
            WBmotion->addRHOriInfo(RHori, drill_in.ready_time);

            if(Mode_cont == DRILL_DRILL)
                SetWaitTime(DRILL_DRILL_READY, drill_in.ready_time);
            else
                Mode_TOOL = DRILL_NOTHING;
            break;
        }
        case DRILL_DRILL_APPROACH:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_APPROACH";

            RHpos[0] = drill_in.approach_Handx;
            RHpos[1] = drill_in.approach_Handy;
            RHpos[2] = drill_in.approach_Handz;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.approach_time);

            if(Mode_cont == DRILL_DRILL)
                SetWaitTime(DRILL_DRILL_APPROACH, drill_in.approach_time);
            else
                Mode_TOOL = DRILL_NOTHING;

            break;
        }
        case DRILL_DRILL_DOWN:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_DRILLING";

            RHpos[0] = drill_in.drilling_Handx;
            RHpos[1] = drill_in.drilling_Handy;
            RHpos[2] = drill_in.drilling_Handz;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.drilling_time);

            if(Mode_cont == DRILL_DRILL)
                SetWaitTime(DRILL_DRILL_DOWN, drill_in.drilling_time);
            else
                Mode_TOOL = DRILL_NOTHING;

            break;
        }
        case DRILL_DRILL_UP:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_FINISH";

            RHpos[0] = drill_in.finish_Handx;  // 0.4;
            RHpos[1] = drill_in.finish_Handy;  //-0.246403;
            RHpos[2] = drill_in.finish_Handz;  //-0.1;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.finish_time);

            Mode_TOOL = DRILL_NOTHING;
            break;
        }        
        case DRILL_PUT_LIFT:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_LIFT";

            RHpos[0] = drill_in.lift_Handx;    // 0.293229;
            RHpos[1] = drill_in.lift_Handy;    //-0.246403;
            RHpos[2] = drill_in.lift_Handz;    // 0.248698;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.lift_time);

            SetOriHand_YP(RHori,-90.0,-90.0);
            WBmotion->addRHOriInfo(RHori, drill_in.lift_time);

            if(Mode_cont == DRILL_PUT)
                SetWaitTime(DRILL_PUT_LIFT, drill_in.lift_time);
            else
                Mode_TOOL = DRILL_NOTHING;

            break;
        }
        case DRILL_PUT_PUT:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_PUT";

            RHpos[0] = drill_in.put_Handx;// 0.393229; //WBmotion->pRH_3x1[0] + 0.1;    //drill_in.lift_Handx + 0.1;   //drill_in.put_Handx;  // 0.393229;
            RHpos[1] = drill_in.put_Handy;//-0.246403; //WBmotion->pRH_3x1[1];          //drill_in.lift_Handy;         //drill_in.put_Handy;  //-0.246403;
            RHpos[2] = drill_in.put_Handz;// 0.298698; //WBmotion->pRH_3x1[2] + 0.05;   //drill_in.lift_Handz + 0.05;  //drill_in.put_Handz;  // 0.298698;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.put_time);

//            Mode_TOOL = DRILL_NOTHING;
            SetWaitTime(DRILL_PUT_PUT, drill_in.put_time);
            break;
        }
        case DRILL_PUT_PUT_OPEN:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_PUT_OPEN";

            //GRIPPER OPEN
            if(FLAG_Gripper != true)
            {
                //joint->RefreshToCurrentReference(GRIPPERonly);
                //usleep(50*1000);
                FLAG_Gripper = true;
                MODE_Gripper = GUI_GRIPPER_OPEN;
                SIDE_Gripper = GUI_GRIPPER_RIGHT;

                MODE_RGripper = GUI_GRIPPER_OPEN;

                DESIRED_Gripper = 0.;

                CalculateLIMITGripper();
            }

            if(Mode_cont == DRILL_PUT)
                SetWaitTime(DRILL_PUT_PUT_OPEN, 3.0);
            else
                Mode_TOOL = DRILL_NOTHING;

            break;
        }
        case DRILL_PUT_PRE_WKRD:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_WKRD";

            RHpos[0] = drill_in.put_Handx - 0.15;
            RHpos[1] = drill_in.put_Handy;
            RHpos[2] = drill_in.put_Handz;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.WKRD_time);

            WBmotion->addRHOriInfo(RHori, drill_in.WKRD_time);

            SetWaitTime(DRILL_PUT_PRE_WKRD,drill_in.WKRD_time);
//            Mode_TOOL = DRILL_NOTHING;
            break;
        }
        case DRILL_PUT_WKRD:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_WKRD";

            RHpos[0] =  drill_in.WKRD_Handx;
            RHpos[1] =  drill_in.WKRD_Handy;
            RHpos[2] =  drill_in.WKRD_Handz;

            WBmotion->addRHPosInfo(RHpos[0], RHpos[1], RHpos[2], drill_in.WKRD_time);

            SetOriHand_YP(RHori, -90.0, 0.0);
            WBmotion->addRHOriInfo(RHori, drill_in.WKRD_time);

            //GRIPPER CLOSE
            if(FLAG_Gripper != true)
            {
                FLAG_Gripper  = true;
                MODE_Gripper  = GUI_GRIPPER_CLOSE;
                SIDE_Gripper  = GUI_GRIPPER_RIGHT;
                MODE_RGripper = GUI_GRIPPER_CLOSE;

                DESIRED_Gripper = 0.;

                CalculateLIMITGripper();
            }

            Mode_TOOL = DRILL_NOTHING;
            break;
        }
        case DRILL_STOP:
        {
            FILE_LOG(logSUCCESS) << "GUI_DRILL_STOP";

            Mode_TOOL = DRILL_NOTHING;
            break;
        }
        case DRILL_GETCOM:
        {
            FILE_LOG(logSUCCESS) << "GUI_GETCOM";


            cout << "pRH_3x1[0] = " << WBmotion->pRH_3x1[0] << endl;
            cout << "pRH_3x1[1] = " << WBmotion->pRH_3x1[1] << endl;
            cout << "pRH_3x1[2] = " << WBmotion->pRH_3x1[2] << endl;

            cout << "COM   (x,y)   = (" << WBmotion->pCOM_2x1[0] << ", "
                                        << WBmotion->pCOM_2x1[1] << ") " << endl;
            cout << "RHand (x,y,z) = (" << WBmotion->pRH_3x1[0]  << ", "
                                        << WBmotion->pRH_3x1[1]  << ", "
                                        << WBmotion->pRH_3x1[2]  << ") " << endl;

            Mode_TOOL = DRILL_NOTHING;
            break;
        }
        case DRILL_NOTHING:
        {
            Mode_TOOL = DRILL_NOTHING;
            break;
        }
    }
}



//*******************************************************************
void CalculateMovingEverage(void)
{
    double temp1 = 0.0;
    double temp2 = 0.0;
    double temp3 = 0.0;
    for(int i=0; i<120; i++){
        temp1 += RWHList[i];
        temp2 += LWHList[i];
        temp3 += BWHList[i];
    }
    OMNImove.RWHinfo.WheelVel_ms = temp1/120.0;
    OMNImove.LWHinfo.WheelVel_ms = temp2/120.0;
    OMNImove.BWHinfo.WheelVel_ms = temp3/120.0;
}

void MoveWheelVelocity()
{
//    printf("x = %f, y = %f, t = %f\n",sharedROS->Base_action.wheel.VelX,sharedROS->Base_action.wheel.VelY,sharedROS->Base_action.wheel.VelTheta);
    VelX = VelX_before*0.2 + 0.8*sharedROS->Base_action.wheel.VelX;
    VelY = VelY_before*0.2 + 0.8*sharedROS->Base_action.wheel.VelY;
    VelT = VelT_before*0.2 + 0.8*sharedROS->Base_action.wheel.VelTheta;

    if(fabs(VelX) >1.) VelX = 0.;
    if(fabs(VelY) >1.) VelY = 0.;
    if(fabs(VelT) >1.) VelT = 0.;

    if(VelX == 0. && VelY == 0. && VelT == 0.){
        pushData(RWHList, 0.0);
        pushData(LWHList, 0.0);
        pushData(BWHList, 0.0);
    } else
    {
        Kspeed = 0.015;
        Move_X = -((float)VelX)*Kspeed;
        Move_Y = ((float)VelY)*Kspeed;
        Move_R = -((float)VelT)*Kspeed*0.8;

        MotorSpeed[0] = (0.866)*Move_X - (-0.5)*Move_Y + Move_R;
        MotorSpeed[1] = (-0.866)*Move_X - (-0.5)*Move_Y + Move_R;
        MotorSpeed[2] = -Move_Y + Move_R;

        pushData(LWHList, MotorSpeed[0]);
        pushData(RWHList, MotorSpeed[1]);
        pushData(BWHList, MotorSpeed[2]);
        if(Move_X != 0 || Move_Y != 0 || Move_R != 0)
        {
//            printf("X = %f, Y = %f, Move_R = %f\n",Move_X, Move_Y, Move_R);
        }
    }
    CalculateMovingEverage();

    OMNImove.RWHinfo.MoveDistance_m += OMNImove.RWHinfo.WheelVel_ms;
    OMNImove.LWHinfo.MoveDistance_m += OMNImove.LWHinfo.WheelVel_ms;
    OMNImove.BWHinfo.MoveDistance_m += OMNImove.BWHinfo.WheelVel_ms;

    joint->SetMoveJoint(RWH, OMNImove.RWHinfo.InitRef_Deg + OMNImove.RWHinfo.MoveDistance_m, 5, MOVE_ABSOLUTE);
    joint->SetMoveJoint(BWH, OMNImove.BWHinfo.InitRef_Deg + OMNImove.BWHinfo.MoveDistance_m, 5, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LWH, OMNImove.LWHinfo.InitRef_Deg + OMNImove.LWHinfo.MoveDistance_m, 5, MOVE_ABSOLUTE);

    VelX_before = VelX;
    VelY_before = VelY;
    VelT_before = VelT;
}

void ChangeManualMode()
{
    static unsigned int cnt_WHEEL_to_HAND = 0;
    static unsigned int cnt_RHAND = 0;
    static unsigned int cnt_LHAND = 0;
    static unsigned int cnt_TWOHAND = 0;
    static int FLAG_MODE_CHANGED = 0;

    if(GL_JOY_LOGITECH == 1 )
    {
        cnt_WHEEL_to_HAND++;

        if(cnt_WHEEL_to_HAND > 50 && Mode_Manual == MANUAL_WHEEL&& FLAG_MODE_CHANGED == 0)
        {
            FILE_LOG(logINFO) << "CHANGE MANUAL MODE:: RHAND";
            Mode_Manual = MANUAL_RHAND;
            _isFirst = true;
            RIGHT_isFirst = true;
            LEFT_isFirst = false;
            FLAG_MODE_CHANGED = 1;
        }

        if(cnt_WHEEL_to_HAND > 50 && (Mode_Manual != MANUAL_WHEEL && Mode_Manual != MANUAL_STOP)&& FLAG_MODE_CHANGED == 0)
        {
            FILE_LOG(logINFO) << "CHANGE MANUAL MODE:: WHEEL";
            Mode_Manual = MANUAL_WHEEL;
            FLAG_MODE_CHANGED = 1;
        }
    }else if((Mode_Manual == MANUAL_RHAND || Mode_Manual == MANUAL_TWOHAND)&& GL_JOY_BACK == 1 && GL_JOY_START == 0)
    {
        cnt_LHAND++;

        if(cnt_LHAND > 50&& FLAG_MODE_CHANGED == 0)
        {
            FILE_LOG(logINFO) << "CHANGE MANUAL MODE:: LHAND";
            Mode_Manual = MANUAL_LHAND;
            _isFirst = true;
            RIGHT_isFirst = false;
            LEFT_isFirst = true;
            FLAG_MODE_CHANGED = 1;
        }
    }else if((Mode_Manual == MANUAL_LHAND || Mode_Manual == MANUAL_TWOHAND) && GL_JOY_BACK == 0 && GL_JOY_START == 1)
    {
        cnt_RHAND++;

        if(cnt_RHAND > 50&& FLAG_MODE_CHANGED == 0)
        {
            FILE_LOG(logINFO) << "CHANGE MANUAL MODE:: RHAND";
            Mode_Manual = MANUAL_RHAND;
            _isFirst = true;
            RIGHT_isFirst = true;
            LEFT_isFirst = false;
            FLAG_MODE_CHANGED = 1;
        }
    }else if((Mode_Manual == MANUAL_RHAND || Mode_Manual == MANUAL_LHAND) && GL_JOY_BACK == 1 && GL_JOY_START == 1)
    {
        cnt_TWOHAND++;

        if(cnt_TWOHAND > 50&& FLAG_MODE_CHANGED == 0)
        {
            FILE_LOG(logINFO) << "CHANGE MANUAL MODE:: TWOHAND";
            Mode_Manual = MANUAL_TWOHAND;
            _isFirst_both_L = true;
            _isFirst_both_R = true;
            FLAG_MODE_CHANGED = 1;
        }
    }else
    {
        cnt_WHEEL_to_HAND = 0;
        cnt_RHAND = 0;
        cnt_LHAND = 0;
        cnt_TWOHAND = 0;
        FLAG_MODE_CHANGED = 0;
    }
}

void ManualMoveHand()
{
    // Variables
    static int counter = 0;
    double pVel[3] = {0,0,0};
//    static double RH_SpeedUP_V0[6] = {0,0,0};
    static double SpeedDW_V0[8] = {0,0,0,0,0,0,0,0};
    static int SpeedUp_time[8] = {0,0,0,0,0,0,0,0};
    static int SlowDown_time[8] = {0,0,0,0,0,0,0,0};
    static int plus_Dcc_time[8] = {0,0,0,0,0,0,0,0};
    static int minus_Dcc_time[8] = {0,0,0,0,0,0,0,0};
    double Acc = 0.5;
    double Dcc = 0.5;
    double MaxVel = 0.07;
    static bool MoveFlag[8] = {false,false,false,false,false,false,false,false};
 //   double ShoulderToHand;
    double ShoulderToWrist;
    static bool Manual_OK = true;
    static double manual_pos[3];
    static double manual_pos_before[3];
    double Accq = 0.05;
    double Dccq = 0.02;
    double MaxVel_ang = 0.006;
    double AngSpeed[8];
    static double RELB;
    static double RELB_before;
    static double WST_ang;
    static double WST_ang_before;
    int Grasping_value = 0;
    static int GL_JOY_A_before;
    static int GL_JOY_AROW_RL_before;
    static int GL_JOY_AROW_UD_before;
    static int GL_JOY_B_before;
    static int GL_JOY_LB_before;
    static int GL_JOY_LJOG_RL_before;
    static int GL_JOY_LJOG_UD_before;
    static int GL_JOY_LT_before;
    static int GL_JOY_RB_before;
    static int GL_JOY_RJOG_RL_before;
    static int GL_JOY_RJOG_UD_before;
    static int GL_JOY_RT_before;
    static int GL_JOY_X_before;
    static int GL_JOY_Y_before;
//    static bool Release_Flag = false;
    static unsigned int same_counter = 0;
    static quat manual_quat;
    static quat manual_quat_before;
    quat qVel;

    if(RIGHT_isFirst == true){
        for(int i=0 ;i<3 ; i++){
            manual_pos[i] = WBmotion->pRH_3x1[i];
            manual_pos_before[i] = WBmotion->pRH_3x1[i];
        }
        manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
        manual_quat_before = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);

        RELB = WBmotion->RElb_ang*R2D;
        RELB_before = WBmotion->RElb_ang*R2D;

        WST_ang = joint->GetJointRefAngle(WST);
        WST_ang_before = joint->GetJointRefAngle(WST);
        RIGHT_isFirst = false;
        cout<<"RIGHT HAND is Activated !!"<<endl;
    }

    else if(LEFT_isFirst == true){
        for(int i=0 ;i<3 ; i++){
            manual_pos[i] = WBmotion->pLH_3x1[i];
            manual_pos_before[i] = WBmotion->pLH_3x1[i];
        }
        manual_quat = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);
        manual_quat_before = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);

        RELB = WBmotion->LElb_ang*R2D;
        RELB_before = WBmotion->LElb_ang*R2D;
        WST_ang = joint->GetJointRefAngle(WST);
        WST_ang_before = joint->GetJointRefAngle(WST);
        LEFT_isFirst = false;
        cout<<"LEFT HAND is Activated !!"<<endl;

    }
    if(_isFirst == true){
        for(int i=0;i<9;i++){
            SpeedDW_V0[i] = 0;
            SpeedUp_time[i] = 0;
            SlowDown_time[i] = 0;
            plus_Dcc_time[i] = 0;
            minus_Dcc_time[i] = 0;
            MoveFlag[i] = false;
        }

        RIGHT_isFirst = false;
        LEFT_isFirst = false;
        GL_JOY_A_before = 0;
        GL_JOY_AROW_RL_before = 0;
        GL_JOY_AROW_UD_before = 0;
        GL_JOY_B_before = 0;
        GL_JOY_LB_before = 0;
        GL_JOY_LJOG_RL_before = 0;
        GL_JOY_LJOG_UD_before = 0;
        GL_JOY_LT_before = 0;
        GL_JOY_RB_before = 0;
        GL_JOY_RJOG_RL_before = 0;
        GL_JOY_RJOG_UD_before = 0;
        GL_JOY_RT_before = 0;
        GL_JOY_X_before = 0;
        GL_JOY_Y_before = 0;


        if(Mode_Manual == MANUAL_RHAND){
            for(int i=0 ;i<3 ; i++){
                manual_pos[i] = WBmotion->pRH_3x1[i];
                manual_pos_before[i] = WBmotion->pRH_3x1[i];
            }
            manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
            manual_quat_before = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);

            RELB = WBmotion->RElb_ang*R2D;
            RELB_before = WBmotion->RElb_ang*R2D;

            WST_ang = joint->GetJointRefAngle(WST);
            WST_ang_before = joint->GetJointRefAngle(WST);
        }
        else{
            for(int i=0 ;i<3 ; i++){
                manual_pos[i] = WBmotion->pLH_3x1[i];
                manual_pos_before[i] = WBmotion->pLH_3x1[i];
            }
            manual_quat = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);
            manual_quat_before = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);

            RELB = WBmotion->LElb_ang*R2D;
            RELB_before =  WBmotion->LElb_ang*R2D;

            WST_ang = joint->GetJointRefAngle(WST);
            WST_ang_before = joint->GetJointRefAngle(WST);
        }
        _isFirst = false;
    }




    if(Mode_Manual == MANUAL_RHAND){
        manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
    }
    else{
        manual_quat = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);
    }



    // Generate Position Trajectory
    for(int i=0;i<3;i++){
        if(MoveFlag[i] == true){
            SpeedUp_time[i]++;
            pVel[i] = Acc*SpeedUp_time[i]*0.005;
            if(pVel[i] >= MaxVel) pVel[i] = MaxVel;
            SlowDown_time[i] = 0;
            SpeedDW_V0[i] = pVel[i];
        }
        else{
            SlowDown_time[i]++;
            pVel[i] = SpeedDW_V0[i] - Dcc*SlowDown_time[i]*0.005;
            if(pVel[i] <= 0) pVel[i] = 0;
            SpeedUp_time[i] = 0;
//            RH_SpeedUP_V0[i] = pVel[i];
        }
    }

    // Generatie Angualr speed Trajectory
    for(int i=3 ; i<8 ; i++){
        if(MoveFlag[i] == true){
            SpeedUp_time[i]++;
            AngSpeed[i] = Accq*SpeedUp_time[i]*0.005;
            if(AngSpeed[i] >= MaxVel_ang) AngSpeed[i] = MaxVel_ang;
            SlowDown_time[i] = 0;
            SpeedDW_V0[i] = AngSpeed[i];
        }
        else{
            SlowDown_time[i]++;
            AngSpeed[i] = SpeedDW_V0[i] - Dccq*SlowDown_time[i]*0.005;
            if(AngSpeed[i] <= 0) AngSpeed[i] = 0;
            SpeedUp_time[i] = 0;
 //         RH_SpeedUP_V0[i] = AngSpeed[i];
        }
    }



    counter++;

 //   if(counter%100 == 0)
 //       cout<<"Joy Value: "<<sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[1]<<" time: "<<SpeedUp_time<<" pVel: "<<pVel<<" MoveFlag: "<<MoveFlag<<endl;


    if(GL_JOY_Y_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[1] && GL_JOY_A_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[2] && GL_JOY_X_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[0]
            && GL_JOY_B_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[3] && GL_JOY_RT_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[4] && GL_JOY_RB_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[5]
            && GL_JOY_LT_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[6] && GL_JOY_LB_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[7] && GL_JOY_AROW_RL_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[8]
            && GL_JOY_AROW_UD_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[9] && GL_JOY_RJOG_RL_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0] && GL_JOY_LJOG_RL_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[1]
            && GL_JOY_RJOG_UD_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[2] && GL_JOY_LJOG_UD_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[3])
    {
        same_counter++;
    }
    else{
        same_counter = 0;
    }

    GL_JOY_A_before = GL_JOY_A;
    GL_JOY_AROW_RL_before = GL_JOY_AROW_RL;
    GL_JOY_AROW_UD_before = GL_JOY_AROW_UD;
    GL_JOY_B_before = GL_JOY_B;
    GL_JOY_LB_before = GL_JOY_LB;
    GL_JOY_LJOG_RL_before = GL_JOY_LJOG_RL;
    GL_JOY_LJOG_UD_before = GL_JOY_LJOG_UD;
    GL_JOY_LT_before = GL_JOY_LT;
    GL_JOY_RB_before = GL_JOY_RB;
    GL_JOY_RJOG_RL_before = GL_JOY_RJOG_RL;
    GL_JOY_RJOG_UD_before = GL_JOY_RJOG_UD;
    GL_JOY_RT_before = GL_JOY_RT;
    GL_JOY_X_before = GL_JOY_X;
    GL_JOY_Y_before = GL_JOY_Y;

    if(same_counter >= 400){
        GL_JOY_Y = 0; GL_JOY_A = 0; GL_JOY_B = 0; GL_JOY_X = 0; GL_JOY_RT = 0; GL_JOY_RB = 0; GL_JOY_LT = 0;
        GL_JOY_LB = 0; GL_JOY_AROW_RL = 0; GL_JOY_AROW_UD = 0; GL_JOY_RJOG_RL = 0; GL_JOY_LJOG_RL = 0;
        GL_JOY_RJOG_UD = 0; GL_JOY_LJOG_UD = 0;
    }


    // RH pos +X
    if(GL_JOY_Y == 1 && GL_JOY_A == 0){
        MoveFlag[0] = true;
        manual_pos[0] += pVel[0]*0.005;
        plus_Dcc_time[0] = pVel[0]/Dcc*200;
    }
    if(GL_JOY_Y == 0 && GL_JOY_A == 0 && plus_Dcc_time[0] > 0){
        MoveFlag[0] = false;
        manual_pos[0] += pVel[0]*0.005;
        plus_Dcc_time[0] -= 1;
    }

    // RH pos -X
    if(GL_JOY_Y == 0 && GL_JOY_A == 1){
        MoveFlag[0] = true;
        manual_pos[0] -= pVel[0]*0.005;
        minus_Dcc_time[0] = pVel[0]/Dcc*200;
    }
    if(GL_JOY_Y == 0 && GL_JOY_A == 0 && minus_Dcc_time[0] > 0){
        MoveFlag[0] = false;
        manual_pos[0] -= pVel[0]*0.005;
        minus_Dcc_time[0] -= 1;
    }

    // RH pos -Y
    if(GL_JOY_B == 1 && GL_JOY_X == 0){
        MoveFlag[1] = true;
        manual_pos[1] -= pVel[1]*0.005;
        plus_Dcc_time[1] = pVel[1]/Dcc*200;
    }
    if(GL_JOY_B == 0 && GL_JOY_X == 0 && plus_Dcc_time[1] > 0){
        MoveFlag[1] = false;
        manual_pos[1] -= pVel[1]*0.005;
        plus_Dcc_time[1] -= 1;
    }

    // RH pos +Y
    if(GL_JOY_B == 0 && GL_JOY_X == 1){
        MoveFlag[1] = true;
        manual_pos[1] += pVel[1]*0.005;
        minus_Dcc_time[1] = pVel[1]/Dcc*200;
    }
    if(GL_JOY_B == 0 && GL_JOY_X == 0 && minus_Dcc_time[1] > 0){
        MoveFlag[1] = false;
        manual_pos[1] += pVel[1]*0.005;
        minus_Dcc_time[1] -= 1;
    }

    // RH pos +Z
    if(GL_JOY_RB == 1 && GL_JOY_RT == 0){
        MoveFlag[2] = true;
        manual_pos[2] += pVel[2]*0.005;
        plus_Dcc_time[2] = pVel[2]/Dcc*200;
    }
    if(GL_JOY_RB == 0 && GL_JOY_RT == 0 && plus_Dcc_time[2] > 0){
        MoveFlag[2] = false;
        manual_pos[2] += pVel[2]*0.005;
        plus_Dcc_time[2] -= 1;
    }

    // RH pos -Z
    if(GL_JOY_RB == 0 && GL_JOY_RT == 1){
        MoveFlag[2] = true;
        manual_pos[2] -= pVel[2]*0.005;
        minus_Dcc_time[2] = pVel[2]/Dcc*200;
    }
    if(GL_JOY_RB == 0 && GL_JOY_RT == 0 && minus_Dcc_time[2] > 0){
        MoveFlag[2] = false;
        manual_pos[2] -= pVel[2]*0.005;
        minus_Dcc_time[2] -= 1;
    }

    // RH ori +X
    if(GL_JOY_AROW_RL == -32767){
        MoveFlag[3] = true;
        qVel  = qVel.rotateZ(AngSpeed[3]);
        manual_quat = manual_quat*qVel;
        plus_Dcc_time[3] = AngSpeed[3]/Dccq*200;
    }
    if(GL_JOY_AROW_RL == 0 && plus_Dcc_time[3] > 0){
        MoveFlag[3] = false;
        qVel  = qVel.rotateZ(AngSpeed[3]);
        manual_quat = manual_quat*qVel;
        plus_Dcc_time[3] -=1;
    }

    // RH ori -X
    if(GL_JOY_AROW_RL == +32767){
        MoveFlag[3] = true;
        qVel  = qVel.rotateZ(-AngSpeed[3]);
        manual_quat = manual_quat*qVel;
        minus_Dcc_time[3] = AngSpeed[3]/Dccq*200;
    }
    if(GL_JOY_AROW_RL == 0 && minus_Dcc_time[3] > 0){
        MoveFlag[3] = false;
        qVel  = qVel.rotateZ(-AngSpeed[3]);
        manual_quat = manual_quat*qVel;
        minus_Dcc_time[3] -=1;
    }

    // RH ori +Y
    if(GL_JOY_AROW_UD == +32767){
        MoveFlag[4] = true;
        qVel  = qVel.rotateY(AngSpeed[4]);
        manual_quat = manual_quat*qVel;
        plus_Dcc_time[4] = AngSpeed[4]/Dccq*200;
    }
    if(GL_JOY_AROW_UD == 0 && plus_Dcc_time[4] > 0){
        MoveFlag[4] = false;
        qVel  = qVel.rotateY(AngSpeed[4]);
        manual_quat = manual_quat*qVel;
        plus_Dcc_time[4] -=1;
    }

    // RH ori -Y
    if(GL_JOY_AROW_UD == -32767){
        MoveFlag[4] = true;
        qVel  = qVel.rotateY(-AngSpeed[4]);
        manual_quat = manual_quat*qVel;
        minus_Dcc_time[4] = AngSpeed[4]/Dccq*200;
    }
    if(GL_JOY_AROW_UD == 0 && minus_Dcc_time[4] > 0){
        MoveFlag[4] = false;
        qVel  = qVel.rotateY(-AngSpeed[4]);
        manual_quat = manual_quat*qVel;
        minus_Dcc_time[4] -=1;
    }

    // RH ori +Z
    if(GL_JOY_LB == 1 && GL_JOY_LT == 0){
        MoveFlag[5] = true;
        qVel  = qVel.rotateX(AngSpeed[5]);
        manual_quat = manual_quat*qVel;
        plus_Dcc_time[5] = AngSpeed[5]/Dccq*200;
    }
    if(GL_JOY_LB == 0 && GL_JOY_LT == 0 && plus_Dcc_time[5] > 0){
        MoveFlag[5] = false;
        qVel  = qVel.rotateX(AngSpeed[5]);
        manual_quat = manual_quat*qVel;
        plus_Dcc_time[5] -=1;
    }

    // RH ori -Z
    if(GL_JOY_LB == 0 && GL_JOY_LT == 1){
        MoveFlag[5] = true;
        qVel  = qVel.rotateX(-AngSpeed[5]);
        manual_quat = manual_quat*qVel;
        minus_Dcc_time[5] = AngSpeed[5]/Dccq*200;
    }
    if(GL_JOY_LB == 0 && GL_JOY_LT == 0 && minus_Dcc_time[5] > 0){
        MoveFlag[5] = false;
        qVel  = qVel.rotateX(-AngSpeed[5]);
        manual_quat = manual_quat*qVel;
        minus_Dcc_time[5] -=1;
    }


    // ELB +
    if(GL_JOY_RJOG_UD == -32767 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[6] = true;
        if(Mode_Manual == MANUAL_RHAND)
            RELB += AngSpeed[6]*R2D*0.2;
        else
            RELB -= AngSpeed[6]*R2D*0.2;
        plus_Dcc_time[6] = AngSpeed[6]/Dccq*200;
    }
    if(GL_JOY_RJOG_UD > -32767 && GL_JOY_RJOG_UD <= 0 && plus_Dcc_time[6] > 0 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[6] = false;
        if(Mode_Manual == MANUAL_RHAND)
            RELB += AngSpeed[6]*R2D*0.2;
        else
            RELB -= AngSpeed[6]*R2D*0.2;
        plus_Dcc_time[6] -=1;
    }
    // ELB -
    if(GL_JOY_RJOG_UD == +32767 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[6] = true;
        if(Mode_Manual == MANUAL_RHAND)
            RELB -= AngSpeed[6]*R2D*0.2;
        else
            RELB += AngSpeed[6]*R2D*0.2;
        minus_Dcc_time[6] = AngSpeed[6]/Dccq*200;
    }
    if(GL_JOY_RJOG_UD < 32767 && GL_JOY_RJOG_UD >=0 && minus_Dcc_time[6] > 0 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[6] = false;
        if(Mode_Manual == MANUAL_RHAND)
            RELB -= AngSpeed[6]*R2D*0.2;
        else
            RELB += AngSpeed[6]*R2D*0.2;
        minus_Dcc_time[6] -=1;
    }

    // WST +
    if(GL_JOY_RJOG_RL == -32767 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = true;
        WST_ang += AngSpeed[7]*R2D*0.2;
        plus_Dcc_time[7] = AngSpeed[7]/Dccq*200;
    }
    if(GL_JOY_RJOG_RL > -32767 && GL_JOY_RJOG_RL <=0 && plus_Dcc_time[7] > 0 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = false;
        WST_ang += AngSpeed[7]*R2D*0.2;
        plus_Dcc_time[7] -=1;
    }
    // WST -
    if(GL_JOY_RJOG_RL == +32767 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = true;
        WST_ang -= AngSpeed[7]*R2D*0.2;
        minus_Dcc_time[7] = AngSpeed[7]/Dccq*200;
    }
    if(GL_JOY_RJOG_RL < 32767 && GL_JOY_RJOG_RL >= 0 && minus_Dcc_time[7] > 0 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = false;
        WST_ang -= AngSpeed[7]*R2D*0.2;
        minus_Dcc_time[7] -=1;
    }

    // Finger Grasping
    if(GL_JOY_LJOG_UD == 32767 && GL_JOY_LJOG_PUSH == 0){
        Grasping_value = 125/2;
    }
    else if(GL_JOY_LJOG_UD == -32767 && GL_JOY_LJOG_PUSH == 0){
        Grasping_value = -125/2;
    }
    else{
        Grasping_value = 0;
    }


    // Add POS info
    if(Mode_Manual == MANUAL_RHAND){
        // boundary of work-space
        //quat Hand_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
        mat3 Hand_Ori_mat = mat3(manual_quat);
        vec3 Hand_pos = vec3(manual_pos[0],manual_pos[1],manual_pos[2]);
        vec3 WristToHand_HandFrame = vec3(0,0,-0.16);
        mat3 Hand_Ori_mat_inv = Hand_Ori_mat.inverse();
        vec3 WristToHand_GlobalFrame = WristToHand_HandFrame*Hand_Ori_mat_inv;
        vec3 Wrist_pos = Hand_pos - WristToHand_GlobalFrame;

        ShoulderToWrist = (Wrist_pos.x - 0)*(Wrist_pos.x - 0) + (Wrist_pos.y + 0.206)*(Wrist_pos.y + 0.206) + (Wrist_pos.z - 0.456)*(Wrist_pos.z - 0.456);
        ShoulderToWrist = sqrt(ShoulderToWrist);

        if(ShoulderToWrist < 0.68 && ShoulderToWrist > 0.15 && Wrist_pos.x > -0.55 && Wrist_pos.y < 0.15)
            Manual_OK = true;

        else
            Manual_OK = false;


        if(Manual_OK == true){
            //--------------------------pos--------------------------------------------
            WBmotion->addRHPosInfo(manual_pos[0], manual_pos[1],manual_pos[2], 0.005);
            for(int i=0 ; i<3 ; i++)
                manual_pos_before[i] = manual_pos[i];

            //-------------------------Ori------------------------------------------------
            doubles RH_manual_ori(4);
            for(int i=0 ; i<4 ; i++)
                RH_manual_ori[i] = manual_quat[i];

            WBmotion->addRHOriInfo(RH_manual_ori, 0.005);

            manual_quat_before = manual_quat;
            //manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);


        }
        else{
            for(int i=0 ; i<3 ; i++)
                manual_pos[i] = manual_pos_before[i];

            manual_quat = manual_quat_before;
        }




        //------------------------ELB--------------------------------------------------
       // if(RELB < 0 || RELB > -90){
            WBmotion->addRElbPosInfo(RELB,0.005);
            WBmotion->des_RElb_ang = RELB;
            RELB_before = RELB;

        //}
//        else{
//            RELB = RELB_before;
//        }
        //-------------------------------------------------------------------------------



        //------------------------Finger-----------------------------------------------
        joint->SetJointRefAngle(RHAND, Grasping_value);
        if(sharedSEN->EXF_R_Enabled){
            joint->SetJointRefAngle(RF1, Grasping_value);
            joint->SetJointRefAngle(RF2, Grasping_value);
            joint->SetJointRefAngle(RF3, Grasping_value);
            joint->SetJointRefAngle(RF4, Grasping_value);
        }
        //----------------------------------------------------------------------------
    }
    else{
        // boundary of work-space

        mat3 Hand_Ori_mat = mat3(manual_quat);
        vec3 Hand_pos = vec3(manual_pos[0],manual_pos[1],manual_pos[2]);
        vec3 WristToHand_HandFrame = vec3(0,0,-0.16);
        mat3 Hand_Ori_mat_inv = Hand_Ori_mat.inverse();
        vec3 WristToHand_GlobalFrame = WristToHand_HandFrame*Hand_Ori_mat_inv;
        vec3 Wrist_pos = Hand_pos - WristToHand_GlobalFrame;

        ShoulderToWrist = (Wrist_pos.x - 0)*(Wrist_pos.x - 0) + (Wrist_pos.y - 0.206)*(Wrist_pos.y - 0.206) + (Wrist_pos.z - 0.456)*(Wrist_pos.z - 0.456);
        ShoulderToWrist = sqrt(ShoulderToWrist);

        if(ShoulderToWrist < 0.68 && ShoulderToWrist > 0.15 && Wrist_pos.x > -0.55 && Wrist_pos.y > -0.15)
            Manual_OK = true;

        else
            Manual_OK = false;


        if(Manual_OK == true){
            //--------------------------pos--------------------------------------------
            WBmotion->addLHPosInfo(manual_pos[0], manual_pos[1],manual_pos[2], 0.005);
            for(int i=0 ; i<3 ; i++)
                manual_pos_before[i] = manual_pos[i];


            //-------------------------Ori------------------------------------------------
            doubles RH_manual_ori(4);
            for(int i=0 ; i<4 ; i++)
                RH_manual_ori[i] = manual_quat[i];

            WBmotion->addLHOriInfo(RH_manual_ori, 0.005);

            manual_quat_before = manual_quat;


        }
        else{
            for(int i=0 ; i<3 ; i++)
                manual_pos[i] = manual_pos_before[i];

            manual_quat = manual_quat_before;
        }
        //---------------------------------------------------------------------------

        //------------------------ELB--------------------------------------------------
//        if(RELB < 0 || RELB > -90){
            WBmotion->addLElbPosInfo(RELB,0.005);
            RELB_before = RELB;
//        }
//        else{
//            RELB = RELB_before;
//        }
        //-------------------------------------------------------------------------------
        //------------------------Finger-----------------------------------------------
        joint->SetJointRefAngle(LHAND, Grasping_value);
        if(sharedSEN->EXF_L_Enabled){
            joint->SetJointRefAngle(LF1, Grasping_value);
            joint->SetJointRefAngle(LF2, Grasping_value);
            joint->SetJointRefAngle(LF3, Grasping_value);
            joint->SetJointRefAngle(LF4, Grasping_value);
        }
        //----------------------------------------------------------------------------
    }
    //--------------------------WST-------------------------------------------------
    if(WST_ang > -540 && WST_ang < 540){
        WBmotion->addWSTPosInfo(WST_ang,0.005);
        WST_ang_before = WST_ang;
    }
    else{
        WST_ang = WST_ang_before;
    }
    //-------------------------------------------------------------------------------
    if(counter >= 100){
        //
        counter = 0;
    }
}

void ManualMoveRHand()
{
    // Variables
    static int counter = 0;
    double pVel[3] = {0,0,0};
//    static double RH_SpeedUP_V0[6] = {0,0,0};
    static double SpeedDW_V0[8] = {0,0,0,0,0,0,0,0};
    static int SpeedUp_time[8] = {0,0,0,0,0,0,0,0};
    static int SlowDown_time[8] = {0,0,0,0,0,0,0,0};
    static int plus_Dcc_time[8] = {0,0,0,0,0,0,0,0};
    static int minus_Dcc_time[8] = {0,0,0,0,0,0,0,0};
    double Acc = 0.5;
    double Dcc = 0.5;
    double MaxVel = 0.07;
    static bool MoveFlag[8] = {false,false,false,false,false,false,false,false};
 //   double ShoulderToHand;
    double ShoulderToWrist;
    static bool Manual_OK = true;
    static double manual_pos[3];
    static double manual_pos_before[3];
    double Accq = 0.05;
    double Dccq = 0.02;
    double MaxVel_ang = 0.006;
    double AngSpeed[8];
    int Grasping_value = 0;
    static int GL_JOY_A_before;
    static int GL_JOY_AROW_RL_before;
    static int GL_JOY_AROW_UD_before;
    static int GL_JOY_B_before;
    static int GL_JOY_LB_before;
    static int GL_JOY_LJOG_RL_before;
    static int GL_JOY_LJOG_UD_before;
    static int GL_JOY_LT_before;
    static int GL_JOY_RB_before;
    static int GL_JOY_RJOG_RL_before;
    static int GL_JOY_RJOG_UD_before;
    static int GL_JOY_RT_before;
    static int GL_JOY_X_before;
    static int GL_JOY_Y_before;
    static int GL_JOY_BACK_before;
    static int GL_JOY_START_before;
//    static bool Release_Flag = false;
    static unsigned int same_counter = 0;
    static quat manual_quat;
    static quat manual_quat_before;
    quat qVel;
    static double WST_ang;
    static double WST_ang_before;

    if(_isFirst_both_R == true){
        for(int i=0;i<9;i++){
            SpeedDW_V0[i] = 0;
            SpeedUp_time[i] = 0;
            SlowDown_time[i] = 0;
            plus_Dcc_time[i] = 0;
            minus_Dcc_time[i] = 0;
            MoveFlag[i] = false;
        }

        GL_JOY_A_before = 0;
        GL_JOY_AROW_RL_before = 0;
        GL_JOY_AROW_UD_before = 0;
        GL_JOY_B_before = 0;
        GL_JOY_LB_before = 0;
        GL_JOY_LJOG_RL_before = 0;
        GL_JOY_LJOG_UD_before = 0;
        GL_JOY_LT_before = 0;
        GL_JOY_RB_before = 0;
        GL_JOY_RJOG_RL_before = 0;
        GL_JOY_RJOG_UD_before = 0;
        GL_JOY_RT_before = 0;
        GL_JOY_X_before = 0;
        GL_JOY_Y_before = 0;
        GL_JOY_START_before = 0;
        GL_JOY_BACK_before = 0;

        for(int i=0 ;i<3 ; i++){
            manual_pos[i] = WBmotion->pRH_3x1[i];
            manual_pos_before[i] = WBmotion->pRH_3x1[i];
        }
        manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
        manual_quat_before = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);

        WST_ang = joint->GetJointRefAngle(WST);
        WST_ang_before = joint->GetJointRefAngle(WST);

        _isFirst_both_R = false;    }


    manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);


    // Generate Position Trajectory
    for(int i=0;i<3;i++){
        if(MoveFlag[i] == true){
            SpeedUp_time[i]++;
            pVel[i] = Acc*SpeedUp_time[i]*0.005;
            if(pVel[i] >= MaxVel) pVel[i] = MaxVel;
            SlowDown_time[i] = 0;
            SpeedDW_V0[i] = pVel[i];
        }
        else
        {
            SlowDown_time[i]++;
            pVel[i] = SpeedDW_V0[i] - Dcc*SlowDown_time[i]*0.005;
            if(pVel[i] <= 0) pVel[i] = 0;
            SpeedUp_time[i] = 0;
        }
    }

    // Generatie Angualr speed Trajectory
    for(int i=3 ; i<8 ; i++){
        if(MoveFlag[i] == true){
            SpeedUp_time[i]++;
            AngSpeed[i] = Accq*SpeedUp_time[i]*0.005;
            if(AngSpeed[i] >= MaxVel_ang) AngSpeed[i] = MaxVel_ang;
            SlowDown_time[i] = 0;
            SpeedDW_V0[i] = AngSpeed[i];
        }
        else{
            SlowDown_time[i]++;
            AngSpeed[i] = SpeedDW_V0[i] - Dccq*SlowDown_time[i]*0.005;
            if(AngSpeed[i] <= 0) AngSpeed[i] = 0;
            SpeedUp_time[i] = 0;
        }
    }



    counter++;

    GL_JOY_A_before = GL_JOY_A;
    GL_JOY_AROW_RL_before = GL_JOY_AROW_RL;
    GL_JOY_AROW_UD_before = GL_JOY_AROW_UD;
    GL_JOY_B_before = GL_JOY_B;
    GL_JOY_LB_before = GL_JOY_LB;
    GL_JOY_LJOG_RL_before = GL_JOY_LJOG_RL;
    GL_JOY_LJOG_UD_before = GL_JOY_LJOG_UD;
    GL_JOY_LT_before = GL_JOY_LT;
    GL_JOY_RB_before = GL_JOY_RB;
    GL_JOY_RJOG_RL_before = GL_JOY_RJOG_RL;
    GL_JOY_RJOG_UD_before = GL_JOY_RJOG_UD;
    GL_JOY_RT_before = GL_JOY_RT;
    GL_JOY_X_before = GL_JOY_X;
    GL_JOY_Y_before = GL_JOY_Y;

    if(same_counter >= 400){
        GL_JOY_Y = 0;
        GL_JOY_A = 0;
        GL_JOY_B = 0;
        GL_JOY_X = 0;
        GL_JOY_RT = 0;
        GL_JOY_RB = 0;
        GL_JOY_LT = 0;
        GL_JOY_LB = 0;
        GL_JOY_AROW_RL = 0;
        GL_JOY_AROW_UD = 0;
        GL_JOY_RJOG_RL = 0;
        GL_JOY_LJOG_RL = 0;
        GL_JOY_RJOG_UD = 0;
        GL_JOY_LJOG_UD = 0;
    }


    // RH pos +X
    if(GL_JOY_Y == 1 && GL_JOY_A == 0){
        MoveFlag[0] = true;
        manual_pos[0] += pVel[0]*0.005;
        plus_Dcc_time[0] = pVel[0]/Dcc*200;
    }
    if(GL_JOY_Y == 0 && GL_JOY_A == 0 && plus_Dcc_time[0] > 0){
        MoveFlag[0] = false;
        manual_pos[0] += pVel[0]*0.005;
        plus_Dcc_time[0] -= 1;
    }

    // RH pos -X
    if(GL_JOY_Y == 0 && GL_JOY_A == 1){
        MoveFlag[0] = true;
        manual_pos[0] -= pVel[0]*0.005;
        minus_Dcc_time[0] = pVel[0]/Dcc*200;
    }
    if(GL_JOY_Y == 0 && GL_JOY_A == 0 && minus_Dcc_time[0] > 0){
        MoveFlag[0] = false;
        manual_pos[0] -= pVel[0]*0.005;
        minus_Dcc_time[0] -= 1;
    }

    // RH pos -Y
    if(GL_JOY_B == 1 && GL_JOY_X == 0){
        MoveFlag[1] = true;
        manual_pos[1] -= pVel[1]*0.005;
        plus_Dcc_time[1] = pVel[1]/Dcc*200;
    }
    if(GL_JOY_B == 0 && GL_JOY_X == 0 && plus_Dcc_time[1] > 0){
        MoveFlag[1] = false;
        manual_pos[1] -= pVel[1]*0.005;
        plus_Dcc_time[1] -= 1;
    }

    // RH pos +Y
    if(GL_JOY_B == 0 && GL_JOY_X == 1){
        MoveFlag[1] = true;
        manual_pos[1] += pVel[1]*0.005;
        minus_Dcc_time[1] = pVel[1]/Dcc*200;
    }
    if(GL_JOY_B == 0 && GL_JOY_X == 0 && minus_Dcc_time[1] > 0){
        MoveFlag[1] = false;
        manual_pos[1] += pVel[1]*0.005;
        minus_Dcc_time[1] -= 1;
    }

    // RH pos +Z
    if(GL_JOY_RB == 1 && GL_JOY_RT == 0){
        MoveFlag[2] = true;
        manual_pos[2] += pVel[2]*0.005;
        plus_Dcc_time[2] = pVel[2]/Dcc*200;
    }
    if(GL_JOY_RB == 0 && GL_JOY_RT == 0 && plus_Dcc_time[2] > 0){
        MoveFlag[2] = false;
        manual_pos[2] += pVel[2]*0.005;
        plus_Dcc_time[2] -= 1;
    }

    // RH pos -Z
    if(GL_JOY_RB == 0 && GL_JOY_RT == 1){
        MoveFlag[2] = true;
        manual_pos[2] -= pVel[2]*0.005;
        minus_Dcc_time[2] = pVel[2]/Dcc*200;
    }
    if(GL_JOY_RB == 0 && GL_JOY_RT == 0 && minus_Dcc_time[2] > 0){
        MoveFlag[2] = false;
        manual_pos[2] -= pVel[2]*0.005;
        minus_Dcc_time[2] -= 1;
    }

    // RH ori +X
    if(GL_JOY_LB == 1 && GL_JOY_LT == 0){
        MoveFlag[3] = true;
        qVel  = qVel.rotateZ(AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[3] = AngSpeed[3]/Dccq*200;
    }
    if(GL_JOY_LB == 0 && GL_JOY_LT == 0 && plus_Dcc_time[3] > 0){
        MoveFlag[3] = false;
        qVel  = qVel.rotateZ(AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[3] -=1;
    }

    // RH ori -X
    if(GL_JOY_LB == 0 && GL_JOY_LT == 1){
        MoveFlag[3] = true;
        qVel  = qVel.rotateZ(-AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[3] = AngSpeed[3]/Dccq*200;
    }
    if(GL_JOY_LB == 0 && GL_JOY_LT == 0 && minus_Dcc_time[3] > 0){
        MoveFlag[3] = false;
        qVel  = qVel.rotateZ(-AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[3] -=1;
    }

    // RH ori +Y
    if(GL_JOY_AROW_UD == +32767){
        MoveFlag[4] = true;
        qVel  = qVel.rotateY(AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[4] = AngSpeed[4]/Dccq*200;
    }
    if(GL_JOY_AROW_UD ==0 && plus_Dcc_time[4] > 0){
        MoveFlag[4] = false;
        qVel  = qVel.rotateY(AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[4] -=1;
    }

    // RH ori -Y
    if(GL_JOY_AROW_UD == -32767){
        MoveFlag[4] = true;
        qVel  = qVel.rotateY(-AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[4] = AngSpeed[4]/Dccq*200;
    }
    if(GL_JOY_AROW_UD ==0 && minus_Dcc_time[4] > 0){
        MoveFlag[4] = false;
        qVel  = qVel.rotateY(-AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[4] -=1;
    }

    // RH ori +Z
    if(GL_JOY_AROW_RL == -32767){
        MoveFlag[5] = true;
        qVel  = qVel.rotateX(AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[5] = AngSpeed[5]/Dccq*200;
    }
    if(GL_JOY_AROW_RL == 0 && plus_Dcc_time[5] > 0){
        MoveFlag[5] = false;
        qVel  = qVel.rotateX(AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[5] -=1;
    }

    // RH ori -Z
    if(GL_JOY_AROW_RL == +32767){
        MoveFlag[5] = true;
        qVel  = qVel.rotateX(-AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[5] = AngSpeed[5]/Dccq*200;
    }
    if(GL_JOY_AROW_RL == 0 && minus_Dcc_time[5] > 0){
        MoveFlag[5] = false;
        qVel  = qVel.rotateX(-AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[5] -=1;
    }


    // WST +
    if(GL_JOY_RJOG_RL == -32767 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = true;
        WST_ang += AngSpeed[7]*R2D*0.2;
        plus_Dcc_time[7] = AngSpeed[7]/Dccq*200;
    }
    if(GL_JOY_RJOG_RL > -32767 && GL_JOY_RJOG_RL <=0 && plus_Dcc_time[7] > 0 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = false;
        WST_ang += AngSpeed[7]*R2D*0.2;
        plus_Dcc_time[7] -=1;
    }
    // WST -
    if(GL_JOY_RJOG_RL == +32767 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = true;
        WST_ang -= AngSpeed[7]*R2D*0.2;
        minus_Dcc_time[7] = AngSpeed[7]/Dccq*200;
    }
    if(GL_JOY_RJOG_RL < 32767 && GL_JOY_RJOG_RL >= 0 && minus_Dcc_time[7] > 0 && GL_JOY_RJOG_PUSH == 0){
        MoveFlag[7] = false;
        WST_ang -= AngSpeed[7]*R2D*0.2;
        minus_Dcc_time[7] -=1;
    }



    // Finger Grasping
    if(GL_JOY_LJOG_UD == 32767 && GL_JOY_LJOG_PUSH == 0){
        Grasping_value = 75/2;
    }
    else if(GL_JOY_LJOG_UD == -32767 && GL_JOY_LJOG_PUSH == 0){
        Grasping_value = -75/2;
    }
    else{
        Grasping_value = 0;
    }


    // Add POS info

    // boundary of work-space
    //quat Hand_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
    mat3 Hand_Ori_mat = mat3(manual_quat);
    vec3 Hand_pos = vec3(manual_pos[0],manual_pos[1],manual_pos[2]);
    vec3 WristToHand_HandFrame = vec3(0,0,-0.16);
    mat3 Hand_Ori_mat_inv = Hand_Ori_mat.inverse();
    vec3 WristToHand_GlobalFrame = WristToHand_HandFrame*Hand_Ori_mat_inv;
    vec3 Wrist_pos = Hand_pos - WristToHand_GlobalFrame;

    ShoulderToWrist = (Wrist_pos.x - 0)*(Wrist_pos.x - 0) + (Wrist_pos.y + 0.206)*(Wrist_pos.y + 0.206) + (Wrist_pos.z - 0.456)*(Wrist_pos.z - 0.456);
    ShoulderToWrist = sqrt(ShoulderToWrist);

    if(ShoulderToWrist < 0.68 && ShoulderToWrist > 0.15 && Wrist_pos.x > -0.5 && Wrist_pos.y < 0.05)
        Manual_OK = true;

    else
        Manual_OK = false;


    if(Manual_OK == true){
        //--------------------------pos--------------------------------------------
        WBmotion->addRHPosInfo(manual_pos[0], manual_pos[1],manual_pos[2], 0.005);
        for(int i=0 ; i<3 ; i++){
            manual_pos_before[i] = manual_pos[i];
        }


        //-------------------------Ori------------------------------------------------
        doubles RH_manual_ori(4);
        for(int i=0 ; i<4 ; i++)
            RH_manual_ori[i] = manual_quat[i];

        WBmotion->addRHOriInfo(RH_manual_ori, 0.005);

        manual_quat_before = manual_quat;
        //manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);


    }
    else{
        for(int i=0 ; i<3 ; i++)
            manual_pos[i] = manual_pos_before[i];

        manual_quat = manual_quat_before;
    }

    //------------------------Finger-----------------------------------------------
    joint->SetJointRefAngle(RHAND, Grasping_value);
    if(sharedSEN->EXF_R_Enabled){
        joint->SetJointRefAngle(RF1, Grasping_value);
        joint->SetJointRefAngle(RF2, Grasping_value);
        joint->SetJointRefAngle(RF3, Grasping_value);
        joint->SetJointRefAngle(RF4, Grasping_value);
    }
    //----------------------------------------------------------------------------
    //------------------------Finger-----------------------------------------------
    joint->SetJointRefAngle(LHAND, Grasping_value);
    if(sharedSEN->EXF_L_Enabled){
        joint->SetJointRefAngle(LF1, Grasping_value);
        joint->SetJointRefAngle(LF2, Grasping_value);
        joint->SetJointRefAngle(LF3, Grasping_value);
        joint->SetJointRefAngle(LF4, Grasping_value);
    }
    //----------------------------------------------------------------------------

    //--------------------------WST-------------------------------------------------
    if(WST_ang > -540 && WST_ang < 540){
        WBmotion->addWSTPosInfo(WST_ang,0.005);
        WST_ang_before = WST_ang;
    }
    else{
        WST_ang = WST_ang_before;
    }
    //-------------------------------------------------------------------------------


}

void ManualMoveLHand()
{
    // Variables
    static int counter = 0;
    double pVel[3] = {0,0,0};
//    static double RH_SpeedUP_V0[6] = {0,0,0};
    static double SpeedDW_V0[8] = {0,0,0,0,0,0,0,0};
    static int SpeedUp_time[8] = {0,0,0,0,0,0,0,0};
    static int SlowDown_time[8] = {0,0,0,0,0,0,0,0};
    static int plus_Dcc_time[8] = {0,0,0,0,0,0,0,0};
    static int minus_Dcc_time[8] = {0,0,0,0,0,0,0,0};
    double Acc = 0.5;
    double Dcc = 0.5;
    double MaxVel = 0.07;
    static bool MoveFlag[8] = {false,false,false,false,false,false,false,false};
 //   double ShoulderToHand;
    double ShoulderToWrist;
    static bool Manual_OK = true;
    static double manual_pos[3];
    static double manual_pos_before[3];
    double Accq = 0.05;
    double Dccq = 0.02;
    double MaxVel_ang = 0.006;
    double AngSpeed[8];
    static int GL_JOY_A_before;
    static int GL_JOY_AROW_RL_before;
    static int GL_JOY_AROW_UD_before;
    static int GL_JOY_B_before;
    static int GL_JOY_LB_before;
    static int GL_JOY_LJOG_RL_before;
    static int GL_JOY_LJOG_UD_before;
    static int GL_JOY_LT_before;
    static int GL_JOY_RB_before;
    static int GL_JOY_RJOG_RL_before;
    static int GL_JOY_RJOG_UD_before;
    static int GL_JOY_RT_before;
    static int GL_JOY_X_before;
    static int GL_JOY_Y_before;
//    static bool Release_Flag = false;
    static unsigned int same_counter = 0;
    static quat manual_quat;
    static quat manual_quat_before;
    quat qVel;
    if(_isFirst_both_L == true){
        for(int i=0;i<9;i++){
            SpeedDW_V0[i] = 0;
            SpeedUp_time[i] = 0;
            SlowDown_time[i] = 0;
            plus_Dcc_time[i] = 0;
            minus_Dcc_time[i] = 0;
            MoveFlag[i] = false;
        }
        GL_JOY_A_before = 0;
        GL_JOY_AROW_RL_before = 0;
        GL_JOY_AROW_UD_before = 0;
        GL_JOY_B_before = 0;
        GL_JOY_LB_before = 0;
        GL_JOY_LJOG_RL_before = 0;
        GL_JOY_LJOG_UD_before = 0;
        GL_JOY_LT_before = 0;
        GL_JOY_RB_before = 0;
        GL_JOY_RJOG_RL_before = 0;
        GL_JOY_RJOG_UD_before = 0;
        GL_JOY_RT_before = 0;
        GL_JOY_X_before = 0;
        GL_JOY_Y_before = 0;

        for(int i=0 ;i<3 ; i++){
            manual_pos[i] = WBmotion->pLH_3x1[i];
            manual_pos_before[i] = WBmotion->pLH_3x1[i];
        }
        manual_quat = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);
        manual_quat_before = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);

        _isFirst_both_L = false;
    }


    manual_quat = quat(WBmotion->qLH_4x1[0],WBmotion->qLH_4x1[1],WBmotion->qLH_4x1[2],WBmotion->qLH_4x1[3]);


    // Generate Position Trajectory
    for(int i=0;i<3;i++){
        if(MoveFlag[i] == true){
            SpeedUp_time[i]++;
            pVel[i] = Acc*SpeedUp_time[i]*0.005;
            if(pVel[i] >= MaxVel) pVel[i] = MaxVel;
            SlowDown_time[i] = 0;
            SpeedDW_V0[i] = pVel[i];
        }
        else{
            SlowDown_time[i]++;
            pVel[i] = SpeedDW_V0[i] - Dcc*SlowDown_time[i]*0.005;
            if(pVel[i] <= 0) pVel[i] = 0;
            SpeedUp_time[i] = 0;
//            RH_SpeedUP_V0[i] = pVel[i];
        }
    }

    // Generatie Angualr speed Trajectory
    for(int i=3 ; i<8 ; i++){
        if(MoveFlag[i] == true){
            SpeedUp_time[i]++;
            AngSpeed[i] = Accq*SpeedUp_time[i]*0.005;
            if(AngSpeed[i] >= MaxVel_ang) AngSpeed[i] = MaxVel_ang;
            SlowDown_time[i] = 0;
            SpeedDW_V0[i] = AngSpeed[i];
        }
        else{
            SlowDown_time[i]++;
            AngSpeed[i] = SpeedDW_V0[i] - Dccq*SlowDown_time[i]*0.005;
            if(AngSpeed[i] <= 0) AngSpeed[i] = 0;
            SpeedUp_time[i] = 0;
 //         RH_SpeedUP_V0[i] = AngSpeed[i];
        }
    }



    counter++;
//    if(GL_JOY_Y_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[1] && GL_JOY_A_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[2] && GL_JOY_X_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[0]
//            && GL_JOY_B_before==(int)sharedCMD->COMMAND[PODO_NO].USER_PARA_CHAR[3] && GL_JOY_RT_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[4] && GL_JOY_RB_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[5]
//            && GL_JOY_LT_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[6] && GL_JOY_LB_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[7] && GL_JOY_AROW_RL_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[8]
//            && GL_JOY_AROW_UD_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[9] && GL_JOY_RJOG_RL_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[0] && GL_JOY_LJOG_RL_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[1]
//            && GL_JOY_RJOG_UD_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[2] && GL_JOY_LJOG_UD_before==sharedCMD->COMMAND[PODO_NO].USER_PARA_INT[3])
//    {
//        same_counter++;
//    }
//    else{
//        same_counter = 0;
//    }

    GL_JOY_A_before = GL_JOY_A;
    GL_JOY_AROW_RL_before = GL_JOY_AROW_RL;
    GL_JOY_AROW_UD_before = GL_JOY_AROW_UD;
    GL_JOY_B_before = GL_JOY_B;
    GL_JOY_LB_before = GL_JOY_LB;
    GL_JOY_LJOG_RL_before = GL_JOY_LJOG_RL;
    GL_JOY_LJOG_UD_before = GL_JOY_LJOG_UD;
    GL_JOY_LT_before = GL_JOY_LT;
    GL_JOY_RB_before = GL_JOY_RB;
    GL_JOY_RJOG_RL_before = GL_JOY_RJOG_RL;
    GL_JOY_RJOG_UD_before = GL_JOY_RJOG_UD;
    GL_JOY_RT_before = GL_JOY_RT;
    GL_JOY_X_before = GL_JOY_X;
    GL_JOY_Y_before = GL_JOY_Y;

    if(same_counter >= 400){
        GL_JOY_Y = 0;
        GL_JOY_A = 0;
        GL_JOY_B = 0;
        GL_JOY_X = 0;
        GL_JOY_RT = 0;
        GL_JOY_RB = 0;
        GL_JOY_LT = 0;
        GL_JOY_LB = 0;
        GL_JOY_AROW_RL = 0;
        GL_JOY_AROW_UD = 0;
        GL_JOY_RJOG_RL = 0;
        GL_JOY_LJOG_RL = 0;
        GL_JOY_RJOG_UD = 0;
        GL_JOY_LJOG_UD = 0;
    }


    // RH pos +X
    if(GL_JOY_Y == 1 && GL_JOY_A == 0){
        MoveFlag[0] = true;
        manual_pos[0] += pVel[0]*0.005;
        plus_Dcc_time[0] = pVel[0]/Dcc*200;
    }
    if(GL_JOY_Y == 0 && GL_JOY_A == 0 && plus_Dcc_time[0] > 0){
        MoveFlag[0] = false;
        manual_pos[0] += pVel[0]*0.005;
        plus_Dcc_time[0] -= 1;
    }

    // RH pos -X
    if(GL_JOY_Y == 0 && GL_JOY_A == 1){
        MoveFlag[0] = true;
        manual_pos[0] -= pVel[0]*0.005;
        minus_Dcc_time[0] = pVel[0]/Dcc*200;
    }
    if(GL_JOY_Y == 0 && GL_JOY_A == 0 && minus_Dcc_time[0] > 0){
        MoveFlag[0] = false;
        manual_pos[0] -= pVel[0]*0.005;
        minus_Dcc_time[0] -= 1;
    }

    // RH pos -Y
    if(GL_JOY_B == 1 && GL_JOY_X == 0){
        MoveFlag[1] = true;
        manual_pos[1] -= pVel[1]*0.005;
        plus_Dcc_time[1] = pVel[1]/Dcc*200;
    }
    if(GL_JOY_B == 0 && GL_JOY_X == 0 && plus_Dcc_time[1] > 0){
        MoveFlag[1] = false;
        manual_pos[1] -= pVel[1]*0.005;
        plus_Dcc_time[1] -= 1;
    }

    // RH pos +Y
    if(GL_JOY_B == 0 && GL_JOY_X == 1){
        MoveFlag[1] = true;
        manual_pos[1] += pVel[1]*0.005;
        minus_Dcc_time[1] = pVel[1]/Dcc*200;
    }
    if(GL_JOY_B == 0 && GL_JOY_X == 0 && minus_Dcc_time[1] > 0){
        MoveFlag[1] = false;
        manual_pos[1] += pVel[1]*0.005;
        minus_Dcc_time[1] -= 1;
    }

    // RH pos +Z
    if(GL_JOY_RB == 1 && GL_JOY_RT == 0){
        MoveFlag[2] = true;
        manual_pos[2] += pVel[2]*0.005;
        plus_Dcc_time[2] = pVel[2]/Dcc*200;
    }
    if(GL_JOY_RB == 0 && GL_JOY_RT == 0 && plus_Dcc_time[2] > 0){
        MoveFlag[2] = false;
        manual_pos[2] += pVel[2]*0.005;
        plus_Dcc_time[2] -= 1;
    }

    // RH pos -Z
    if(GL_JOY_RB == 0 && GL_JOY_RT == 1){
        MoveFlag[2] = true;
        manual_pos[2] -= pVel[2]*0.005;
        minus_Dcc_time[2] = pVel[2]/Dcc*200;
    }
    if(GL_JOY_RB == 0 && GL_JOY_RT == 0 && minus_Dcc_time[2] > 0){
        MoveFlag[2] = false;
        manual_pos[2] -= pVel[2]*0.005;
        minus_Dcc_time[2] -= 1;
    }

    // RH ori +X
    if(GL_JOY_LB == 1 && GL_JOY_LT == 0){
        MoveFlag[3] = true;
        qVel  = qVel.rotateZ(AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[3] = AngSpeed[3]/Dccq*200;
    }
    if(GL_JOY_LB == 0 && GL_JOY_LT == 0 && plus_Dcc_time[3] > 0){
        MoveFlag[3] = false;
        qVel  = qVel.rotateZ(AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[3] -=1;
    }

    // RH ori -X
    if(GL_JOY_LB == 0 && GL_JOY_LT == 1){
        MoveFlag[3] = true;
        qVel  = qVel.rotateZ(-AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[3] = AngSpeed[3]/Dccq*200;
    }
    if(GL_JOY_LB == 0 && GL_JOY_LT == 0 && minus_Dcc_time[3] > 0){
        MoveFlag[3] = false;
        qVel  = qVel.rotateZ(-AngSpeed[3]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[3] -=1;
    }

    // RH ori +Y
    if(GL_JOY_AROW_UD == +32767){
        MoveFlag[4] = true;
        qVel  = qVel.rotateY(AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[4] = AngSpeed[4]/Dccq*200;
    }
    if(GL_JOY_AROW_UD ==0 && plus_Dcc_time[4] > 0){
        MoveFlag[4] = false;
        qVel  = qVel.rotateY(AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[4] -=1;
    }

    // RH ori -Y
    if(GL_JOY_AROW_UD == -32767){
        MoveFlag[4] = true;
        qVel  = qVel.rotateY(-AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[4] = AngSpeed[4]/Dccq*200;
    }
    if(GL_JOY_AROW_UD ==0 && minus_Dcc_time[4] > 0){
        MoveFlag[4] = false;
        qVel  = qVel.rotateY(-AngSpeed[4]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[4] -=1;
    }

    // RH ori +Z
    if(GL_JOY_AROW_RL == -32767){
        MoveFlag[5] = true;
        qVel  = qVel.rotateX(AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[5] = AngSpeed[5]/Dccq*200;
    }
    if(GL_JOY_AROW_RL == 0 && plus_Dcc_time[5] > 0){
        MoveFlag[5] = false;
        qVel  = qVel.rotateX(AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        plus_Dcc_time[5] -=1;
    }

    // RH ori -Z
    if(GL_JOY_AROW_RL == +32767){
        MoveFlag[5] = true;
        qVel  = qVel.rotateX(-AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[5] = AngSpeed[5]/Dccq*200;
    }
    if(GL_JOY_AROW_RL == 0 && minus_Dcc_time[5] > 0){
        MoveFlag[5] = false;
        qVel  = qVel.rotateX(-AngSpeed[5]);
        manual_quat = qVel*manual_quat;
        minus_Dcc_time[5] -=1;
    }



    // Add POS info

    // boundary of work-space
    //quat Hand_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
    mat3 Hand_Ori_mat = mat3(manual_quat);
    vec3 Hand_pos = vec3(manual_pos[0],manual_pos[1],manual_pos[2]);
    vec3 WristToHand_HandFrame = vec3(0,0,-0.16);
    mat3 Hand_Ori_mat_inv = Hand_Ori_mat.inverse();
    vec3 WristToHand_GlobalFrame = WristToHand_HandFrame*Hand_Ori_mat_inv;
    vec3 Wrist_pos = Hand_pos - WristToHand_GlobalFrame;

    ShoulderToWrist = (Wrist_pos.x - 0)*(Wrist_pos.x - 0) + (Wrist_pos.y - 0.206)*(Wrist_pos.y - 0.206) + (Wrist_pos.z - 0.456)*(Wrist_pos.z - 0.456);
    ShoulderToWrist = sqrt(ShoulderToWrist);

    if(ShoulderToWrist < 0.68 && ShoulderToWrist > 0.15 && Wrist_pos.x > -0.5 && Wrist_pos.y > -0.05)
        Manual_OK = true;

    else
        Manual_OK = false;


    if(Manual_OK == true){
        //--------------------------pos--------------------------------------------
        WBmotion->addLHPosInfo(manual_pos[0], manual_pos[1],manual_pos[2], 0.005);
        for(int i=0 ; i<3 ; i++)
            manual_pos_before[i] = manual_pos[i];

        //-------------------------Ori------------------------------------------------
        doubles manual_ori(4);
        for(int i=0 ; i<4 ; i++)
            manual_ori[i] = manual_quat[i];

        WBmotion->addLHOriInfo(manual_ori, 0.005);

        manual_quat_before = manual_quat;
        //manual_quat = quat(WBmotion->qRH_4x1[0],WBmotion->qRH_4x1[1],WBmotion->qRH_4x1[2],WBmotion->qRH_4x1[3]);
    }
    else{
        for(int i=0 ; i<3 ; i++)
            manual_pos[i] = manual_pos_before[i];

        manual_quat = manual_quat_before;
    }
}

void ROS_Clean()
{
//    sharedROS->Arm_action.joint[i].GoalmsTime = 0.;
}

int  CheckRobotState_ARM()
{
    switch(sharedROS->state_arm)
    {
    case ROBOT_NOT_MOVE:
    {
        return true;
    }
    case ROBOT_MOVING_WBIK:
    {
        FILE_LOG(logERROR) << "Robot still moving wbik. Disregard commands";
        return false;
    }
    case ROBOT_MOVING_JOINT:
    {
        FILE_LOG(logERROR) << "Robot still moving joint. Disregard commands";
        return false;
    }
    case ROBOT_JOINT_PUBLISHED:
    {
        FILE_LOG(logERROR) << "Robot still moving joint. Disregard commands";
        return false;
    }
    default:
        return false;
    }
}

void Calculate_FK()
{
    double Q[34];
    double RH_pos[3];
    double LH_pos[3];
    double RH_ori[4], LH_ori[4];
    double WST_angle, Relb_angle, Lelb_angle;

    WST_angle = sharedSEN->ENCODER[MC_ID_CH_Pairs[WST].id][MC_ID_CH_Pairs[WST].ch].CurrentReference;

    for(int i=0; i<3; i++)
    {
        RH_pos[i] = WBmotion->pRH_3x1[i];
        LH_pos[i] = WBmotion->pLH_3x1[i];
        sharedROS->Arm_feedback.wbik[RIGHT_HAND].Goal_pos[i] = RH_pos[i];
        sharedROS->Arm_feedback.wbik[LEFT_HAND].Goal_pos[i] = LH_pos[i];
    }

    for(int i=0; i<4; i++)
    {
        RH_ori[i] = WBmotion->qRH_4x1[i];
        LH_ori[i] = WBmotion->qLH_4x1[i];
        sharedROS->Arm_feedback.wbik[RIGHT_HAND].Goal_quat[i]= RH_ori[i];
        sharedROS->Arm_feedback.wbik[LEFT_HAND].Goal_quat[i]= LH_ori[i];
    }

    sharedROS->Arm_feedback.wbik[RIGHT_ELBOW].Goal_angle = Relb_angle;
    sharedROS->Arm_feedback.wbik[LEFT_ELBOW].Goal_angle = Lelb_angle;
    sharedROS->Arm_feedback.wbik[WAIST].Goal_angle = WST_angle;

    for(int i=0; i<NUM_PARTS; i++)
    {
        sharedROS->Arm_feedback.wbik[i].ONOFF_movepos = sharedROS->Arm_action.wbik[i].ONOFF_movepos;
        sharedROS->Arm_feedback.wbik[i].ONOFF_moveori = sharedROS->Arm_action.wbik[i].ONOFF_moveori;
    }
}

void Write_Feedback()
{
    if(sharedROS->state_arm != ROBOT_NOT_MOVE)
    {
//        FILE_LOG(logERROR) << "ARM RESULT FLAG IS OFF";
        Calculate_FK();
        for(int i=0;i<NUM_JOINTS;i++)
        {
            sharedROS->Arm_feedback.joint[i].reference = sharedSEN->ENCODER[ROS_MC_Pairs[i].id][ROS_MC_Pairs[i].ch].CurrentReference;
        }
        sharedROS->Arm_feedback.result_flag = false;
    }else
    {
//        FILE_LOG(logSUCCESS) << "ARM RESULT FLAG IS ON";

        sharedROS->Arm_feedback.result_flag = true;
        for(int i=0;i<NUM_JOINTS;i++)
        {
            sharedROS->Arm_feedback.joint[i].reference = sharedSEN->ENCODER[ROS_MC_Pairs[i].id][ROS_MC_Pairs[i].ch].CurrentReference;
        }
    }

    for(int i=0;i<NUM_JOINTS; i++)
    {
        sharedROS->Arm_feedback.joint[i].ONOFF_control = sharedROS->Arm_action.joint[i].ONOFF_control;
    }

    if(sharedROS->state_base == BASE_MOVING)
    {
        sharedROS->Base_feedback.wheel.MoveX = OMNImove.OMNIinfo.Probot.X;
        sharedROS->Base_feedback.wheel.MoveY = OMNImove.OMNIinfo.Probot.Y;
        sharedROS->Base_feedback.wheel.ThetaDeg = OMNImove.OMNIinfo.Probot.Theta;
        sharedROS->Base_feedback.result_flag = false;
    }else
    {
        sharedROS->Base_feedback.result_flag = true;
    }

    if(FLAG_Gripper == true)
        sharedROS->Gripper_feedback.result_flag = false;
    else
        sharedROS->Gripper_feedback.result_flag = true;
}

int  CheckRobotState_BASE()
{
    if(sharedROS->state_base == BASE_NOT_MOVE)
    {
        return true;
    } else
    {
        FILE_LOG(logERROR) << "Robot base still moving. Disregard commands";
        return false;
    }
}

void GripperTH()
{
    if(FLAG_Gripper == true)
    {
        //get position of each Gripper//
        float EncoderRHAND = sharedSEN->ENCODER[MC_ID_CH_Pairs[RHAND].id][MC_ID_CH_Pairs[RHAND].ch].CurrentPosition;
        float EncoderLHAND = sharedSEN->ENCODER[MC_ID_CH_Pairs[LHAND].id][MC_ID_CH_Pairs[LHAND].ch].CurrentPosition;
        //set velocity of each Gripper//
        int velocityRGripper = 130;
        int velocityLGripper = 130;
        if(sharedSEN->EXF_L_Enabled)
            velocityLGripper = 30;
        if(sharedSEN->EXF_R_Enabled)
            velocityRGripper = 30;

        static int DoneR, DoneL = true;
        static int CMDprint = false;

        if(CMDprint == false)
        {
            printf("CMD = %d\n",MODE_RGripper);
            CMDprint = true;
        }


        switch(MODE_RGripper)
        {
        case GRIPPER_STOP:
        {
            joint->SetJointRefAngle(RHAND, 0);
            DoneR = true;
            break;
        }
        case GRIPPER_OPEN:
        {
            static int gripper_cnt = 0;
            DoneR = false;
            if(gripper_cnt > MAX_GRIPPER_CNT)
            {
                FILE_LOG(logINFO) << "Right Gripper open stop (time over)";
                MODE_RGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                CMDprint = false;
                break;
            }
            if(EncoderRHAND < LIMIT_Gripper)
            {//open done
                FILE_LOG(logSUCCESS) << "Right Gripper open done";
                MODE_RGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                CMDprint = false;
                break;
            }
            joint->SetJointRefAngle(RHAND, -velocityRGripper);
            gripper_cnt++;
            break;
        }
        case GRIPPER_CLOSE:
        {
            static int gripper_cnt = 0;
            DoneR = false;
            if(gripper_cnt > 120)//MAX_GRIPPER_CNT)
            {
                FILE_LOG(logINFO) << "Right Gripper close stop (time over)";
                MODE_RGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                break;
            }
            if(EncoderRHAND > LIMIT_Gripper)
            {//grasp done
                FILE_LOG(logSUCCESS) << "Right Gripper grasp done";
                MODE_RGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                break;
            }
            joint->SetJointRefAngle(RHAND, velocityRGripper);
            gripper_cnt++;
            break;
        }
        }

        switch(MODE_LGripper)
        {
        case GRIPPER_STOP:
        {
            joint->SetJointRefAngle(LHAND, 0);
            DoneL = true;
            break;
        }
        case GRIPPER_OPEN:
        {
            static int gripper_cnt = 0;
            DoneL = false;
            if(gripper_cnt > MAX_GRIPPER_CNT)
            {
                FILE_LOG(logINFO) << "Left Gripper open stop (time over)";
                MODE_LGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                break;
            }
            if(EncoderLHAND < LIMIT_Gripper)
            {//open done
                FILE_LOG(logSUCCESS) << "Left Gripper open done";
                MODE_LGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                break;
            }
            joint->SetJointRefAngle(LHAND, -velocityLGripper);
            gripper_cnt++;
            break;
        }
        case GRIPPER_CLOSE:
        {
            static int gripper_cnt = 0;
            DoneL = false;
            if(gripper_cnt > MAX_GRIPPER_CNT)
            {
                FILE_LOG(logINFO) << "Left Gripper close stop (time over)";
                MODE_LGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                break;
            }
            if(EncoderLHAND > LIMIT_Gripper)
            {//grasp done
                FILE_LOG(logSUCCESS) << "Left Gripper grasp done";
                MODE_LGripper = GRIPPER_STOP;
                gripper_cnt = 0;
                break;
            }
            joint->SetJointRefAngle(LHAND, velocityLGripper);
            gripper_cnt++;
            break;
        }
        }

        if(DoneR && DoneL)
        {
            FILE_LOG(logSUCCESS) << "Both Gripper move done!!";
            FLAG_Gripper = false;
        }
    }
}

int  IsReadyTrajectory200Hz()
{

    printf("IsReadyTrajectory200Hz start %d\n",sharedROS->refsLen);
    int IsReady = false;
    //Interpolation sharedROS->refs
    double vel[NUM_JOINTS][sharedROS->refsLen] = {0.,};
    double acc[NUM_JOINTS][sharedROS->refsLen] = {0.,};

    for(int t_iter=0; t_iter<sharedROS->refsLen-1; t_iter++)
    {
        for(int j_iter=0; j_iter<NUM_JOINTS; j_iter++)
        {
            if(sharedROS->refarray[t_iter].ref[j_iter].ONOFF_control == true)
            {
                double ti = 0;
                double tf = sharedROS->refarray[t_iter+1].ref[j_iter].GoalmsTime;
                double tem = 0.;
                for(double k=0.;k<tf;k+=0.005)
                {
                    tem = k;
                }
                tf = tem;
                double p_i = sharedROS->refarray[t_iter].ref[j_iter].reference*R2Df;
                double p_f = sharedROS->refarray[t_iter+1].ref[j_iter].reference*R2Df;
                double v_i = vel[j_iter][t_iter];
                double v_f = 0;
                double a_i = acc[j_iter][t_iter];
                double a_f = 0;

                if(t_iter == 0)
                {
                    v_i = 0.;
                    a_i = 0.;
                }

                if(t_iter < sharedROS->refsLen-2)
                {
                    v_f = (sharedROS->refarray[t_iter+2].ref[j_iter].reference*R2Df - p_i)/(tf + sharedROS->refarray[t_iter+2].ref[j_iter].GoalmsTime);
                }

                MatrixXd M66 = MatrixXd::Zero(6,6);
                M66 << 1, ti, ti*ti, ti*ti*ti, ti*ti*ti*ti, ti*ti*ti*ti*ti,
                      1, tf, tf*tf, tf*tf*tf, tf*tf*tf*tf, tf*tf*tf*tf*tf,
                      0, 1, 2*ti, 3*ti*ti, 4*ti*ti*ti, 5*ti*ti*ti*ti,
                      0, 1, 2*tf, 3*tf*tf, 4*tf*tf*tf, 5*tf*tf*tf*tf,
                      0, 0, 2, 6*ti, 12*ti*ti, 20*ti*ti*ti,
                      0, 0, 2, 6*tf, 12*tf*tf, 20*tf*tf*tf;
                MatrixXd M66_inv = M66.inverse();

                VectorXd Y16 = VectorXd::Zero(6);
                VectorXd Coef16 = VectorXd::Zero(6);
                Y16 << p_i, p_f, v_i, v_f, a_i, a_f;

                Coef16 = M66_inv*Y16;

                double t = 0.;
                double tempPt   = 0.;
                double tempdPt  = 0.;
                double tempddPt = 0.;

                while(t < tf)
                {
                    tempPt   = Coef16[0] + Coef16[1]*t + Coef16[2]*t*t + Coef16[3]*t*t*t + Coef16[4]*t*t*t*t + Coef16[5]*t*t*t*t*t;
                    tempdPt  = Coef16[1] + 2*Coef16[2]*t + 3*Coef16[3]*t*t + 4*Coef16[4]*t*t*t + 5*Coef16[5]*t*t*t*t;
                    tempddPt = 2*Coef16[2] + 6*Coef16[3]*t + 12*Coef16[4]*t*t + 20*Coef16[5]*t*t*t;

                    //if(t>0.)
                    {
                        Pt[j_iter].p.push_back(tempPt);
                        dPt[j_iter].p.push_back(tempdPt);
                        ddPt[j_iter].p.push_back(tempddPt);
                        IsONOFF[j_iter].s.push_back(sharedROS->refarray[t_iter].ref[j_iter].ONOFF_control);
                    }
                    t += 0.005;
                }
                vel[j_iter][t_iter + 1] = tempdPt;
                acc[j_iter][t_iter + 1] = tempddPt;

                IsReady = true;
            }
        }
    }
    return IsReady;
}

void CalculateLIMITGripper()
{
    if(sharedSEN->EXF_L_Enabled || sharedSEN->EXF_R_Enabled)
    {
        if(DESIRED_Gripper == 0)
        {//default(max open or close)
            if(MODE_Gripper == GRIPPER_OPEN)
            {
                LIMIT_Gripper = -999;
            }else
            {
                LIMIT_Gripper = 0.;
            }
        }else
        {
            double MaxOpenGripperEncoder = -99999;
            double MaxOpenGripperDistance = 125;

            LIMIT_Gripper = (DESIRED_Gripper*MaxOpenGripperEncoder)/MaxOpenGripperDistance;
        }
    }else
    {
        if(MODE_Gripper == GRIPPER_OPEN)
        {
            LIMIT_Gripper = -1990.;
        }else
        {
            LIMIT_Gripper = 0.;
        }
    }
    printf("Desired_Distance : %f\nDesired_Encoder : %f\n",DESIRED_Gripper,LIMIT_Gripper);

}

void ROS_Joint_Publish()
{
    if(FLAG_JointPublish == true)
    {
        switch(STATE_JointPublish)
        {
        case PUB_DONE:
        {//First call
            joint->RefreshToCurrentReference(ARMonly);
//            usleep(500*1000);
            joint->SetAllMotionOwner();

            FILE_LOG(logSUCCESS) << "JOINT PUBLISH START!!!";
            if(sharedROS->state_arm == ROBOT_JOINT_PUBLISHED)
                STATE_JointPublish = PUB_START;
            else
                STATE_JointPublish = PUB_TRAJECTORY;
            break;
        }
        case PUB_START:
        {
            PushJointReference();
            break;
        }
        case PUB_TRAJECTORY:
        {
            PushJointTrajectory();
            break;
        }
        }
    }else if(FLAG_JointPublish == false && STATE_JointPublish != PUB_DONE)
    {
        FILE_LOG(logSUCCESS) << "JOINT PUBLISH DONE!!!";
        STATE_JointPublish = PUB_DONE;
    }
}

void PushJointReference()
{
    for(int i=0;i<NUM_JOINTS;i++)
    {
        if(sharedROS->COMMAND.CMD_JOINT != MODE_MOVE_JOINT && sharedROS->COMMAND.CMD_JOINT != MODE_SET_WBIK)
        {
            if(sharedROS->Arm_action.joint[i].ONOFF_control == CONTROL_ON)
            {
                double _ref = sharedROS->Arm_action.joint[i].reference;
                if(i==rosREB || i==rosLEB)
                {
                    _ref += 20.0;
                }
                if(i==rosRSR) _ref += 15.0;
                if(i==rosLSR) _ref -= 15.0;
                joint->SetJointRefAngle(TransNum[i], _ref);

            }
        }
        sharedROS->joint_before[i] = sharedROS->Arm_action.joint[i];
    }

}

void PushJointReference2()
{
    for(int i=0;i<NUM_JOINTS;i++)
    {
        if(sharedROS->COMMAND.CMD_JOINT != MODE_MOVE_JOINT && sharedROS->COMMAND.CMD_JOINT != MODE_SET_WBIK)
        {
            if(sharedROS->Arm_action.joint[i].ONOFF_control == CONTROL_ON)
            {
                if(sharedROS->Arm_action.joint[i].reference == sharedROS->joint_before[i].reference)
                    continue;

                double _ref = sharedROS->Arm_action.joint[i].reference;
                if(i==rosREB || i==rosLEB)
                {
                    _ref += 20.0;
                }
                if(i==rosRSR) _ref += 15.0;
                if(i==rosLSR) _ref -= 15.0;
                joint->SetJointRefAngle(TransNum[i], _ref);

            }
        }
        sharedROS->joint_before[i] = sharedROS->Arm_action.joint[i];
    }
}

void PushJointTrajectory()
{
    if(sharedROS->COMMAND.CMD_JOINT != MODE_MOVE_JOINT && sharedROS->COMMAND.CMD_JOINT != MODE_SET_WBIK)
    {
        int emptycnt = 0;
        for(int i=0;i<NUM_JOINTS;i++)
        {
            if(IsONOFF[i].s.empty())
            {
//                printf("%d th vector is empty\n",i);
                emptycnt++;
                continue;
            }

            if(IsONOFF[i].s.first() == CONTROL_ON)
            {
                double _ref = Pt[i].p.first();
                double _vel = dPt[i].p.first();
                double _acc = ddPt[i].p.first();

                IsONOFF[i].s.pop_front();
                Pt[i].p.pop_front();
                dPt[i].p.pop_front();
                ddPt[i].p.pop_front();

                if(i==rosREB || i==rosLEB)
                {
                    _ref += 20.0;
                }
                if(i==rosRSR) _ref += 15.0;
                if(i==rosLSR) _ref -= 15.0;

                joint->SetJointRefAngle(TransNum[i], _ref);
//                printf("setjoinref\n");
                curPt[i] = _ref;
//                printf("curPt push\n");
                curdPt[i] = _vel;
                curddPt[i] = _acc;

            }
        }

        if(emptycnt == NUM_JOINTS)
        {
            printf("every joint vector is empty!!!!!!\n");
            FLAG_trajectory = true;
            FLAG_JointPublish = false;
            sharedROS->state_arm = ROBOT_NOT_MOVE;
        }
    }
}

void SetMoveJoint()
{
    FILE_LOG(logSUCCESS) << "MOVE JOINT START!!!";
    for(int i=0;i<NUM_JOINTS;i++)
    {
        if(sharedROS->Arm_action.joint[i].ONOFF_control == CONTROL_ON)
        {
            joint->SetMoveJoint(TransNum[i], sharedROS->Arm_action.joint[i].reference, sharedROS->Arm_action.joint[i].GoalmsTime, MODE_ABSOLUTE);
            printf("%d cur = %f, ref = %f\n",i, sharedSEN->ENCODER[MC_ID_CH_Pairs[REB].id][MC_ID_CH_Pairs[REB].ch].CurrentReference,sharedROS->Arm_action.joint[i].reference);
        }
    }

    sharedROS->state_arm = ROBOT_MOVING_JOINT;
}

void SetWBIK()
{
    FILE_LOG(logSUCCESS) << "MOVE WBIK START!!!";

    int tempNum = RIGHT_HAND;
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_movepos == CONTROL_ON)
        WBmotion->addRHPosInfo(sharedROS->Arm_action.wbik[tempNum].Goal_pos[0], sharedROS->Arm_action.wbik[tempNum].Goal_pos[1], sharedROS->Arm_action.wbik[tempNum].Goal_pos[2], sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_moveori == CONTROL_ON)
    {
        doubles tempQuat(4);
        for(int i=0;i<4;i++)
        {
            tempQuat[i] = sharedROS->Arm_action.wbik[tempNum].Goal_quat[i];
        }
        WBmotion->addRHOriInfo(tempQuat, sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
    }

    tempNum = LEFT_HAND;
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_movepos == CONTROL_ON)
        WBmotion->addLHPosInfo(sharedROS->Arm_action.wbik[tempNum].Goal_pos[0], sharedROS->Arm_action.wbik[tempNum].Goal_pos[1], sharedROS->Arm_action.wbik[tempNum].Goal_pos[2], sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_moveori == CONTROL_ON)
    {
        doubles tempQuat(4);
        for(int i=0;i<4;i++)
        {
            tempQuat[i] = sharedROS->Arm_action.wbik[tempNum].Goal_quat[i];
        }
        WBmotion->addLHOriInfo(tempQuat, sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
    }

    tempNum = PEL;
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_movepos == CONTROL_ON)
    {
        WBmotion->addCOMInfo(sharedROS->Arm_action.wbik[tempNum].Goal_pos[0], sharedROS->Arm_action.wbik[tempNum].Goal_pos[1], sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
        WBmotion->addPELPosInfo(sharedROS->Arm_action.wbik[tempNum].Goal_pos[2], sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
    }
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_moveori == CONTROL_ON)
    {
        doubles tempQuat(4);
        for(int i=0;i<4;i++)
        {
            tempQuat[i] = sharedROS->Arm_action.wbik[tempNum].Goal_quat[i];
        }
        WBmotion->addPELOriInfo(tempQuat, sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
    }

    tempNum = WAIST;
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_movepos == CONTROL_ON)
    {
        WBmotion->addWSTPosInfo(sharedROS->Arm_action.wbik[tempNum].Goal_angle, sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);
    }
    tempNum = RIGHT_ELBOW;
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_movepos == CONTROL_ON)
        WBmotion->addRElbPosInfo(sharedROS->Arm_action.wbik[tempNum].Goal_angle, sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);

    tempNum = LEFT_ELBOW;
    if(sharedROS->Arm_action.wbik[tempNum].ONOFF_movepos == CONTROL_ON)
        WBmotion->addLElbPosInfo(sharedROS->Arm_action.wbik[tempNum].Goal_angle, sharedROS->Arm_action.wbik[tempNum].GoalmsTime/1000);

}

void save()
{
    if(Save_Index < ROW)
    {
        Save_Data[0][Save_Index] = sharedROS->ROSindex;
        Save_Data[1][Save_Index] = sharedROS->Arm_action.joint[rosRSP].reference;
        Save_Data[2][Save_Index] = sharedROS->Arm_action.wbik[RIGHT_HAND].Goal_pos[0];
        Save_Data[3][Save_Index] = sharedROS->Base_action.wheel.MoveX;

        Save_Data[4][Save_Index] = sharedROS->Arm_feedback.joint[rosRSP].reference;
        Save_Data[5][Save_Index] = sharedROS->Arm_feedback.wbik[RIGHT_HAND].Goal_pos[0];
        Save_Data[6][Save_Index] = sharedROS->Base_feedback.wheel.MoveX;

        Save_Data[7][Save_Index] = sharedSEN->ENCODER[MC_ID_CH_Pairs[WST].id][MC_ID_CH_Pairs[WST].ch].CurrentReference;
        Save_Data[8][Save_Index] = sharedROS->Arm_feedback.wbik[WAIST].Goal_angle;
        Save_Data[9][Save_Index] = sharedROS->joint_before[rosWST].reference;
        Save_Data[10][Save_Index] = sharedROS->joint_before[rosREB].reference;
        Save_Data[11][Save_Index] = sharedROS->Arm_action.joint[rosWST].reference;

        Save_Data[12][Save_Index] = sharedSEN->ENCODER[MC_ID_CH_Pairs[RSP].id][MC_ID_CH_Pairs[RSP].ch].CurrentReference;
        Save_Data[13][Save_Index] = curPt[rosRSP];
        Save_Data[14][Save_Index] = curdPt[rosRSP];
        Save_Data[15][Save_Index] = curddPt[rosRSP];
        Save_Data[16][Save_Index] = joint->GetJointRefAngle(RSP);
        Save_Data[17][Save_Index] = sharedREF->JointReference[PODO_NO][MC_ID_CH_Pairs[RSP].id][MC_ID_CH_Pairs[RSP].ch];
        Save_Data[18][Save_Index] = sharedCMD->MotionOwner[MC_ID_CH_Pairs[RSP].id][MC_ID_CH_Pairs[RSP].ch];
        Save_Index++;
        if(Save_Index >= ROW) Save_Index = 0;
    }
}


//***********************************************************
//******************** DRILL MOTIONS ************************
//***********************************************************
void GotoHomePos(){
    double postime = 3000.0;
    for(int i=0; i<NO_OF_JOINTS; i++)
        joint->SetMoveJoint(i, 0.0, postime, MOVE_ABSOLUTE);
}

void GotoWalkReadyPos(){
    double postime = 3000.0;

    WB_FLAG = false;

    joint->SetMoveJoint(RSP,    40.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(RSR,    10.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(RSY,     0.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(REB,  -130.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(RWY,     0.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(RWP,    20.0, postime, MOVE_ABSOLUTE);

    joint->SetMoveJoint(LSP,    40.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LSR,   -10.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LSY,     0.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LEB,  -130.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LWY,     0.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LWP,    20.0, postime, MOVE_ABSOLUTE);

    joint->SetMoveJoint(WST,     0.0, postime, MOVE_ABSOLUTE);

    joint->SetMoveJoint(RWY2,    0.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(RHAND,   0.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LWY2,    0.0, postime, MOVE_ABSOLUTE);
    joint->SetMoveJoint(LHAND,   0.0, postime, MOVE_ABSOLUTE);
}

void SetOriHand(doubles &target, double _pitch, double _yaw)
{
    quat pelori = quat(vec3(0,0,1), _yaw*D2R)*quat(vec3(0,1,0), _pitch*D2R);
    for(int i=0;i<4;i++)
    {
        target[i] = pelori[i];
    }
}

void SetOriHand_YP(doubles &target, double _pitch, double _yaw) //_YawPitch
{
    quat pelori = quat(vec3(0,1,0), _pitch*D2R)*quat(vec3(0,0,1), _yaw*D2R);
    for(int i=0;i<4;i++)
    {
        target[i] = pelori[i];
    }
}


//JOYSTICK
void ResetJOY()
{
    GL_JOY_A = 0;
    GL_JOY_B = 0;
    GL_JOY_X = 0;
    GL_JOY_Y = 0;
    GL_JOY_AROW_RL = 0;
    GL_JOY_AROW_UD = 0;
    GL_JOY_RT = 0;
    GL_JOY_LT = 0;
    GL_JOY_RB = 0;
    GL_JOY_LB = 0;

    GL_JOY_RJOG_PUSH = 0;
    GL_JOY_RJOG_UD = 0;
    GL_JOY_RJOG_RL = 0;

    GL_JOY_LJOG_PUSH = 0;
    GL_JOY_LJOG_UD = 0;
    GL_JOY_LJOG_RL = 0;

    GL_JOY_BACK = 0;
    GL_JOY_START = 0;
    GL_JOY_LOGITECH = 0;

    for(int i=0; i<120; i++)
    {
        pushData(RWHList, 0.0);
        pushData(LWHList, 0.0);
        pushData(BWHList, 0.0);
    }
}

/******************************************************************************/

void StartWBIKmotion(int _mode)
{
    WB_FLAG = false;
    usleep(10*1000);

    joint->RefreshToCurrentReference(ARMonly);

    WBmotion->ResetGlobalCoord(_mode);

    WBmotion->StopAll();

    WBmotion->RefreshToCurrentReference();

    usleep(500*1000);
    joint->SetAllMotionOwner();

    WB_FLAG = true;
}

int CheckMotionOwned()
{
    for(int i=0;i<NO_OF_JOINTS;i++)
    {
        if(sharedCMD->MotionOwner[MC_ID_CH_Pairs[i].id][MC_ID_CH_Pairs[i].ch]!=PODO_NO)	return 0;
    }
    return 1;
}

int HasAnyOwnership()
{
    for(int i=0; i<NO_OF_JOINTS; i++)
    {
        if(sharedCMD->MotionOwner[MC_ID_CH_Pairs[i].id][MC_ID_CH_Pairs[i].ch] == PODO_NO)
            return true;
    }
    return false;
}

void CatchSignals(int _signal)
{
    switch(_signal)
    {
    case SIGHUP:
    case SIGINT:     // Ctrl-c
    case SIGTERM:    // "kill" from shell
    case SIGKILL:
    case SIGSEGV:
        isTerminated = -1;
        break;
    }
    usleep(1000*500);
}

int RBInitialize(void)
{
    // Block program termination
    isTerminated = 0;

    int shmFD;
    // Core Shared Memory Creation [Reference]==================================
    shmFD = shm_open(RBCORE_SHM_NAME_REFERENCE, O_RDWR, 0666);
    if(shmFD == -1)
    {
        FILE_LOG(logERROR) << "Fail to open core shared memory [Reference]";
        return false;
    }else
    {
        if(ftruncate(shmFD, sizeof(RBCORE_SHM_REFERENCE)) == -1)
        {
            FILE_LOG(logERROR) << "Fail to truncate core shared memory [Reference]";
            return false;
        }else
        {
            sharedREF = (pRBCORE_SHM_REFERENCE)mmap(0, sizeof(RBCORE_SHM_REFERENCE), PROT_WRITE, MAP_SHARED, shmFD, 0);
            if(sharedREF == (void*)-1)
            {
                FILE_LOG(logERROR) << "Fail to mapping core shared memory [Reference]";
                return false;
            }
        }
    }
    FILE_LOG(logSUCCESS) << "Core shared memory creation = OK [Reference]";
    // =========================================================================

    // Core Shared Memory Creation [Sensor]=====================================
    shmFD = shm_open(RBCORE_SHM_NAME_SENSOR, O_RDWR, 0666);
    if(shmFD == -1)
    {
        FILE_LOG(logERROR) << "Fail to open core shared memory [Sensor]";
        return false;
    }else{
        if(ftruncate(shmFD, sizeof(RBCORE_SHM_SENSOR)) == -1)
        {
            FILE_LOG(logERROR) << "Fail to truncate core shared memory [Sensor]";
            return false;
        }else
        {
            sharedSEN = (pRBCORE_SHM_SENSOR)mmap(0, sizeof(RBCORE_SHM_SENSOR), PROT_READ, MAP_SHARED, shmFD, 0);
            if(sharedSEN == (void*)-1)
            {
                FILE_LOG(logERROR) << "Fail to mapping core shared memory [Sensor]";
                return false;
            }
        }
    }
    FILE_LOG(logSUCCESS) << "Core shared memory creation = OK [Sensor]";
    // =========================================================================

    // Core Shared Memory Creation [Command]====================================
    shmFD = shm_open(RBCORE_SHM_NAME_COMMAND, O_RDWR, 0666);
    if(shmFD == -1){
        FILE_LOG(logERROR) << "Fail to open core shared memory [Command]";
        return false;
    }else{
        if(ftruncate(shmFD, sizeof(RBCORE_SHM_COMMAND)) == -1){
            FILE_LOG(logERROR) << "Fail to truncate core shared memory [Command]";
            return false;
        }else{
            sharedCMD = (pRBCORE_SHM_COMMAND)mmap(0, sizeof(RBCORE_SHM_COMMAND), PROT_READ|PROT_WRITE, MAP_SHARED, shmFD, 0);
            if(sharedCMD == (void*)-1){
                FILE_LOG(logERROR) << "Fail to mapping core shared memory [Command]";
                return false;
            }
        }
    }
    FILE_LOG(logSUCCESS) << "Core shared memory creation = OK [Command]";
    // =========================================================================


    // User Shared Memory Creation ============================================
    shmFD = shm_open(USER_SHM_NAME, O_RDWR, 0666);
    if(shmFD == -1){
        FILE_LOG(logERROR) << "Fail to open user shared memory";
        return -1;
    }else{
        if(ftruncate(shmFD, sizeof(USER_SHM)) == -1){
            FILE_LOG(logERROR) << "Fail to truncate user shared memory";
            return -1;
        }else{
            userData = (pUSER_SHM)mmap(0, sizeof(USER_SHM), PROT_READ|PROT_WRITE, MAP_SHARED, shmFD, 0);
            if(userData == (void*)-1){
                FILE_LOG(logERROR) << "Fail to mapping user shared memory";
                return -1;
            }
        }
    }
    FILE_LOG(logSUCCESS) << "User shared memory creation = OK";
    // =========================================================================

    // User Shared Memory Creation ============================================
    shmFD = shm_open(ROS_SHM_NAME, O_RDWR, 0666);
    if(shmFD == -1){
        FILE_LOG(logERROR) << "Fail to open ros shared memory";
        return -1;
    }else{
        if(ftruncate(shmFD, sizeof(ROS_SHM)) == -1){
            FILE_LOG(logERROR) << "Fail to truncate ros shared memory";
            return -1;
        }else{
            sharedROS = (pROS_SHM)mmap(0, sizeof(ROS_SHM), PROT_READ|PROT_WRITE, MAP_SHARED, shmFD, 0);
            if(sharedROS == (void*)-1){
                FILE_LOG(logERROR) << "Fail to mapping ros shared memory";
                return -1;
            }
        }
    }
    FILE_LOG(logSUCCESS) << "ROS shared memory creation = OK";
    // =========================================================================

    // Initialize internal joint classes =======================================
    joint = new JointControlClass(sharedREF, sharedSEN, sharedCMD, sharedROS, PODO_NO);
    joint->RefreshToCurrentReference();
    // =========================================================================


    // Create and start real-time thread =======================================
    if(rt_task_create(&rtFlagCon, "ROScommand_FLAG", 0, 95, 0) == 0){
        cpu_set_t aCPU;
        CPU_ZERO(&aCPU);
        CPU_SET(3, &aCPU);
        if(rt_task_set_affinity(&rtFlagCon, &aCPU) != 0){
            FILE_LOG(logWARNING) << "Flag real-time thread set affinity CPU failed..";
        }
        if(rt_task_start(&rtFlagCon, &RBFlagThread, NULL) == 0 ){
            FILE_LOG(logSUCCESS) << "Flag real-time thread start = OK";
        }else{
            FILE_LOG(logERROR) << "Flag real-time thread start = FAIL";
            return -1;
        }
    }else{
        FILE_LOG(logERROR) << "Fail to create Flag real-time thread";
        return -1;
    }

    if(rt_task_create(&rtTaskCon, "ROScommand_TASK", 0, 90, 0) == 0){
        cpu_set_t aCPU;
        CPU_ZERO(&aCPU);
        CPU_SET(2, &aCPU);
        if(rt_task_set_affinity(&rtTaskCon, &aCPU) != 0){
            FILE_LOG(logWARNING) << "Task real-time thread set affinity CPU failed..";
        }
        if(rt_task_start(&rtTaskCon, &RBTaskThread, NULL) == 0 ){
            FILE_LOG(logSUCCESS) << "Task real-time thread start = OK";
        }else{
            FILE_LOG(logERROR) << "Task real-time thread start = FAIL";
            return -1;
        }
    }else{
        FILE_LOG(logERROR) << "Fail to create Task real-time thread";
        return -1;
    }
    // =========================================================================

    //----JoyStick Thread------------------
    if(rt_task_create(&rtJoystickCon, "JOYSTICK_THREAD", 0, 90, 0) == 0){
        if(rt_task_start(&rtJoystickCon, &JoystickThread, NULL) == 0 ){
            FILE_LOG(logSUCCESS) << "Joystick real-time thread start = OK";
        }else{
            FILE_LOG(logERROR) << "Joystick real-time thread start = FAIL";
            return -1;
        }
    }else{
        FILE_LOG(logERROR) << "Fail to create Task real-time thread";
        return -1;
    }
    // =========================================================================

    return 0;
}


//WAIT TIME
void SetWaitTime(int mode, double time)
{
    Mode_TOOL = DRILL_WAIT;
    WaitCount = 0;
    WaitMode = mode;
    WaitTime = time;
}

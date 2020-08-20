#ifndef ROSCOMMAND_H
#define ROSCOMMAND_H

#define ROS_SHM_NAME        "ROS_SHARED_MEMORY"


enum ROS2PODO_COMMAND
{
    CMD_NOTHING = 0,
    CMD_MOVE_JOINT,
    CMD_MOVE_GRIPPER,
    CMD_MOVE_BASE
};

enum MOVEJOINT_MODE
{
    MODE_BREAK = 0,
    MODE_JOINT_PUBLISH,
    MODE_MOVE_JOINT,
    MODE_SET_WBIK
};

enum MOVEGRIPPER_MODE
{
    GRIPPER_STOP = 0,
    GRIPPER_OPEN,
    GRIPPER_CLOSE
};

enum MOVEWHEEL_MODE
{
    WHEELMOVE_STOP = 0,
    WHEELMOVE_
};

enum MOVEGRIPPER_PARA
{
    GRIPPER_BOTH = 0,
    GRIPPER_RIGHT,
    GRIPPER_LEFT
};

enum
{
    CONTROL_OFF = 0, CONTROL_ON
};

enum JOINTNUMBER
{
    rosRSP=0, rosRSR, rosRSY, rosREB, rosRWY, rosRWP, rosRWY2,
    rosLSP, rosLSR, rosLSY, rosLEB, rosLWY, rosLWP, rosLWY2,
    rosWST, rosRWH, rosLWH, rosBWH, NUM_JOINTS
};

enum PARTNUMBER
{
    RIGHT_HAND = 0, RIGHT_ELBOW, LEFT_HAND, LEFT_ELBOW,
    PEL, WAIST, NUM_PARTS
};

typedef struct _JOINT_DATA_
{
    int ONOFF_control;
    double reference;
    double GoalmsTime;
}JOINT_DATA;

typedef struct _WBIK_DATA_
{
    int ONOFF_movepos;
    int ONOFF_moveori;
    double Goal_pos[3];
    double Goal_quat[4];
    double Goal_angle;
    double GoalmsTime;
}WBIK_DATA;

typedef struct _WHEELMOVE_DATA_
{
    double MoveX;
    double MoveY;
    double ThetaDeg;
}WHEELMOVE_DATA;

typedef struct _ROS2PODO_DATA_
{
    int ROS_CMD;
    int ROS_MODE;
    int ROS_PARA_INT;

    JOINT_DATA joint[NUM_JOINTS];
    WBIK_DATA  wbik[NUM_PARTS];
    WHEELMOVE_DATA wheelmove;
}ROS2PODO_DATA;

typedef struct _ROS_SHM_
{
    ROS2PODO_DATA R2P;
}ROS_SHM, *pROS_SHM;

typedef struct _PODO2ROS_DATA_
{

}PODO2ROS_DATA;



#endif // COMMAND_H

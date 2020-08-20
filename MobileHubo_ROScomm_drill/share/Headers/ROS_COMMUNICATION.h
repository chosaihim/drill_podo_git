#ifndef ROSCOMM_H
#define ROSCOMM_H

#define ROS_SHM_NAME        "ROS_SHARED_MEMORY"

#include "ROS_COMMAND.h"
#include "ROS_DATA.h"
#include "PODO_STATE.h"
#include <QVector>

typedef struct _ROS2PODO_DATA_
{
    JOINTMOVE_CMD       CMD_JOINT;
    GRIPPERMOVE_CMD     CMD_GRIPPER;
    WHEELMOVE_CMD       CMD_WHEEL;

    MANIPULATOR_ACTION  Arm_action;
    BASE_ACTION         Base_action;
    GRIPPER_ACTION      Gripper_action;

    int index;
}ROS2PODO_DATA;

typedef struct _PODO2ROS_DATA_
{
    MANIPULATOR_ACTION  Arm_feedback;
    BASE_ACTION         Base_feedback;
    GRIPPER_ACTION      Gripper_feedback;

    SENSOR_DATA sensor;
    ROBOT_STATE_ARM  state_arm;
    ROBOT_STATE_BASE state_base;

    int index;
}PODO2ROS_DATA;

typedef struct _ROS_JOINTREF_
{
    JOINT_DATA ref[NUM_JOINTS];
    int DoneFlag;
    int StartFlag;
}__attribute__((packed))ROS_JOINTREF;

typedef QVector<ROS_JOINTREF>   ROS_JOINTREFs;

typedef struct _ROS_SHM_
{
    ROS_COMMAND COMMAND;

    int ROSindex;
    int DoneFlag;
    MANIPULATOR_ACTION  Arm_action;
    BASE_ACTION         Base_action;
    GRIPPER_ACTION      Gripper_action;

    MANIPULATOR_ACTION  Arm_feedback;
    BASE_ACTION         Base_feedback;
    GRIPPER_ACTION      Gripper_feedback;

    JOINT_DATA joint_before[NUM_JOINTS];

    ROBOT_STATE_ARM  state_arm;
    ROBOT_STATE_BASE state_base;

    float                   *refs_Addr;
    ROS_JOINTREFs            *refs;
    ROS_JOINTREFs            refs_interpolated;
    ROS_JOINTREF             ref;
    ROS_JOINTREF            refarray[200];
    ROS_JOINTREFs::iterator  refsIter;
    int                      refsLen;
    double                   refsGoalTime[NUM_JOINTS];
}ROS_SHM, *pROS_SHM;


#endif // ROSCOMM_H

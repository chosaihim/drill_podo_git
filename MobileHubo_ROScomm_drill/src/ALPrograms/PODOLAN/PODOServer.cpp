#include "PODOServer.h"

PODO_GUI_Server::PODO_GUI_Server()
{
    //dataSize = sizeof(USER_COMMAND);
    dataSize = sizeof(LAN_GUI2PODO);
    dataReceived.clear();
    RBData.resize(dataSize);
}

void PODO_GUI_Server::RBReadData(){
    QDataStream in(RBTcpClient);
    in.setVersion(QDataStream::Qt_5_2);

    if(RBTcpClient->bytesAvailable() < dataSize)
        return;

    while(RBTcpClient->bytesAvailable() >= dataSize){
        in.readRawData(RBData.data(), dataSize);
        dataReceived.push_back(RBData);
    }
}


// =========================================

PODO_VISION_Server::PODO_VISION_Server()
{
    dataSize = sizeof(LAN_VISION2PODO);
    dataReceived.clear();
    RBData.resize(dataSize);
}

void PODO_VISION_Server::RBReadData(){
    QDataStream in(RBTcpClient);
    in.setVersion(QDataStream::Qt_5_2);

    if(RBTcpClient->bytesAvailable() < dataSize)
        return;

    while(RBTcpClient->bytesAvailable() >= dataSize){
        in.readRawData(RBData.data(), dataSize);
        dataReceived.push_back(RBData);
    }
}

// =========================================

ROS_CMD_Server::ROS_CMD_Server()
{
    dataSize = sizeof(LAN_R2M_CMD);
    dataReceived.clear();
    RBData.resize(dataSize);
}

void ROS_CMD_Server::RBReadData()
{
    QDataStream in(RBTcpClient);
    in.setVersion(QDataStream::Qt_5_2);

    if(RBTcpClient->bytesAvailable() < dataSize)
        return;

    while(RBTcpClient->bytesAvailable() >= dataSize){
        in.readRawData(RBData.data(), dataSize);
        dataReceived.push_back(RBData);
    }
}
// =========================================


PODO_ROS_Server::PODO_ROS_Server()
{
//    printf("size of ros2podo data = %d\n",sizeof(ROS2PODO_DATA));
    dataSize = sizeof(LAN_ROS2PODO);
    dataReceived.clear();
    RBData.resize(dataSize);
}

void PODO_ROS_Server::RBReadData()
{
    QDataStream in(RBTcpClient);
    in.setVersion(QDataStream::Qt_5_2);
    printf("ROS Server dataSize = %d\n",dataSize);

    if(RBTcpClient->bytesAvailable() < dataSize)
    {
        printf("ROS Server data small : %d\n",RBTcpClient->bytesAvailable());
        return;
    }

    while(RBTcpClient->bytesAvailable() >= dataSize){
        printf("ROS Server data read : %d\n",RBTcpClient->bytesAvailable());
        in.readRawData(RBData.data(), dataSize);
        dataReceived.push_back(RBData);
    }
}

Ref_Receive_Server::Ref_Receive_Server()
{
    dataSize = sizeof(LAN_JOINTREF);
    dataReceived.clear();
    RBData.resize(dataSize);
}

void Ref_Receive_Server::RBReadData()
{
//    printf("ReadData\n");
    printf("dataSize = %d\n",dataSize);
    QDataStream in(RBTcpClient);
    in.setVersion(QDataStream::Qt_5_2);

    if(RBTcpClient->bytesAvailable() < dataSize)
    {
        printf("data size small : %d\n",RBTcpClient->bytesAvailable());
        return;
    }

    while(RBTcpClient->bytesAvailable() >= dataSize)
    {
        printf("data read : %d\n",RBTcpClient->bytesAvailable());
        in.readRawData(RBData.data(), dataSize);
        dataReceived.push_back(RBData);
    }
}

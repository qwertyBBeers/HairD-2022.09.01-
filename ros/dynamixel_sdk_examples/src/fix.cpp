#include <ros/ros.h>

#include "std_msgs/String.h"
#include "dynamixel_sdk_examples/SetPosition.h" //msg 타입
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <string>

std::string mesg="";

void StartCallback(const std_msgs::String::ConstPtr& msg)
{
    if (msg->data=="open"){
        mesg ="open";
    }
    if (msg->data=="close"){
        mesg ="close";
    }

}

void Open(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    
    set.id = 7;
    set.position=0;   
    set_position_pub1.publish(set);

    set.id = 8;
    set.position=0;
    set_position_pub1.publish(set);

    set.id = 9;
    set.position=0;
    set_position_pub1.publish(set);

    mesg=""; 
}

void Close(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    
    set.id = 7;
    set.position=0;   
    set_position_pub1.publish(set);

    set.id = 8;
    set.position=0;
    set_position_pub1.publish(set);

    set.id = 9;
    set.position=0;
    set_position_pub1.publish(set);
    
    mesg="";
}





int main(int argc,char **argv){
    ros::init(argc,argv,"Dynamixel_fix");
    ros::NodeHandle nh;
    ros::Publisher set_position_pub1 =nh.advertise<dynamixel_sdk_examples::SetPosition>("/set_position",10);
    //ros::Publisher clean_pub = nh.advertise<std_msgs::String>("fix_info",1000);
    ros::Subscriber clean_sub = nh.subscribe<std_msgs::String>("fix",1000,StartCallback);
    std_msgs::String st;
    dynamixel_sdk_examples::SetPosition set;
    ros::Rate loop_rate(10);
        


    while(ros::ok()){
        if(mesg=="open"){
            ROS_INFO("open");
            Open(set,set_position_pub1);
        }else if(mesg =="close"){
            ROS_INFO("close");
            Close(set,set_position_pub1);
        }else{
            ROS_INFO("wait");
        }
        
        
        ros::spinOnce();
        loop_rate.sleep();
    }
}

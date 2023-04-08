#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <omo_r1_bringup/yolo_check.h>
#include <omo_r1_bringup/navigation_check.h>


class robot_con
{
  public:
    std::string qt_con= 0;                   //1, 2, 3
    std::string nav_con = "before";          //before, proceeding, done
    std::string bbangle_con = "before";      //before, proceeding, done
    std::string yolo_con = "before";         //yet, detected, done
    int flag = 0;                            //0, 1
};

robot_con con = robot_con();



void qtCallback(const std_msgs::String::ConstPtr& msg)
{
  if(con.flag == 0){
    con.qt_con = msg->data.c_str();
    con.flag = 1;
  }
}

void navCallback(const std_msgs::String::ConstPtr& msg)
{
  con.nav_con = msg->data.c_str();
}

void bbangleCallback(const std_msgs::String::ConstPtr& msg)
{
  con.bbangle_con = msg->data.c_str();
}

void yoloCallback(const std_msgs::String::ConstPtr& msg)
{
  con.bbangle_con = msg->data.c_str();
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "haird_maincode");
  ros::NodeHandle nh;

  ros::Publisher navStart_pub = nh.advertise<std_msgs::String>("nav_start", 1000);
  ros::Publisher bbangleStart_pub = nh.advertise<std_msgs::String>("bbangle_start", 1000);


  ros::Subscriber qt_sub = nh.subscribe("qt_info", 1000, qtCallback);
  ros::Subscriber nav_sub = nh.subscribe("nav_info", 1000, navCallback);
  ros::Subscriber bbangle_sub = nh.subscribe("bbangle_info", 1000, bbangleCallback);
  ros::Subscriber yolo_sub = nh.subscribe("yolo_info", 1000, yoloCallback);
  
  ros::Rate rate(10);
  while (ros::ok())
  {
    
    if (con.flag == 1){
      if (con.nav_con == "before"){                                   //before cleaning
        std_msgs::String nav_msg;
        nav_msg.data = con.qt_con;
        navStart_pub.publish(nav_msg); 
      }
      if (con.nav_con == "done" && con.yolo_con == "detected"){       //Confirm marker detection after cleaning -> return to tray process
        std_msgs::String nav_msg;
        nav_msg.data = "stop";
        navStart_pub.publish(nav_msg); 
      }
      if (con.nav_con == "done" && con.yolo_con == "yet"){            //Marker detection failure after cleaning -> rotation operation for marker detection
        std_msgs::String nav_msg;
        nav_msg.data = "stop";
        navStart_pub.publish(nav_msg); 
        
        std_msgs::String bbangle_msg;
        bbangle_msg.data = "start";
        bbangleStart_pub.publish(bbangle_msg);
      }
      if (con.nav_con == "done" && con.yolo_con == "done"){           //return to tray complete
        std_msgs::String bbangle_msg;
        bbangle_msg.data = "stop";
        bbangleStart_pub.publish(bbangle_msg);
        
        con.flag = 0;   
      }
    } 
    
    rate.sleep();
  }

  return 0;
}

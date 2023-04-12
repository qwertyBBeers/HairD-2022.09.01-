#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <omo_r1_bringup/yolo_check.h>
#include <omo_r1_bringup/navigation_check.h>
#include "std_msgs/Int32.h"
#include <omo_r1_bringup/qt_check.h>


class robot_con
{
  public:
    int qt_con= 0;                           //1, 2, 3
    std::string nav_con = "before";          //before, proceeding, done
    std::string bbangle_con = "before";      //before, proceeding, done
    std::string yolo_con = "before";         //yet, detected, done
    std::string yolo_check = "stop";         //stop, start
    int flag = 0;                            //0, 1
};

robot_con con = robot_con();


// 서비스 핸들러 함수
bool qtServiceHandler(omo_r1_bringup::qt_check::Request& req, omo_r1_bringup::qt_check::Response& res)
{
    //ROS_INFO("Service Request: %s, Service Response: %s", req.request_data.c_str(), res.response_data.c_str()); // 로그 출력
    if(con.flag == 0)
    {
      con.qt_con = req.qt_req;
      con.flag = 1;
    }

    return true; // 서비스 요청 처리 성공
}




// void qtCallback(const std_msgs::String::ConstPtr& msg)
// {
//   if(con.flag == 0){
//     con.qt_con = std::stoi(msg->data.c_str());
//     con.flag = 1;
//   }
// }

void navCallback(const std_msgs::String::ConstPtr& msg)
{
  con.nav_con = msg->data.c_str();
  ROS_INFO("%s\n", msg->data.c_str());
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
  ros::init(argc, argv, "main_hair");
  ros::NodeHandle nh;

  ros::ServiceServer service_server = nh.advertiseService("qt_service", qtServiceHandler);

  ros::Publisher navStart_pub = nh.advertise<std_msgs::Int32>("nav_start", 1000);
  ros::Publisher bbangleStart_pub = nh.advertise<std_msgs::String>("bbangle_start", 1000);
  ros::Publisher yoloStart_pub = nh.advertise<std_msgs::String>("yolo_start", 1000);


  //ros::Subscriber qt_sub = nh.subscribe("qt_info", 1000, qtCallback);
  ros::Subscriber nav_sub = nh.subscribe("nav_info", 1000, navCallback);
  ros::Subscriber bbangle_sub = nh.subscribe("bbangle_info", 1000, bbangleCallback);
  ros::Subscriber yolo_sub = nh.subscribe("yolo_info", 1000, yoloCallback);
  
  ros::Rate rate(10);
  while (ros::ok())
  {
    
    if (con.flag == 1){
      if (con.nav_con == "before"){                                                           //before cleaning
        std_msgs::Int32 nav_msg;
        nav_msg.data = con.qt_con;
        navStart_pub.publish(nav_msg); 

        std_msgs::String bbangle_msg;
        bbangle_msg.data = "stop";
        bbangleStart_pub.publish(bbangle_msg);
      }
      if (con.nav_con == "done" && con.yolo_con == "detected"){                               //Confirm marker detection after cleaning -> return to tray process
        std_msgs::Int32 nav_msg;
        nav_msg.data = 10;
        navStart_pub.publish(nav_msg); 

        std_msgs::String bbangle_msg;
        bbangle_msg.data = "stop";
        bbangleStart_pub.publish(bbangle_msg);

        std_msgs::String yolo_msg;
        yolo_msg.data = "start";
        yoloStart_pub.publish(yolo_msg);
      }
      if (con.nav_con == "done" && con.yolo_con == "yet" && con.yolo_check == "start"){       //Marker detection failure -> rotation operation for marker detection
        std_msgs::Int32 nav_msg;
        nav_msg.data = 10;
        navStart_pub.publish(nav_msg); 
        
        std_msgs::String bbangle_msg;
        bbangle_msg.data = "start";
        bbangleStart_pub.publish(bbangle_msg);

        std_msgs::String yolo_msg;
        yolo_msg.data = "start";
        yoloStart_pub.publish(yolo_msg);
      }
      if (con.nav_con == "done" && con.yolo_con == "yet" && con.yolo_check == "stop"){        //after cleanong -> start yolo process
        std_msgs::Int32 nav_msg;
        nav_msg.data = 10;
        navStart_pub.publish(nav_msg); 
        
        std_msgs::String yolo_msg;
        yolo_msg.data = "start";
        yoloStart_pub.publish(yolo_msg);
        con.yolo_check == "start";
      }
      if (con.nav_con == "done" && con.yolo_con == "done"){                                   //return to tray complete
        std_msgs::String bbangle_msg;
        bbangle_msg.data = "stop";
        bbangleStart_pub.publish(bbangle_msg);

        std_msgs::String yolo_msg;
        yolo_msg.data = "stop";
        yoloStart_pub.publish(yolo_msg);
        con.yolo_check == "stop";

        std_msgs::Int32 nav_msg;
        nav_msg.data = 0;
        navStart_pub.publish(nav_msg);
        
        con.flag = 0;   
      }
    } 
    
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}

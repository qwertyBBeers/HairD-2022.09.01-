#!/usr/bin/env python3

import rospy
import actionlib
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from math import radians, degrees, pi, sin, cos
from actionlib_msgs.msg import *
from geometry_msgs.msg import PoseWithCovarianceStamped
from copy import deepcopy
import tf
import numpy as np
import time
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Int32
from std_msgs.msg import String
import threading

class con:
    def __init__(self):
        self.flag = 0
        self.a = 0
        self.list_stage = []
        self.listFlag = 0
        self.count = 0
        self.arm_info = 0


def callback(msg):
    global current_pose
    current_pose = msg


def cleanInfoCallback(msg):
    curr.arm_info = msg.data


def callbackRoom(data):
    stage = data.data
    print("stage: {} ", stage)
    if (stage == 100 and curr.flag == 0):
        tray_pose = current_pose

    print("flag: ",curr.flag)
    
    if(stage == 100 and curr.flag == 0 and curr.count == 0):
        #목적지 순서
        curr.list_stage = []

        # if stage == 11:
        #     c_x = -10
        #     c_y = -1
        # elif stage == 22:
        #     c_x = 1
        #     c_y = 1
        # elif stage == 33:
        #     c_x = 1
        #     c_y = 1
        c_x = 2.032741242737444                  #5gong
        c_y = 0.13712451358191208       ##### emptying place

        for i in range(1,9):
        #목적지 순서당 가지는 Goal 값
            if i == 1:
                # c_x = -1.9978294902364455
                # c_y = 1.5209675508127791
                hh_stage.stage_goal = [c_x, c_y, 0.025430730456035645, 0.9996765866761472]
            elif i == 2:
                # c_x = -1.9978294902364455
                # c_y = 1.5209675508127791
                hh_stage.stage_goal = [c_x, c_y, 0.025430730456035645, 0.9996765866761472]
            elif i == 3:
                # c_x = -1.9978294902364455
                # c_y = 1.5209675508127791
                hh_stage.stage_goal = [c_x, c_y, 0.025430730456035645, 0.9996765866761472]
            elif i == 4:
                # c_x = -1.9978294902364455
                # c_y = 1.5209675508127791
                hh_stage.stage_goal = [c_x, c_y, 0.025430730456035645, 0.9996765866761472]
            elif i == 5:
                # c_x = -1.9978294902364455
                # c_y = 1.5209675508127791
                hh_stage.stage_goal = [c_x, c_y, 0.025430730456035645, 0.9996765866761472]
            elif i == 6:
                c_x = tray_pose.pose.pose.position.x + 2.0
                c_y = tray_pose.pose.pose.position.y
                hh_stage.stage_goal = [c_x, c_y, tray_pose.pose.pose.orientation.z, tray_pose.pose.pose.orientation.w]
            elif i == 7:
                c_x = tray_pose.pose.pose.position.x + 2.0
                c_y = tray_pose.pose.pose.position.y
                hh_stage.stage_goal = [c_x, c_y, tray_pose.pose.pose.orientation.z, tray_pose.pose.pose.orientation.w]
            elif i == 8:
                c_x = tray_pose.pose.pose.position.x + 2.0
                c_y = tray_pose.pose.pose.position.y
                hh_stage.stage_goal = [c_x, c_y, tray_pose.pose.pose.orientation.z, tray_pose.pose.pose.orientation.w]

            curr.list_stage.append(hh_stage.stage_goal)
        if(len(curr.list_stage) == 8):
            curr.listFlag = 1



    if(stage == 100 and curr.listFlag == 1):
        curr.flag = 1
    if(stage > 5 and stage < 11):
        curr.flag = 0

    if (curr.flag == 0):
        if (stage == 0):
            nav_info_msg = "before"
            main_pub.publish(nav_info_msg)
            print("pub before")
            curr.count = 0
        elif (stage == 10):
            nav_info_msg = "done"
            main_pub.publish(nav_info_msg)
            curr.count = 0


    if(curr.flag == 1 and stage == 100 and curr.count == 0):
        print(curr.list_stage)
        goal_def(curr.list_stage)

class hh_stage:
    stage_goal = []


class GoalPose:
    x = 0.
    y = 0.
    theta = 0.
    z = 0.
    w = 0.

def move_to(goal_point):
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()

    print(curr.a)
    #print(len(stage_check))
    curr.a += 1 

    goal.target_pose.pose.orientation.x = 0
    goal.target_pose.pose.orientation.y = 0
    goal.target_pose.pose.orientation.z = goal_point.z
    goal.target_pose.pose.orientation.w = goal_point.w

    goal.target_pose.pose.position.x = goal_point.x
    goal.target_pose.pose.position.y = goal_point.y
    goal.target_pose.pose.position.z = 0

    print(goal)
    ac.send_goal(goal)

def goal_def(list_stage):
    goal_test = GoalPose()
    error = 0.5

    for i in range(8):
        stage_check = list_stage[i]
        goal_test.x = stage_check[0]
        goal_test.y = stage_check[1]
        goal_test.z = stage_check[2]
        goal_test.w = stage_check[3]
        nav_info_msg = "proceeding"
        main_pub.publish(nav_info_msg)
        
        move_to(goal_test)

        while((abs(current_pose.pose.pose.position.x - goal_test.x) > error) or (abs(current_pose.pose.pose.position.y - goal_test.y) > error)):
            pass
        print("b")
        if(i == 4):
            clean_msg = "empty_start"
            clean_pub.publish(clean_msg)
            print("pub arm")
            while(curr.arm_info == "yet"):
                print("waiting arm")
                print(curr.arm_info)
            curr.arm_info == "done"

    
    print("c")
    nav_info_msg = "done"
    main_pub.publish(nav_info_msg)
    curr.flag = 0
    curr.arm_info = 0
    curr.listFlag = 0
    curr.count += 1



# def main_process():
#     odom_sub = rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, callback)
#     tu_sub = rospy.Subscriber('nav_start_em', Int32, callbackRoom)


#     rospy.spin()

# def callback_process():
#     arm_sub = rospy.Subscriber('arm_info', String, ArmCallback)
#     rospy.spin()
    

if __name__=='__main__':
    current_pose = PoseWithCovarianceStamped()
    tray_pose = PoseWithCovarianceStamped()
    rospy.init_node('map_navigation_lis', anonymous=True)

    curr = con()
    main_pub = rospy.Publisher('nav_info_em', String, queue_size=10)
    clean_pub = rospy.Publisher('clean_start', String, queue_size=10)


    odom_sub = rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, callback)
    tu_sub = rospy.Subscriber('nav_start_em', Int32, callbackRoom)
    clean_sub = rospy.Subscriber('clean_info', String, cleanInfoCallback)


    ac = actionlib.SimpleActionClient("move_base", MoveBaseAction)
    ac.wait_for_server() # !!!!!!!!!!!!!!!!!!!!!!!!!!!

    # t1 = threading.Thread(target=main_process)
    # t2 = threading.Thread(target=callback_process)

    # t1.start()
    # t2.start()

    # t1.join()
    # t2.join()

    rospy.spin()
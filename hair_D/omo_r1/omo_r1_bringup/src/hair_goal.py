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
from std_msgs.msg import Int16


def callback(msg):
    global current_pose
    current_pose = msg

def callbackRoom(data):
    stage = data
    #목적지 순서
    list_stage = []
    
    for i in 8:
        #목적지 순서당 가지는 Goal 값
        if i == 1:
            hh_stage.stage_goal = [1, 2, 3, 4]
        elif i == 2:
            hh_stage.stage_goal = [1, 2, 3, 4]
        elif i == 3:
            hh_stage.stage_goal = [1, 2, 3, 4]
        elif i == 4:
            hh_stage.stage_goal = [1, 2, 3, 4]
        elif i == 5:
            hh_stage.stage_goal = [1, 2, 3, 4]
        elif i == 6:
            hh_stage.stage_goal = [1, 2, 3, 4]
        elif i == 7:
            hh_stage.stage_goal = [1, 2, 3, 4]
        elif i == 8:
            hh_stage.stage_goal = [1, 2, 3, 4]
        
        list_stage.append(hh_stage.stage_goal)
    
    goal_def(list_stage)

class hh_stage:
    stage_goal = []


class GoalPose:
    x = 0.
    y = 0.
    theta = 0.
    z = 0.
    w = 0.

def move_to(stage_check):
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()

    goal.target_pose.pose.orientation.x = 0
    goal.target_pose.pose.orientation.y = 0
    goal.target_pose.pose.orientation.z = stage_check[0]
    goal.target_pose.pose.orientation.w = stage_check[1]

    goal.target_pose.pose.position.x = stage_check[2]
    goal.target_pose.pose.position.y = stage_check[3]
    goal.target_pose.pose.position.z = 0

    # print(goal)
    ac.send_goal(goal)

def goal_def(list_stage):
    goal_test = GoalPose()
    error = 0.1

    for i in 8:
        stage_check = list_stage[i]

    # for room in stage:
    #     if room == 101:
    #         rospy.loginfo("101")
    #         goal_test.x = -1.73096152587
    #         goal_test.y = 0.651883785386
    #         goal_test.z = 0.213383708578
    #         goal_test.w = 0.976968478788
    #     elif room == 102:
    #         rospy.loginfo("102")
    #         goal_test.x = 1.75060760178
    #         goal_test.y = -0.279016830127
    #         goal_test.z = 0.657537242689
    #         goal_test.w = 0.753422042733
    #     elif room == 103:
    #         rospy.loginfo("103")
    #         goal_test.x = -1.73096152587
    #         goal_test.y = 0.651883785386
    #         goal_test.z = 0.213383708578
    #         goal_test.w = 0.976968478788
    #     elif room == 104:
    #         rospy.loginfo("104")
    #         goal_test.x = 1.75060760178
    #         goal_test.y = -0.279016830127
    #         goal_test.z = 0.657537242689
    #         goal_test.w = 0.753422042733
        move_to(stage_check)

        while((abs(current_pose.pose.pose.position.x - goal_test.x) > error) or (abs(current_pose.pose.pose.position.y - goal_test.y) > error)):
            pass

if __name__=='__main__':
    current_pose = PoseWithCovarianceStamped()
    rospy.init_node('map_navigation_lis', anonymous=True)
    odom_sub = rospy.Subscriber('/amcl_pose', PoseWithCovarianceStamped, callback)
    tu_sub = rospy.Subscriber('stage_info', Int16, callbackRoom)
    ac = actionlib.SimpleActionClient("move_base", MoveBaseAction)
    ac.wait_for_server() # !!!!!!!!!!!!!!!!!!!!!!!!!!!

    rospy.spin()
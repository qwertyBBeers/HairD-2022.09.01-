import rospy
from geometry_msgs.msg import Point
from geometry_msgs.msg import Twist
from std_msgs.msg import String


cen_x=0
cen_y=0
yolo_info = "yet"

def callback(data):
    # rospy.loginfo("centerpoint is %d %d ",data.x,data.y)
    global cen_x
    cen_x=data.x

    global cen_y
    cen_y=data.y
    # print(cen_x)

def yoloInfoCallback(data):
    # rospy.loginfo("centerpoint is %d %d ",data.x,data.y)
    global yolo_info
    yolo_info=data.data


def listener():
    rospy.init_node('qr_receive',anonymous = True)
    rospy.Subscriber("qr",Point,callback)
    rospy.Subscriber("yolo_info",String,yoloInfoCallback)
    cmd_pub = rospy.Publisher('cmd_vel',Twist,queue_size=10)
    rate =rospy.Rate(10)
    msg=Twist()

    vel =0.0
    while not rospy.is_shutdown():
        print(cen_x)
        if cen_x>304 and cen_x<400:    #차가 오른쪽으로 조금 더 가있음  -> 왼쪽으로 조금 회전
            ang = -0.1
        elif cen_x>=400:               
            ang = -0.13
        elif cen_x<296 and cen_x>200:
            ang = 0.1
        elif cen_x<=200 and cen_x>0:
            ang = 0.13
        else:
            ang = 0.0
        # if cen_y > 100:
        #     vel = -0.025
        # elif cen_y<100 and cen_y>10:
        #     vel = -0.015
        # else:
        #     vel = 0.0
        if cen_y <200:
            vel = 0.0
            ang = 0.0
        elif cen_y<260 and cen_y>= 200:
            vel = -0.02
            if ang > 0:
                ang = 0.05
            else:
                ang = -0.05
        else:
            vel = -0.02
        msg.angular.z = -ang 
        msg.linear.x = vel
        print(msg)
        print(yolo_info)
        if yolo_info == "detected":
            cmd_pub.publish(msg)
            print("pub-ing!")
        else:
            msg.angular.z = 0.0
            msg.linear.x = 0.0
            cmd_pub.publish(msg)
            print("pub-ing!")
        rate.sleep()

if __name__ == '__main__':
    
    listener()
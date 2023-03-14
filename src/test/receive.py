import rospy
from geometry_msgs.msg import Point

def callback(data):
    rospy.loginfo("centerpoint is %d %d",data.x,data.y)

def listener():

    rospy.init_node('qr_receive',anonymous =True)
    rospy.Subscriber("qr",Point,callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
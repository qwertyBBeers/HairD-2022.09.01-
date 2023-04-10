import rospy
from rospy_tutorials.srv import AddTwoInts


def client(st):
    rospy.wait_for_service('yolostart')
    try:

        yolostart = rospy.ServiceProxy('yolostart',AddTwoInts)
        resp = yolostart(st,0)
        return resp.sum
        
    except rospy.ROSInterruptException or KeyboardInterrupt or rospy.ServiceException as e:
        exit()  
if __name__ == '__main__':
    x=1
    print(client(x))
    
    
#include <ros/ros.h>

#include "std_msgs/String.h"
#include "dynamixel_sdk_examples/SetPosition.h" //msg 타입
#include "dynamixel_sdk_examples/sig_dy.h" //srv
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <string>

int start=0;
int number;
int time_count=0;
int init_position;
int degree[7]={0,0,0,0,0,0,0};
int count=0;


bool Start(
  dynamixel_sdk_examples::sig_dy::Request & req,
  dynamixel_sdk_examples::sig_dy::Response & res)
{
    ROS_INFO("servo1 에서 dynamixel %d",req.st);
    if(req.st==true){
        start=1;
    }else{
        start=0;
    }
    
}
void init(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    /*  //이건 한번에 6개 제어가 안될 시에 대비해서 짠 코드
    int clock=0;
    while(1){
        clock +=1;
        if(clock==1){

            set.id = 1;
            set.position=2810;   //3470
            set_position_pub1.publish(set);
            
        }else if(clock ==2){

            set.id = 2;
            set.position=3500;
            set_position_pub1.publish(set);
            
        }else{
            start+=1; 
            break;
        }
    }
    */
    

    set.id = 1;
    set.position=2810;   
    set_position_pub1.publish(set);

    set.id = 2;
    set.position=3470;
    set_position_pub1.publish(set);

    
    
}

void one(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("up");
        time_count++;
        init_position=3470;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[1])<=2810){
                count=0;
                number+=1;
                status=2;
                 
                return;
            }
            else if(count>=0){
                degree[1] = degree[1]+15;
            }
       }
        set.id=1;
        set.position=init_position-degree[1];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);
        
    }
    else if(status==0){
        ROS_INFO("down");  
        time_count++;
        init_position=2810;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[1])>=3470){
                
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[1] = degree[1]+15;
            }
       }
        set.id=1;
        set.position=init_position+degree[1];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
}

void two(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("open");
        time_count++;
        init_position=3500;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[2])<=2000){
                count=0;
                status=2;
                number+=1; 
                return;
            }
            else if(count>=0){
                degree[2] = degree[2]+30;
            }
       }
        set.id=2;
        set.position=init_position-degree[2];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
        
        
    }
    else if(status==0){
        ROS_INFO("close");  
        time_count++;
        init_position=2000;
        
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[2])>=3500){
               
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[2] = degree[2]+15;
            }
       }
        set.id=2;
        set.position=init_position+degree[2];
        set_position_pub1.publish(set);  
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);      
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
}
void three(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("up");
        time_count++;
        init_position=4000;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[3])<=2500){
                count=0;
                number+=1;
                status=2;
                
                return;
            }
            else if(count>=0){
                degree[3] = degree[3]+15;
            }
       }
        set.id=3;
        set.position=init_position-degree[3];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);
        
    }
    else if(status==0){
        ROS_INFO("down");  
        time_count++;
        init_position=2500;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[3])>=4000){
                
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[3] = degree[3]+15;
            }
       }
        set.id=3;
        set.position=init_position+degree[3];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
}
void four(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("close");
        time_count++;
        init_position=4000;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[4])<=2500){
                count=0;
                status=2;
                number+=1; 
                return;
            }
            else if(count>=0){
                degree[4] = degree[4]+15;
            }
       }
        set.id=4;
        set.position=init_position-degree[4];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
        
        
    }
    else if(status==0){
        ROS_INFO("open");  
        time_count++;
        init_position=2500;
        
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[4])>=4000){
               
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[4] = degree[4]+15;
            }
       }
        set.id=4;
        set.position=init_position+degree[4];
        set_position_pub1.publish(set);  
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);      
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
}
void five(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("down");
        time_count++;
        init_position=1125;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[5])<=0){
                count=0;
                number+=1;
                status=2;
                
                return;
            }
            else if(count>=0){
                degree[5] = degree[5]+15;
            }
       }
        set.id=5;
        set.position=init_position-degree[5];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);
        
    }
    else if(status==0){
        ROS_INFO("up");  
        time_count++;
        init_position=0;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[5])>=1125){
                
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[5] = degree[5]+15;
            }
       }
        set.id=5;
        set.position=init_position+degree[5];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
} //각도 수정 필요!!! -> 기어 각도가 최대로 했지만 안내려감
void six(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("close");
        time_count++;
        init_position=1030;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[6])<=800){
                count=0;
                status=2;
                number+=1; 
                return;
            }
            else if(count>=0){
                degree[6] = degree[6]+15;
            }
       }
        set.id=6;
        set.position=init_position-degree[6];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
        
        
    }
    else if(status==0){
        ROS_INFO("open");  
        time_count++;
        init_position=800;
        
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[6])>=1030){
               
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[6] = degree[6]+15;
            }
       }
        set.id=6;
        set.position=init_position+degree[6];
        set_position_pub1.publish(set);  
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);      
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
} //연결안되어 있어서 연결 필요

void Motion1(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){

        if(number==0){
            ROS_INFO("number0");
            
            //five(1,set,set_position_pub1); //2번 open
        }
        else if(number==1){
            ROS_INFO("number1");
            
            degree[5]=0;
            //five(0,set,set_position_pub1);
            //one(0,set,set_position_pub1); //1번 down
        }
        else if(number==2){
            ROS_INFO("number2");
            degree[1]=0;
            //two(0,set,set_position_pub1); //2번 close
        }
        else if(number==3){
            ROS_INFO("number3");
            degree[2]=0;
            //one(1,set,set_position_pub1); //1번 up
        }
        else{
            ROS_INFO("break");
            degree[1]=0;
            number=4;
            return;
        }

    
        
}


int main(int argc,char **argv){

    ros::init(argc,argv,"Dynamixel");
    ros::NodeHandle nh;
    ros::Publisher set_position_pub1 =nh.advertise<dynamixel_sdk_examples::SetPosition>("/set_position",10);
    
    ros::ServiceServer service = nh.advertiseService("servo1_to_dynamic",Start);
    dynamixel_sdk_examples::SetPosition set;
    ros::Rate loop_rate(10);
        


    while(ros::ok()){
        
        while(start==0){
            init(set,set_position_pub1);
            start=1;
        }
        if(start==1){
            
            Motion1(set,set_position_pub1);
           
        }
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

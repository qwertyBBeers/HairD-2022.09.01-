#include <ros/ros.h>

#include "std_msgs/String.h"
#include "dynamixel_sdk_examples/SetPosition.h" //msg 타입
#include "dynamixel_sdk_examples/sig_dy.h" //srv
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <string>

int start=0;
int clean=0;
int empty_start=0;
int number;
int time_count=0;
int init_position;
int degree[7]={0,0,0,0,0,0,0};
int count=0;

void StartCallback(const std_msgs::String::ConstPtr& msg)
{
    if (msg->data=="start"){
        start =1;
    }
    if(msg->data == "clean"){
        clean =1;
    }
    if(msg->data == "empty_start"){
        empty_start=1;
    }
}

void init(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    
    

    set.id = 1;
    set.position=2810;   
    set_position_pub1.publish(set);

    set.id = 2;
    set.position=3500;
    set_position_pub1.publish(set);

    set.id = 3;
    set.position=2500;
    set_position_pub1.publish(set);

    set.id = 4;
    set.position=2500;
    set_position_pub1.publish(set);

    set.id = 5;
    set.position=4000;
    set_position_pub1.publish(set);

    set.id = 6;
    set.position=550;
    set_position_pub1.publish(set);

    
    
}

void one(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("down");
        time_count++;
        init_position=2700;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[1])<=1100){
                count=0;
                number+=1;
                status=2;
                 
                return;
            }
            else if(count>=0){
                degree[1] = degree[1]+32;
            }
       }
        set.id=1;
        set.position=init_position-degree[1];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);
        
    }
    else if(status==0){
        ROS_INFO("up");  
        time_count++;
        init_position=1100;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[1])>=1600){
                
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[1] = degree[1]+32;
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
} // 0 위 , 1 아래         -1600-32  //수정예정
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
} // 0 닫힘 , 1 오픈        -1500-30
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
                degree[3] = degree[3]+30;
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
                degree[3] = degree[3]+30;
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
} // 0 아래 , 1 위          -1500-30  //수정예정
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
                degree[4] = degree[4]+30;
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
                degree[4] = degree[4]+30;
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
} // 0 오픈 , 1 닫힘        -1500-30
void five(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("down");
        time_count++;
        init_position=4000; //3480
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
                degree[5] = degree[5]+80;
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

            if((init_position+degree[5])>=4000){
                
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[5] = degree[5]+80;
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
} // 0 위 ,1 아래          - 4000-80
void six(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("up 위로 기울이기");
        time_count++;
        init_position=1030;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[6])<=550){
                count=0;
                status=3;
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
        ROS_INFO("-  평평");  
        time_count++;
        init_position=550;
        
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[6])>=1030){
               
                count=0;
                number+=1;
                status=3;
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
    else if(status ==2){
        ROS_INFO("down 기울이기");
        time_count++;
        init_position=1030;
        
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[6])>=1510){
               
                count=0;
                number+=1;
                status=3;
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
    else if(status ==3) {

        ROS_INFO("end");
        
    }
} // 0 평평 ,1 위 , 2 아래  - 480 -15

void clean_base(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
        /*
        one(0,set,set_position_pub1); //1 down
        two(1,set,set_position_pub1); //2 open
        three(0,set,set_position_pub1); //3 down
        four(0,set,set_position_pub1); //4 open
        five(1,set,set_position_pub1); //5 down
        six(0,set,set_position_pub1); //6 평평
        */
        if(number==0){
            ROS_INFO("number0");
            six(0,set,set_position_pub1); 
            five(1,set,set_position_pub1); //5 down
        }
        else if(number==1){
            ROS_INFO("number1");    
            five(1,set,set_position_pub1); //5 down
            degree[6]=0;
        }
        else if(number==2){
            ROS_INFO("number2");
            degree[5]=0;
            one(1,set,set_position_pub1);
            three(0,set,set_position_pub1);
            two(1,set,set_position_pub1);
            four(0,set,set_position_pub1);
            
            //two(0,set,set_position_pub1); //2번 close
        }
        else if(number==3){
            ROS_INFO("number3");
            degree[1]=0;
            degree[2]=0;
            degree[3]=0;
            degree[4]=0;
            //one(1,set,set_position_pub1); //1번 up
        }
        else{
            ROS_INFO("break");
            degree[1]=0;
            number=4;
            return;
        }

    
        
}

void hair(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
        /*
        one(0,set,set_position_pub1); //1 down
        two(1,set,set_position_pub1); //2 open
        three(0,set,set_position_pub1); //3 down
        four(0,set,set_position_pub1); //4 open
        five(1,set,set_position_pub1); //5 down
        six(0,set,set_position_pub1); //6 평평
        */
        if(number==0){
            ROS_INFO("number0");
            
            //five(1,set,set_position_pub1); //5 down
        }
        else if(number==1){
            ROS_INFO("number1");
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

void empty(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
        /*
        one(0,set,set_position_pub1); //1 down
        two(1,set,set_position_pub1); //2 open
        three(0,set,set_position_pub1); //3 down
        four(0,set,set_position_pub1); //4 open
        five(1,set,set_position_pub1); //5 down
        six(0,set,set_position_pub1); //6 평평
        */
        if(number==0){
            ROS_INFO("number0");
            two(1,set,set_position_pub1);
            four(0,set,set_position_pub1);
        }
        else if(number==1){
            ROS_INFO("number1");    
        }
        else if(number==2){
            ROS_INFO("number2");
             degree[2]=0;
            degree[4]=0;
            six(2,set,set_position_pub1);

            //two(0,set,set_position_pub1); //2번 close
        }
        else if(number==3){
            ROS_INFO("number3");
             degree[6]=0;
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
    ros::Publisher clean_pub = nh.advertise<std_msgs::String>("clean_info",1000);
    ros::Subscriber clean_sub = nh.subscribe<std_msgs::String>("clean_start",1000,StartCallback);

    dynamixel_sdk_examples::SetPosition set;
    ros::Rate loop_rate(10);
        


    while(ros::ok()){
        if(clean==1){
            
            clean_base(set,set_position_pub1);
        }
        if(start==0){
            init(set,set_position_pub1);
        }
        else if(start==1){
            clean_base(set,set_position_pub1);
        }
       
        
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

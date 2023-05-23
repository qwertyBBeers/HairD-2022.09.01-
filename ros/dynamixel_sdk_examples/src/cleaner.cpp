#include <ros/ros.h>

#include "std_msgs/String.h"
#include "dynamixel_sdk_examples/SetPosition.h" //msg 타입
#include "dynamixel_sdk_examples/sig_dy.h" //srv
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <string>

int start=0;
int clean=0;
int empty_start=0;
int stop=0;
int done = 0;
int number;
int time_count=0;
int init_position;
int degree[7]={0,0,0,0,0,0,0};
int count=0;

void StartCallback(const std_msgs::String::ConstPtr& msg)
{
    if (msg->data=="start"){
        ROS_INFO("start");
        stop=0;
        start =1;
        done=0;
    }
    if(msg->data == "clean"){
        clean =1;
        done=0;
    }
    if(msg->data == "stop"){
        stop =1;
        start =0;
        done=0;
    }
    if(msg->data == "empty_start"){
        stop=0;
        empty_start=1;
        done=0;
    }
}

void init(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    
    set.id = 1;
    set.position=2500;   
    set_position_pub1.publish(set);

    set.id = 2;
    set.position=1500;
    set_position_pub1.publish(set);

    set.id = 3;
    set.position=2500;  
    set_position_pub1.publish(set);

    set.id = 4;
    set.position=1500;
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
        init_position=2500;
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
                degree[1] = degree[1]+28;
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

            if((init_position+degree[1])>=2500){
                
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[1] = degree[1]+28;
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
} // 0 위 , 1 아래         -1400-28  
void two(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("open");
        time_count++;
        init_position=1500;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[2])>=2800){
                count=0;
                status=2;
                number+=1; 
                return;
            }
            else if(count>=0){
                degree[2] = degree[2]+26;
            }
       }
        set.id=2;
        set.position=init_position+degree[2];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
        
        
    }
    else if(status==0){
        ROS_INFO("close");  
        time_count++;
        init_position=2800;
        
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[2])<=1500){
               
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[2] = degree[2]+26;
            }
       }
        set.id=2;
        set.position=init_position-degree[2];
        set_position_pub1.publish(set);  
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);      
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
} // 0 닫힘 , 1 오픈        -1300-26
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
} // 0 아래 , 1 위          -1500-30  
void four(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("close");
        time_count++;
        init_position=300;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[4])>=1500){
                count=0;
                status=2;
                number+=1; 
                return;
            }
            else if(count>=0){
                degree[4] = degree[4]+24;
            }
       }
        set.id=4;
        set.position=init_position+degree[4];
        set_position_pub1.publish(set);
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);  
        
        
    }
    else if(status==0){
        ROS_INFO("open");  
        time_count++;
        init_position=1500;
        
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[4])<=300){
               
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[4] = degree[4]+24;
            }
       }
        set.id=4;
        set.position=init_position-degree[4];
        set_position_pub1.publish(set);  
        ROS_INFO("id : %d , set.position :%d",set.id,set.position);      
    }
    else if(status ==2) {

        ROS_INFO("end");
        
    }
} // 0 오픈 , 1 닫힘        -1200-24
void five(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("down");
        time_count++;
        init_position=3970; //3480
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[5])<=1370){
                count=0;
                number+=1;
                status=2;
                
                return;
            }
            else if(count>=0){
                degree[5] = degree[5]+52;
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
        init_position=1370;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position+degree[5])>=3970){
                
                count=0;
                number+=1;
                status=2;
                return;
            }
            else if(count>=0){
                degree[5] = degree[5]+52;
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
} // 0 위 ,1 아래          - 4000-80  //변경예정
void six(int status,dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1){
    

    if (status==1){
        ROS_INFO("up 위로 기울이기");
        time_count++;
        init_position=1030;
        if(time_count >=1){
            time_count=0;
            count++;

            if((init_position-degree[6])<=530){
                count=0;
                status=3;
                number+=1; 
                return;
            }
            else if(count>=0){
                degree[6] = degree[6]+10;
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
        init_position=530;
        
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
                degree[6] = degree[6]+10;
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

            if((init_position+degree[6])>=1530){
               
                count=0;
                number+=1;
                status=3;
                return;
            }
            else if(count>=0){
                degree[6] = degree[6]+10;
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
} // 0 평평 ,1 위 , 2 아래  - 500 -10

void clean_base(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1,std_msgs::String st,ros::Publisher clean_pub){
    if(done==0){
        st.data="yet";
        clean_pub.publish(st);    
        if(number==0){
            three(0,set,set_position_pub1);
            four(0,set,set_position_pub1);
        }
        else if(number==2){
            //ROS_INFO("1,2,3,4 run");
            degree[3]=0;
            degree[4]=0;
            one(1,set,set_position_pub1);
            two(1,set,set_position_pub1);
            
        }
        else if(number==4){
            degree[1]=0;
            degree[2]=0;

            //ROS_INFO("5,6 run");
            six(0,set,set_position_pub1); 
            five(1,set,set_position_pub1); //5 down

        }
        else if(number==6){

            degree[5]=0;
            degree[6]=0;
            number=0;
            done=1;
            return;
        }
    }else if(done==1){

            ROS_INFO("clean_base_status");
            st.data="done";
            clean_pub.publish(st);
            return;
    }
    
        
}

void hair(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1,std_msgs::String st,ros::Publisher clean_pub){
    if(done ==0){

        st.data="yet";
        clean_pub.publish(st);
        if(number==0){                 //2번 닫힘
            //ROS_INFO("2 run");

            set.id = 1;
            set.position=1100;   
            set_position_pub1.publish(set);
            two(0,set,set_position_pub1);
        }
        else if(number==1){
            degree[2]=0;
            number+=1;
        }
        else if(number==2){            //1번 올리고 2번 열고 4번 닫힘
            //ROS_INFO("1,2,4 run");
            one(0,set,set_position_pub1);
            two(1,set,set_position_pub1);
            four(1,set,set_position_pub1);
        }
        else if(number==5){
            degree[1]=0;
            degree[2]=0;
            degree[4]=0;
            number+=1;
        }
        else if(number==6){             // 1번 내리고 3번 올리면서 4번 열기
            //ROS_INFO("1,3,4 run");
            one(1,set,set_position_pub1);
            three(1,set,set_position_pub1);
            four(0,set,set_position_pub1);

        }
        else if(number==9){
            degree[1]=0;
            degree[3]=0;
            degree[4]=0;
            number+=1;
        }
        else if(number==10){            // 3번 내림
            //ROS_INFO("3 run");
            three(0,set,set_position_pub1);
        }
        else{
            ROS_INFO("clean done");
            
            degree[3]=0;
            number=0;
            done = 1;
            return;
        }
    }else if(done==1){
        st.data="done";
        clean_pub.publish(st);
        clean=0;
        return;
    }
        

    
        
}

void empty(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1,std_msgs::String st,ros::Publisher clean_pub){
    if(done==0){
        st.data="yet";
        clean_pub.publish(st);
        if(number==0){              //2번 4번 열기
            //ROS_INFO("number0");
            two(1,set,set_position_pub1);
            four(0,set,set_position_pub1);
        }
        else if(number==2){         // 아래로 기울이기
            //ROS_INFO("number2");
            degree[2]=0;
            degree[4]=0;
            six(2,set,set_position_pub1);
        }
        else if(number>=3 && number<100){         // 대기
            ROS_INFO("number : %d",number);
            degree[6]=0;
            number+=1;
        }
        else if(number==100){         // 초기 상태
            ROS_INFO("number : %d",number);
            six(1,set,set_position_pub1);       //  아래에서 평평하게 해야함!!! -수정필요
        }
        else if(number==101){              //2번 4번 닫기
            degree[6]=0;
            two(0,set,set_position_pub1);
            four(1,set,set_position_pub1);
        }
        else{
            degree[2]=0;
            degree[4]=0;
            number=0;
            done=1;
        }
    }else if(done==1){
            
            ROS_INFO("empty done");
            st.data="done";
            clean_pub.publish(st);
            start=0;
            stop=0;
            empty_start =0;
            return;
    }
    
        
}
void stop_init(dynamixel_sdk_examples::SetPosition set,ros::Publisher set_position_pub1,std_msgs::String st,ros::Publisher clean_pub){
    
    if(done==0){
        st.data="yet";
        clean_pub.publish(st);
        if(number>=0 && number<4){            // 1번 3번 올리고 5번올리고 6번 들고 
            one(0,set,set_position_pub1);
            three(1,set,set_position_pub1);
            five(0,set,set_position_pub1);
            six(1,set,set_position_pub1);
            ROS_INFO("number : %d",number);
        }
        else if(number==4){       //초기화
            degree[1]=0;
            degree[3]=0;
            degree[5]=0;
            degree[6]=0;
            number+=1;
        }
        else if(number==5){    //2번 4번 닫기 
            two(0,set,set_position_pub1);
            four(1,set,set_position_pub1);
            
        }
        else {         //초기화

            degree[2]=0;
            degree[4]=0;
            number=0;
            done=1;
        }
    }else if(done==1){
            
            ROS_INFO("stop done");
            st.data="done";
            clean_pub.publish(st);
            return;
    }
    
        
}




int main(int argc,char **argv){

    ros::init(argc,argv,"Dynamixel");
    ros::NodeHandle nh;
    ros::Publisher set_position_pub1 =nh.advertise<dynamixel_sdk_examples::SetPosition>("/set_position",10);
    ros::Publisher clean_pub = nh.advertise<std_msgs::String>("clean_info",1000);
    ros::Subscriber clean_sub = nh.subscribe<std_msgs::String>("clean_start",1000,StartCallback);
    std_msgs::String st;
    dynamixel_sdk_examples::SetPosition set;
    ros::Rate loop_rate(10);
        

    while(ros::ok()){
        //ROS_ERROR("done %d",done);

        if(stop == 1){              //초기 상태로 stop눌렀을때!!!
            ROS_INFO("stop");
            //init(set,set_position_pub1,st,clean_pub);  //여기 바꿔야함!!! clean_base 에서 천천히 올라가는거 -> 충돌안나게 하려면 어떻게 할까요??? 다른 함수 만들든지해야할듯
            stop_init(set,set_position_pub1,st,clean_pub);
                
        }
        else if(stop == 0){
            if(start==0){
                if(empty_start==0){
                    ROS_INFO("init");
                    stop_init(set,set_position_pub1,st,clean_pub);
                
                }else if(empty_start==1){
                    empty(set,set_position_pub1,st,clean_pub);
                }   
            }
            else if(start==1){
                if(clean==1){
                    ROS_INFO("hair");
                    hair(set,set_position_pub1,st,clean_pub);

                }else if(clean ==0){
                    ROS_INFO("clean_base");
                    clean_base(set,set_position_pub1,st,clean_pub);
                }
                
            }
       
        }
        
        
            
        
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

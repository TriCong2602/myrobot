#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <ncurses.h>

int main(int argc, char **argv) {
    std::cout << "Hello World!\n";

    ros::init(argc, argv, "wheel_controller");
    ros::NodeHandle n;

    ros::Publisher wheelPub1 = n.advertise<std_msgs::Float64>("/my_diffbot/joint1_position_controller/command", 10);
    ros::Publisher wheelPub2 = n.advertise<std_msgs::Float64>("/my_diffbot/joint2_position_controller/command", 10);
	
	 ros::Rate loop_rate(50);

    // Khởi tạo thư viện ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);

    float i = 0, j = 0; // Di chuyển khai báo biến i và j ở đây

    while (ros::ok()) {
        char in;

        std_msgs::Float64 speedMsg1;
        std_msgs::Float64 speedMsg2;

        // Đọc phím nhấn từ bàn phím
        in = getchar();

        switch (in) {
            case 'w':
                i++;
                j++;
                speedMsg1.data = i / 15.0;
                speedMsg2.data = -j / 15.0;
                break;

            case 's':
                i--;
                j--;
                speedMsg1.data = i / 15.0;
                speedMsg2.data = -j / 15.0;
                break;

            case 'a':
                j++;
                speedMsg1.data = i / 45.0;
                speedMsg2.data = -j / 45.0;
                break;

            case 'd':
                i++;
                speedMsg1.data = i / 45.0;
                speedMsg2.data = -j / 45.0;
                break;
			
        }
		
		if (in!= 'w' || in!='a' || in!='s' || in!='d'){
			speedMsg1.data = i / 45.0;
             speedMsg2.data = -j / 45.0;
		}

        wheelPub1.publish(speedMsg1);
        wheelPub2.publish(speedMsg2);

        ros::spinOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
		//loop_rate.sleep();
    }

    // Kết thúc thư viện ncurses
    endwin();

    return 0;
}

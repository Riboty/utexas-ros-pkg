#include <ros/ros.h>
#include <geometry_msgs/Twish.h>
#include <signal.h>
#include <termios.h>

#define KEYCODE_R 0x43 
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71

int kfd = 0;
struct termios cooked, raw;

void init() {
  // put console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  //Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);
}

void quit(int) {
  // get back out of raw
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}

int main(int argc, char** argv) {
  ros::init(argc,argv,"teleop");
  signal(SIGINT,quit);
  // initialize the terminal
  init();

  char ch;
  while (ros::ok()) {
    ros::spinOnce(10);
    if (read(kfd,&ch,1) < 0) {
      perror("read():");
      exit(-1);
    }

    switch (ch) {
      case KEYCODE_R:
        ROS_DEBUG("RIGHT");
        break;
      case KEYCODE_L:
        ROS_DEBUG("LEFT");
        break;
      case KEYCODE_U:
        ROS_DEBUG("UP");
        break;
      case KEYCODE_D:
        ROS_DEBUG("DOWN");
        break;
      case KEYCODE_Q:
        ROS_DEBUG("Q");
        break;
    }
  }

  return 0;
}

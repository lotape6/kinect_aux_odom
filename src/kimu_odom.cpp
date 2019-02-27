
 #include <ros/ros.h>
 #include <ros/console.h>
 #include <string>
 #include <iostream>
 #include <sensor_msgs/Imu.h>
 #include <geometry_msgs/Pose.h>
 #include <geometry_msgs/Vector3Stamped.h>
 #include <geometry_msgs/PoseStamped.h>
 #include <tf2/LinearMath/Vector3.h>
 //#include "tf2_bullet/tf2_bullet.h"
 #include "tf2_geometry_msgs/tf2_geometry_msgs.h"
 #include <time.h>
 //#include <Scalar.h>
 // #include <boost/bind.hpp>
#define MIN_DATA_AMOUNT 3

/* Global variables */
tf2::Stamped<tf2::Vector3>  acc, vel, pos;
tf2::Stamped<tf2::Vector3>  prev_vel, prev_pos;
tf2Scalar delta_t;

bool enought_data=false;
int data_counter=0;

// prev_pos=prev_vel=geometry_msgs::Vector3(0);


/* ****** Callback function ****** */
void imuCb(const sensor_msgs::ImuConstPtr& imu_msg){
  /*
    ROS_INFO_STREAM("data x: " << imu_msg->linear_acceleration.x);
    ROS_INFO_STREAM("data y: " << imu_msg->linear_acceleration.y);
    ROS_INFO_STREAM("data z: " << imu_msg->linear_acceleration.z);
  */
  geometry_msgs::Vector3Stamped acc_gm_msg;
  double dt;

  acc_gm_msg.header = imu_msg->header;
  acc_gm_msg.vector = imu_msg->linear_acceleration;

  // Convert geometry_msgs to tf2
  tf2::convert(acc_gm_msg,acc);

   if (!enought_data){
     if (data_counter >= MIN_DATA_AMOUNT) enought_data=true;
     data_counter++;
     return;
   }
   // If have enought data in buffer ..
   dt = double(imu_msg->header.stamp.sec) + double(imu_msg->header.stamp.nsec)*1e-9;

   ROS_INFO_STREAM("time: " << dt);

   // Convert double to tf2Scalar
   tf2::convert(dt,delta_t);

   // Calculate velocity
   //acc *= delta_t;
   //vel *= prev_vel+(acc*delta_t);

   return;
}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "kimu_odom");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("imu", 100, imuCb);

  ros::Rate loop_rate(10);
  // Main loop.
  while (n.ok())
  {
    // Publish the message.
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
} // end main()

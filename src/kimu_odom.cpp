 #include <ros/ros.h>
 #include <ros/console.h>
 #include <string>
 #include <iostream>
 #include <sensor_msgs/Imu.h>
 #include <geometry_msgs/Pose.h>
 #include <geometry_msgs/PoseStamped.h>
 // #include <boost/bind.hpp>

void imuCb(const sensor_msgs::ImuConstPtr& imu_msg){

  ROS_INFO_STREAM("data x: " << imu_msg->linear_acceleration.x);
  ROS_INFO_STREAM("data y: " << imu_msg->linear_acceleration.y);
  ROS_INFO_STREAM("data z: " << imu_msg->linear_acceleration.z);
}

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "kimu_odom");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("Imu", 100, imuCb);

  // Main loop.
  while (n.ok())
  {
    // Publish the message.

    ros::spinOnce();
    //r.sleep();
  }

  return 0;
} // end main()

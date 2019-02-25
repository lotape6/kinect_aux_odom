/*--------------------------------------------------------------------
 *
 *------------------------------------------------------------------*/

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "kimu_odom");
  ros::NodeHandle n;



  // Main loop.
  while (n.ok())
  {
    // Publish the message.

    ros::spinOnce();
    r.sleep();
  }

  return 0;
} // end main()

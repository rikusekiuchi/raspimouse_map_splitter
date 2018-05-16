#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>
#include <fstream>

class MapSplitter{
public:
  MapSplitter();
  double entropy;
  double entropy_temp;

private:
  ros::NodeHandle nh_;
  ros::NodeHandle private_nh_;
  ros::Subscriber entropy_sub_;
  double time1;
  double time2;
  double entropy_th;
  bool shell_script_generated;
  void entropyCallback(const std_msgs::Float64::ConstPtr& msg);
  void computeKidnappedTime();
  void generateShellScript(double kidnapped_time);
};

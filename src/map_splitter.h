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
  ros::NodeHandle n;
  ros::Subscriber entropy_sub;
  double entropy_th;
  bool shell_script_generated;
  void entropyCallback(const std_msgs::Float64::ConstPtr& msg);
  void computeKidnappedTime();
  void generateShellScript(double kidnapped_time);
};

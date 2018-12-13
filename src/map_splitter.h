#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>
#include <fstream>

class MapSplitter{
public:
  MapSplitter();
  double w_sum;
  double w_sum_temp;
  double w_sum_diff_temp;

private:
  ros::NodeHandle nh_;
  ros::Subscriber w_sum_sub_;
  double time1;
  double time2;
  bool shell_script_generated;
  void wSumCallback(const std_msgs::Float64::ConstPtr& msg);
  void computeKidnappedTime();
  void generateShellScript(double kidnapped_time);
};

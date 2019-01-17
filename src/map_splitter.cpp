#include "map_splitter.h"

MapSplitter::MapSplitter() 
{
  if(!nh_.getParam("time_margin_1", time1)) 
  {
    time1 = 4.0;
  }
  if(!nh_.getParam("time_margin_2", time2)) 
  {
    time2 = 10.0;
  }
  if(!nh_.getParam("loose_condition", loose_condition)) 
  {
    loose_condition = false;
  }

  w_sum_sub_ = nh_.subscribe("slam_gmapping/w_sum", 1, &MapSplitter::wSumCallback, this);
  w_sum_temp = 0;
  shell_script_generated = false;
}

void MapSplitter::wSumCallback(const std_msgs::Float64::ConstPtr& msg)
{
  w_sum = msg->data; 
  if (!shell_script_generated) {
    computeKidnappedTime();
  }
}

void MapSplitter::computeKidnappedTime() 
{
  double w_sum_diff = w_sum - w_sum_temp; 

  if((w_sum_diff < 0 && w_sum_diff_temp < 0)
  || (w_sum_diff < 0 && loose_condition)
  && !shell_script_generated) 
  {
    ros::Time t = ros::Time::now();
    generateShellScript(t.sec);
    shell_script_generated = true;
  }

  w_sum_temp = w_sum;
  w_sum_diff_temp = w_sum_diff;
}

void MapSplitter::generateShellScript(double kidnapped_time) 
{
  std::ofstream outputfile("split.sh");

  outputfile << "#! /bin/bash" << "\n";
  outputfile << "rosbag filter target.bag target_before.bag \"t.secs < " << std::setprecision(10) << kidnapped_time - time1 << "\"" << "\n";
  outputfile << "rosbag filter target.bag target_after.bag \"t.secs > " << std::setprecision(10) << kidnapped_time + time2 << "\"" << "\n";

  outputfile.close();
  ROS_INFO("Shell script generated.");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "map_splitter");
  
  MapSplitter MSobj;

  ros::spin();
  return 0;
}

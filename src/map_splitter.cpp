#include "map_splitter.h"

MapSplitter::MapSplitter(){
  entropy_sub = n.subscribe("slam_gmapping/entropy", 1, &MapSplitter::entropyCallback, this);
  entropy_temp = 0;
  entropy_th = -3.0;
  shell_script_generated = false;
}

void MapSplitter::entropyCallback(const std_msgs::Float64::ConstPtr& msg){
  entropy = msg->data; 
  computeKidnappedTime();
}

void MapSplitter::computeKidnappedTime(){
  double entropy_diff = entropy - entropy_temp; 

  if(entropy_diff < entropy_th && !shell_script_generated){
    ros::Time t = ros::Time::now();
    generateShellScript(t.sec);
    shell_script_generated = true;
  }

  entropy_temp = entropy;
}

void MapSplitter::generateShellScript(double kidnapped_time){
  std::ofstream outputfile("split.sh");

  outputfile << "#! /bin/bash" << "\n";
  outputfile << "rosbag filter target.bag target_before.bag \"t.secs <\"" << kidnapped_time << "\n";
  outputfile << "rosbag filter target.bag target_after.bag \"t.secs >\"" << kidnapped_time << "\n";

  outputfile.close();
  ROS_INFO("Shell script generated.");
}

int main(int argc, char **argv){
  ros::init(argc, argv, "map_splitter");
  
  MapSplitter MSobj;

  ros::spin();
  return 0;
}

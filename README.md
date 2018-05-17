# raspimouse_map_splitter
By using it with gmapping you can split the map at the time the robot was kidnapped.

However, it is not sufficiently verified whether the operation of this package is normal or not.

## Requirements

This package requires the following to run:
* Robot
  * Raspberry Pi Mouse
* Laser Rangefinder
  * URG-04LX-UG01
* IMU
  * RT-USB-9AXIS-00
* Ubuntu
  * Ubuntu 16.04 (Ubuntu 16.04 Server recomended)
* ROS
  * Kinetic Kame
* ROS Package
  * raspimouse_gmapping - [zaki0929/raspimouse_gmapping](https://github.com/zaki0929/raspimouse_gmapping)
  * Customized gmapping - [zaki0929/gmapping](https://github.com/zaki0929/gmapping)
  * raspimouse_navigation_2 - [zaki0929/raspimouse_navigation_2](https://github.com/zaki0929/raspimouse_navigation_2)
  * Customized ROS Navigation Stack - [zaki0929/navigation](https://github.com/zaki0929/navigation)
  * IMU Driver - [AtsushiSaito/lab_usb_9axisimu_driver](https://github.com/AtsushiSaito/lab_usb_9axisimu_driver)
  * urg_node - [urg_node - ROS WiKi](http://wiki.ros.org/urg_node)

## Installation

First of all, install the latest stable version of ROS.
Please refer to [ROS WiKi](http://wiki.ros.org/kinetic/Installation) for installation.

Next, download the dependent ROS package and this repository.

```
sudo apt install ros-kinetic-urg-node
cd ~/catkin_ws/src
git clone https://github.com/zaki0929/raspimouse_gmapping.git
git clone https://github.com/zaki0929/gmapping.git
git clone https://github.com/zaki0929/raspimouse_navigation_2.git
git clone https://github.com/zaki0929/navigation.git
git clone https://github.com/AtsushiSaito/lab_usb_9axisimu_driver.git
git clone https://github.com/zaki0929/raspimouse_navigation_2.git
```

Finally, build the downloaded ones.

```
cd ~/catkin_ws
catkin_make
source ~/catkin_ws/devel/setup.bash
```````
## Usage

### Step 1

In order to use this package, you need to launch the launch file on Raspberry Pi Mouse side and PC side as follows.

#### PC side

```
roslaunch raspimouse_gmapping remote_desktop.launch
roslaunch raspimouse_map_splitter generate_bag_file_and_shell_script.launch
```

#### Raspberry Pi Mouse side

```
roslaunch raspimouse_navigation_2 remote_robot.launch
```

### Step 2

Please kidnap the robot while generating the map and check that the following Info will be output.

```
ROS [ INFO] [ROS Time]: Shell script generated.
```
After checking the above info, please continue to generate the map as it is.

Please terminate the process executed above when the map generation is completed.

Next, please execute the generated shell script.

```
source ~/.ros/split.sh
```

### Step 3

In step 2, two bagfiles named target_before.bag and target_after.bag should be generated.

By playing these bagfiles as follows you can get a map before kidnapping and a map after kidnapping.

#### Generate a map before kidnapping

```
roslaunch raspimouse_gmapping remote_desktop.launch
rosbag play ~/.ros/target_before.bag
```

#### Generate a map after kidnapping

```
roslaunch raspimouse_gmapping remote_desktop.launch
rosbag play ~/.ros/target_after.bag
```

## License
This repository is licensed under the MIT license, see [LICENSE](./LICENSE).````

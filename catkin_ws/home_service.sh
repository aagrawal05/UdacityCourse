#!/bin/sh
xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; rosrun home_service home_service_marker_node" &
sleep 5
xterm -e "source /home/workspace/catkin_ws/devel/setup.bash; rosrun home_service home_service_goal_node"

#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;
bool adjusted_algorithm = false;
void drive_robot (float lin_x, float ang_z)
{
	ROS_INFO("Moving with linear_velocity: %1.2f, and angle:%1.2f", lin_x, ang_z);
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x = lin_x;
	srv.request.angular_z = ang_z;
	if (!client.call(srv)) ROS_ERROR("Failed to call move service");
}

void process_image_callback(const sensor_msgs::Image img){
	bool detected = false;
	for (int i=0; i<img.height*img.step*3; i+=3){
		if (img.data[i] == 255 && img.data[i+1] == 255 && img.data[i+2] == 255){
			detected = true;
			if (adjusted_algorithm){
				//Test new algorithm
				//Scanning from top-to-bottom, so therefore the pixel is most likely top-center pixel
				//Adjust our movements within a PI radians or 180* range ahead of us scaled to that pixels distance from the center of the image
				drive_robot(0.5, ((((i/3)%img.step)/img.step)-0.5) * 3.1415);				
				break;
			} else {
				if (i%img.step <= img.step/3) drive_robot(0.5, 0.5);
				else if (i%img.step >= 2*img.step/3) drive_robot(0.5, -0.5);
				else drive_robot(0.5, 0.0);
				break;
			}
		}	
	}
	if (!detected) drive_robot(0.0, 0.0);
}

int main (int argc, char** argv){
	ros::init(argc, argv, "process_image");
	ros::NodeHandle n;
	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
	ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);
	ros::spin();
	return 0;
}

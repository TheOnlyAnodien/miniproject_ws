// This program publishes randomly/generated velocity
// messages for Turtlesim
#include <ros/ros.h>
#include <geometry_msgs/Twist.h> // For geometry_msgs::Twist
#include <stdlib.h> // For rand() and RAND_MAX

int main (int argc, char **argv) {
	// Initialize the ROS system and becoming a node
	ros::init(argc, argv, "publish_velocity");
	ros::NodeHandle nh;
	
	// Create a publisher object
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

	// Seed the random number generator
	srand(time(0));

	// Loop ath 2Hz until the node is shut down
	ros::Rate rate(2);
	while(ros::ok()) {
		// Create and fill in the message. The other four fields,
		// which are ignored by turtlesim are set to default 0.
		geometry_msgs::Twist msg;
		msg.linear.x = double(rand())/double(RAND_MAX);
		msg.angular.z = 2*double(rand())/double(RAND_MAX)-1;

		// Publish the message
		pub.publish(msg);

		// Send the message to rosout with the details
		ROS_INFO_STREAM("Sending random velocity command: "
		<< " linear= " << msg.linear.x
		<< " angular= " << msg.angular.z);

		// Wait until it`s time for anouther iteration (delaying)
		rate.sleep();
	}
}


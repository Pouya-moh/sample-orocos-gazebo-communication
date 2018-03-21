/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#ifndef RTTGAZEBOGETPOSE_HPP
#define RTTGAZEBOGETPOSE_HPP

// RTT header files. Might missing some or some be unused
#include <rtt/RTT.hpp>
#include <string>
#include <rst-rt/robot/JointState.hpp>

#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

#include <geometry_msgs/PoseStamped.h> //TODO stamped maybe?

class RttGazeboGetPose: public RTT::TaskContext {
public:
    RttGazeboGetPose(std::string const & name);

    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

private:
	// Declare ports and their datatypes    
    gazebo::physics::ModelPtr model;//, coman;
//    gazebo::physics::JointPtr joint;
//    gazebo::physics::LinkPtr  link;
//    gazebo::physics::BasePtr  object;

//    RTT::OutputPort<rstrt::geometry::Pose>  pose_out_port;
//    rstrt::geometry::Pose                   pose_out_data;

    RTT::OutputPort<geometry_msgs::PoseStamped> ball_pose_out_port;
    geometry_msgs::PoseStamped ball_pose_out_data;


    std::string object_name;

    std::string publish_topic;
};

#endif // RTTGAZEBOGETPOSE_HPP

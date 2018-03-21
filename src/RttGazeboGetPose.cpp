/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#include "RttGazeboGetPose.hpp"
#include <rtt/Component.hpp>
#include <rtt_roscomm/rtt_rostopic.h>
#include <rtt_rosclock/rtt_rosclock.h>


RttGazeboGetPose::RttGazeboGetPose(std::string const & name) : RTT::TaskContext(name) {
    publish_topic = "/RTT/ball_pose";
    addProperty("object_name", this->object_name);
    addProperty("publish_topic", this->publish_topic);

    ball_pose_out_port.setDataSample(ball_pose_out_data);
    ports()->addPort(ball_pose_out_port);
}

bool RttGazeboGetPose::configureHook() {
    model = gazebo::physics::get_world()->GetModel(object_name);
    if (model.get() == NULL) {
        RTT::log(RTT::Info) << "Target object or robot is null"<<RTT::endlog();
        return false;
    } else {
        ball_pose_out_port.createStream(rtt_roscomm::topic(publish_topic));
        return true;
    }

}


bool RttGazeboGetPose::startHook() {
    // this method starts the component
    return true;
}

void RttGazeboGetPose::updateHook() {
    gazebo::math::Pose pose_ball = model->GetWorldPose();

    if(pose_ball.pos.z>=0.1){
        ball_pose_out_data.header.stamp = rtt_rosclock::host_now();
        ball_pose_out_data.pose.position.x = pose_ball.pos.x;
        ball_pose_out_data.pose.position.y = pose_ball.pos.y;
        ball_pose_out_data.pose.position.z = pose_ball.pos.z;
        ball_pose_out_port.write(ball_pose_out_data);
    }
}

void RttGazeboGetPose::stopHook() {
    // stops the component (update hook wont be  called anymore)
}

void RttGazeboGetPose::cleanupHook() {
    // cleaning the component data
}

// This macro, as you can see, creates the component. Every component should have this!
ORO_CREATE_COMPONENT_LIBRARY()ORO_LIST_COMPONENT_TYPE(RttGazeboGetPose)

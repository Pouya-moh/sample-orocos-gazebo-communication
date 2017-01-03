/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#include "RttGazeboGetPose.hpp"
#include <rtt/Component.hpp>

RttGazeboGetPose::RttGazeboGetPose(std::string const & name) : RTT::TaskContext(name) {

}

bool RttGazeboGetPose::configureHook() {
    model = gazebo::physics::get_world()->GetModel("coman");
    if (model.get() == NULL) {
        RTT::log(RTT::Info) << "model is null"<<RTT::endlog();
        return false;
    } else {        
        return bool(model);
    }
}


bool RttGazeboGetPose::startHook() {
    // this method starts the component
    return true;
}

void RttGazeboGetPose::updateHook() {
    this->link = this->model->GetLink("RShy");
    if (link.get()==NULL) {
        RTT::log(RTT::Info) << "Cannot find link"<<RTT::endlog();
    } else {
        gazebo::math::Pose pose = link->GetWorldPose();
        RTT::log(RTT::Info) << pose.pos.x<<"\t"<<pose.pos.y<<"\t"<<pose.pos.z<<RTT::endlog();
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

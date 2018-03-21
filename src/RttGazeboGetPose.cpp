/* Author: Pouya Mohammadi
 * Date:   09/06/2016
 *
 * Description: This is a simple orocos/rtt component template. It should be
 *              modified and extended by users to accomodate their needs.
 */

#include "RttGazeboGetPose.hpp"
#include <rtt/Component.hpp>

RttGazeboGetPose::RttGazeboGetPose(std::string const & name) : RTT::TaskContext(name) {
    addProperty("object_name", this->object_name);

    this->position_as_joint_out_data = rstrt::robot::JointState(3);
    this->position_as_joint_out_data.angles.setZero();
    this->position_as_joint_out_port.setName("out_pos_as_angles");
    this->position_as_joint_out_port.setDataSample(position_as_joint_out_data);
    ports()->addPort(position_as_joint_out_port).doc("position of object reported as joint angles because!");

    this->waist_pose_as_joint_out_data = rstrt::robot::JointState(7);
    this->waist_pose_as_joint_out_data.angles.setZero();
    this->waist_pose_as_joint_out_port.setName("waist_pos_as_angles");
    this->waist_pose_as_joint_out_port.setDataSample(waist_pose_as_joint_out_data);
    ports()->addPort(waist_pose_as_joint_out_port).doc("waist_pose of object reported as joint angles because!");
}

bool RttGazeboGetPose::configureHook() {
    model = gazebo::physics::get_world()->GetModel(object_name);
    coman = gazebo::physics::get_world()->GetModel("coman");
    if (model.get() == NULL || coman.get()== NULL) {
        RTT::log(RTT::Info) << "Target object or robot is null"<<RTT::endlog();
        return false;
    } else {        
        this->link = coman->GetLink("base_link");
        if (link.get()==NULL) {
            RTT::log(RTT::Info) << "Cannot find link"<<RTT::endlog();
        }

        return (bool(model)&&bool(coman)&&bool(link));
    }
}


bool RttGazeboGetPose::startHook() {
    // this method starts the component
    return true;
}

void RttGazeboGetPose::updateHook() {
    gazebo::math::Pose pose_ball = model->GetWorldPose();
    position_as_joint_out_data.angles(0) = pose_ball.pos.x;
    position_as_joint_out_data.angles(1) = pose_ball.pos.y;
    position_as_joint_out_data.angles(2) = pose_ball.pos.z;

    std::cout<<position_as_joint_out_data.angles.transpose()<<std::endl;

    position_as_joint_out_port.write(position_as_joint_out_data);

    gazebo::math::Pose pose_waist = link->GetWorldPose();
    waist_pose_as_joint_out_data.angles(0) = pose_waist.pos.x;
    waist_pose_as_joint_out_data.angles(1) = pose_waist.pos.y;
    waist_pose_as_joint_out_data.angles(2) = pose_waist.pos.z;

    waist_pose_as_joint_out_data.angles(3) = pose_waist.rot.w;
    waist_pose_as_joint_out_data.angles(4) = pose_waist.rot.x;
    waist_pose_as_joint_out_data.angles(5) = pose_waist.rot.y;
    waist_pose_as_joint_out_data.angles(6) = pose_waist.rot.z;

    position_as_joint_out_port.write(position_as_joint_out_data);
    waist_pose_as_joint_out_port.write(waist_pose_as_joint_out_data);
}

void RttGazeboGetPose::stopHook() {
    // stops the component (update hook wont be  called anymore)
}

void RttGazeboGetPose::cleanupHook() {
    // cleaning the component data
}

// This macro, as you can see, creates the component. Every component should have this!
ORO_CREATE_COMPONENT_LIBRARY()ORO_LIST_COMPONENT_TYPE(RttGazeboGetPose)

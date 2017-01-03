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

#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

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
    gazebo::physics::ModelPtr model;
    gazebo::physics::JointPtr joint;
    gazebo::physics::LinkPtr  link;
//    gazebo::physics::BasePtr  object;
};

#endif // RTTGAZEBOGETPOSE_HPP

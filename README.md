# Thesis(Variable till the project takes shape)

This code is written for my thesis and more description will follow as the project takes shape.

# Hardware design

The rig is basically a cartesian manipulator which can move in a fixed X-Y plane. For accurate movement, ball-screw actuators are proposed.
A little background on ball-screw actuators :-
These are basically of 3 types, based on how the balls are recirculated
  - [External circulation](http://1ugn2l2m3z2y31d4y73c1m5w.wpengine.netdna-cdn.com/wp-content/uploads/2015/08/External-Tube-Recirculation.jpg)
  - [Internal circulation](http://1ugn2l2m3z2y31d4y73c1m5w.wpengine.netdna-cdn.com/wp-content/uploads/2015/08/Deflector-Recirculation.jpg)
  - [End cap circulation](http://1ugn2l2m3z2y31d4y73c1m5w.wpengine.netdna-cdn.com/wp-content/uploads/2015/08/End-Cap-Recirculation.jpg)

Contact Geometry
  - Pitch circle diameter : The diameter formed by the ball while it rests on the screw.
  - Ball diameter : Diameter of the bearing.
  - Lead : The distance travelled by the ball in one complete rotation about the screw.
  - Outer diameter : Maximum diameter of the screw.
  - Root diameter : Minumum diameter of the screw.

Parameters while desiging the joint
  - Basic Dynamic load rating : 90% of identical bearings should retain their frictional properties after 1 million rotations.
  - Basic Static load rating : Plastic deformation upon applied force on the bearing.
  - Preload/Backlash : If the bearing is small, preload is less but backlash is more, converse is true for larger bearings. How well the bearing fits in the slots decides how find the actuator
                       can move.
  - Rigdidity : This is also decided by the bearing size. More rigid means more fine motion.
  - Positioning accuracy : Lead should be identical for larger duration.

Mechanical manufacturing ensures an accuracy within a micron for everything to fall in place.


# Extension and Usage

The rig is designed to have a fixed dimension and the software associated with it tries to match with the hardware. Rig is camera or camera array agnostic and extending the DataGrabber class will provide the functionality of taking data from the sensor. It was designed to simulate complex multi-camera arrays and explore the properties of The Light Field(reference here).

TODO: Design a generic rig that can be used to move the cameras around.(Working on this)
TODO: Software for making generic (x,y) motion with minimal inputs as possible.
TODO: Integrate Kinect 360 camera with this.(On hold till thermal paste arrives)
TODO: Integrate Depth grabbing.
TODO: Build a GUI on top of this.

# Dependencies

  - [libfreenect](https://github.com/OpenKinect/libfreenect)
  - [spdlog](https://github.com/gabime/spdlog)
  - [opencv](https://github.com/opencv/opencv)

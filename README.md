# Thesis(Variable till the project takes shape)

This code is written for my thesis and more description will follow as the project takes shape.

# Extension and Usage

The rig is designed to have a fixed dimension and the software associated with it tries to match with the hardware. Rig is camera or camera array agnostic and extending the DataGrabber class will provide the functionality of taking data from the sensor. It was designed to simulate complex multi-camera arrays and explore the properties of The Light Field(reference here).

TODO: Integrate Kinect 360 camera with this.(Working on this)
TODO: Integrate Depth grabbing.
TODO: Build a GUI on top of this.

# Dependencies

  - [libfreenect](https://github.com/OpenKinect/libfreenect)
  - [spdlog](https://github.com/gabime/spdlog)
  - [opencv](https://github.com/opencv/opencv)

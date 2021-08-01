# HandDetector
This repository contains the project I worked on during my internship at Simtek

## About This Project
This project has hand detection, hand tracking, finger tracking, finger counting and drawing functionalities. It's written in C++ and uses OpenCv library. 
At startup, the program asks the user to place their hand in the middle of the camera and press the 'Enter' key to read the hand color. 

After this step it automatically switches to the finger counting mode. There is also a drawing mode that the user can switch to using the 'S' key. The user can exit the program using the 'Esc' key. Alongside the main window the program will also create additional windows to show what it sees. It uses 4 color masks to identify the hand which are YCbCr/Cr, YCbCr/Cr, LAB/A and HSV/H. The user can interact with these masks by using their individual trackbars. What the program evantually sees will be displayed in the 'combined' window.

![Combined](https://i.imgur.com/slwgD0j.png)

### Finger Tracking Mode

![Finger Tracking Gif](https://media.giphy.com/media/SxIcXxRvDbxwgCGDIj/giphy.gif)

### Drawing Mode

In drawing mode the program tracks the highest point of the users hand. The user can spawn rectangles,circles,triangles and arrows using the specified keys. The user can also start/stop drawing using the 'D' key. Spawned objects stick to the highest point if the point is inside them for more than 2 seconds. The user can also relase the carried object by not moving their hand for 2 seconds.

![Drawing GIF](./drawingModeGif.gif)

## How to Run

### Linux

The program needs C++ and OpenCv to run. You can follow [this](https://docs.opencv.org/4.5.2/d7/d9f/tutorial_linux_install.html) guide for more detailed explanation. It also needs cmake to build which can be found [here](https://cmake.org/install/). After setting up these you can clone and build the project.

```bash
$ git clone https://github.com/kaantuncer/HandDetector.git
$ cd HandDetector
$ cmake .
$ cmake --build .
```

Finally you can run the project.
```bash
$ ./Main
```

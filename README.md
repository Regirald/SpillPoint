# SpillPoint C++ Project

This C++ project focuses on detecting spill points in a grid-like terrain using a specific algorithm. A spill point is a location where water would flow out of the grid if the terrain was filled with water up to that point. The code in this project involves various functions for detecting and analyzing these points.

## Files

- `FindSpillPoint.h`: This header file contains function declarations, including those for detecting spill points, updating queues, and managing visited points.

- `FindSpillPoint.cpp`: This source file contains the implementation of the functions declared in `FindSpillPoint.h`. It includes functions for updating queues, propagating by layer, and finding spill points.

- `Main.cpp`: This file contains the main function where you can set up the grid and starting point for detecting spill points. It uses the functions defined in the header and source files to perform the detection and display the results.

## Compilation and Execution

To compile and run the project:

1. Compile the project using the following command:

g++ Main.cpp FindSpillPoint.cpp -o FindSpillPoint

2.Run the compiled executable:

./FindSpillPoint

## Usage

1. The `Main.cpp` file includes a pre-defined grid and starting point. You can modify the `grid` array and the `startX` and `startY` variables to analyze different terrains and starting points.

2. Upon running the executable, the program will detect spill points in the provided terrain and starting point.

3. The coordinates of the detected spill points will be displayed in the terminal.

## Note

Please note that this project serves as a demonstration of the algorithm for detecting spill points and doesn't include error handling or extensive user interactions.

Feel free to modify, improve, and adapt the code for your specific use cases.


*************************************************
Title:          README.txt
Author:         Abdullah Khan
Date Created:   2016-09-19
Class:          [CSCI 493.69] Computer Vision
Professor:      Stamos
Purpose:        Homework #2
*************************************************

I. Parts Completed
    - p1

II. Bugs Encountered
    - Upon running `make`, the following warnings are shown:

g++ -g -std=c++14 -Wall -pedantic -I.  -c image.cc -o image.o
image.cc: In function ‘void ComputerVisionProjects::DrawLine(int, int, int, int, int, ComputerVision
Projects::Image*)’:
image.cc:152:5: warning: unused variable ‘incrS’ [-Wunused-variable]
     incrS,
     ^
image.cc:154:5: warning: unused variable ‘incrN’ [-Wunused-variable]
     incrN;     

This does not seem to have any effect on the output.

III. Run Instructions
    - Run `make` to build.
    - ./p1 <input_image.pgm> <threshold> <output_image.pgm>

    - To clean up directory, run `make clean`.
        * This will also delete the compiled programs.

IV. Input and Output Files
    - Input: two_objects.pgm
    - Output: User defined.

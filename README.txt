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
	- p2

II. Bugs Encountered
	- When running p2 on a binary image, some objects are almost as dark as
		the background.
		Attempted solution: After first and second pass, I do a third pass
		changing all the background (0) pixels to (255). The image's grayscale
		level is changed to the std::min(255, label) in the case that label is
		larger than 255.

This does not seem to have any effect on the output.

	- The DisjointSets class' explicit constructor compared signed and unsigned
		types together. This makes the compiler show a warning. I fixed this by
		changing the for loop in the constructor from initializing an `int` to `size_t`.

III. Run Instructions
	- Run `make` to build.
	- ./p1 <input_image.pgm> <threshold> <output_image.pgm>
		* The best threshold is between 120 and 125. I prefer 125.
	- ./p2 <input_binary_image.pgm> <output_labeled_image.pgm>

	- To clean up directory, run `make clean`.
		* This will also delete the compiled programs.

IV. Input and Output Files
	- PGM images.
	- Input: User defined.
	- Output: User defined.

/*
 * Author: Abdullah Khan
 * Program 3: Create database of objects from labeled images, then draw lines
 	to show positions and orientations of objects in the input image using a
	dot for the position and a short line segment originating from the dot for
	the orientation.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::min
#include <vector> // for labels
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	if (argc != 4) {
		cout <<
		"Usage: " << argv[0] << " <input_labled_image.pgm> <output_database.txt> <output_image.pgm>"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const string database(argv[2]);
	const string output(argv[3]);


	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	} // Loaded image into memory.

	// Do things to image.

	img.SetNumberGrayLevels(255); // Set gray levels to whatever they should be.

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	} // Wrote image to file.

	return 0;
}

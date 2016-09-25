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
#include <set> // for counting labels
#include <map>
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

	auto rows = img.num_rows();
	auto cols = img.num_columns();
	map<int, int> labels;

	/* First pass.
	 * Create associative array based on object.
	 */
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			int currentp = img.GetPixel(i, j);
			if (currentp != 255) {
				labels.emplace(img.GetPixel(i, j), 0);
			}
		}
	}

	// Get the area.
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			int currentp = img.GetPixel(i, j);
			if (currentp != 255)
			{
				auto label = labels.find(currentp);
				if (label != labels.end())
					label->second = label->second + 1;
			}
		}
	}

	for (auto l : labels)
	{
		cout << "Object Label: " << l.first << endl << "Area: " << l.second << endl;
		cout << endl;
	}

	// if (!WriteImage(output, img)) {
	// 	cout << "Can\'t write to file." << endl;
	// 	return 0;
	// } // Wrote image to file.

	return 0;
}

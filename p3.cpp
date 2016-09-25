/*
 * Author: Abdullah Khan
 * Program 3: Create database of objects from labeled images, then draw lines
 	to show positions and orientations of objects in the input image using a
	dot for the position and a short line segment originating from the dot for
	the orientation.
 */

#include <iostream>
#include <string>
#include <map> // for labels
#include <list> // For storing database entries.
#include <fstream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

void ObjectCenter(const int label, const int area, int &x, int &y, Image &img)
{
	// These will be used as sums.
	int X = 0;
	int Y = 0;

	int r = img.num_rows();
	int c = img.num_columns();

	for(int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			int current = img.GetPixel(i, j);
			if (current == label)
			{
				// Assuming pixel area is 1.
				X += i * 1;
				Y += j * 1;
			}
		}
	}

	// These are our x-bar and y-bar.
	x = (1 / area) * X;
	y = (1 / area) * Y;
}

int main(int argc, char ** argv)
{
	if (argc != 4) {
		cout <<
		"Usage: " << argv[0]
		<< " <input_labled_image.pgm> <output_database.txt> <output_image.pgm>"
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

	// Print out objects and their respective areas.
	for (auto l : labels)
	{
		cout << "Object Label: " << l.first << endl
		<< "Object " << l.first << "\'s "
		<< "Area: " << l.second << endl;
		cout << endl;
	}

	int xbar = 0;
	int ybar = 0;
	list<string> entries;

	for (auto l : labels)
	{
		ObjectCenter(l.first, l.second, xbar, ybar, img);
		cout << "Area: " << l.first << " x: " << xbar << " y: " << ybar << endl;
	}

	// if (!WriteImage(output, img)) {
	// 	cout << "Can\'t write to file." << endl;
	// 	return 0;
	// } // Wrote image to file.

	return 0;
}

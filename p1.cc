/*
 * Author: Abdullah Khan
 * Program 1: Convert gray level image to binary image.
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	// Best threshold is 125.
	if (argc != 4) {
		cout <<
		"Usage: " << argv[0] << " <input_image.pgm> <threshold> <output_image.pgm>"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const float threshold = atof(argv[2]);
	const string output(argv[3]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}

	int rows = img.num_rows();
	int cols = img.num_columns();

	img.SetNumberGrayLevels(1);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (img.GetPixel(i, j) < threshold)
				img.SetPixel(i, j, 0);
			else
				img.SetPixel(i, j, 1);
		}
	}

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}

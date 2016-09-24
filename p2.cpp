/*
 * Author: Abdullah Khan
 * Program 2: Convert binary image to labeled image.
 */

#include <iostream>
#include <string>
#include <vector>
#include "image.h"
#include "DisjSets.h"


using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	if (argc != 3) {
		cout <<
		"Usage: " << argv[0] << " <input_binary_image.pgm> <output_labeled_image.pgm>"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const string output(argv[2]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}

	// Create disjoint set with size 400. Size doesn't matter too much.
	DisjSets ds(400);

	int label = 1;
	int rows = img.num_rows();
	int cols = img.num_columns();

	/*
	 * Should be 6 way connected, not 4.
	 * Only check if pixel is non-zero, this way I don't have to worry about
	 * being on row 0, col 0.
	 */

	// Change this algorithm!
	for (auto r = 1; r < rows; r++)
	{
		for (auto c = 1; c < cols; c++)
		{
			// If pixel isn't white, don't do anything.
			if (r == 0 || c == 0)
			{
				if (img.GetPixel(r, c) != 0) img.SetPixel(r, c, label++);
			}

			if (img.GetPixel(r, c) != 0)
			{
				// Pixel above current position and pixel to the left of current position
				// both have no labels.
				if (img.GetPixel(r-1, c) == 0 && img.GetPixel(r, c-1) == 0)
					img.SetPixel(r, c, label++);
				// Label above is non-zero, label to the left is zero. Take above label.
				if (img.GetPixel(r-1, c) != 0 && img.GetPixel(r, c-1) == 0)
					img.SetPixel(r, c, img.GetPixel(r-1, c));
				// Label to the left is non-zero, take it.
				if (img.GetPixel(r, c-1) != 0 && img.GetPixel(r-1, c) == 0)
					img.SetPixel(r, c, img.GetPixel(r, c-1));
				// Both are non-zero, arbitrarily take the above label.
				if (img.GetPixel(r, c-1) != 0 && img.GetPixel(r-1, c) != 0)
				{
					img.SetPixel(r, c, img.GetPixel(r-1, c));
					/* The left and above labels are equivalent and I need to record this */
				}
			}
		}
	}

	img.SetNumberGrayLevels(label);

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}

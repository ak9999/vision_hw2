/*
 * Author: Abdullah Khan
 * Program 2: Convert binary image to labeled image.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
	} // Loaded image into memory.

	// Create disjoint set with size 400. Size doesn't matter too much.
	DisjointSets ds(400);

	int label = 1; // Start label counter at 1.
	int rows = img.num_rows();
	int cols = img.num_columns();

	// Skipping the first row and first column is a dirty hack.
	for (auto i = 1; i < rows; i++)
	{
		for (auto j = 1; j < cols; j++)
		{
			/* Pixel locations relative to current position (A).
			 * See Slide 40 of "Binary Images" presentation.
			 * Saving these values also saves computation time.
			 */

			int current = img.GetPixel(i, j); // current pixel
			int north = img.GetPixel(i-1, j); // North
			int west = img.GetPixel(i, j-1); // West
			int northwest = img.GetPixel(i-1, j-1); // North-West

			if (current != 0)
			{
				if (north == 0 && west == 0 && northwest == 0) // First white pixel?
					img.SetPixel(i, j, label++);
				if (north == 0 && west == 0 && northwest != 0) // B and C unlabeled, but D is.
					img.SetPixel(i, j, northwest);
				if (northwest == 0 && north == 0 && west != 0) // D and B unlabeled, but C is.
					img.SetPixel(i, j, west);
				if (west == 0 && northwest == 0 && north != 0)
					img.SetPixel(i, j, north);
				// North and West pixels are equivalent.
				if (north == west)
					img.SetPixel(i, j, north);
				if (north != 0 && west != 0 && north != west)
				{
					img.SetPixel(i, j, min(north, west));
					ds.UnionSets(north, west);
				}
			}
		}
	} // First pass.

	img.SetNumberGrayLevels(label);

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	} // Wrote image to file.

	return 0;
}

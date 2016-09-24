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
			// Pixel locations relative to current position (A).
			// See Slide 40 of "Binary Images" presentation.
			int A = img.GetPixel(i, j); // current pixel
			int B = img.GetPixel(i-1, j); // North
			int C = img.GetPixel(i, j-1); // West
			int D = img.GetPixel(i-1, j-1); // North-West

			if (A != 0)
			{
				if (B == 0 && C == 0 && D == 0) // First white pixel?
					img.SetPixel(i, j, label++);
				if (B == 0 && C == 0 && D != 0) // B and C unlabeled, but D is.
					img.SetPixel(i, j, D);
				if (D == 0 && B == 0 && C != 0) // D and B unlabeled, but C is.
					img.SetPixel(i, j, C);
				if (C == 0 && D == 0 && B != 0)
					img.SetPixel(i, j, B);
				// North and West pixels are equivalent.
				if (B == C)
					img.SetPixel(i, j, B);
				if (B != 0 && C != 0 && B != C)
				{
					img.SetPixel(i, j, min(B, C));
					ds.UnionSets(B, C);
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

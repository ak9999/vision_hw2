/*
 * Author: Abdullah Khan
 * Program 2: Convert binary image to labeled image.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::min
#include <map> // For resolving conflicts.
#include <vector> // for labels
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

	int label = 0; // Start label counter.
	int rows = img.num_rows();
	int cols = img.num_columns();

	// First pass.
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int current = img.GetPixel(i, j); // current pixel

			if (current == 1)
			{
				int north = img.GetPixel(i-1, j); // North
				int west = img.GetPixel(i, j-1); // West
				int northwest = img.GetPixel(i-1, j-1); // North-West

				if (northwest != 0)
					current = northwest;
				if (west == north && north != 0)
					current = north;
				if ((west != 0 && north == 0) || (west == 0 && north !=0))
					current = max(west, north);
				if (northwest == 0 && north == 0 && west == 0)
				{
					current = ++label;
					ds.UnionSets(current, current);
				}
				if ((north != west) && (north != 0 && west != 0))
				{
					current = north;
					ds.UnionSets(ds.Find(north), ds.Find(west));
				}
				img.SetPixel(i, j, current);
			}
		}
	}

	// Second pass.
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			img.SetPixel(i, j, ds.Find(img.GetPixel(i, j)));
		}
	}

	img.SetNumberGrayLevels(10);

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	} // Wrote image to file.

	return 0;
}

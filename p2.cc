/*
 * Author: Abdullah Khan
 * Program 2: Convert binary image to labeled image.
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include <vector>
#include "image.h"

// Boost libs
#include <boost/pending/disjoint_sets.hpp> // boost::disjoint_sets
#include <boost/unordered/unordered_set.hpp> // boost::unordered_set


using namespace std;
using namespace ComputerVisionProjects;

void search(int x, int y, int label);
void find_components();

int main(int argc, char ** argv)
{
	if (argc != 3) {
		cout <<
		"Usage: " << argv[0] << " <input_binary_image.pgm> <output_labeled_image.pgm>"
		<< endl;
		return 0;
	}

	// Using-declarations
	using std::vector<int> = VecInt;
	using boost::unordered_set<int> = SetInt;

	const string input(argv[1]);
	const string output(argv[2]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}

	int label = 1;
	int rows = img.num_rows();
	int cols = img.num_columns();

	VecInt rank(rows*cols);
	VecInt parent(rows*cols);
	SetInt elements;

	boost::disjoint_sets<int, int> ds(rank[0], parent[0]);

	for (size_t c = 0; c < cols; c++)
	{
		for (size_t r = 0; r < rows; r++)
		{
			// If pixel isn't white, don't do anything.
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
					img.SetPixel(r, c, img.GetPixel(r-1, c));
				/* The left and above labels are equivalent and I need to record this */
			}
		}
	}
}

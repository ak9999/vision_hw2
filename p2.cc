/*
 * Author: Abdullah Khan
 * Program 2: Convert binary image to labeled image.
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include "image.h"

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

	const string input(argv[1]);
	const string output(argv[2]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}

	int rows = img.num_rows();
	int cols = img.num_columns();

}

void search(int x, int y, int label)
{
	if (x < 0 || x == rows) return; // out of range
	if (y < 0 || y == cols) return; // out of range
	if (label[x][y] || !m[x][y]) return; // Labeled
}

void find_components(int rows, int cols)
{
	int comp = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (!label[i][j] && m[i][j])
				search(i, j, ++component);
}

/*
 * Author: Abdullah Khan
 * Program 4: Compare labled image with database.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <map> // for labels
#include <fstream>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

void fillmap(Image &img, size_t &rows, size_t &cols, std::map<int, int> &labels)
{
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
}

void findArea(Image &img, size_t &rows, size_t &cols, std::map<int, int> &labels)
{
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
}

void printMap(const std::map<int, int> &labels)
{
	// Print out objects and their respective areas.
	for (auto l : labels)
	{
		cout << "Object Label: " << l.first << endl
		<< "Object " << l.first << "\'s "
		<< "Area: " << l.second << endl;
		cout << endl;
	}
}

void ObjectCenter(const int label, double area, int &x, int &y, Image &img)
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

void GetABC(const int label, double area, int &x, int &y, Image &img, double &a, double &b, double &c)
{
	// Adapted from Chapter 10, page 126 of Horn and Winston's Lisp.
	int sum_a = 0; int sum_b = 0; int sum_c = 0;
	int rows = img.num_rows(); int cols = img.num_columns();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (label == img.GetPixel(i, j))
			{
				sum_a += pow(i, 2) * label;
				sum_b += i * j * label;
				sum_c += pow(j, 2) * label;
			}
		}
	}

	a = sum_a - area * pow(x, 2);
	b = 2.0 * sum_b - 2.0 * area * x * y;
	c = sum_c - area * pow(y, 2);
}

int main(int argc, char ** argv)
{
	if (argc != 3) {
		cout <<
		"Usage: " << argv[0]
		<< " <input_labled_image.pgm> <output_database.txt> <output_image.pgm>"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const string database(argv[2]);
	// const string output(argv[3]);

	ifstream fs(database);
	if (!fs.is_open())
	{
		fs.clear();
		cout << "Could not open database for reading." << endl;
		return 0;
	}

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	} // Loaded image into memory.

	size_t rows = img.num_rows();
	size_t cols = img.num_columns();
	map<int, int> labels;

	fillmap(img, rows, cols, labels);
	findArea(img, rows, cols, labels);
	printMap(labels);

	int xbar = 0;
	int ybar = 0;
	double a = 0; double b = 0; double c = 0;

	cout << "Checking for similar objects." << endl;

	for (auto l : labels)
	{
		string entry, line;
		stringstream ss;
		double theta = 0;
		ObjectCenter(l.first, l.second, xbar, ybar, img);
		GetABC(l.first, l.second, xbar, ybar, img, a, b, c);
		theta = atan2(b, a-c) / 2.0;
		double E = (0.5 * (a + c)) - (0.5 * (a - c)) * (2.0 * pow(cos(theta), 2) - 1) - (0.5 * b * 2.0 * sin(theta) * cos(theta));

		ss << l.first << " " << xbar << " " << ybar << " " << E << " " << theta;
		entry = ss.str();

		std::string::size_type n;
		while(std::getline(fs, line))
		{
			string search = to_string(l.second);
			n = line.find(search);
			if (n != std::string::npos)
			{
				cout << "Label: " << entry.substr(n) << " from database \"" << input
					 << "\" is similar to " << l.first << " in terms of area." << endl;
			}
		}
	}

	return 0;
}

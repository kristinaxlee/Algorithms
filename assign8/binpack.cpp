#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>

using namespace std;

void printArray(int *array, int capacity) {

	for(int i = 0; i < capacity; i++) {
		cout << array[i] << " ";
	}

	cout << endl;

}


// returns the number of bins taken
int firstFit(int *items, int numItems, int capacity) {

	int numBins = 0;
	int binCap[numItems];


	//initialize bin containers to 0
	for(int i = 0; i < numItems; i++) {
		binCap[i] = capacity;
	}

	//printArray(binCap, numItems);


	//fill the bins with items
	for(int i = 0; i < numItems; i++) {

		//index of where we are in the bins
		int index = 0;
		bool placed = false;

		while(placed == false) {

			// if we're at the next empty bin
			if(index == numBins) {
				binCap[index] -= items[i];
				placed = true;
				numBins++;
			}

			// looking at the bins that have been opened
			else {

				//if the item can fit in the current bin
				if(binCap[index] - items[i] >= 0) {
					binCap[index] -= items[i];
					placed = true;
				}

				// item can't fit in the opened bins, so increase the index and move to next empty bin
				else {
					index++;
				}
			}

		}

	}

	//printArray(binCap, numItems);


	return numBins;

}

// returns the number of bins taken
int firstFitDecreasing(int *items, int numItems, int capacity) {

	//sort takes in array, and then array+size, then last one for decreasing order
	sort(items, items+numItems,greater<int>());

	int numBins = 0;
	int binCap[numItems];


	//initialize bin containers to 0
	for(int i=0; i < numItems; i++) {
		binCap[i] = capacity;
	}

	//printArray(binCap, numItems);


	//fill the bins with items
	for(int i = 0; i < numItems; i++) {

		//index of where we are in the bins
		int index = 0;
		bool placed = false;

		while(placed == false) {

			// if we're at the next empty bin
			if(index == numBins) {
				binCap[index] -= items[i];
				placed = true;
				numBins++;
			}

			// looking at the bins that have been opened
			else {

				//if the item can fit in the current bin
				if(binCap[index] - items[i] >= 0) {
					binCap[index] -= items[i];
					placed = true;
				}

				// item can't fit in the opened bins, so increase the index and move to next empty bin
				else {
					index++;
				}
			}

		}

	}

	//printArray(binCap, numItems);

	return numBins;

}

int bestFit(int *items, int numItems, int capacity) {

	int numBins = 0;

	// create array for bin capacities
	int binCap[numItems];


	//initialize bin containers to 0
	for(int i = 0; i < numItems; i++) {
		binCap[i] = capacity;
	}

	//printArray(binCap, numItems);

	// put first item in a bin
	binCap[0] -= items[0];
	numBins++;

	// put rest of items in the bins, starting with the second item
	for(int i = 1; i < numItems; i++) {
		int min = capacity;
		int spot = -1;

		for(int j = 0; j < numBins; j++) {
			if(binCap[j]-items[i] >= 0) {
				int tempMin = binCap[j]-items[i];
				if(tempMin < min) {
					min = tempMin;
					spot = j;
				}
			}
		}

		if(spot == -1) {
			binCap[numBins] -= items[i];
			numBins++;
		}

		else {
			binCap[spot] -= items[i];
		}

	}

	//printArray(binCap, numItems);

	return numBins;

}

void readFile() {

	fstream input;
	input.open("bin.txt");

	if(input.is_open()) {

		string line;

		// get number of test cases
		getline(input, line);
		int testCases = atoi(line.c_str());

		for(int i = 0; i < testCases; i++) {

			// get the bin capacity
			getline(input, line);
			int capacity = atoi(line.c_str());

			// get the number of items
			getline(input, line);
			int numItems = atoi(line.c_str());

			int items[numItems];

			for(int j = 0; j < numItems - 1; j++) {
				getline(input, line, ' ');
				items[j] = atoi(line.c_str());
			}

			// get the last item
			getline(input, line);
			items[numItems-1] = atoi(line.c_str());

			//printArray(items, numItems);


			// executing the fits:
			cout << "=================" << endl;
			cout << "Test Case " << i+1 << ": " << endl;

			int first = firstFit(items, numItems, capacity);

			cout << "First fit: " << first << endl;

			int best = bestFit(items, numItems, capacity);

			int ffd = firstFitDecreasing(items, numItems, capacity);

			cout << "First fit decreasing: " << ffd << endl;

			cout << "Best fit: " << best << endl;

		}
	}

}



int main(int argc, char **argv) {

	/*int items[] = {2,2,2,2,2,2,2,2,2,2,6,6,6,6,6,6,6,6,6,6};

	int numBins = firstFit(items, 20, 10);

	cout << "First fit: " << numBins << endl;

	int best = bestFit(items, 20, 10);

	int ffd = firstFitDecreasing(items, 20, 10);

	cout << "First fit decreasing: " << ffd << endl;

	cout << "Best fit: " << best << endl;*/

	readFile();

	return 0;

}

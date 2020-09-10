#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stdio.h>
#include <algorithm>

using namespace std;

void comparisonTable(int *weight, int *profit, int **P, int maxWeight, int numItems) {

	//when the item is 0, then benefit is 0, can't add any weight
	for (int j = 0; j < maxWeight + 1; j++) {
		P[j][0] = 0;
	}

	//when the weight is 0, then benefit is 0, can't add any items
	for (int k = 0; k < numItems + 1; k++) {
		P[0][k] = 0;
	}

	//going through all of the items
	for (int i = 1; i < numItems + 1; i++) {

		//going through all of the weights
		for (int w = 1; w < maxWeight + 1; w++) {

			int item = i - 1; //since the weight and item arrays don't have a slot for weight=0 or item=0, the indexes are shifted; this is an offset for where the item would be

			//if the weight of the item is less than the weight, we can consider it in the solution
			if (weight[item] <= w) {

				if ((profit[item] + P[(w - weight[item])][i - 1]) > P[w][i - 1]) {
					P[w][i] = profit[item] + P[w - weight[item]][i - 1];
				}
				
				else {
					P[w][i] = P[w][i - 1];
				}

			}

			//person can't carry any more
			else {
				P[w][i] = P[w][i - 1];
			}

		}
	}
}

int **allocateArray(int maxWeight, int numItems) {
	int **Profits = new int *[maxWeight + 1];
	
	for (int i = 0; i < maxWeight + 1; i++) {
		Profits[i] = new int[numItems + 1];
	}

	return Profits;
}

void printArray(int maxWeight, int numItems, int **array) {
	cout << "printing:" << endl;
	
	for (int i = 0; i < maxWeight + 1; i++) {
		for (int j = 0; j < numItems + 1; j++) {
			cout << array[i][j];
		}
		cout << endl;
	}
	
}

void deleteArray(int maxWeight, int numItems, int **array) {
	
	for (int i = 0; i < maxWeight + 1; i++) {
		delete[] array[i];
	}

	delete[] array;
}

void findItems(int **P, int *weight, int *profit, int *counts, int maxCarry, int numItems) {

	int w = maxCarry; //index of heaviest weight person can carry

	int i = numItems; //index of the last item

	//therefore, P[w][i] would store the maximum profit for someone who would carry w weight

	//while we haven't found all of the items yet, since profit is not 0
	while (P[w][i] != 0) {

		int item = i - 1;

		//checks if person can carry item with their remainding weight
		if (weight[item] <= w) {

			if ((P[w][i] - P[w - weight[item]][i - 1]) == profit[item]) {
				//cout << "item " << i << " was found" << endl;
				counts[i - 1]++;
				w -= weight[item];
				i--;
			}

			else {
				i--;
			}
		}

		else{
			i--;
		}
	}
}

void calculateProfit(int *profit, int *counts, int items, int &total) {
	for (int i = 0; i < items; i++) {
		total += (counts[i] * profit[i]);
	}
}

void writeObjects(int *array, int personNum, int size) {

	ofstream ofs;

	// if there are going to be multiple lines in the data.txt file, this makes it that whenever we have a new array to sort, the numbers are appended
	// so there will show multiple arrays instead of just 1
	ofs.open("shopping.txt", ios::out | ios::app);
	ofs << "Person " << personNum+1 << ": ";

	for (int i = 0; i < size; i++) {
		if (array[i] == 1) {
			ofs << i + 1 << " ";
		}
	}

	ofs << "\n";

	ofs.close();
}

void readFile() {
	fstream input;
	input.open("input.txt");

	if (input.is_open()) {
		string line;

		//getting number of test cases
		getline(input, line);
		int cases = atoi(line.c_str());

		//for loop to read each case
		for (int i = 0; i < cases; i++) {
			ofstream ofs;
			ofs.open("shopping.txt", ios::out | ios::app);
			ofs << "===============\n";
			ofs << " -=+ Case " << i + 1 << "+=- \n";
			ofs << "Member Items: \n";
			ofs.close();

			cout << "==============" << endl;
			cout << "CASE #" << i + 1 << endl;
			//read in number of items
			getline(input, line);
			int items = atoi(line.c_str());

			int profit[items];	//stores the profit amounts for each item
			int weight[items];	//stores the weight of each item
			int counts[items]; 	//array to store the counts of each item
			int total = 0;			//holds the family total

			//read in item information
			for (int j = 0; j < items; j++) {

				getline(input, line, ' ');
				profit[j] = atoi(line.c_str());
				getline(input, line, '\n');
				weight[j] = atoi(line.c_str());
			}

			//read in number of people in family
			getline(input, line);
			int people = atoi(line.c_str());

			//array to store the carrying capacities of each person
			int maxCarry[people];

			//get the carrying capacities of each person
			for (int k = 0; k < people; k++) {
				getline(input, line);
				int weight = atoi(line.c_str());
				maxCarry[k] = weight;
			}

			//finding the max element in the array
			int *max = max_element(maxCarry, maxCarry + people);

			int maxWeight = *max;

			//create max profit table using the largest weight a person can carry
			int **Profits = allocateArray(maxWeight, items);
			comparisonTable(weight, profit, Profits, maxWeight, items);

			//find the carrying capacity for each person
			for(int i = 0; i < people; i++) {

				//clear counts array
				for(int j = 0; j < items; j++) {
					counts[j] = 0;
				}
				
				//find out how many items each person is getting
				findItems(Profits, weight, profit, counts, maxCarry[i], items);

				//add person's items to family total
				calculateProfit(profit, counts, items, total);

				//append person's earnings to file
				writeObjects(counts, i, items);

				//cout << "total is: " << total << endl;
			}

			cout << "total is: " << total << endl;
			ofs.open("shopping.txt", ios::out | ios::app);
			ofs << "Total: " << total << "\n";
			
			ofs.close();
		
			deleteArray(maxWeight, items, Profits);
		}
	}
}

int main(int argc, char **argv) {

	readFile();

	cout << "Check shopping.txt for all results." << endl;

	return 0;
}

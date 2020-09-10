#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

void printArray(int *array, int length) {

	for(int i = 0; i < length; i++) {
		cout << array[i] << " | ";
	}

	cout << endl;
}

void writeFile(int c, int k, int n, int *coins, int *counts) {
	ofstream ofs;

	ofs.open("change.txt", ios::out | ios::app);
	ofs << "Data input: c = " << c << ", k = "  << k << ", n = " << n << "\n";

	for (int i = k ; i >= 0; i--) {
		ofs << "Denomination: " << coins[i] << " Quantity: " << counts[i] << "\n";
	}

	ofs << "\n";

	ofs.close();
}


void makeChange(int c, int k, int n) {

	cout << " -- Making change for: " << n << " -- "<<endl;

	int length = k+1; // since coins go from c^0 to c^k, the length of the array would be k+1
	int curIndex = k; // highest index of coin array, we'll start here for greedy algorithm

	//arrays to keep the coint amounts and the number of times we used a coin
	int coins[length];
	int counts[length];
	int change = n;

	//filling in coin amounts
	for(int i=0; i < length; i++) {
		coins[i] = (int)(pow(c, i));
	}

		//initializing counts for each coin to be 0
	for(int i=0; i < length; i++) {
		counts[i] = 0;
	}
	cout << "Coins and their corresponding counts: " << endl;
	printArray(coins, length);
	cout << "-----------------------" << endl;


	//array to calculate the change
	while(n > 0) {
		if(n < coins[curIndex]) {
			curIndex--;
		}

		else {
			n -= coins[curIndex];
			counts[curIndex]++;
		}
	}

	//printing the number of coins it took:
	//printArray(counts, length);

	writeFile(c,k,change,coins,counts);
	cout << endl;
}



int main(int argc, char **argv) {
	//cout << "hello world" << endl;
	int c, k, n;
	ifstream input("data.txt");

	string line;

	while(getline(input, line, ' ')) {

		//getline(input, line, ' ');
		c = atoi(line.c_str());
		//cout << "c: " << c << endl;

		getline(input, line, ' ');
		k = atoi(line.c_str());
		//cout << "k: " << k << endl;

		getline(input, line);
		n = atoi(line.c_str());
		//cout << "n: " << n << endl;

		makeChange(c,k,n);
	}

	return 0;
}

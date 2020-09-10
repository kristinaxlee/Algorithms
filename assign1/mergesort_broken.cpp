#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdio.h>

using namespace std;

void merge(int arr[], int lo, int mid, int hi){
	int lSize = mid - lo + 1;
	int rSize = hi - mid;

	int L[lSize];
	int R[rSize];

	for(int i=0; i<lSize; i++) {
		L[i] = arr[i+lo];
	}

	for(int j=0; j<rSize; j++) {
		R[j] = arr[j+mid+1];
	}

	int i = 0; //current index of the left array
	int j = 0; //current index of the right array
	int k = 0; //current displacement
	int length = hi-lo+1; //length of the subsection that we're looking at in array

	for(int k=0; k<length; k++) {
		//if we haven't used all of the elements in the right array and value is smaller, insert
		if(i < lSize && L[i] <= R[j]) {
			arr[lo+k] = L[i];
			i++;
		}

		//if we haven't used all of the elements in the left array and value is smaller, insert
		else if(j < rSize && R[j] < L[i]) {
			arr[lo+k] = R[j];
			j++;
		}

		// when either all elements are used in one sub-array, fill the rest of the array with the unused elements

		else {
			if(i == lSize) {
				arr[lo+k] = R[j];
				j++;
			}
			else {
				arr[lo+k] = L[i];
				i++;
			}
		}
	}

}

//first time function is called, lo is the index of the first number (index 0) and hi is
//the index of the last number in the array
void mergeSort(int arr[], int lo, int hi){

	if(lo < hi) {
		//stores the middle index of the array
		int mid = (lo+hi)/2;

		//divide up the left half of the array
		mergeSort(arr, lo, mid);

		//divide up the right half of the array
		mergeSort(arr, mid+1, hi);

		//merge and sort the two halves
		merge(arr, lo, mid, hi);

	}

}

void printArray(int array[], int size){

	for (int i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}

	cout << endl;
}

void readFile() {
	ifstream numbers("numbers.txt");

	//each line is stored in string called contents

	while(!numbers.eof()) {
		string contents;
		getline(numbers, contents);

		string cur;

		//create a variable to keep track of where we are in the array after getting the first char
		int spot = 0;
		while (contents.at(spot) >= '0' && contents.at(spot) <= '9')
		{
			char ch = contents.at(spot);
			cur.push_back(ch);
			spot++;
		}

		int x = atoi(cur.c_str());
		spot++; //moves spot to the next char

		//array to store the numbers from the text file
		int *array = new int[x];
		int arrIndex = 0;

		int offset = spot;

		//temporary variable to store numbers read in from text file
		string number;

		//initialize array values to 0
		for (int i = 0; i < x; i++)
		{
			array[i] = 0;
		}

		for (int i = 0; i < contents.length() - offset; i++)
		{

			if (contents.at(spot + i) >= '0' && contents.at(spot + i) <= '9')
			{
				char ch = contents.at(spot + i);
				number.push_back(ch);
				if (i == (contents.length() - offset - 1))
				{
					int num = atoi(number.c_str());
					array[arrIndex] = num;
					arrIndex++;
				}
			}

			else
			{
				int num = atoi(number.c_str());
				array[arrIndex] = num;
				arrIndex++;
				number.clear();
			}
		}

		printArray(array, x);	

		delete [] array;
	}
	

}



int main() {
	int arr_size = 0;
	//int *array = readFile(arr_size);
	readFile();

	/*cout << "Unsorted array values" << endl;
	printArray(array, arr_size);

	mergeSort(array, 0, arr_size-1);

	cout << "Sorted array values:" << endl;
	printArray(array, arr_size);

	ofstream ofs;
	ofs.open("merge.out");
	for(int i=0; i<arr_size; i++) {
		ofs << array[i] << "  ";
	}

	ofs << "\n";

	ofs.close();




	delete [] array;*/

	return 0;
}

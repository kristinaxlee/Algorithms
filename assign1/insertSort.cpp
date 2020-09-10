#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdio.h>

using namespace std;

void swap(int *array, int x, int y) {
	int temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

void insertSort(int *array, int length) {

	//start at index 1, so you can start comparing things from the second element on and so forth
	for(int i=1; i<length; i++) {

		// temporary int to hold our current position, so when we enter the while loop
		// we won't get lost and adjust i
		int j = i;

		while(array[j] < array[j-1] && j > 0) {
			swap(array, j, j-1);
			j--;
		}
	}
}

void printArray(int *array, int size) {
	for(int i=0; i<size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

}

void writeFile(int *array, int size)
{
  ofstream ofs;

  // if there are going to be multiple lines in the data.txt file, this makes it that whenever we have a new array to sort, the numbers are appended
  // so there will show multiple arrays instead of just 1

  ofs.open("insert.out", ios::out | ios::app);
  for (int i = 0; i < size; i++)
  {
    ofs << array[i] << " ";
  }

  ofs << "\n";

  ofs.close();
}

void readFile()
{
  ifstream numbers("data.txt");
  while (!numbers.eof())
  {
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

    //printArray(array, x);
    insertSort(array, x);
    //printArray(array, x);
    writeFile(array, x);

    delete[] array;
  }

  numbers.close();
}

int main(int argc, char **argv) {

	readFile();

	return 0;
}

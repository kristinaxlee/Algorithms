#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

void badSort(int *arr, int start, int end, float alpha) {

  int size = end - start + 1;

  if (size == 2 && arr[start] > arr[start + 1]) {
    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
  }

  else if (size > 2) {
    int m = ceil(alpha * size);
    
    badSort(arr, start, start + m - 1, alpha);
    badSort(arr, start + m - 1, end, alpha);
    badSort(arr, start, start + m - 1, alpha);
  }
}

void printArray(int *array, int size) {
  
  for (int i = 0; i < size; i++) {

    cout << array[i] << " ";
 
  }
  cout << endl;
}

void writeFile(int *array, int size) {

  ofstream ofs;

  // if there are going to be multiple lines in the data.txt file, this makes it that whenever we have a new array to sort, the numbers are appended
  // so there will show multiple arrays instead of just 1
  ofs.open("bad.out", ios::out | ios::app);
  for (int i = 0; i < size; i++) {
    ofs << array[i] << " ";
  }

  ofs << "\n";

  ofs.close();
}

void readFile(float alpha)
{
  ifstream numbers("data.txt");

  //while there are still lines left in the data file, keep reading them and sorting the arrays
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

    //takes the rest of the numbers in the line and inserts it into an array
    for (int i = 0; i < contents.length() - offset; i++)
    {
      //reads chars and appends it to a string until a space is encountered, and then turns the string into an int and stores into the data array
      if (contents.at(spot + i) >= '0' && contents.at(spot + i) <= '9')
      {
        char ch = contents.at(spot + i);
        number.push_back(ch);

        // this is for when we're at the last number in the array, since there won't be a space after it
        // if we're at the last index, this means that this is the last number and it won't reach the else statement, so we have to input the number into the array here
        if (i == (contents.length() - offset - 1))
        {
          int num = atoi(number.c_str());
          array[arrIndex] = num;
          arrIndex++;
        }
      }

      //if here, we've reached a space, and now it's time to convert the string into a number and insert it into the array
      else
      {
        int num = atoi(number.c_str());
        array[arrIndex] = num;
        arrIndex++;
        number.clear();
      }
    }

    //send data array to get sorted with merge sort
    //mergeSort(array, 0, x - 1);

    //write the results to merge.out
    cout << "array before sorting: " << endl;
    printArray(array, x);
    badSort(array, 0, x-1, alpha);
    cout << "array after sorting: " << endl;
    printArray(array, x);
    writeFile(array, x);

    delete[] array;
  }

  numbers.close();
}


int main(int argc, char **argv) {
  float alpha;
  cout << "Enter a number for alpha: " << endl;
  cin >> alpha;
  cout << alpha << endl;
  readFile(alpha);
	return 0;
}

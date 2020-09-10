#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <stdio.h>

using namespace std;

//merges two halves of an array, and sorts it
void merge(int arr[], int lo, int mid, int hi)
{
  int lSize = mid - lo + 1;
  int rSize = hi - mid;

  int L[lSize];
  int R[rSize];

  for (int i = 0; i < lSize; i++)
  {
    L[i] = arr[i + lo];
  }

  for (int j = 0; j < rSize; j++)
  {
    R[j] = arr[j + mid + 1];
  }

  int i = 0;  //current index of the left array
  int j = 0;  //current index of the right array
  int k = 0;  //current displacement
  int length = hi - lo + 1; //length of the subsection that we're looking at in array

  for (int k = 0; k < length; k++)
  {
    //if we haven't used all of the elements in the right array and value is smaller, insert
    if (i < lSize && L[i] <= R[j])
    {
      arr[lo + k] = L[i]; //insert the sorted numbers back into the original array
      i++;
    }

    //if we haven't used all of the elements in the left array and value is smaller, insert
    else if (j < rSize && R[j] < L[i])
    {
      arr[lo + k] = R[j];
      j++;
    }

    // when either all elements are used in one sub-array, fill the rest of the array with the unused elements
    else
    {
      if (i == lSize)
      {
        arr[lo + k] = R[j];
        j++;
      }
      else
      {
        arr[lo + k] = L[i];
        i++;
      }
    }
  }
}

//first time function is called, lo is the index of the first number (index 0) and hi is
//the index of the last number in the array
void mergeSort(int arr[], int lo, int hi)
{

  if (lo < hi) {
    //stores the middle index of the array
    int mid = (lo + hi) / 2;

    //divide up the left half of the array
    mergeSort(arr, lo, mid);

    //divide up the right half of the array
    mergeSort(arr, mid + 1, hi);

    //merge and sort the two halves
    merge(arr, lo, mid, hi);
  }
}

//function for debugging purposes
void printArray(int array[], int size)
{

  for (int i = 0; i < size; i++)
  {
    cout << array[i] << " ";
  }

  cout << endl;
}

void writeFile(int *array, int size)
{
  ofstream ofs;

  // if there are going to be multiple lines in the data.txt file, this makes it that whenever we have a new array to sort, the numbers are appended
  // so there will show multiple arrays instead of just 1
  ofs.open("merge.out", ios::out | ios::app);
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
    mergeSort(array, 0, x - 1);

    //write the results to merge.out
    writeFile(array, x);

    delete[] array;
  }

  numbers.close();
}

int main()
{
  //reads input file and puts numbers into an array
  readFile();

  return 0;
}

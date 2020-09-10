#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;

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

  if (lo < hi)
  {
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
    std::cout << array[i] << " ";
  }

  std::cout << std::endl;
}


int main() {
  int array[20000];

  for(int i=0;i<20000; i++) {
    array[i] = rand() % 10001;
  }

  std::cout << "Array size: 20000" << std::endl;

  //auto start = std::chrono::high_resolution_clock::now();

  auto start = high_resolution_clock::now();
  mergeSort(array, 0, 19999);
  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop-start).count();

  std::cout << "Time: " << duration << std::endl;

  return 0;
}

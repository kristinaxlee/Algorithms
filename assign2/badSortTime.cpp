#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>

using namespace std::chrono;

//constant to help speed up process of collecting data
#define SIZE 2500

void badSort(int *arr, int start, int end, float alpha)
{

  int size = end - start + 1;

  if (size == 2 && arr[start] > arr[start + 1])
  {
    int temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;
  }

  else if (size > 2)
  {
    int m = 0;
    m = ceil(alpha * size);

    badSort(arr, start, start + m - 1, alpha);
    badSort(arr, start + m - 1, end, alpha);
    badSort(arr, start, start + m - 1, alpha);
  }
}


int main(int argc, char **argv)
{
  float alpha;
  std::cout << "Enter a decimal number for alpha: " << std::endl;
  std::cin >> alpha;

  int array[SIZE];

  for (int i = 0; i < SIZE; i++)
  {
    array[i] = rand() % 10001;
  }
  std::cout << "array size: " << SIZE << std::endl;

  //auto start = std::chrono::high_resolution_clock::now();

  auto start = high_resolution_clock::now();
  badSort(array, 0, SIZE - 1, alpha);
  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop - start).count();

  std::cout << "Time: " << duration << std::endl;

  return 0;
}

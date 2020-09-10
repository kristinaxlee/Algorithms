#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std::chrono;

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


int main() {
  int array[5000];

  for(int i=0;i<5000; i++) {
    array[i] = rand() % 10001;
  }

  std::cout << "Array size: 5000" << std::endl;

  //auto start = std::chrono::high_resolution_clock::now();

  auto start = high_resolution_clock::now();
  insertSort(array, 5000);
  auto stop = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>(stop-start).count();

  std::cout << "Time: " << duration << std::endl;

  return 0;
}

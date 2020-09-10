For badSort, make sure that data.txt is in the same directory.
This program accepts user input for alpha as a decimal. Ex: 0.66, 0.75. It will not accept input such as 2/3 or 3/4.

This algorithm uses the fixed version of badSort where if alpha > 0.66, the split is converted to the floor of alpha*n.

To compile badSort.cpp, execute the following command:
g++ -o badSort badSort.cpp

Then to run badSort.cpp, execute the following:
./badSort



This algorithm is not fixed. I tried using my fixed version when running it on large array sizes and I got core dumps. When you want to use this algorithm for
n > 0.66, replace line 27 with m = floor(alpha * size);

To compile badSortTime.cpp, execute the following command:
g++ -std=c++11 -o badSortTime badSortTime.cpp

Then to run badSortTime.cpp, execute the following:
./badSortTime



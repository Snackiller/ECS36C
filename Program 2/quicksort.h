// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int& numMemAcc, int& numComp);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& numMemAcc, int& numComp);
int Partition(std::vector<int>* numbers, int i, int k, int& numMemAcc, int& numComp);
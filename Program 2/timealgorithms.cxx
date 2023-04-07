
#include<iostream>
#include<fstream>
#include<vector>
#include<chrono>
#include"quicksort.h"
#include"insertionsort.h"
#include"mergesort.h"
#include"json.hpp"
using namespace std;

int main(int argc, char** argv) {
    if (argc!=2) { //check if correct files are entered
		printf("Usage: %s file.json\n", argv[0]); //remind user to enter correct input
		return EXIT_FAILURE; //exit code if the amount of argument is not equal to 2.
	}
    ifstream file;// read file
    file.open(argv[1]); //open input file
    nlohmann::json jsonObj; //create json object
    if(file.is_open()){ //read contents of file 
        file >> jsonObj;// put content into json object
    }
    file.close();//close file

    const int MAX_NUM_SAMPLES=jsonObj["metadata"]["numSamples"]; //store number of samples
    const int MAX_ARRAY_SIZE = jsonObj["metadata"]["arraySize"]; //store the length

    cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTIme,QuickSortCompares,QuickSortMemaccess" << endl;
    //first line of output

    for (int i = 1; i <= MAX_NUM_SAMPLES; i++){// go through every sample

        vector<int> needSort;//new vector of unsorted saomples

        for (auto j = 0; j < MAX_ARRAY_SIZE; j++) {// for every index in the array
            if(i<10)// for sample 1 to 9
            {
                needSort.push_back(jsonObj["Sample0"+to_string(i)][j]);
            }
            else// for sample 10 and up
            {
                needSort.push_back(jsonObj["Sample"+to_string(i)][j]);
            }
        }

        //Store the to needSort array into three new vectors to seperate them in the three runtime methods. 
        vector<int> insertionSorted = needSort; //create vector to store insertion sort
        vector<int> insemergeSorted = needSort; //create vector to store merge sort
        vector<int> quickSorted = needSort; //create vector to store quick sort

        int insertComp = 0;// create insert comparison counter
        int insertMemAcc = 0;// create insert memory access counter
        auto start = chrono::high_resolution_clock::now();//start timer
        InsertionSort(&insertionSorted, insertMemAcc, insertComp);
        auto end = chrono::high_resolution_clock::now();//end timer
        double insert_time = chrono::duration<double, micro>(end - start).count(); //store time for insert

        int mergeComp = 0; //create merge comparison counter
        int  mergeMemAcc = 0; //create merge memory access counter
        start = chrono::high_resolution_clock::now();//start timer
        MergeSort(&insemergeSorted, mergeMemAcc, mergeComp);
        end = chrono::high_resolution_clock::now();//end timer
        double merge_time = chrono::duration<double, micro>(end - start).count(); //store time for merge

        int quickComp = 0; //create quick comparison counter
        int quickMemAcc = 0; //create quick memory access counter
        start = chrono::high_resolution_clock::now(); //start timer
        QuickSort(&quickSorted, quickMemAcc ,quickComp);
        end = chrono::high_resolution_clock::now();//end timer
        double quick_time = chrono::duration<double, micro>(end - start).count(); //store time for quick
        if(i<10) //print out csv file with ',' between each value 
        {
            cout << "Sample0"+to_string(i) << ',' << insert_time << ',' << insertComp << ',' << insertMemAcc << ',' << merge_time << ','  << mergeComp << ',' << mergeMemAcc << ',' << quick_time << ','  << quickComp << ',' << quickMemAcc << endl;
        }
        else
        {
            cout << "Sample"+to_string(i) << ',' << insert_time << ',' << insertComp << ',' << insertMemAcc << ',' << merge_time << ','  << mergeComp << ',' << mergeMemAcc << ',' << quick_time << ','  << quickComp << ',' << quickMemAcc << endl;
        }
    }
    return 0;
}//end of main()
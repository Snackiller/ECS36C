#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
int main(int argc, char** argv) {
    if (argc!=3) {//determine whether the numbers of file is 3
		printf("Usage: %s file1.json file2.json\n", argv[0]);//print the format
		return EXIT_FAILURE;//return value exception
	}
    ifstream file1;//build a file
    ifstream file2;//build a file
	file1.open(argv[1]);//open testfile1
    file2.open(argv[2]);//open testfile2
    json samples1;//create a json to store testfile1
    json samples2;//create a json to store testfile2
    json result;//create a json for output
    file1>>samples1;//send testfile1 data to json sample1
    file2>>samples2;//send testfile1 data to json sample2
    result["metadata"]["File1"]=samples1["metadata"];//get the information in metadata of sample1
    result["metadata"]["File1"]["name"]=argv[1];//get the file name of sample1
    result["metadata"]["File2"]=samples2["metadata"];//get the information in metadata of sample2
    result["metadata"]["File2"]["name"]=argv[2];//get the file name of sample2
    int count=0;//for the number of conflicting
    int Conflicting=0;//for determine whether the numbers in json has conflicting
    int numSamples=samples1["metadata"]["numSamples"];//get the number of samples
    int arraySize=samples1["metadata"]["arraySize"];//get the number of array sizes
    for(int i=1;i<=numSamples;i++)//check sample from start to end
    {
        for(int j=0;j<arraySize;j++)//check the array from start to end
        {
            if(i<10)//determine to use which format
            {
                if(samples1["Sample0"+to_string(i)][j]!=samples2["Sample0"+to_string(i)][j])//determine whether the numbers in two samples has conflicting
                {
                    Conflicting=1;//it is a conflicting
                    result["Sample0"+to_string(i)]["Mismatches"][to_string(j)][0]=samples1["Sample0"+to_string(i)][j];//put the conflicting number in result
                    result["Sample0"+to_string(i)]["Mismatches"][to_string(j)][1]=samples2["Sample0"+to_string(i)][j];//put the conflicting number in result
                }
            }
            else//i>=10
            {
                if(samples1["Sample"+to_string(i)][j]!=samples2["Sample"+to_string(i)][j])//determine whether the numbers in two samples has conflicting
                {
                    Conflicting=1;
                    result["Sample"+to_string(i)]["Mismatches"][to_string(j)][0]=samples1["Sample"+to_string(i)][j];//put the conflicting number in result
                    result["Sample"+to_string(i)]["Mismatches"][to_string(j)][1]=samples2["Sample"+to_string(i)][j];//put the conflicting number in result
                }
            }
        }
        if(Conflicting==1)
        {
            count++;//number of conflicting add 1
            Conflicting=0;//change conflicting to 1
            if(i<10)//determine to use which format
            {
                result["Sample0"+to_string(i)][argv[1]]=samples1["Sample0"+to_string(i)];//put the number in samples to result
                result["Sample0"+to_string(i)][argv[2]]=samples2["Sample0"+to_string(i)];//put the number in samples to result
            }
            else//i>=10
            {
                result["Sample"+to_string(i)][argv[1]]=samples1["Sample"+to_string(i)];//put the number in samples to result
                result["Sample"+to_string(i)][argv[2]]=samples2["Sample"+to_string(i)];//put the number in samples to result
            }
        }
    }
    result["metadata"]["samplesWithConflictingResults"]=count;//get the count of inversion
    cout<<result.dump(2)<<endl;//print the result 
    file1.close();//close the testfile;
    file2.close();//close the testfile;
    return 0;//normal return
}
#include <cstdio>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
int main(int argc, char** argv) {
    if (argc!=2) {//determine whether the numbers of file is 2
		printf("Usage: %s file.json\n", argv[0]);//print the format
		return EXIT_FAILURE;//return value exception
	}
    ifstream in;//build a file
	in.open(argv[1]);//open testfile
    json samples;//create a json to store testfile
    json result;//create a json for output
    in>>samples;//send testfile data to json
    result["metadata"]=samples["metadata"];//get the information in metadata
    result["metadata"]["file"]=argv[1];//get the file name
    int count=0;//for the number of inversion
    int Inversion=0;//for determine whether the numbers in json has inversion
    int numSamples=samples["metadata"]["numSamples"];//get the number of samples
    int arraySize=samples["metadata"]["arraySize"];//get the number of array sizes
    for(int i=1;i<=numSamples;i++)//check sample from start to end
    {
        for(int j=0;j<arraySize-1;j++)//check the array from start to end
        {
            if(i<10)//determine to use which format
            {
                if(samples["Sample0"+to_string(i)][j]>samples["Sample0"+to_string(i)][j+1])//determine whether the numbers in the order are inversion
                {
                    Inversion=1;//it is a inversion
                    result["Sample0"+to_string(i)]["ConsecutiveInversions"][to_string(j)][0]=samples["Sample0"+to_string(i)][j];//put the inversion number in result
                    result["Sample0"+to_string(i)]["ConsecutiveInversions"][to_string(j)][1]=samples["Sample0"+to_string(i)][j+1];//put the inversion number in result
                }
            }
            else//i>=10
            {
                if(samples["Sample"+to_string(i)][j]>samples["Sample"+to_string(i)][j+1])//determine whether the numbers in the order are inversion
                {
                    Inversion=1;//it is a inversion
                    result["Sample"+to_string(i)]["ConsecutiveInversions"][to_string(j)][0]=samples["Sample"+to_string(i)][j];//put the inversion number in result 
                    result["Sample"+to_string(i)]["ConsecutiveInversions"][to_string(j)][1]=samples["Sample"+to_string(i)][j+1];//put the inversion number in result
                }
            }
        }
        if(Inversion==1)//if it is inversion
        {
            count++;//number of inversion add 1
            Inversion=0;//change inversion to 1
            if(i<10)//determine to use which format
            {
                result["Sample0"+to_string(i)]["sample"]=samples["Sample0"+to_string(i)];//put the number in samples to result
            }
            else//i>=10
            {
                result["Sample"+to_string(i)]["sample"]=samples["Sample"+to_string(i)];//put the number in samples to result
            }
        }
    }
    result["metadata"]["samplesWithInversions"]=count;//get the count of inversion
    cout<<result.dump(2)<<endl;//print the result 
    in.close();//close the testfile;
    return 0;//normal return
}
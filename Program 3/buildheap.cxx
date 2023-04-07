#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;
using json = nlohmann :: json; 
json jsonObject;
json newObject;
int length = 0;
int maxHeapSize = 0;
int numOperations = 0;

int main(int argc, char** argv) {
  std :: ifstream file;
  file.open(argv[1]);
  if(file.is_open()){
    file >> jsonObject; 
  }
  file.close();
  
  maxHeapSize = jsonObject["metadata"]["maxHeapSize"];

  PriorityQueue p1(maxHeapSize);

  for(auto itr = jsonObject.begin();itr != jsonObject.end();++itr){
    length++;
  }

  numOperations = length - 1;

  for(auto itr = jsonObject.begin();itr != jsonObject.end();++itr){
    if(length>1){
      //auto key = jsonObject[itr.key()]["key"];
      string operation = jsonObject[itr.key()]["operation"];
      if(operation == "insert"){
        double key = jsonObject[itr.key()]["key"];
        p1.insert(key);
      }
      if(operation == "removeMin"){
        p1.removeMin();
      }
      //auto x = itr.value()["operation"];  Alternative way to find operation
      length--;
    }
  }
  newObject = p1.JSON();
  newObject["metadata"]["numOperations"] = numOperations;

  cout << newObject.dump(2) << endl;
}

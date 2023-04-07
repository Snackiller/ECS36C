#include <iostream>
#include <fstream>
#include <string>
#include <stdbool.h>
#include <vector>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;
using json = nlohmann :: json; 
json jsonObject;
json result;
vector<int> playersinteams;
vector<int> foundj;
int counter = 0;
int n = 0;
int player1 = 0;
int player2 = 0;
Key targetkey = 0;


int main(int argc, char** argv) {
  std :: ifstream file;
  file.open(argv[1]);
  if(file.is_open()){
    file >> jsonObject; 
  }
  file.close();
  n = jsonObject["metadata"]["numPlayers"];

  for(unsigned long int i = 0; i < (unsigned long int)jsonObject["teamStats"].size(); i++){
    counter++;
  }
  PriorityQueue p1(counter);
  for(int i = 0; i < counter; i++){
    p1.insert(abs((double)jsonObject["teamStats"][i]["winPercentage"] - 50));
  }

  for(int i = 0; i < counter; i++){
    targetkey = p1.min().first;
    for(int j = 0; j < counter; j++){
      if(abs((double)jsonObject["teamStats"][j]["winPercentage"] - 50) == targetkey){
        foundj.push_back(j);
      }
    }
    player1 = jsonObject["teamStats"][foundj[0]]["playerOne"];
    player2 = jsonObject["teamStats"][foundj[0]]["playerTwo"];
    
    if(!(std :: count(playersinteams.begin(),playersinteams.end(),player1)) && !(std :: count(playersinteams.begin(),playersinteams.end(),player2))){
      playersinteams.push_back(player1);
      playersinteams.push_back(player2);
    }
    foundj.clear();
    p1.removeMin();
  }  
  int x;
  unsigned long int n=playersinteams.size()/2;
  for(unsigned long int i=0;i<n;i++)
  {
    x=2*i;
    result["teams"][i][0]=playersinteams[x];
    result["teams"][i][1]=playersinteams[x+1];
    
  }
  cout << result.dump(2) << endl;
}

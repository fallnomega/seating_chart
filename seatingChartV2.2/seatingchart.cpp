#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "agents.h"
using namespace std;



int menu();
ostream& operator<<(ofstream, vector<const Agent*>);
ostream& operator<<(ostream& out, const Agent* agent);
//vector<const Agent*> text(vector<const Agent*> agents);
void printToFile(const vector<const Agent*>);
vector<const Agent*> dat(vector<const Agent*> agents);
vector<const Agent*> addAgent(vector<const Agent*> agents);
vector<const Agent*> deleteAgent(vector<Agent*> agents);
vector<const Agent*> text(vector<const Agent*> agents);
vector<const Agent*> editAgent(vector<Agent*> agents);
vector<const Agent*> deskMove(vector<const Agent*> agents);

int main()
{
  vector<const Agent*> agents; 
  cout << "Seating Chart\n-------------\n\n";
  while (true)
  {
    int choice = menu();
    if(choice==1)agents =dat(agents);//if choice 1
    if(choice==2) printToFile(agents);//if choice 2
    if(choice==3)
    {
      vector<const Agent*>::iterator it;
      for(it=agents.begin();it!=agents.end();it++)cout << *it;
    }//if choice 3
    if(choice==4) agents = addAgent(agents); //if choice = 4
    if(choice==5) agents = deleteAgent(agents);//if choice = 5
    if(choice==6) agents = editAgent(agents);//if choice = 6
    if(choice==7) agents = deskMove(agents);
    if(choice==99) break;//if choice 99
    if(choice==9988) agents =text(agents);
  }//while
}//main

/////////////
//functions//
/////////////






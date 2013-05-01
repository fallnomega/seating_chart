#include "agents.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
const char* delim = "\t";
void Agent::print() const
{
  cout << setw(15);
  cout << "Location: " <<  location<< "\tName: ";;
cout << setw(20);
cout  << name << "\tUUID: " 
    << uuid << endl;
};

int menu()
{
  int choice;
  cout << "\tMENU\n\t----\n\n[1]Pull from seating.dat\n[2]Export to seating.dat\n[3]Print listing\n[4]Add to list\n[99]Quit\n";
  cin >> choice;
  return choice;
};

void printToFile(vector<const Agent*> agents)
{
  ofstream fout;
  fout.open("seatingTestOut.dat",ios::out|ios::binary);
  

      vector<const Agent*>::iterator it;
      for(it=agents.begin();it!=agents.end();it++)
      {

        fout <<   (*it)->location  << "\t" << (*it)->name << "\t" 
          << (*it)->uuid << "\t"<< (*it)->om  << "\t" << (*it)->desktop << "\t" 
          << (*it)->monitor << endl;
      }
  fout.close();
};

vector<const Agent*> dat(vector<const Agent*> agents)
{
  ifstream fin;
  fin.open("seatingchart.dat",ios::in|ios::binary);
    if(!fin.good()) return agents; //file not found //file not found
  while(!fin.eof())
  {
    char name[512];
    fin.getline(name,512);

    //index
    int index = 0;

    //array for index of entries
    const char * token[6] = {};
    token[0]=strtok(name,delim);
    if(token[0])
    {
      for(index=1;index<6;index++)
      {
        token[index]=strtok(0,delim);
        if(!token[index]) token[index] = "0";//break;
      }//for token
    }//if token
    for (int i =0;i<index;i++)//for looop to build objects into agent array elements
    {
     const Agent* const s = new Agent(token);
      agents.push_back(s);
      break;
    }//for
  
  }//while
  return agents;
};
vector<const Agent*> addAgent(vector<const Agent*> agents)
{
  string uuid;
  string name;
  string om;
  string location;
  string desktop;
  string monitor;
  cout << "Provide UUID, Name, OM, Location, Desktop Asset tag, and Monitor Asset tag.\n"
    << "Type in the following with no spaces except between the fields.\n"
    << "Example: sm1111 Smith,John OM-NAME 3N000FFF CD1234567 HP6789098\n->:";
  cin >> uuid >> name >> om >> location >> desktop >> monitor;
  Agent* s =new Agent(uuid,name, om, location, desktop , monitor);
  agents.push_back(s);
  return agents;
};


vector<const Agent*> deleteAgent(vector<const Agent*> agents)
{
  int nCount = 1;
  string dUUID = "jj1111";
  vector<const Agent*>::iterator it;
  for(it=agents.begin();it<agents.end();it++)
  {
    if ((*it)->uuid == dUUID)
    {
      agents.erase(it);
      return agents;
    }
  }
  return agents;
}

vector<const Agent*> text(vector<const Agent*> agents)
{
    ifstream fin;
  fin.open("seatingTestTXT.txt");
  if(!fin.good()) return agents; //file not found
  while(!fin.eof())
  {
    char name[512];
    fin.getline(name,512);

    //index
    int index = 0;

    //array for index of entries
    const char * token[6] = {};
    token[0]=strtok(name,delim);
    if(token[0])
    {
      for(index=1;index<6;index++)
      {
        token[index]=strtok(0,delim);
        if(!token[index]) token[index] = "0";//break;
      }//for token
    }//if token
    for (int i =0;i<index;i++)//for looop to build objects into agent array elements
    {
     const Agent* const s = new Agent(token);
      agents.push_back(s);
      break;
    }//for
  
  }//while
  return agents;
}
#include "agents.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

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
  cout << "\tMENU\n\t----\n\n[1]Pull from seating.dat\n[2]Export to seating.dat\n"
    <<"[3]Print listing\n[4]Add to list\n[5]Delete agent\n[6]Edit agent\n"
    << "[99]Quit\n";
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

    //to upper case
    int i = 0;
    char c;
    while(name[i])
    {
      name[i] = toupper(name[i]);
      i++;
    }

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
  cout << "\nEnter Agents UUID: ";
  string dUUID;
  cin >> dUUID;
  cin.ignore(1000,10);
  transform(dUUID.begin(),dUUID.end(),dUUID.begin(),toupper);
  vector<const Agent*>::iterator it;
  for(it=agents.begin();it<agents.end();it++)
  {
    if ((*it)->uuid == dUUID)
    {
      cout << "Confirm you want to delete:\n";
      (*it)->print();
      cout << "\nDelete? [y/n]:";
      char choice;
      cin >> choice;
      cin.ignore(1000,10);
      if(choice =='y')
      {
        agents.erase(it);
        return agents;
      }
      else return agents;
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

ostream& operator<<(ostream& out, const Agent* agent)
{
  agent->print();
  return out;
};

vector<const Agent*> editAgent(vector<const Agent*> agents)
{
  cout << "Enter UUID or Cubicle to edit: ";
  string entry;
  cin >> entry;
  cin.ignore(1000,10);
  transform(entry.begin(),entry.end(),entry.begin(),toupper);
  for(int it=0;it<agents.size();it++)
  {
    if(agents[it]->uuid == entry || agents[it]->location == entry)
    {
      agents[it]->print();
      cout << endl << "What would you like to update:\n"
        << "[1]Name\t[2]UUID\n[3]OM\t[4]Location\n[5]Desktop\t[6]Monitor\n\nChoice:>";
      string ctemp;
      cin >> ctemp;
      char choice;
      cin.ignore(1000,10);
      choice = atoi(ctemp.c_str());
      if(choice==1)
      {
        cout << "Full Name To be created \"Firstname Lastname\"" << endl;
        string tempName;
        getline(cin, tempName);
        cout << "Confirm you want to replace:\n"
          << agents[it]->name << " with " << tempName << " ?";
        cout << "\nReplace? [y/n]:";
        char yayNay;
        cin >> yayNay;
        cin.ignore(1000,10);
        if(yayNay =='y')
        {
          Agent* temp = new Agent(agents[it]->uuid,tempName, agents[it]->om,agents[it]->location,agents[it]->desktop,agents[it]->monitor);
          agents.push_back(temp);
          agents.erase(agents.begin()+it);
          return agents;
        }
      }//choice 1

      if(choice==2)
      {
        cout << "UUID To be created : " << endl;
        string tempName;
        getline(cin, tempName);
        cout << "Confirm you want to replace:\n"
          << agents[it]->uuid << " with " << tempName << " ?";
        cout << "\nReplace? [y/n]:";
        char yayNay;
        cin >> yayNay;
        cin.ignore(1000,10);
        if(yayNay =='y')
        {
          Agent* temp = new Agent(tempName,agents[it]->name, agents[it]->om,agents[it]->location,agents[it]->desktop,agents[it]->monitor);
          agents.push_back(temp);
          agents.erase(agents.begin()+it);
          return agents;
        }
      }//choice 2
      if(choice==3)
      {
        cout << "OM To be created : " << endl;
        string tempName;
        getline(cin, tempName);
        cout << "Confirm you want to replace:\n"
          << agents[it]->om << " with " << tempName << " ?";
        cout << "\nReplace? [y/n]:";
        char yayNay;
        cin >> yayNay;
        cin.ignore(1000,10);
        if(yayNay =='y')
        {
          Agent* temp = new Agent(agents[it]->uuid,agents[it]->name, tempName,agents[it]->location,agents[it]->desktop,agents[it]->monitor);
          agents.push_back(temp);
          agents.erase(agents.begin()+it);
          return agents;
        }

      }//choice 3
      if(choice==4)
      {
        cout << "Location To be created : " << endl;
        string tempName;
        getline(cin, tempName);
        cout << "Confirm you want to replace:\n"
          << agents[it]->location << " with " << tempName << " ?";
        cout << "\nReplace? [y/n]:";
        char yayNay;
        cin >> yayNay;
        cin.ignore(1000,10);
        if(yayNay =='y')
        {
          Agent* temp = new Agent(agents[it]->uuid,agents[it]->name, agents[it]->om,tempName,agents[it]->desktop,agents[it]->monitor);
          agents.push_back(temp);
          agents.erase(agents.begin()+it);
          return agents;
        }
      }//choice 4
      if(choice==5)
      {
        cout << "Desktop Asset To be created : " << endl;
        string tempName;
        getline(cin, tempName);
        cout << "Confirm you want to replace:\n"
          << agents[it]->desktop << " with " << tempName << " ?";
        cout << "\nReplace? [y/n]:";
        char yayNay;
        cin >> yayNay;
        cin.ignore(1000,10);
        if(yayNay =='y')
        {
          Agent* temp = new Agent(agents[it]->uuid,agents[it]->name, agents[it]->om ,agents[it]->location,tempName,agents[it]->monitor);
          agents.push_back(temp);
          agents.erase(agents.begin()+it);
          return agents;
        }
      }//choice 5
      if(choice==6)
      {
        cout << "Monitor Asset To be created" << endl;
        string tempName;
        getline(cin, tempName);
        cout << "Confirm you want to replace:\n"
          << agents[it]->monitor << " with " << tempName << " ?";
        cout << "\nReplace? [y/n]:";
        char yayNay;
        cin >> yayNay;
        cin.ignore(1000,10);
        if(yayNay =='y')
        {
          Agent* temp = new Agent(agents[it]->uuid,agents[it]->name, agents[it]->om,agents[it]->location,agents[it]->desktop,tempName);
          agents.push_back(temp);
          agents.erase(agents.begin()+it);
          return agents;
        }
      }//choice 6
      else return agents;
    }
  }//for
  return agents;
}

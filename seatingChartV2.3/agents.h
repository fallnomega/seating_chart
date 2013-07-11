#ifndef AGENTS_H
#define AGENTS_H
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ofstream;
using namespace std;
class Agent
{
protected:
  string uuid;
  string name;
  string om;
  string location;
  string desktop;
  string monitor;
public:
  Agent();
  Agent(string uuid1,string name1, string om1, string location1, string desktop1,string monitor1):
    uuid(uuid1),
    name(name1),
    om(om1),
    location(location1),
    desktop(desktop1),
    monitor(monitor1)
    {};
  Agent(const char* const token[6]):location(token[0]),name(token[1]),uuid(token[2]),om(token[3]),desktop(token[4]),monitor(token[5]){};
  //copy constructor
  Agent(const Agent &temp)
  {
    uuid = temp.uuid;
    location =temp.location;
    name = temp.name;
    om = temp.om;
    desktop = temp.desktop;
    monitor = temp.monitor;
  }
  friend void printToFile(vector<const Agent*> agents);
  friend vector<const Agent*> deskMove(vector<const Agent*> agents);
  friend vector<const Agent*> deleteAgent(vector<const Agent*> agents);
  friend vector<const Agent*> editAgent(vector<const Agent*> agents);
  void print() const;
  ~Agent(){};

};


//class Agent_Desk
//{
//protected:
//
//public:
//  ~Agent_Desk(){};
//  void print() const;
//};



#endif
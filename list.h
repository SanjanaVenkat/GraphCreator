#include <iostream>
#include <cstring>

using namespace std;


class Vertex {
 public:
  Vertex(char* l, int e, int d, bool v);
  ~Vertex();
  Vertex* getNext();
  void setNext(Vertex* newnext);
  int getDistance();
  void setDistance(int d);
  int getEdge();
  void setEdge(int e);
  char* getLabel();
  void setLabel(char* l);
  bool getVisited();
  void setVisited(bool v);
 private:
  Vertex* next;
  int edge;
  int distance;
  char label[1000];
  bool visited;
};

#include <iostream>
#include <cstring>
#include "list.h"

using namespace std;

Vertex* addvertex(Vertex* root);
void printVertices(Vertex* root);
void printTable(Vertex* root, int array[20][20]);
int addEdge(Vertex* root, int array[20][20]);
void shortestPath(Vertex* root, int array[20][20]);

Vertex* addvertex(Vertex* root) {
  char vertexlabel[1];
  Vertex* current = root;
  cout << "Adding vertex" << endl;
  cout << "Enter a letter to be the label of your vertex" << endl;
  cin >> vertexlabel;
  Vertex* vertex = new Vertex(vertexlabel, 0, 0, false);
  cout << "Vertex has been added" << endl;
  if (current == NULL) {
    current = vertex;
    root = current;
  }
  else {
    while (current->getNext() != NULL) {
      current = current->getNext();
    }
    current->setNext(vertex);
  }
  return root;
}

void printVertices(Vertex* root) {
  Vertex* current = root;
  while (current != NULL) {
    cout << current->getLabel() << " " << current->getDistance() << endl;
    current = current->getNext();
  }
  
}

void printTable(Vertex* root, int array[20][20]) {
  int counter = 0;
  Vertex* current = root;
  while (current != NULL) {
    counter++;
    current = current->getNext();
  }
  current = root;
  cout << "  ";
  while (current != NULL) {
  cout << current->getLabel() << " ";
  current = current->getNext();
  }
  cout << endl;
  current = root;
  for (int i = 0; i < counter; i++) {
    cout << current->getLabel() << " ";
    for (int j = 0; j < counter; j++) { 
      cout << array[i][j] << " ";
    }
    cout << endl;
    current = current->getNext();
  }
}

int addEdge(Vertex* root, int array[20][20]) {
  char firstedge[1000];
  char secondedge[1000];
  cout << "Enter the label of the vertex that your edge starts from" << endl;
  cin >> firstedge;
  cout << "Enter the label of the vertex that your edge ends at" << endl;
  cin >> secondedge;
  int counter = 0;
  int firstcounter = 0;
  int secondcounter = 0;
  Vertex* current = root;
  while (current != NULL) {
    //    counter++;
    if(strcmp(current->getLabel(), firstedge) == 0) {
      firstcounter = counter;
    }
    if (strcmp(current->getLabel(), secondedge) == 0) {
      secondcounter = counter;
    }
    counter++;
    current = current->getNext();
  }
  int edgeweight;
  cout << "Enter the weight of the edge" << endl;
  cin >> edgeweight;
  array[firstcounter][secondcounter] = edgeweight;
  return edgeweight;
}

void shortestPath(Vertex* root, int array[20][20]) {
  char firstnode[1000];
  char secondnode[1000];
  cout << "Enter the label of the node that your path will start from" << endl;
  cin >> firstnode;
  cout << "Enter the label of the node that your path will end on" << endl;
  cin >> secondnode;
  int totaldistance = 0;
  int moverdistance = 0;
  int firstcounter = 0;
  int counter = 0;
  int secondcounter = 0;
  int extracounter = 0;
  Vertex* current = root;
  bool done = false;
  while (current != NULL) {
    //current is root, do setup
    if (done == false) {
      cout << "Here" << endl;
      //counter = 0;
      //firstcounter = 0;
      while (current != NULL) {
	if (strcmp(current->getLabel(), firstnode) == 0) {
	  firstcounter = counter;
	}
	if (strcmp(current->getLabel(), secondnode) == 0) {
	  secondcounter = counter;
	}
	counter++;
	if (current->getNext() == root) {
	  current->setNext(NULL);
	}
	current = current->getNext();
      }
      done = true;
    
    current = root;
    //        cout << firstcounter << endl;
    //	cout << counter << endl;
    if (current == root) {
      cout << "Firstcounter " << firstcounter << endl;
    for (int j = 0; j < counter; j++) {
      //if (firstcounter == 0) {
      current->setDistance(array[firstcounter][j]);
      //}
      //else {
      //current->setDistance(array[firstcounter-1][j]);
      //}
if (current->getNext() == root) {
          current->setNext(NULL);
        }
      current = current->getNext();
    }
    }
    
    current = root;
    
    done = true;
    }
    //current is firstnode
    if (done = true) {
      //      current = root;
      cout << "CURRENT: " << current->getLabel()  << endl;
  if (strcmp(current->getLabel(), secondnode) == 0) {
      cout << "Second node" << endl;
      totaldistance = totaldistance + current->getDistance();
      cout << "Total distance: " << totaldistance << endl;
      return;
    }
  else  if (strcmp(current->getLabel(), firstnode) == 0 && strcmp(current->getLabel(), secondnode) != 0) {
	cout << "First node" << endl;
	  current->setVisited(true);

	  current = current->getNext();
	  //	  cout << current->getLabel() << endl;
	  //	  cout << current->getNext()->getLabel() << endl;
      }
    //current is 0 and not firstnode
      else if (strcmp(current->getLabel(), firstnode) != 0 && current->getDistance() == 0 && extracounter < counter && strcmp(current->getLabel(), secondnode) != 0) {
      cout << counter << endl;
      extracounter++;
      //if (current->getNext() != NULL) {
      current = current->getNext();
      //}
    }
    //current is secondnode and not zero
      else if (strcmp(current->getLabel(), secondnode) == 0) {
      cout << "Second node" << endl;
      totaldistance = totaldistance + current->getDistance();
      cout << "Total distance: " << totaldistance << endl;
      return;
    }
    //current is not zero, not visited
    //current's next is NULL
      else if (current->getDistance() != 0) {
      cout << "non 0 node" << endl;
      if (current->getVisited() == true) {
	cout << "Skip" << endl;
	//	if (current->getNext() == root) {
	//current->setNext(NULL);
        //}

	current = current->getNext();
      }
      else {
	if (current->getDistance() >= moverdistance) {
	  cout << "Distance change" << current->getDistance() << endl;
	  moverdistance = current->getDistance();
	  totaldistance = totaldistance + moverdistance;
	  strcpy(firstnode, current->getLabel());
	  current = current->getNext();
	}
	else {
	  cout << "Skip, not big enough" << endl;
	  current = current->getNext();
	}
      }

    }

    if (current->getNext() == NULL || current->getNext() == root) {
      //restart
      cout << "End" << endl;
      current->setNext(root);
      current = current->getNext();
      counter = 0;
      firstcounter = 0;
      done = false;
      extracounter = 0;
    }
    
    //   cout << "Drop" << endl;

    }
  }
  cout << "Out of while loop" << endl;
  
}


int main() {
  Vertex* root = NULL;
  int response;
  int array[20][20] = {0};
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  while (response != 1000000000) {
  if (response == 1) {
    //   cout << "Add vertex" << endl;
    root = addvertex(root);
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  }
  if (response == 2) {
    cout << "Add edge" << endl;
  addEdge(root, array);
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  }
  if (response == 3) {
    cout << "Remove vertex" << endl;
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  }
  if (response == 4) {
    cout << "Remove edge" << endl;
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  }
  if (response == 5) {
    cout << "Find shortest path" << endl;
    shortestPath(root, array);
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  }
  if (response == 6) {
    cout << "Printing adjacency table" << endl;
    //   printVertices(root);
    printTable(root, array);
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
    cin >> response;
  }
  }
  return 0;
}

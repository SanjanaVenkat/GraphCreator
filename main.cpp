//Sanjana Venkat
//5.16.19
//Graph creator
#include <iostream>
#include <cstring>
#include "list.h"

using namespace std;
//functions
Vertex* addvertex(Vertex* root);
void printVertices(Vertex* root);
void printTable(Vertex* root, int array[20][20]);
int addEdge(Vertex* root, int array[20][20]);
void shortestPath(Vertex* root, int array[20][20], Vertex*& path);
void clearVertices(Vertex* root);
int getIndex(Vertex* currentVertex, Vertex* root);
int getIndexs(char label[1000], Vertex* root);
Vertex* getVertex(int index, Vertex* root);
Vertex* addtoPath(Vertex* currentVertex, Vertex* path);
int removeEdge(Vertex* root, int array[20][20]);
Vertex* deleteList(Vertex* root);
int deleteRoot(Vertex* root, int array[20][20]);
//add vertex to one of the two linked lists
Vertex* addvertex(Vertex* root) {
  char vertexlabel[1];
  Vertex* current = root;
  Vertex* previous = root;
  cout << "Adding vertex" << endl;
  cout << "Enter a letter to be the label of your vertex" << endl;
  cin >> vertexlabel;
  Vertex* vertex = new Vertex(vertexlabel, 0, 0, false);
  cout << "Vertex has been added" << endl;
  if (current == NULL) {
    current = vertex;
    root = current;
    root->setPrevious(NULL);
  }
  else {
    while (current->getNext() != NULL) {
      previous = current;
      current = current->getNext();
    }
    current->setPrevious(previous);
    current->setNext(vertex);
  }
  return root;
}
//prints list of vertices from linked list
void printVertices(Vertex* root) {
  Vertex* current = root;
  while (current != NULL) {
    current = current->getPrevious();
  }
  while (current != NULL) {
    cout << current->getLabel() << endl;
    current = current->getNext();
  }
  
}
//print adjacency table
void printTable(Vertex* root, int array[20][20]) {
  int counter = 0;
  Vertex* current = root;
  while (current != NULL) {
    counter++;
    current = current->getNext();
  }
  current = root;
  cout << "  ";
  //labels print
  while (current != NULL) {
  cout << current->getLabel() << " ";
  current = current->getNext();
  }
  cout << endl;
  current = root;
  //values print
  for (int i = 0; i < counter; i++) {
    cout << current->getLabel() << " ";
    for (int j = 0; j < counter; j++) { 
      cout << array[i][j] << " ";
    }
    cout << endl;
    current = current->getNext();
  }
}

//add edge, change array spot from 0 to the value that of the edge
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

//find shortest path
void shortestPath(Vertex* root, int array[20][20], Vertex*& path) {
  char sourceLabel[1000];
  char destLabel[1000];
  //setup
  cout << "Enter the label of the vertex that you want to start at" << endl;
  cin >> sourceLabel;
  cout << "Enter the label of the vertex that you want to end at" << endl;
  cin >> destLabel;
   int currentIndex = getIndexs(sourceLabel, root);
  int destIndex = getIndexs(destLabel, root);
  Vertex* destvertex = getVertex(destIndex, root);
  //cout << destIndex << endl;
  clearVertices(root);
  path = NULL;
  bool done = false;
   Vertex* sourceVertex = getVertex(currentIndex, root);
  Vertex* currentVertex = getVertex(currentIndex, root);
 int shortestNextDistance = 0;
  Vertex* shortestNextVertex = NULL;
  path = addtoPath(currentVertex, path);
  currentVertex->setVisited(true);
  //  cout << "Printing vertices" << endl;
  //printVertices(root);
  //while not found
  while (done == false) {
    //found destination
    if (currentIndex == destIndex) {
      //  cout << "Breaking " << endl;
      break;
    }
    shortestNextVertex = NULL;
    shortestNextDistance = 0;
    //    cout <<"Current label   " <<  currentVertex->getLabel() << " " << currentIndex << endl;
    //cout << "Destination   " << destIndex << "    " << destLabel << endl;
    for (int i = 0; i < 20; i++) {

      if (array[currentIndex][i] == 0) {
        continue;
      }
      //continue
            if (i == currentIndex) {
	continue;
      }
	    //    cout << "I: " << i << endl;
      
      Vertex* nextVertex = getVertex(i, root);
      //cout << "I2: " << i << endl;
      //stop from crashing
      if (nextVertex == NULL) {
	//	printVertices(root);
	continue;
      }
      //skip if visited
      if (nextVertex->getVisited() == true) {
	continue;
      }
      //      cout << "Test 1" << endl;
      //change distance
      if (nextVertex->getDistance() == 0) {
	//cout << "Test 2" << endl;
	nextVertex->setDistance(currentVertex->getDistance() + array[currentIndex][i]);
	//cout << "Next vertex: " << nextVertex->getLabel() << "    " << nextVertex->getDistance() << endl;
      }
      //longer distance, dont go this way
      else if (currentVertex->getDistance() + array[currentIndex][i] <= nextVertex->getDistance()) {
	//cout << "Test 3" << endl;
	nextVertex->setDistance(currentVertex->getDistance() + array[currentIndex][i]);
      }
      //shorter distance, go this way
      if (shortestNextDistance == 0 || shortestNextDistance > nextVertex->getDistance()) {
	//cout << "Test 4" << endl;
	shortestNextDistance = nextVertex->getDistance();
	shortestNextVertex = nextVertex;
      }
      
 

      
    }

    //      cout << "Check: " << endl;
    //error
      if (shortestNextVertex == NULL) {
	// 	cout << "Error" << endl;
	done = true;
      }
      else {
	Vertex* currentholder = root;
	int intcurrentholder = 0;
	while (currentholder != NULL) {
	  if (currentholder->getVisited() == false && currentholder->getDistance() != 0 && currentholder->getDistance() < intcurrentholder) {
	    cout << "Test" << endl;
	    currentVertex = currentholder;
	    intcurrentholder = currentholder->getDistance();
	    currentIndex = getIndex(currentholder, root);
	    }
	  
	  currentholder = currentholder->getNext();
	}
	shortestNextVertex = currentVertex;
	currentVertex->setVisited(true);
	//      	cout << currentVertex->getLabel() << endl;
	//	cout << "Test" << endl;
      }
  }
  //print
  cout << "Path" << endl;
  printVertices(path);
  cout << "Distance: " <<  destvertex->getDistance() << endl;
}
//clears vertices of linked list
void clearVertices(Vertex* root) {
  Vertex* current = root;
  while (current != NULL) {
    current->setVisited(false);
    current->setDistance(0);
    current = current->getNext();
  }
}
//get index of vertex
int getIndex(Vertex* currentVertex, Vertex* root) {
  int counter = 0;
  Vertex* current = root;
  while (current != NULL) {
    if (strcmp(current->getLabel(), currentVertex->getLabel()) == 0) {
      return counter;
    }
    counter++;
    current = current->getNext();
  }
}
//get index of vertex
int getIndexs(char label[], Vertex* root) {
  int counter = 0;
  Vertex* current = root;
  while (current != NULL) {
    if (strcmp(current->getLabel(), label) == 0) {
      return counter;
    }
    counter++;
    current = current->getNext();
  }
}
//get vertex
Vertex* getVertex(int index, Vertex* root) {
  int counter = 0;
  Vertex* current = root;
  while (current != NULL) {
    if (index == counter) {
      return current;
    }
    counter++;
    current = current->getNext();
  }
}
//add to shortest path
Vertex* addtoPath(Vertex* currentVertex, Vertex* path) {
  Vertex* current = path;
  char label[1000];
  strcpy(label, currentVertex->getLabel());
  Vertex* newVertex = new Vertex(label, 0, 0, false);
  if (current == NULL) {
    current = newVertex;
    path = current;
  }
  else {
    while(current->getNext() != NULL) {
      current = current->getNext();
    }
    current->setNext(newVertex);

  }
  return path;
}
//remove edge, change to 0
int removeEdge(Vertex* root, int array[20][20]) {
  char firstedge[1000];
  char secondedge[1000];
  cout << "Enter the label of the vertex that your edge starts at" << endl;
  cin >> firstedge;
  cout << "Enter the label of the vertex that your edge ends at" << endl;
  cin >> secondedge;
  int counter = 0;
  int firstcounter = 0;
  int secondcounter = 0;
  Vertex* current = root;
  while (current != NULL) {
    if (strcmp(current->getLabel(), firstedge) == 0) {
      firstcounter = counter;
    }
    if (strcmp(current->getLabel(), secondedge) == 0) {
      secondcounter = counter;
    }
    counter++;
    current = current->getNext();
  }
  array[firstcounter][secondcounter] = 0;
  return 0;
}
//delete from linked list
Vertex* deleteList(Vertex* root) {
  char todelete[1000];
  cout << "Reenter the label of the vertex that you want to delete" << endl;
  cin >> todelete;
  Vertex* current = root;
  Vertex* previous = NULL;
  Vertex* next = current->getNext();
  while (current != NULL) {
    if (strcmp(current->getLabel(), todelete) == 0) {
      break;
    }
    else {
      previous = current;
      current = current->getNext();
      next = current->getNext();
    }
  }
    if (current == root) {
      root = next;
    }
    else {
    previous->setNext(next);
    }
    return root;

}
//delete from array
int deleteArray(Vertex* root, int array[20][20]) {
  char todelete[1000];
  cout << "Which vertex do you want to delete?" << endl;
  cin >> todelete;
  int counter = 0;
  Vertex* current = root;
  while (current != NULL) {
    if (strcmp(current->getLabel(), todelete) == 0) {
      break;
    }
    counter++;
    current = current->getNext();
  }
  int icounter = counter;
  int jcounter = counter;
  for (int i = icounter + 1; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      array[i-1][j] = array[i][j];
    }

  }

  for (int i = 0; i < 20; i++) {
    for (int j = jcounter + 1; j < 20; j++) {
      array[i][j-1] = array[i][j];
    }
  }
  return 0;

}
//main
int main() {
  Vertex* root = NULL;
  Vertex* path = NULL;
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
    deleteArray(root, array);
    root = deleteList(root);
    //cout << "New list: " << endl;
    //printVertices(root);
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  }
  if (response == 4) {
    cout << "Remove edge" << endl;
    removeEdge(root, array);
    cout << "Enter 1 to add vertex, 2 to add edge, 3 to remove vertex, 4 to remove edge, 5 to find shortest path, and 6 to print the adjacency table" << endl;
  cin >> response;
  }
  if (response == 5) {
    cout << "Find shortest path" << endl;
    shortestPath(root, array, path);
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

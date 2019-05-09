#include <iostream>
#include <cstring>
#include "list.h"

using namespace std;

Vertex::Vertex(char* l, int e, int d) {
  next = NULL;
  edge = e;
  distance = d;
  strcpy(label, l);
}

Vertex::~Vertex() {
  next = NULL;
}

void Vertex::setNext(Vertex* newnext) {
  next = newnext;
}

Vertex* Vertex::getNext() {
  return next;
}

void Vertex::setEdge(int e) {
  edge = e;
}

int Vertex::getEdge() {
  return edge;
}

void Vertex::setDistance(int d) {
  distance = d;
}

int Vertex::getDistance() {
  return distance;
}

void Vertex::setLabel(char* l) {
  strcpy(label, l);
}

char* Vertex::getLabel() {
  return label;
}



/**
 * A Graph is made up of Vertex objects that hold data values
 * A vertex is connected to other vertices via Edges
 * A vertex can be visited/unvisited
 * Can connect to another vertex via directed edge with weight
 * The edge can be disconnected
 * A vertex cannot have an edge back to itself
 * getNextNeighbor returns the next neighbor each time it is called
 * when there are no more neighbors, the vertex label is returned
 */

#include "edge.h"
#include "vertex.h"
#include <algorithm>


using namespace std;

ostream &operator<<(ostream &Os, const Vertex &V) {
   Os << V.Label;
  return Os;
}
Vertex::Vertex(const string &Label) {
   this->Label = Label;
   Visited = false;
}
Vertex::Vertex() {
   Label = "";
   Visited = false;
}

Vertex::~Vertex() {
   Neighbors.clear();
}

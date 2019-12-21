#include "graph.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <map>
#include <queue>
#include <utility>

using namespace std;

//-----------------------------------------------------------------------------
// constructor, empty graph
Graph::Graph(bool DirectionalEdges) {
  this->DirectionalEdges = DirectionalEdges;
  NumOfEdges = 0;
  NumOfVertices = 0;
}

//-----------------------------------------------------------------------------
// destructor, deletes all vertices and edges
Graph::~Graph() {
  // for all Vertices
  for (int I = 0; I < Vertices.size(); I++) {
    Vertex* Temp = Vertices.at(I);
    // for all Neighbors of current Vertex
    for (int J = 0; J < Temp->Neighbors.size(); J++) {
      delete Temp->Neighbors.at(J); // delete Neighbors
    }
    Temp->Neighbors.clear();
    delete Temp; // delete Vertex
  }
  Vertices.clear();
  NumOfEdges = 0;
  NumOfVertices = 0;
}

//-----------------------------------------------------------------------------
// readFile
// creates a Graph by reading edges from a file
// first line of file must be number of edges in file
// Each line after first must be in format "From To Weight"
// @returns true if file successfully read, returns false otherwise
bool Graph::readFile(const string& Filename) {
  ifstream File(Filename);
  if (!File.is_open()) return false; // file can't be read

  int Lines;
  File >> Lines; // first line is number of edges

  string F, T;
  int W;

  for (int I = 0; I < Lines; I++) {
    File >> F >> T >> W; // After first line, read From, TO, Weight
    connect(F, T, W); // Create Edge
  }

  File.close();
  return true;
}

//-----------------------------------------------------------------------------
// verticeSize
// @returns number of Vertices in Graph
int Graph::verticesSize() const { return NumOfVertices; }

//-----------------------------------------------------------------------------
// edgesSize
// @returns number of Edges in Graph
int Graph::edgesSize() const { return NumOfEdges; }

//-----------------------------------------------------------------------------
// neighborsSize
// @returns number of Vertices adjacent to Label, returns -1 if Label not found
int Graph::neighborsSize(const string& Label) const {
  Vertex* V = nullptr;
  // if Vertex found
  if (this->find(Label, V)) {
    return V->Neighbors.size(); // return the size of its Neighbors vector
  }

  return -1;
}

//-----------------------------------------------------------------------------
// add
// @return true if Vertex successfully added, false otherwise
// Will not add Vertex if Graph already contains Label
bool Graph::add(const string& Label) {
  // if Graph doesn't contain Label
  if (!this->contains(Label)) {
    auto V = new Vertex(Label); // create new Vertex
    Vertices.push_back(V); // add Vertex
    NumOfVertices++;
    return true;
  }
  return false;
}

//-----------------------------------------------------------------------------
// contains
// return true if vertex already in graph 
bool Graph::contains(const std::string& Label) const {
  // for Vertices
  for (auto& V : Vertices) {
    if (V->Label == Label) return true; // Check if Label is in Graph
  }
  return false;
}

//-----------------------------------------------------------------------------
// getEdgesAsString
// returns string representing edges and weights, returns "" if not found
string Graph::getEdgesAsString(const string& Label) const {
  string S;
  Vertex* V = nullptr;
  //if Vertex found
  if (this->find(Label, V)) {
    if (V->Neighbors.empty()) return S; // if no Edges, return empty string
    S += V->Neighbors[0]->To->Label; // add Label of first Edge to string S
    S += "(" + to_string(V->Neighbors[0]->Weight) + ")"; // append weight
    // for second to last Neighbors of Vertex from parameter
    for (auto It = V->Neighbors.begin() + 1; It != V->Neighbors.end(); ++It) {
      string L = (*It)->To->Label;
      int W = (*It)->Weight;
      S += "," + L; // append Label
      S += "(" + to_string(W) + ")"; // append Weight
    }
  }
  return S;
}

//-----------------------------------------------------------------------------
// connect
// @returns true if successfully connected
// Won't connect if Edge already exists
bool Graph::connect(const string& From, const string& To, int Weight) {
  if (From == To) return false; // Can't connect Vertex to itself

  Vertex* V1 = nullptr, * V2 = nullptr;
  // if Vertices don't exist, then add them
  if (!find(From, V1)) {
    V1 = new Vertex(From);
    Vertices.push_back(V1);
    NumOfVertices++;
  }
  if (!find(To, V2)) {
    V2 = new Vertex(To);
    Vertices.push_back(V2);
    NumOfVertices++;
  }

  bool C1 = false; // flag for if Edge was added
  bool C2 = false; // flag for if 2nd Edge (in Non-Directed Graph) was added

  auto E1 = new Edge(V1, V2, Weight); // Edge to add
  // for Neighbors of From
  for (int I = 0; I < V1->Neighbors.size(); I++) {
    Edge* Temp = V1->Neighbors.at(I);
    // if Edge already exists don't add it
    if (From == Temp->From->Label && To == Temp->To->Label) {
      delete E1;
      return false;
    }
    // if Edge to add is alphabetically less than current Neighbor
    if (To < Temp->To->Label) {
      // add edge at index I so that Neighbors is sorted
      V1->Neighbors.insert(V1->Neighbors.begin() + I, E1);
      NumOfEdges++;
      C1 = true; // edge has been added, so set flag to true
      break;
    }
  }

  // if first edge hasn't been added
  if (!C1) {
    V1->Neighbors.push_back(E1); // add it to the end of Neighbors
    NumOfEdges++;
  }

  // if graph is non-directed, add opposite edge
  if (!DirectionalEdges) {
    auto E2 = new Edge(V2, V1, Weight); // 2nd Edge to add
    // for Neighbors of To
    for (int I = 0; I < V2->Neighbors.size(); I++) {
      Edge* Temp = V2->Neighbors.at(I);
      // Don't add Edge if it already exists
      if (From == Temp->From->Label && To == Temp->To->Label) {
        delete E2;
        return false;
      }
      if (To < Temp->To->Label) {
        // insert in sorted order
        V2->Neighbors.insert(V2->Neighbors.begin() + I, E2);
        C2 = true;
        break;
      }
    }

    // if 2nd edge not added
    if (!C2) {
      V2->Neighbors.push_back(E2); // add to end of To's Neighbors
    }
  }

  return true; // successfully connected
}

//-----------------------------------------------------------------------------
// disconnect
// @returns true if successfully disconnected, false if Edge doesn't exist
bool Graph::disconnect(const string& From, const string& To) {
  Vertex* V = nullptr;
  if (!find(From, V)) return false; // Vertex doesn't exist so Edge doesn't

  // for each Neighbor, check if Edge exists and remove
  for (int I = 0; I < V->Neighbors.size(); I++) {
    Edge* E = V->Neighbors.at(I);
    // if Edge found
    if (From == E->From->Label && To == E->To->Label) {
      V->Neighbors.erase(V->Neighbors.begin() + I); // remove from Neighbors
      delete E;
      NumOfEdges--;

      // do same for other edge if Non-Directed Graph
      if (!DirectionalEdges) {
        Vertex* V2 = nullptr;
        find(To, V2);
        // for Neighbors of To
        for (int J = 0; J < V2->Neighbors.size(); J++) {
          Edge* E2 = V2->Neighbors.at(J);
          // if Edge found
          if (To == E2->From->Label && From == E2->To->Label) {
            V2->Neighbors.erase(V2->Neighbors.begin() + J); // remove
            delete E2;
            break;
          }
        }
      }

      return true; // success
    }
  }

  return false; // failure
}

//-----------------------------------------------------------------------------
// dfs
// 
void Graph::dfs(const string& StartLabel, void Visit(const string& Label)) {
  // mark all vertices as not visited
  for (auto& V : Vertices)
    V->Visited = false;

  Vertex* V = nullptr;
  if (!find(StartLabel, V)) return; // if Vertex not found, do nothing
  dfsHelper(V, Visit); // Vertex found
}
void Graph::dfsHelper(Vertex* V, void Visit(const string& Label)) {
  if (V == nullptr) return; // base case: Vertex is nullptr so stop

  V->Visited = true; // set Visited to true
  Visit(V->Label); // visit

  // for Neighbors of Vertex
  for (int I = 0; I < V->Neighbors.size(); I++) {
    Vertex* Temp = V->Neighbors.at(I)->To;
    if (!Temp->Visited) // if Neighbor not visited
      dfsHelper(Temp, Visit); // recurse on Neighbor
  }
}

//-----------------------------------------------------------------------------
// bfs
// 
void Graph::bfs(const string& StartLabel, void Visit(const string& Label)) {
  // mark all vertices as not visited
  for (auto& V : Vertices)
    V->Visited = false;

  Vertex* V = nullptr;
  if (!find(StartLabel, V)) return; // do nothing if Start not found

  V->Visited = true; // Vertex found so set Visited to true
  queue<Vertex*> Q;
  Q.push(V); // add Vertex to queue
  // while Queue is not empty
  while (!Q.empty()) {
    Vertex* Temp = Q.front(); // take front of Q
    Q.pop(); // remove front
    Visit(Temp->Label); // visit

    // for Neighbors of Temp
    for (int I = 0; I < Temp->Neighbors.size(); I++) {
      Vertex* N = Temp->Neighbors.at(I)->To;
      if (!N->Visited) { // if current Neighbor not Visited
        N->Visited = true; // Visit
        Q.push(N); // push Neighbor to front of queue
      }
    }
  }
}

//-----------------------------------------------------------------------------
// dijkstra
// finds shortest distance of each Vertex from StartLabel
// store the weights in a map
// store the previous label in a map
// returns pair where first is Weights, second is Previous
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string& StartLabel) const {
  map<string, int> Weights;
  map<string, string> Previous;

  // mark all as visited
  for (auto& V : Vertices)
    V->Visited = false;

  Vertex* V = nullptr;
  // if StartLabel not found return pair of empty maps
  if (!find(StartLabel, V)) return make_pair(Weights, Previous);

  vector<Vertex*> VisitedArr; // store Vertices that have been visited
  V->Visited = true; // Visit Start
  VisitedArr.push_back(V);

  // for Vertices that have been visited
  for (int I = 0; I < VisitedArr.size(); I++) {
    // get vector containing smallest cost Edge from each visited Vertex
    vector<Edge*> SmallestEdges = smallestNeighbors(VisitedArr);
    Edge* E = minDistance(SmallestEdges, Weights); // get smallest cost Edge
    if (E == nullptr) break; // All Vertices have been visited so stop
    E->To->Visited = true; // visit Vertex on end of Edge
    VisitedArr.push_back(E->To);

    auto It = Weights.find(E->From->Label);
    // if From not in Previous/Weights
    if (It == Weights.end()) {
      // S is adjacent to Start
      Weights.emplace(E->To->Label, E->Weight);
      Previous.emplace(E->To->Label, E->From->Label);
    }
    else {
      // S's Total Weight = Previous Weight + S's Weight
      Weights.emplace(E->To->Label, (*It).second + E->Weight);
      Previous.emplace(E->To->Label, E->From->Label);
    }
  }

  return make_pair(Weights, Previous);
}

/**
 * minimum spanning tree
 * @param function to be called on each edge
 * @return length of the minimum spanning tree or -1 if start vertex not found
 */
int Graph::mst(const string& StartLabel,
  void Visit(const string& From, const string& To,
    int Weight)) const {
  assert(!DirectionalEdges);

  // mark all as visited
  for (auto& V : Vertices)
    V->Visited = false;

  Vertex* V = nullptr;
  if (!find(StartLabel, V)) return -1; // Vertex not found

  vector<Vertex*> Mst; // Vector of Visited Vertices
  V->Visited = true; // Visit StartLabel and add to Mst
  Mst.push_back(V);

  int Total = 0; // Total cost of MST

  // for (Visited) Vertices in MST
  for (int I = 0; I < Mst.size(); I++) {
    // find smallest cost that hasn't been visited
    vector<Edge*> SmallestEdges = smallestNeighbors(Mst);
    Edge* E = minWeight(SmallestEdges);
    if (E == nullptr) break;
    // add to Visited and set Visited to true
    E->To->Visited = true;
    Mst.push_back(E->To);
    // call Visit on smallest Edge
    Visit(E->From->Label, E->To->Label, E->Weight);
    Total += E->Weight;
  }

  return Total;
}

//-----------------------------------------------------------------------------
// smallestNeighbors
// returns vector containing smallest cost Edge from each Vertex in VisitedArr
vector<Edge*> Graph::smallestNeighbors(vector<Vertex*> VisitedArr) const {
  vector<Edge*> SmallestEdges;
  // for visited Vertices
  for (int I = 0; I < VisitedArr.size(); I++) {
    // N is Neighbor of current Vertex
    vector<Edge*> N = VisitedArr.at(I)->Neighbors;
    // Min is Smallest cost edge from current Vertex
    Edge* Min;
    // if N is empty
    if (N.empty()) {
      // remove curent Vertex from VisitedArr
      VisitedArr.erase(VisitedArr.begin() + I);
      I--;
      continue;
    }
    int E = 0;
    Min = N[E]; // set Min to first Neighbor
    // while Min has been Visited
    while (E + 1 < N.size() && Min->To->Visited) {
      Min = N[++E]; // set Min to next Neighbor
    }
    // for Neighbors of current Vertex
    for (int J = E + 1; J < N.size(); J++) {
      Edge* Temp = N.at(J);
      // if current Neighbor has been visited, continue to next neighbor
      if (Temp->To->Visited) continue;
      // if current Neighbor is less than Min
      if (Temp->Weight < Min->Weight) Min = Temp; // Set Min to Neighbor
    }

    // if Min has been visited or is nullptr
    if (Min == nullptr || Min->To->Visited) {
      // remove current Vertex from VisitedArr
      VisitedArr.erase(VisitedArr.begin() + I);
      I--;
      continue; // continue to next Vertex
    }
    // add to vector of smallest Edges
    SmallestEdges.push_back(Min);
  }

  return SmallestEdges;
}

//-----------------------------------------------------------------------------
// minWeight
// returns Edge with smallest Weight from SmallestEdges
Edge* Graph::minWeight(vector<Edge*> SmallestEdges) const {
  if (SmallestEdges.empty()) return nullptr; // nothing to return if empty

  Edge* Min = SmallestEdges[0];
  // for smallest Edges
  for (int I = 1; I < SmallestEdges.size(); I++) {
    // find min in smallest Edges
    Edge* Temp = SmallestEdges[I];
    if (Temp->Weight < Min->Weight) Min = Temp;
  }

  return Min;
}

//-----------------------------------------------------------------------------
// minDistance
// returns Edge from SmallestEdges with smallest distance from 
// dijkstra's StartLabel
Edge* Graph::minDistance(vector<Edge*> SmallestEdges, map<string, int> Weights)
const {
  if (SmallestEdges.empty()) return nullptr; // nothing to return if empty
  Edge* Min = SmallestEdges[0];
  // for smallest Edges
  for (int I = 1; I < SmallestEdges.size(); I++) {
    // find Edge with smallest distance from Origin
    Edge* Temp = SmallestEdges[I];

    auto ItMin = Weights.find(Min->From->Label);
    auto ItTemp = Weights.find(Temp->From->Label);

    // Distance of previous Edges for Min and Temp
    int MinDistance = (ItMin == Weights.end()) ? 0 : (*ItMin).second;
    int TempDistance = (ItTemp == Weights.end()) ? 0 : (*ItTemp).second;

    if (Temp->Weight + TempDistance < Min->Weight + MinDistance) Min = Temp;
  }

  return Min;
}

//-----------------------------------------------------------------------------
// find
// returns true if StartLabel found in Graph, false otherwise
// If found, assigns found Vertex to V. If not found, V is useless.
bool Graph::find(const string& Label, Vertex*& V) const {
  // for Vertices
  for (auto& Vtx : Vertices) {
    if (Vtx->Label == Label) { // if Vertex found
      V = Vtx; // Assign Vtx to V
      return true;
    }
  }
  return false;
}

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <list>
#include <iterator>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

// returns int position of name from name list
int getName(string names[], string input, int numWrestlers) {
  for(int i=0; i<numWrestlers; i++) {
    if(names[i] == input) {
      return i;
    }
  }
}

// I received help from https://www.tutorialspoint.com/cplusplus-program-to-implement-adjacency-list
// and https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/ for the idea of keeping a seen/looked at node list
// I also followed the pseudocode from this week's lecture, which was basically the same format as the BFS in the second link

bool bfs(list<int> adj[], int u, int team[], int numWrestlers) {

  bool seen[numWrestlers];
  queue<int> q;

  for(int i=0; i<numWrestlers; i++) {
    seen[i] = false;
  }

  seen[u] = true;
  q.push(u);

  // iterator to represent the child node we're currently looking at
  list<int>::iterator v;

  // while our queue isn't empty
  while(!q.empty()) {
    
    //get the next node
    u = q.front();
    
    //remove it from the queue
    q.pop();

    // citation for for loop condition: https://www.tutorialspoint.com/cplusplus-program-to-implement-adjacency-list
    for (v = adj[u].begin(); v != adj[u].end(); v++) {
      
      // if we haven't looked at this node yet, examine it
      if (!seen[*v]) {
        seen[*v] = true;
        
        // if the parent node and child node have the same team, this means we cannot separate the teams because adj nodes should be of opposite teams
        if(team[u] == team[*v]) {
          cout << "Teaming not possible." << endl;
          return false;
        }

        // node is of opposite team
        else {
          q.push(*v);
        }

      }
    }
  }

  // if we've gone through all of the vertices and there was no conflict, then we know we can separate the two teams
  cout << "Teaming successful." << endl;
  return true;

}

// initialize teams of each node when they're inserted into the adjacency list
void add_edge(list<int> adj[], int u, int v, int team[]) { 

  // add nodes to eachother's adjacency list
  adj[u].push_back(v);
  adj[v].push_back(u);

  // if both wrestlers haven't been assigned a team yet, then assign first to 0 and second to 1
  if(team[u] == 2 && team[v] == 2) {
    team[u] = 0;
    team[v] = 1;
  }

  // if second wrestler has no team, assign it opposite team to first wrestler
  else if((team[u] != 2) && (team[v] == 2)) {
    team[v] = 1-team[u];
  }

  // assign first wrestler opposite team of second wrestler
  else {
    team[u] = 1 - team[v];
  }

}

void readFile(string &filename) {
  fstream input;

  input.open(filename.c_str());

  if (input.is_open()) {
    int numWrestlers;
    int rivalries;
    string line;

    getline(input, line);
    numWrestlers = atoi(line.c_str());

    string names[numWrestlers]; //array to store names of all wrestlers
    int team[numWrestlers];     //array to store which team each wrestler is on

    list<int> adj[numWrestlers]; //adjacency list for graph, stored as integer representations for each wrestler

    // initializing all teams for wrestlers; assigning to 2 to represent that wrestler isn't part of any team yet
    for (int i = 0; i < numWrestlers; i++)
    {
      team[i] = 2;
    }

    // putting all names inside name array
    for (int i = 0; i < numWrestlers; i++)
    {
      getline(input, line, '\n');
      names[i] = line;
    }

    //get number of rivalries
    getline(input, line);
    rivalries = atoi(line.c_str());

    for (int i = 0; i < rivalries; i++)
    {
      getline(input, line, ' ');
      string p1 = line;
      getline(input, line, '\n');
      string p2 = line;

      // since we get string input, get the int representation of the wrestlers
      int u = getName(names, p1, numWrestlers);
      int v = getName(names, p2, numWrestlers);

      add_edge(adj, u, v, team);
    }

    bool possible = bfs(adj, 0, team, numWrestlers);

    if (possible)
    {

      cout << "Babyfaces: ";
      for (int i = 0; i < numWrestlers; i++)
      {
        if (team[i] == 0)
        {
          cout << names[i] << " ";
        }
      }
      cout << endl;

      cout << "Heels: ";
      for (int i = 0; i < numWrestlers; i++)
      {
        if (team[i] == 1)
        {
          cout << names[i] << " ";
        }
      }
      cout << endl;
    }
  }

  input.close();
}


int main(int argc, char *argv[]) {
  
  string filename;
  
  if(argc == 2) {
    filename = argv[1];
  }
  readFile(filename);

  return 0;
}

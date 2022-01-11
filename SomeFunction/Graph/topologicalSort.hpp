#include <stack>
#include <list>
#include <vector>

using namespace std;

class Graph {
    int V; // number of vertices

    // pointer to an array containing adjacency list
    list<int>* adjacency;

    // function used by topological sort
    void topologicalSort(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;

        list<int>::iterator i;
        for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i) {
            if (!visited[*i])
                topologicalSort(*i, visited, Stack);
        }
        Stack.push(v);
    }

public:
    Graph(int v) : V(v) {
        adjacency = new list<int>[V];
    }

    void addEdge(int v, int w) {
        adjacency[v].push_back(w);
    }

    void topologicalSort(vector<int>& sorted) {
        stack<int> Stack;
        vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                topologicalSort(i, visited, Stack);
        }

        while (!Stack.empty()) {
            sorted.push_back(Stack.top());
            Stack.pop();
        }
    }
};


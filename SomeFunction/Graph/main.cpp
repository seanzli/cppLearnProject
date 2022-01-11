#include <iostream>
#include "topologicalSort.hpp"

// Driver program to test above functions
int main()
{
    // Create a graph given in the above diagram
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    cout << "Following is a Topological Sort of the given graph n";
    vector<int> out;
    g.topologicalSort(out);

    for (auto& itr : out) {
        cout << itr << ", ";
    }

    return 0;
}
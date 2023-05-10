#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    int graphs = 0;
    cin >> graphs;
    for(int i = 0; i < graphs; i++)
    {
        int size = 0;
        cin >> size;
        graph test(size);
        test.createGraph();
        //test.printGraph();
        test.shortestPath(0);
        test.printShortest(0);
    }
    return 0;
}
#include <iostream>
#include <iomanip>
#include <cfloat>
#include <vector>
#include <stack>
#include "graph.h"

using namespace std;

graph::graph(int size)
{
    //sets the graph size to the inputted size
    gSize = size;

    //allocated memory for all variables, except for previous (which is done in shortestPath())
    weights = new double*[size];
    for (int i = 0; i < size; i++)
    {
        weights[i] = new double[size];
    }
    smallestWeight = new double[size];
    names = new string[gSize];
}

graph::~graph()
{
    //calls clearGraph() to delete the data
    clearGraph();
}

void graph::createGraph()
{
    //reads in the names of all the vertices
    for(int i = 0; i < gSize; i++)
    {
        string temp = "";
        cin >> temp;
        names[i] = temp;
    }
    
    //reads in the connection of the vertices
    for(int i = 0; i < gSize; i++)
    {
        for(int j = 0; j < gSize; j++)
        {
            double temp = 0;
            cin >> temp;
            weights[i][j] = temp;
        }
    }
}

void graph::printGraph()
{
    //prints the name of the vertices in order from the beginning to end
    for(int i = 0; i < gSize; i++)
    {
        cout << names[i] << endl;
    }
    
    //prints the connections in a matrix format
    for(int i = 0; i < gSize; i++)
    {
        for(int j = 0; j < gSize; j++)
        {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }
}

void graph::printShortest(int vertex)
{
    //creates a stack to store the names of the vertices
    stack<string> shortestPathNames;
    
    //creates an int that points at the previous vertex
    int currentVertex = gSize - 1;

    //while the current vertex doesn't equal the starting vertex
    while(currentVertex != vertex)
    {
        //pushes the name of the previous vertex onto the stack
        shortestPathNames.push(names[currentVertex]);

        //moves back to the previous vertex in the shortest path
        currentVertex = previousPlaces[currentVertex];
    }

    //adds the vertex name to the stack
    shortestPathNames.push(names[vertex]);

    //while the shortest path is not empty
    while(shortestPathNames.empty() == false)
    {
        //prints out the name of the vertex, then removes the name from the stack
        cout << shortestPathNames.top() << " ";
        shortestPathNames.pop();
    }

    //print the weight of the shortest path
    cout << smallestWeight[gSize-1] << endl;
}

void graph::shortestPath(int vertex)
{
    //deletes the old previous values and makes a new array for the previous positions
    delete[] previousPlaces;
    previousPlaces = new int[gSize];

    //creates an empty array with the same size as the vertices in the graph
    double distance[gSize];

    //makes an array of the vertices that have been visited in the shortest path
    bool shortestPathSet[gSize];

    //sets all data to the max, not visited, and no previous locations respectively
    for(int i = 0; i < gSize; i++)
    {
        distance[i] = DBL_MAX;
        shortestPathSet[i] = false;
        previousPlaces[i] = -1;
    }
    //makes the distance at the current vertex 0
    distance[vertex] = 0;

    //iterates through all positions before the last vertex
    for(int count = 0; count < gSize-1; count++)
    {
        //sets the current minimum distance as the max for a double and declares a minIndex position
        double min = DBL_MAX;
        int minIndex;
    
        for (int v = 0; v < gSize; v++)
        {
            //checks if the vertex in the shortestPathSet has not been visited yet and 
            //the weight of the vertex v is less than the current minimum
            if (shortestPathSet[v] == false && distance[v] < min)
            {
                //sets the minimum distance as the weight at v and the minIndex as s
                min = distance[v];
                minIndex = v;
            }
        }

        //marks the vertex as having been visited
        shortestPathSet[minIndex] = true;

        //goes through all the vertices in the graph
        for(int i = 0; i < gSize; i++)
        {
            //checks to see if the current vertex has been visited already
            //and the weight connecting the minimum and the current vertex is not 0
            //and that the distance has not hit the max
            if(shortestPathSet[i] == false && weights[minIndex][i] != 0 && distance[minIndex] != DBL_MAX)
            {
                //checks to see if the distance at the minimum weight plus the weight of the vertex is less than the distance at the vertex
                if(distance[minIndex] + weights[minIndex][i] < distance[i])
                {
                    //adds up the distances from all the vertices visited
                    distance[i] = distance[minIndex] + weights[minIndex][i];
                    //loads in the the current vertex as being in the shortest path
                    previousPlaces[i] = minIndex;
                }
            }
        }
        
    }

    //moves all the data from the distance array to the smallestWeight array
    for(int i = 0; i < gSize; i++)
    {
        smallestWeight[i] = distance[i];
    }
}

void graph::clearGraph()
{
    //goes through and deletes all the arrays in weights
    for (int i = 0; i < gSize; i++)
    {
        delete [] weights[i];
    }

    //deletes all the allocated memory and sets gSize to 0
    delete [] weights;
    delete smallestWeight;
    gSize = 0;
}
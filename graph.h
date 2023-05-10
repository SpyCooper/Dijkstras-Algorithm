#ifndef GrApH
#define GrApH

#include <vector>

using namespace std;

class graph
{
    public:
        graph(int size); //constructor
        ~graph(); //deconstructor (calls clearGraph())
        void createGraph(); //creates the graph from the input data from the keyboard
        void printShortest(int vertex); //prints out the shortest path from the inputted vertex
        void shortestPath(int vertex); //finds the shortest path from the vertex to the end of the graph
        void clearGraph(); //clears all the allocated data
        void printGraph(); //prints the graph with the names and the connects in a matrix form (similar to input data)

    protected:
        double **weights; //pointer to creat weight matrix
        double *smallestWeight; //pointer to create the array to store the smallest weight from source to vertices
        int gSize; //size of the graph
        string *names; //an array of all the names of the vertices
        int *previousPlaces; //the array of previous vertices in the shortest path
};

#endif
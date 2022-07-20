//
//  CSCE 311
//  HW_4_Problem_1
//
//  Created by Jared Vaughn on 4/22/22.
//
/* By reading in values from a .txt, this program creates a graph composed of verticies, the edges which they share, and the value(or length) of those edges.
  
    With a constructed graph, the program prompts the user to input a source vertex and a destination vertex. Utilizing dijkstra's algorith, the program provides the shortests path between the two, by accessing each vertex's adjecenices.
 
 
 !!! Note - Line 333
 !!! text.txt pathname used for Xcode on Mac, may need to be changed to current project directory
 */

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

class VertexPoint {
    /* The VertexPoint class was designed as a result of combining all the data structures needed to hold all required information. This format simplifies calculations by limiting the scope to a single instance of the class rather than multiple data structures*/
private:
    int point;
    string pointName;
     // vector containing ordered pair of (adjecent vertex, weight)
    double Length; // for use in the
    int Edges;
    
public:
    //constructors
    VertexPoint(int x, string name, int e);
    VertexPoint(VertexPoint *a);
    
    vector<pair<int, double> > adjecents;
    void updateLength(double x);
    void makePair(int point, double weight);
    int getPoint();
    string getName();
    double getLength();
    int minWeight();
    int minVertex();
    int getEdge();
    ~VertexPoint();
};

VertexPoint::VertexPoint(int x, string name, int e): point(x), pointName(name)
{
    // constructor for vertex
                        // adjecency vector to be updated
    Length = numeric_limits<double>::max(); // set to infinity
    Edges = e;
};

VertexPoint::VertexPoint(VertexPoint *a) {
    //creates a VetrexPoint copy of a VertexPoint pointer
    point = a->getPoint();
    pointName = a->getName();
    Length = a->getLength();
    Edges = a->getEdge();
    adjecents = a->adjecents;
    
}

VertexPoint::~VertexPoint() {
    
}


int VertexPoint::getEdge() {
    //returns # of edges
    return Edges;
}

void VertexPoint::updateLength(double x){
    // updates current length
    Length = x;
}


void VertexPoint::makePair(int point, double weight) {
    // Converts the line of the text file that contains the adjecent vertex and weight to an ordered pair
    // and places the pair in the VertexPoint member variable adjacents
    
    pair<int, double>  p;
    p.first = point;
    p.second = weight;
    
    adjecents.push_back(p);
    
}

string VertexPoint::getName() {
    // Returns the Vertex's Name
    return pointName;
}

int VertexPoint::getPoint() {
    // Returns the Vertex's Number
    return point;
}

double VertexPoint::getLength() {
    // Returns Vertex Length
    return Length;
}



int VertexPoint::minWeight() {
    // returns the minimum weight of adjacent verteccies
    
    int min = numeric_limits<int>::max(); // initialize to infinity
    
    for (auto i: adjecents) {
        if (i.second < min) {
            min = i.second;
        }
    }
    return min;
}


int VertexPoint::minVertex(){
    // returns the point number of the minimum weight adjecent vertex
    
    int min = numeric_limits<int>::max(); // initialize to infinity
    
    for (auto i: adjecents) {
        if (i.second < min) {
            min = i.first;
        }
    }
    
    return min;
}

int minLengthOfGrid(vector<VertexPoint> a) {
    // returns the position of the minimum length in the vector of vertex points
    if (a.size() == 0) {
        return 0;
    }
    
    double minL = numeric_limits<double>::max();
    int minP = 0;
 
    for (int i = 0; i < a.size(); i++) {
        
        if (a[i].getLength() < minL) {
            minL = a[i].getLength();
            minP = i;
        }
    }

    return minP;
}

void printVector(vector<VertexPoint> a) {
    // For all verticies with a vector, this prints its point number and name
    for (auto i:a) {
        cout << i.getPoint() << " " << i.getName() << endl;
    }
    
}

void printAdjecent(VertexPoint a) {
    //prints the adjecent vertecies and their weight for a given Vertex
    for (int i = 0; i < a.adjecents.size(); i++) {
        cout << a.adjecents[i].first << " " << a.adjecents[i].second << endl;
    }
}


void djist(vector<VertexPoint> grid, int origin, int destination) {
    /*
     This function follows Dijkstra's Algorithm for findign the shortest distance between 2 verticies within a graph.
     
     Input:
     vector<VertexPoint> grid: A vector representation of the entire graph comprised of individual VertexPoint classes
     int origin: The Point number of the starting vertex
     int destination: The point number of the desired ending vertex
     
     OutPut:
        None. Prints prevLength which is the cumilitave shortests length between the origin and destination
     
     */
    
    
    vector<VertexPoint> Tvec = grid; // T set
    vector<int> Qvec = {};          // Q set
    int placeHolder;
    bool containsTarget = false;
    VertexPoint* current = NULL;  // Vertex Pointer
    double prevLength = 0.0;       // For printing
    string originName;              // For printing
    string destName;                // for printing
    
    
    //ensure the origin is a valid vertex within the set...
    // set a pointer to it
    // get its name
    for (int i = 0; i < Tvec.size(); i++) {
        if (Tvec[i].getPoint() == origin) {
            current = &Tvec[i];
            originName = Tvec[i].getName();
            break;
        }
    }
    
    // create an actual VertexPoint the holds the values of the origin, as the origin will
    // eventually be deleted from the set, thus deleting the pointer
    VertexPoint currentActual(current);
    currentActual.updateLength(0); // set the length to 0
    
    
    
    // ensure the destination is a valid vertex in the set
    // get its name
    for (int i = 0; i < Tvec.size(); i++) {
        if (Tvec[i].getPoint()  == destination) {
            containsTarget = true;
            destName = Tvec[i].getName();
        }
    }
    
    cout << endl;
    cout << originName << " to " << destName << endl;
    
    
    
    // while the destination vertex is in the set
    
    while(containsTarget) {
        // add the current vertex to the Q set
        Qvec.push_back(current->getPoint());
        
       
        // erase the vertex in set T that matches the origin pointer
        placeHolder = 0;
        for (int i = 0; i < Tvec.size(); i++ ) {
            if (Tvec[i].getPoint() == current->getPoint()) {
                Tvec.erase(Tvec.begin()+ i);
                break;
            }
        }
    
        
        // iterate through remaining vertexs in set T
        // iterate through the currentActual vertex's adjecencies
        // update the length of any adjecent vertex found in both set T and currentActual's adjecencies
        
        for (int i = 0; i < Tvec.size(); i++) {
            
            for (int j = 0; j < currentActual.adjecents.size(); j++) {
                if (currentActual.adjecents[j].first == Tvec[i].getPoint()) {
                    if (currentActual.getLength() + currentActual.adjecents[j].second < Tvec[i].getLength()) {
                        Tvec[i].updateLength(currentActual.getLength() + currentActual.adjecents[j].second);
                    }
                }
            }
        }
        
       
       
        prevLength = currentActual.getLength(); // // retain the current length
        
        // set current pointer equal to vertex in set T that has the smallest length
        current = &Tvec[minLengthOfGrid(Tvec)];
       
        // CurrentActual has been moved from set T to set Q  and its length store in prevLength
        // currentActual can now be updated as the vertex in set T that has the smallest length
        currentActual = current;
        
        
        // exit while loop
        // unless destination remains a vertex of set T
        containsTarget = false;
        for (int i = 0; i < Tvec.size(); i++) {
            if (Tvec[i].getPoint() == destination) {
                containsTarget = true;
            }
        }
    }
    
    //
    if (prevLength == 0) {
        cout << "You are already at your destination" << endl;
    }
    else {
    cout << "The total distance from " << originName << " to " << destName << " is " << prevLength << endl;
    }
    
        
        
}




void printAdj(VertexPoint a) {
    // helper fucntion to visual program build
    for (int i = 0; i < a.adjecents.size(); i++) {
        cout << a.adjecents[i].first << "   " << a.adjecents[i].second << endl;
    }
}



int main() {
    
    vector<VertexPoint> grid;
    int NumberOfStops;
    int PointNumber;
    string StopName;
    int adjacentPoints;
    int line;
    int vertex;
    double weight;
    ifstream inFS;
    string temp;
    int source;
    int dest;
   
    
    
    // read in text document line by line
    // loop for # of points and number of adjecencies for each point
    
    inFS.open("/Users/vaughn/Desktop/text.txt"); // use inFS.open("text.txt") with included file
    getline(inFS, temp);
    NumberOfStops = stoi(temp);
    
    for (int i = 0; i < NumberOfStops; i++) {
        getline(inFS, temp) ;// Vertex #
        PointNumber = stoi(temp);
        getline(inFS, StopName);
        getline(inFS, temp);
        adjacentPoints = stoi(temp);
        
        grid.push_back(new VertexPoint(PointNumber, StopName, adjacentPoints));
        
        for (int j = 0; j < adjacentPoints; j++) {
            getline(inFS, temp);
            stringstream VandW(temp);
            getline(VandW, temp, ' ');
            line = stoi(temp);
            getline(VandW, temp);
            weight = stod(temp);
            
            grid[i].makePair(line, weight);
        }
    }
    
    
    //While loop to prompt user to search for shortest path
    
    cout << "Shortest Path Finder \n------------------" << endl;
    
    
    bool run = true;
    
    while(run) {
        printVector(grid);
        char again = 'x';
        cout << "Enter source number:  ";
        cin >> source;
        cout << "Enter destination number: ";
        cin >> dest;
        
        djist(grid, source, dest);
        cout<<endl;
        while ((again != 'y') and (again != 'n')) {
            cout << "Would you like to search again? (y/n) :    ";
            cin >> again;
        }
        if (again == 'n') {
            run = false;
        }
    }
    
}

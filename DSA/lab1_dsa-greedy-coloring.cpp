/**
 * 
 * Greedy algorithm for coloring
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>
#define max 100

using namespace std;
typedef bool graph[max][max];
graph g;
unsigned int color[max];
bool colored[max];
void init(unsigned int);
void colorize(unsigned int);
void display(unsigned int);

int main(int argc, char** argv) {
    unsigned int nbr;
    cout << "Enter number of edges,less than "<< max-1 <<" : ";
    cin >> nbr;

    // verify nbr of edges is less than max-1
    while (nbr > max-2) {
        cout << "Bad argument, enter a number less that " << max - 1 << " :";
        cin >> nbr;
    }
    // calling functions
    init(nbr+1);
    colorize(nbr+1);
    display(nbr+1);

    return 0;
}
// initialize the graph
void init(unsigned int nbr) {
    char ch;
    for (int i=1;i<nbr;i++)
        g[i][i]=0;
    cout << "Edges and node connections: " << endl;
    cout << "Tell if the following edges have a common node" << endl;

    for (int i=1;i<nbr-1;i++)
        for(int j=i+1;j<nbr;j++) {
            cout << i <<" -- "<< j <<" ? Y / N: ";
            cin >> ch;
            while((toupper(ch)!='Y') && (toupper(ch)!='N'))
            {
                cout << "\nInvalid choice :( try again!!! ";
                cin >> ch;
            }
            if (toupper(ch)=='Y')
                g[i][j] = g[j][i] = true;
            else
                g[i][j] = g[j][i] = false;
        }
}
// colorize the graph function
void colorize(unsigned int nbr) {
    int clr = 1;                // color variable
    for(int i = 1;i < nbr;i++)  // init all edges as not colored
        colored[i]=false;
    int check = 1;              // this variable to check edge with previous colored edges
    // start coloring
    for(int i = 1; i < nbr;i++){
        if (!colored[i]) {      // if edge already colored move to next one
            color[i]=clr;       // assign color to current edge
            colored[i] = true;  // set edge as colored
            for(int k = i + 1;k < nbr;k++) {
                if ( !colored[k] && !g[i][k] ) {    // check if i and j edges if colored and have a common node ?
                    if ( !g[check][k]) {            // check j edge with previous colored edges
                        color[k] = color[i];
                        colored[k] = true;
                        check = k;
                    }
                }
            }
            check = 1;
            clr++;              // increment color
        }
    }
}
// display the result
void display(unsigned int nbr) {
    cout << "Array representation: \n" << endl;
    for ( int i = 1;i < nbr;i++) {
        for ( int j = 1;j < nbr;j++)
            cout << g[i][j] << "  ";
        cout << endl;
    }

    cout<<endl<< "Edges\t | Colors: "<< endl;
    for ( int i = 1;i < nbr;i++)
    {
        cout << i<<"\t | "<< color[i] << endl;
    }
}



/**
 * 
 * Huffman algorithm
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>
#include <fstream>
#define max 40

using namespace std;

//  initialize maximum number of trees and characters
const int max_char = 36;
const int max_tree = 2*max_char -1;

// node that hold information about other left
// and right and parent nodes connected to it
// leaf cell structure
struct leafcell {
    char sym;
    int occur;
    double prob;
};
struct node {
    int left,right,parent;
};
// root cell structure
struct rootcell {
    double weight;
    int root;
    char sym;
};

// create leafs and trees and forest
node tree[max_tree];
rootcell forest[max_char];
leafcell symbLeaf[max_char];

void init(int size);
void smallest(int & least, int & second, int remaintrees); // get smallest leafs in the forest
int create( int, int, int&); // create a new node
void huffman(int&,int&); // make the huffman tree by connecting the nodes created
void printCode (int size); // print the codes
void readStr(int & size); // read and get string

int main() {
    cout << "huffman tree encoder:\n\n";
    int size = 0;
    // read characters from the file
    readStr(size);
    // initialize last tree, and last node
    int remaintrees = size;
    int nodeCount = size-1;
    // initialize the tree and the forest
    init(size);
    // call huffman() to create the tree
    huffman(remaintrees, nodeCount);

    // assign codes to the characters
    printCode(size);

    return 0;
}

// read characters from the file
void readStr(int & size) {
        // reading file is 'test.txt'
        char temp[max];
        ifstream is("test.txt");     // open file

        int count = 0; // character counter
        char ch;
        while (is.get(ch))  // read char by char until end-of-file EOF
                if ( ch != EOF) {
                    temp[count] = ch;
                    count++;
                }
        is.close(); // close file
        count--;
        // copy chars in new array without null chars
        char read_char[count];
        for(int i = 0; i<count; i++)
            read_char[i] = temp[i];
        cout << "Your text is: \n" << read_char << endl;
        for (int i = 0; i<=count+1; i++) {
            double repeat = 1;
            if ( read_char[i] != '\0') {
                    for (int j=i+1;j<=count+1;j++)
                        if ( read_char[i] == read_char[j] ) {
                                repeat++;
                                read_char[j] = '\0';
                        }
                        symbLeaf[size].sym = read_char[i];
                        symbLeaf[size].occur = repeat;
                        symbLeaf[size].prob = repeat/(count);
                        size++;
                }
        }
        size--;
        size--;
        for (int k = 0; k<size; k++)
            cout << k << "\t" << "\'" << symbLeaf[k].sym << "\'" << " , p = " << symbLeaf[k].occur << endl;
}

// initialize the tree and the forest
void init(int size) {
    // initialize the tree to -1 for each node
    for(int i=0;i<2*size;i++){
        tree[i].left = -1;
        tree[i].right = -1;
        tree[i].parent = -1;
    }
    // initializing the weights of the chars in string in a forest
    for(int i=0;i<size;i++) {
        forest[i].weight = symbLeaf[i].occur;
        forest[i].sym = symbLeaf[i].sym;
        forest[i].root = i;
    }
}

// check the two smallest numbers in the forest based on their weight
// get smallest weights from last similar to ordering them
void smallest(int &least, int &second, int remaintrees) {
    if ( forest[0].weight <= forest[1].weight) {
        least = 0;
        second = 1;
    }
    else {
        least = 1;
        second = 0;
    }

    for(int i=2;i<remaintrees;i++) {
        if( forest[i].weight < forest[least].weight ) {
            second = least;
            least = i;
        }
        else if ( forest[i].weight < forest[second].weight )
            second = i;
    }
}

// create and return a new node from the two smallest node, update the parent of the smallest node
// put least in left and second in right
int create( int l, int r, int &nodeCount) {
    nodeCount++;
    tree[nodeCount].left = forest[l].root;
    tree[nodeCount].right = forest[r].root;
    tree[forest[l].root].parent = nodeCount;
    tree[forest[r].root].parent = nodeCount;
    return nodeCount;
}

// huffman tree builder function
void huffman(int &remaintrees, int &nodeCount) {
    int least,second, newroot;

    while( remaintrees > 1 ) {
        // return the smallest nodes based on their weights
        smallest(least, second, remaintrees);
        //cout << least << "->" << forest[least].weight << " - " << second << "->" << forest[second].weight << endl; ///
        newroot = create(least, second, nodeCount); // create a new node
        forest[least].weight += forest[second].weight;
        forest[least].sym = '\0';
        //cout << "=" << forest[least].weight << endl; ///
        forest[least].root = newroot;
        for(int i = second; i<remaintrees; i++) {
            forest[i].root = forest[i+1].root;
            forest[i].sym = forest[i+1].sym;
            forest[i].weight = forest[i+1].weight;
        }
        //forest[second].root = forest[remaintrees-1].root;
        //forest[second].sym = forest[remaintrees-1].sym;
        //forest[second].weight = forest[remaintrees-1].weight;
        remaintrees--;

        /////////////////////////////////////////////////////////////////////
        //cout << second << "->" << forest[second].weight << endl;
        //for (int k = 0; k<remaintrees; k++)
        //    cout << k << "\t" << "\'" << forest[k].sym << "\'" << "\tp = " << forest[k].weight << endl;
        /////////////////////////////////////////////////////////////////////
    }
}

// assign codes to the characters
void printCode(int size) {
    cout << "\nThe resulting codes: ";
    int j;
    cout << endl;
    string code;
    for(int i = 0; i<size; i++) {
        code = "";
        cout << "\'" << symbLeaf[i].sym << "\'" << " ::: ";
        j = i;
        // check if the parent is  present (not equal to = -1)
        while(tree[j].parent != -1 ) {
            // if the character is a left child assign code 0 to it
            // else assign code 1 to it
            if (j == tree[tree[j].parent].left )
                code = "0" + code;
            else
                code = "1" + code;
            j = tree[j].parent;
        }
        cout << code << endl;
    }
}

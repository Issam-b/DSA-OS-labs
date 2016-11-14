/**
 * 
 * List implementation
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>
#include <string.h>
#define max 100 //maximum size for number of names for array list

using namespace std;

typedef struct list { // define new type of structure for array list
    unsigned int size;
    string name[];
} list;
list l;

struct Node { // structure for nodes of pointer list
    string name;
    Node* next;
};
typedef Node * list_p; // defining new type list_p of pointer to Node
list_p lp; // pointer list object

void display_menu(); // function to display the menu

// array functions
void init(list& l);
void insert(list& l, string new_name, unsigned int pos);
void remove(list& l, unsigned int pos);
void search(list& l, string new_name);
void forward(list& l);
void backward(list& l);

// pointer functions
void init_p(list_p & lp);
void insert_p(list_p & lp, string new_name, unsigned int pos);
void remove_p(list_p & lp, unsigned int pos);
void search_p(list_p & lp, string new_name);
void forward_p(list_p & lp);
void backward_p(list_p & lp);
int count; // used with pointer backward listing to enumerate names

int main(int argc, char** argv) {
    cout << "Name management menu: " << endl;
    int choice; // work option variable (array or pointer)
    int pos; // position variable
    bool pointer;
    init(l); // initialize array list
    init_p(lp); // initialize pointer list

    // check if user want pointers or array
    char p_choice;
    cout << "use pointer functions ? y / n : ";
    cin >> p_choice;
    // check the input is Y or N only
    while((toupper(p_choice)!='Y') && (toupper(p_choice)!='N')) {
                cout << "Try again!!! ";
                cin >> p_choice;
            }
            if (toupper(p_choice)=='Y')
                pointer = true; // choose to work with pointers
            else
                pointer = false; // choose to work with arrays
    string myname;
    display_menu();
    cin >> choice;
    while ( choice < 7 ) {
        switch (choice) {
            case 1: // new name
                cout << "----> New name <----\n";
                cout << "Enter a name: ";
                cin >> myname;
                cout << "Position: ";
                cin >> pos;
                if(pointer) // choose work pointer
                    insert_p(lp, myname, pos);
                else
                    insert(l, myname, pos);
                break;
            case 2: // delete a name by position
                cout << "----> Delete a name <----\n";
                cout << "Position to remove: ";
                cin >> pos;
                if(pointer) // choose work pointer
                    remove_p(lp, pos);
                else
                    remove(l, pos);
                break;
            case 3: // search for a name
                cout << "----> Search for a name <----\n";
                cout << "Name to search: ";
                cin >> myname;
                if(pointer) // choose work pointer
                    search_p(lp, myname);
                else
                    search(l, myname);
                break;
            case 4: // show names in increasing order
                cout << "----> List names forward <----\n";
                cout << "Forward listing: \n";
                if(pointer) // choose work pointer
                    forward_p(lp);
                else
                    forward(l);
                break;
            case 5: // show names in decreasing order
                cout << "----> List names backward <----\n";
                cout << "Backward listing: \n";
                if(pointer) { // choose work pointer
                    if(lp != NULL) {
                        // variable to keep track of of backward_p listing names
                        count = 1;
                        cout << "position:\t  name" << endl;
                        backward_p(lp);
                    }
                    else
                        cout << "empty list" << endl;
                }
                else
                    backward(l);
                break;
            case 6: // re-display the menu
                display_menu();
                break;
        }
        cin >> choice;
    }
    cout << "Quiting ..." << endl;

    return 0;
}// end main()

void display_menu() {
    string menu = "1- New name\n2- Delete a name\n3- Search for a name\n4- List names forward\n5- List names backward\n6- Menu\n7- Quit";
    cout << menu << endl;
    cout << "\nSelect an option: ";
} // end function display_menu()

// array functions
void init(list& l) {
    l.size = 0; // or NULL
} // end function init

// insert a name in specific position
void insert(list& l, string new_name,unsigned int pos) {
    // check that list is not full
    if(l.size == max)
        cout << "list is full" << endl;
    else {
        if(pos < 0 || pos > max) // check position pos exists
            cout << "No such position" << endl;
        // if position is higher than current list size then put the new name at the endl
        // if new name should be inserted in the middle of list then shift the names below that position
        // down and put the name in that position
        else {
            if(pos <= l.size) {
                for(int i = l.size;i >= pos;i--)
                    l.name[i+1] = l.name[i]; // reorder names
                l.name[pos] = new_name;
            }
            else
                l.name[l.size+1] = new_name;
            l.size++;
        }
    }
} // end function insert()

// remove a name by its position
void remove(list &l, unsigned int pos) {
    if(l.size == 0)
        cout << "list is empty" << endl;
    if(pos < 0 || pos >= l.size )
        cout << "No such position" << endl;
    // if list is neither empty or position does not exist the program remove the wanted name
    // and shift the names below it to top
    else {
        for(int i = pos;i < l.size;i++)
            l.name[i] = l.name[i+1];
        l.name[l.size] = ""; // set removed name to empty string
        l.size--;
    }
} // end function remove()

// search for a name
void search(list &l, string new_name) {
    bool nothing = false; // variable to indicate no result found
    
    // loop the whole array and check each time if name exists
    // then return the results because this can return more than one result
    for(int i = 1;i < l.size+1;i++)
        if(new_name == l.name[i]) {
            cout << "Position is: " << i << endl;
            nothing = true; // no need to print error message
        }
        if(!nothing)
            cout << "No such name" << endl;
} // end function search()

// forward display of names (array)
void forward(list& l) {
    if(l.size == 0)
        cout << "list empty" << endl;
    else {
        cout << "position:\t  name" << endl; // tab titles
        // loop the list and display names one by one
        for(int i = 1;i < l.size+1;i++)
            cout << i << "\t\t  " << l.name[i] << endl;
    }
} // end function forward()

// backward display of names (array)
void backward(list& l) {
    if(l.size == 0)
        cout << "empty list" << endl;
    else {
        cout << "position:\t  name" << endl; // tab titles
        for(int i = l.size;i > 0;i--) // listing each name in list
            cout << i << "\t\t  " << l.name[i] << endl;
    }
} // end function backward()

// pointer functions
void init_p(list_p & lp) {
    lp = 0; // or NULL
} // end function init_p()

// insert a name in specific position (pointer)
void insert_p(list_p & lp, string new_name, unsigned int pos){
    if(pos < 0) // reject negative positions
        cout << "Can't have negative position" << endl;
    else {
        list_p temp = new Node; // temporary node
        temp = lp;
        list_p newNode = new Node; // node to be added to list
        newNode -> name = new_name; // assign name to node
        // if list is empty then assign new node to head and next node to null
        if(lp == 0) {
            lp = newNode;
            lp -> next = 0;
        }
        else {
            if(pos == 1) { // insert node as head of list (position 1)
                // assign new node to point to current head in list
                newNode -> next = temp;
                lp = newNode; // reassign the head to node inserted
            }
            // 
            else {
                int i = 1;
                // assign temporary node to position needed
                while(temp -> next != 0 && i < pos) {
                    i++;
                    temp = temp -> next;
                    }
                // new node points to node in pos+1, which were in position "pos"
                newNode -> next = temp -> next;
                temp -> next = newNode; // node in pos-1 to point to new node
            }
        }
    }
} // end function insert_p()

// remove a name by its position (pointer)
void remove_p(list_p & lp, unsigned int pos) {
    list_p temp = new Node; // temporary node
    temp = lp;
    list_p temp1 = new Node; // second temporary node
    int i = 1;
    // if removing first node (head), assign current head to next node
    if(pos == 1) {
        lp = lp -> next;
    }
    // if removing a node in middle of list we need two temporary nodes
    // used to change node connections
    else {
        // assign temporary node to node of position needed
        while( temp != 0 && i < pos) {
            temp1 = temp;
            i++;
            temp = temp -> next;
        }
        if(temp == 0) // position does not exist
            cout << "No such position" << endl;
        // change node connections to second node in front of it
        else {
            temp1 -> next = temp -> next;
        }
    }
    temp = 0; // set temporary node to null
    delete temp; // remove temporary node
} // end function remove_p()

// search for a name (pointer)
void search_p(list_p & lp, string new_name) {
    list_p temp = new Node; // temporary node
    temp = lp; // assign it to list head node
    if(temp == 0)
        cout << "List empty" << endl;
    else {
        bool found = false;
        int i = 1;
        // search and compare names node by node, it may return multiple matches
        // check node is not null
        while(temp != NULL) {
            if(temp -> name == new_name) { // check the names are equal or not
                cout << "Position is: " << i << endl;
                found = true; // a match found 
            }
            temp = temp -> next;
            i++;
        }
        if(temp == 0 && !found) // name not found
                cout << "No such name" << endl;
    }
} // end function search_p()

// forward display of names (pointer)
void forward_p(list_p & lp) {
    if(lp == 0)
        cout << "List empty" << endl;
    else {
        int i = 1; // name order or position
        list_p temp = new Node;
        temp = lp;
        cout << "position:\t  name" << endl; // title tab
        while(temp != 0) { // check node is not null
            cout << i << "\t\t  " << temp -> name << endl;
                temp = temp -> next; // assign node to next node
            i++;
        }
    }
} // end function forward_p()

// backward display of names (pointer)
void backward_p(list_p & lp) {
    // temporary node used to shift the linked list and display names
    list_p temp = new Node;
    if(lp != NULL) { // check node is not null
        temp = lp;
        count++;
        // recursion is used, it stops when reaching null node in previous if condition
        backward_p(temp -> next);
        cout << count << "\t\t  " << temp -> name << endl; // display the names
    }
    count--; // name position decrease
} // end function backward_p()

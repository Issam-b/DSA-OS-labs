/**
 * 
 * Stacks with arrays
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>
#define max 100

using namespace std;

struct Person {
    string first_name;
    string last_name;
    int age;
};

typedef struct Stack_cell {
    Person person[max];
    unsigned int size;
} Stack;
Stack stack;

unsigned int age;
unsigned int option;
string first_name, last_name;

/* define the functions */
void init (Stack &);
void push(Stack &, int, string , string);
void pop(Stack &);
void display(Stack &);
void backward(Stack &);

int main() {

    cout << "**** Stack Implementation with Arrays ****"<<endl;
    init(stack); // initialize the stack
    // print the menu and ask the user to choose and option
    cout <<endl<<" Choose an Option:\n 1. Add\n 2. Delete\n 3. Traverse Forward\n 4. Traverse Backward\n 5. Quit\n";
    cin >> option;
    while(option < 5) {
        switch(option) {
            case 1:
                cout << "Enter the First Name: ";
                cin >> first_name;
                cout << "Enter the Last Name: ";
                cin >> last_name;
                cout<<"Please Enter the Age: ";
                cin >> age;
                // call the push function
                push(stack,age,first_name,last_name);
                break;
            case 2:
                // call the pop function
                pop(stack);
                break;
            case 3:
                cout<<"\nthe Stack (forward): \n\n";
                display(stack);
                break;
            case 4:
                cout<<"\nthe Stack (backward): \n\n";
                backward(stack);
                break;
        } // end switch
        // print the menu and ask the user to choose and option
        cout <<endl<<" Choose an Option:\n 1. Add\n 2. Delete\n 3. Traverse Forward\n 4. Traverse Backward\n 5. Quit\n";
        cin >> option;
    }// end of while

    cout << "Quiting ..." << endl;
    return 0;
}

// initialize function
void init (Stack & stack) {
    stack.size = 0;
}

// push function to add a new person cell at the top of the stack
void push(Stack & stack,int age,string first_name,string last_name) {
    stack.person[stack.size].age = age;
    stack.person[stack.size].first_name = first_name;
    stack.person[stack.size].last_name = last_name;
    stack.size++;
}

// pop function to remove the person cell from on top of the stack
void pop(Stack & stack) {
    if (stack.size == 0)
        cout << "\nStack is empty" << endl;
    else {
        cout << "Removing person:" << endl;
        cout << ">" << stack.person[stack.size-1].age << "\t>" << stack.person[stack.size-1].first_name << "\t>" << stack.person[stack.size-1].last_name << endl;
        stack.size--;
    }
}

// forward function to print the stack elements backwardly
void backward(Stack & stack) {
    if(stack.size == 0 )
        cout << "Stack is empty" << endl;
    else
        for( int i = stack.size-1; i>=0; i--)
            cout<<">"<<stack.person[i].age << "\t>" << stack.person[i].first_name << "\t>" << stack.person[i].last_name << endl;
}

// display function print the stack elements forwardly
void display(Stack & stack) {
    if (stack.size == 0)
        cout << "Stack is empty" << endl;
    else
        for(int i=0; i<stack.size; i++)
            cout<<">" << stack.person[i].age << "\t>" << stack.person[i].first_name << "\t>" << stack.person[i].last_name << endl;
}

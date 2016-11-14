/**
 * 
 * Stacks and Queues
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>
#define bufferSize 20 // maximum length of one name

using namespace std;

struct Person { // structure that contain a person's info
    string first_name;
    string last_name;
    unsigned int age;
    Person * next;
};

struct Queue_p {
    Person * head;
    Person * tail;
};

typedef Queue_p * Queue; // define new type as pointer to one queue cell Queue_p
Queue queue = new Queue_p;

typedef Person * Stack;
Stack stack;

void Menu(bool QueueOrStack); // function to display the menu
unsigned int check_input(unsigned int n); // validate integer input

// Stack functions
void init_stack(Stack & stack);
void push_stack(Stack & stack, string first_name, string last_name, unsigned age);
void pop_stack(Stack & stack);
void forward_stack(Stack & stack);
void backward_stack(Stack & stack);

// Queue functions
void init_queue(Queue & queue);
void insert_queue(Queue & queue, string first_name, string last_name, unsigned age);
void remove_queue(Queue & queue);
void forward_queue(Queue & queue);
void backward_queue(Queue & queue);

unsigned int count;

int main(int argc, char** argv) {
    cout << "Persons management program: " << endl;
    int choice; // menu choice
    bool QueueOrStack;
    init_stack(stack);
    init_queue(queue);

    // check if user want QueueOrStacks or array
    char p_choice;
    cout << "Use Queue or Stack functions ? Q / S : ";
    cin >> p_choice;

    // choose to work with stack or queue
    while((toupper(p_choice)!='Q') && (toupper(p_choice)!='S')) {
                cout << "Try again!!! ";
                cin >> p_choice;
            }
            if (toupper(p_choice)=='Q')
                QueueOrStack = true; // choose to work with Queue
            else
                QueueOrStack = false; // choose to work with Stack

    unsigned int age;
    char first_name[bufferSize], last_name[bufferSize];
    Menu(QueueOrStack); // print the menu
    choice = check_input(choice); // get choice input and validate it
    while ( choice < 6 ) {
        switch (choice) {
            case 1: // new name
                cout << "----> New name <----\n";
                cin.ignore();
                cout << "First name: ";
                cin.getline(first_name, bufferSize);
                cout << "Last name: ";
                cin.getline(last_name, bufferSize);
                cout << "age: ";
                age = check_input(age); // input age and check integer validity
                if(QueueOrStack)
                    insert_queue(queue, first_name, last_name, age);
                else
                    push_stack(stack, first_name, last_name, age);
                break;
            case 2: // delete a name by position
                if(QueueOrStack)
                    remove_queue(queue);
                else
                    pop_stack(stack);
                break;
            case 3: // show names in increasing order
                cout << "----> List forward <----\n";
                if(QueueOrStack)
                    forward_queue(queue);
                else
                    forward_stack(stack);
                break;
            case 4: // show names in decreasing order
                cout << "----> List backward <----\n";
                if(QueueOrStack) {
                    if(queue -> head != 0) {
                        count = 1; // variable to keep track of of backward_p listing names
                        cout << "position:\tfirst name:\tlast name:\tage:" << endl;
                        backward_queue(queue);
                    }
                    else
                        cout << "Queue empty" << endl;
                }
                else {
                    if(stack != 0) {
                        // variable to keep track of of backward_p listing names
                        count = 1;
                        cout << "position:\tfirst name:\tlast name:\tage:" << endl;
                        backward_stack(stack);
                    }
                    else
                        cout << "Stack empty" << endl;
                }
                break;
            case 5: // re-display the menu
                Menu(QueueOrStack);
                break;
        }
        cout << "\nSelect an option: ";
        cin >> choice;
    }
    cout << "Quiting ..." << endl;

    return 0;
}// end main()

// function to print menu
void Menu(bool QueueOrStack) {
    string menu;
    if(QueueOrStack)
        menu = "1- New name\n2- Delete first name\n3- List forward\n4- List backward\n5- Menu\n6- Quit";
    else
        menu = "1- Push new name\n2- Pop the stack\n3- List forward\n4- List backward\n5- Menu\n6- Quit";
    cout << menu << endl;
    cout << "\nSelect an option: ";
} //

// function to check integer validity
unsigned int check_input(unsigned int n) {
    for (;;) {
        if (cin >> n && n >= 0) {
            break;
        } else {
            cout << "Try again [integer]: ";
            cin.clear();
            cin.ignore(10, '\n');
        }
    }
    return n;
}

// Stack functions
void init_stack(Stack & stack) {
    stack = NULL;
}

// function push stack
void push_stack(Stack & stack, string first_name, string last_name, unsigned age) {
    Stack NewPerson = new Person; // new stack cell to be added

    // fill person info
    NewPerson -> first_name = first_name;
    NewPerson -> last_name = last_name;
    NewPerson -> age = age;
    if(stack == 0) { // if stack is empty assign new cell to current stack
        stack = NewPerson;
        stack -> next = 0;
    }
    else { // if not empty add new cell to top of stack
        NewPerson -> next = stack;
        stack = NewPerson;
    }
}

// function pop stack
void pop_stack(Stack & stack) {
    if(stack == 0)
        cout << "Stack empty" << endl;
    else { // print top cell of stack and assign stack top to next person cell
        cout << "Poping person: " << stack -> first_name << " " << stack -> last_name << ", " << stack -> age << " years old"<< endl;
        stack = stack -> next;
    }
}

// function print stack elements forwardly
void forward_stack(Stack & stack) {
    if(stack == 0)
        cout << "Stack empty" << endl;
    else {
        int i = 1; // name order or position
        Stack temp = new Person; // temporary cell used to traverse the stack
        temp = stack; // assign temp cell to top of stack
        cout << "position:\tfirst name:\tlast name:\tage:" << endl; // title tab
        while(temp != 0) { // loop until last stack cell is null
            cout << i << "\t\t" << temp -> first_name << "\t\t" << temp -> last_name << "\t\t" << temp -> age << endl;
                temp = temp -> next; // assign cell to next cell
            i++;
        }
    }
}

// function print stack elements backwardly
void backward_stack(Stack & stack) {
    Stack temp = new Person; // temporary cell used to traverse the stack
    if(stack != NULL) {
        temp = stack;
        count++;
        backward_stack(temp -> next); // use recursion with next cell in stack this will execute recursively until last cell
        // print person's info
        cout << count << "\t\t" << temp -> first_name << "\t\t" << temp -> last_name << "\t\t" << temp -> age << endl;
    }
    count--;
}

// Queue functions
void init_queue(Queue & queue) {
    queue -> head = 0;
    queue -> tail = 0;
}

// function to insert new person to queue
void insert_queue(Queue & queue, string first_name, string last_name, unsigned age) {
    Queue temp = new Queue_p; // temporary queue cell
    temp = queue; // assign temp to current queue
    Person * tempPerson = new Person; // new person to be added
    
    // fill person info
    tempPerson -> first_name = first_name;
    tempPerson -> last_name = last_name;
    tempPerson -> age = age;
    tempPerson -> next = 0; // point to null
    if(queue -> head == 0) // if queue is empty
        queue -> head = temp -> tail = tempPerson; // assign queue head and tail to new cell
    else {
        queue -> tail -> next = tempPerson; // put new cell at queue tail
        queue -> tail = queue -> tail -> next; // update tail address
    }
}

// function to remove person from the queue
void remove_queue(Queue & queue) {
    if(queue -> head == 0)
        cout << "Queue empty" << endl;
    else {
        Person * tempPerson; // temporary cell used to print and then delete first cell in the queue
        tempPerson = queue -> head;

        // print first person in queue
        cout << "deleting person: " << tempPerson -> first_name << " " << tempPerson -> last_name << ", " << tempPerson -> age << " years old"<< endl;
        queue -> head = queue -> head -> next;
        tempPerson = 0; // set to null
        delete tempPerson; // delete first cell in queue
    }
}

// function to print persons in queue forwardly
void forward_queue(Queue & queue) {
    if(queue -> head == 0)
        cout << "Queue empty" << endl;
    else {
        int i = 1; // name order or position
        Person * tempPerson;
        tempPerson = queue -> head;
        cout << "position:\tfirst name:\tlast name:\tage:" << endl; // title tab
        while(tempPerson != 0) { // loop until person cell is null
            cout << i << "\t\t" << tempPerson -> first_name << "\t\t" << tempPerson -> last_name << "\t\t" << tempPerson -> age << endl;
                tempPerson = tempPerson -> next; // assign cell to next cell
            i++;
        }
    }
}

// function to print persons in queue backwardly
void backward_queue(Queue & queue) {
    Queue TQueue = new Queue_p; // temporary cell used to traverse the stack
    if(queue -> head != 0) {
            TQueue -> head = queue -> head -> next;
        count++;
        backward_queue(TQueue); // use recursion with next cell in queue this will execute recursively until last cell
        // print person's info
        cout << count << "\t\t" << (queue -> head) -> first_name << "\t\t" << (queue -> head) -> last_name << "\t\t" << (queue -> head) -> age << endl;
    }
    count--;
}

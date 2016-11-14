/**
 * 
 * Scheduling algorithms
 * Priority & round Robin
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>

using namespace std;

typedef struct Process {
    unsigned int pid;
    unsigned int burstTime;
    unsigned int priority;
    unsigned int arrivalTime;
    unsigned int waitingTime;
    unsigned int turnaroundTime;
} Process;
unsigned int timeQ;

void priority(Process pool[], unsigned int n);
void roundRobin(Process pool[], unsigned int n);
void sortPr(Process pool[], unsigned int n);

int main() {
    unsigned int n;
    Process pool[n], poolr[n];
    cout << "enter the number of processes: ";
    cin >> n;
    for(int i = 1; i<n+1; i++) { // inputting process info
            pool[i].pid = i;
            poolr[i].pid = i = pool[i].pid = i;
            cout << "Enter burst time and arrival time and priority and time quntum of process " << i << " : ";
            cin >> pool[i].burstTime;
            poolr[i].burstTime = pool[i].burstTime;
            cin >> pool[i].arrivalTime;
            poolr[i].arrivalTime = pool[i].arrivalTime;
            cin >> pool[i].priority;
            // make sure first process arrival time is 0
            if(pool[1].arrivalTime != 0) {
                cout << "First PID arrival time should be 0" << endl;
                pool[1].arrivalTime = 0;
            }
        }
    cout << "Enter Quntum time: ";
    cin >> timeQ;

    // call priority()
    cout << "\nPriority algorithm:" << endl;
    priority(pool, n);
    cout << "\nRoundRobin algorithm:" << endl;
    roundRobin(poolr, n);

    return 0;
}

void priority(Process pool[], unsigned int n) {
    int tbt =0;
    int burst[n];
    double awt=0;

    // sort the processes by the burst time increasingly
    sortPr(pool, n);

    // initialize the waiting time and calculate the sum of the burst time for each processes
    // and create a temporary copy of burst times
    for (int i=1; i<n+1; i++) {
        pool[i].waitingTime = 0;
        tbt += pool[i].burstTime;
        burst[i]= pool[i].burstTime;
    }

    // loop from 0 time to total burst time (time line)
    for(int i = 0; i<tbt; i++) {
        // check if the first process with the shortest burst time has arrived
        // and if the burst time hasn't reached zero
        for(int j=1; j<n+1; j++) {
            if (pool[j].arrivalTime <= i && burst[j] != 0 ) {
                burst[j]--;
                // check if the other processes are already arrived and keep them in the waiting queue
                // increment the waiting of other processes
                for(int k=1; k<n+1; k++)
                    if (pool[k].arrivalTime <= i && burst[k] != 0 )
                        if (k!=j)
                            pool[k].waitingTime++;
                break;
            }
        }
    }

    // calculate total waiting time and turnaround time for each process
    for(int i = 1; i<n+1; i++) {
        awt += pool[i].waitingTime;
        pool[i].turnaroundTime = pool[i].burstTime + pool[i].waitingTime;
    }

    // print table
        cout<<"Process Id\t|Burst Time\t|Arrival Time\t|Priority\t|Waiting Time\t|Turnaround Time"<<endl;
        for(int i = 1; i<n+1; i++) {
            cout << "   " << pool[i].pid << "\t\t   " << pool[i].burstTime << "\t\t   " << pool[i].arrivalTime << "\t\t   " << pool[i].priority << "\t\t   " << pool[i].waitingTime << "\t\t   " << pool[i].turnaroundTime << endl;
        }

    cout << "the average waiting time is: "<< (double)awt / n << endl;

    cout << "\nThe Gantt Chart" << endl;
    // print table of dashes
    cout << "-";
    for(int i = 1; i<tbt+1; i++)
        cout << "---";
    cout << "\n";

    // print process PID in the gantt chart
    for (int i=1; i<n+1; i++)
        burst[i]= pool[i].burstTime;
    int temp;
    for(int i=0;i<=tbt;i++)
        for(int j=1;j<n+1;j++)
            if( pool[j].arrivalTime <= i && burst[j]!=0)
                {
                    if(temp != pool[j].pid)
                      cout<< "|P" << pool[j].pid;
                    else
                        cout << "   ";
                      burst[j]--;
                      temp = pool[j].pid;
                      break;
                }

    // print table of dashes
    cout << "|\n-";
    for(int i = 1; i<tbt+1; i++)
        cout << "---";
    cout << endl;

    // print time unber the gantt chart
    for(int i=0;i<=tbt;i++) {
        if(i > 9)
            cout << "\b";
        cout << i<< "  ";
    }
    cout << endl << endl;
}

void roundRobin(Process pool[], unsigned int n) {
    unsigned int tbt=0, time=0;
    unsigned int burst[n];
    double awt=0;

    for (int i=1; i<n+1; i++) {
        pool[i].waitingTime = 0;
        tbt += pool[i].burstTime;
        burst[i]= pool[i].burstTime;
    }

    int temp;
    while( time < tbt ) {
        for(int i=1; i<n+1; i++) {
            // check if the first process has arrived and burst time isn't zero
            if (pool[i].arrivalTime <= time &&  burst[i] != 0 ) {
                // if the burst time is greater or equal the quantum time  => assign a quantum time for that process
                // else the process will work for the burst time that it has
                if( burst[i] <= timeQ)
                    temp = burst[i];
                else
                    temp = timeQ ;

                // burst time of the process will be decremented based on the quantum time and
                // the other process which have arrived will be in the waiting queue
                while(temp > 0) {
                burst[i]--;
                        for(int j=1; j<n+1; j++)
                            if (pool[j].arrivalTime <= time && burst[j] != 0 )
                                if (j!=i)
                                    pool[j].waitingTime++;
                time++;
                temp--;
                }
            }
        }
    }

    // calculate the turnaround time and the average waiting time
    for(int i=1; i<n+1; i++) {
        pool[i].turnaroundTime= pool[i].burstTime+pool[i].waitingTime;
        awt+=pool[i].waitingTime;
    }

    cout<<"Process Id\t|Burst Time\t|Arrival Time\t|Waiting Time\t|Turnaround Time"<<endl;
    for(int i=1; i<n+1; i++)
        cout<< pool[i].pid <<"\t\t|"<<pool[i].burstTime<<"\t\t|"<<pool[i].arrivalTime << "\t\t|"<<pool[i].waitingTime<<"\t\t|"<<pool[i].turnaroundTime<<endl;

    cout<<endl;
    cout<<"the average waiting time is: "<<awt/n<<endl<<endl;

    cout<<"the Gantt Chart"<<endl;

    // print table of dashes
    cout << "-";
    for(int i = 1; i<tbt+1; i++)
        cout << "---";
    cout << endl;

    // print the gantt chart
    for (int i=1; i<n+1; i++)
        burst[i]= pool[i].burstTime;
    int i =0;
    int temp1;
    while ( i < tbt )
        for(int k=1; k<n+1; k++)
            if( pool[k].arrivalTime <= i && burst[k]!=0 ) {
                if( burst[k] <= timeQ)
                    temp = burst[k];
                else
                    temp = timeQ;

                while(temp > 0)
                {
                    if(temp1 != pool[k].pid)
                      cout<< "|P" << pool[k].pid;
                    else
                        cout << "   ";
                      temp1 = pool[k].pid;
                      burst[k]--;
                      temp--;
                      i++;
                }
            }

    // print table of dashes
    cout << "|\n-";
    for(int i = 1; i<tbt+1; i++)
        cout << "---";
    cout << endl;

    // print time unber the gantt chart
    for(int i=0;i<=tbt;i++) {
        if(i > 9)
            cout << "\b";
        cout << i<< "  ";
    }
    cout << endl << endl;
}

// function to sort processes according to their burst time
void sortPr(Process pool[], unsigned int n) {
    bool match = true;
    Process temp;
    while(match)
    {
        match = false;
        for (int i=1; i<n; i++)
        {
            if (pool[i].priority > pool[i+1].priority)
            {
                temp = pool[i+1];
                pool[i+1] = pool[i];
                pool[i] = temp;
                match = true;
            }
        }
    }
}

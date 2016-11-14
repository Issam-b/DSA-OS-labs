/**
 * 
 * Scheduling algorithms
 * FCFS - SJF
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>

using namespace std;

// define Process type
typedef struct Process {
    unsigned int pid;
    unsigned int burstTime;
    unsigned int arrivalTime;
    unsigned int waitingTime;
    unsigned int turnaroundTime;
} Process;

void fcfs (Process processPool[], unsigned int pnbr);
void sjf (Process processPool[], unsigned int pnbr);
void sortBurst(Process processPool[], unsigned int pnbr); // sort decreasingly according to burst time

int main (int agrc, char ** argv) {
    unsigned int pnbr; // number of processes
    cout << "Scheduling algorithm calculator:" << endl;
    cout << "Enter number of processes: ";
    cin >> pnbr;
    Process processPool[pnbr]; // create an array of processes
    for(int i = 1; i<pnbr+1; i++) { // inputting process info
        processPool[i].pid = i;
        cout << "Enter burst time and arrival time of process " << i << " : ";
        cin >> processPool[i].burstTime;
        cin >> processPool[i].arrivalTime;
        // make sure first process arrival time is 0
        if(processPool[1].arrivalTime != 0) {
            cout << "First PID arrival time should be 0" << endl;
            processPool[1].arrivalTime = 0;
        }
    }
    
    cout << "Using FCFS algorithm: " << endl;
    fcfs(processPool, pnbr);
    cout << "Using SJF algorithm: " << endl;
    sjf(processPool, pnbr);

    return 0;
}

// function for FCFS algorithm calculation
void fcfs (Process processPool[], unsigned int pnbr) {

    //calculation of wait and turnaround time for each process
    for(int i = 1; i<pnbr+1; i++) {
        unsigned int btsum = 0;
        for(int j = 1; j<i; j++) {
            btsum += processPool[j].burstTime; // total burst time
        }
        processPool[i].waitingTime = btsum - processPool[i].arrivalTime;
        processPool[i].turnaroundTime = processPool[i].burstTime + processPool[i].waitingTime;
    }

    // print table of info
    if(pnbr == 0)
        cout << "no processes !" << endl;
    else {
        cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time" << endl;
        for(int i = 1; i<pnbr+1; i++) {
            cout << "   " << processPool[i].pid << "\t\t   " << processPool[i].burstTime << "\t\t   " << processPool[i].arrivalTime << "\t\t   " << processPool[i].waitingTime << "\t\t   " << processPool[i].turnaroundTime << endl;
        }
    }

    // print average waiting time
    unsigned int awt = 0;
    for(int i = 1; i<pnbr+1; i++)
        awt += processPool[i].waitingTime; // total waiting time
    cout << "The average waiting time is: " << (double)awt / pnbr << endl << endl;

    // print gantt chart for FCFS
    cout << "The Gantt chart using FCFS algorithm: " << endl;
    unsigned int btsum = 0; // total sum of burst times
    for(int i = 1; i<pnbr+1; i++)
        btsum += processPool[i].burstTime;
    // print table of dashes
    cout << "-";
    for(int i = 1; i<btsum+1; i++)
        cout << "---";
    cout << "\n|";
    
    // print process PIDs ordered with FCFS algorithm
    int n = 1;
    int temp = processPool[1].burstTime;
    for(int i = 1; i<3*btsum+1; i++) {
        if(i == 3*temp) {
            cout << "\b\bP" << n << "|";
            n++;
            temp += processPool[n].burstTime;
        }
        else
            cout << " ";
    }

    // print table of dashes
    cout << "\n-";
    for(int i = 1; i<btsum+1; i++)
        cout << "---";
    cout << "\n";

    // print time scale of gantt chart
    cout << 0;
    n = 1;
    temp = processPool[1].burstTime;
    for(int i = 1; i<3*btsum+1; i++) {
        if(i == 3*temp) {
            if(processPool[n-1].burstTime > 9 && n > 1)
                cout << "\b";
            cout << temp;
            n++;
            temp += processPool[n].burstTime;
        }
        else
            cout << " ";
    }
    cout << endl << endl;
}

// function for SJF algorithm calculation
void sjf(Process processPool[], unsigned int pnbr) {
    int tbt =0;
    int burst[pnbr];
    double awt=0;

    // initialize the waiting time and calculate the sum of the burst time for each processes
    for (int i=1; i<pnbr+1; i++) {
        processPool[i].waitingTime = 0;
        tbt += processPool[i].burstTime;
    }

    // sort the processes by the burst time increasingly
    sortBurst(processPool, pnbr);

    // create a temporary copy of burt times
    for (int i=1; i<pnbr+1; i++)
        burst[i]= processPool[i].burstTime;

    // loop from 0 time to total burst time (time line)
    for(int i = 0; i<tbt; i++) {
        // check if the first process with the shortest burst time has arrived
        // and if the burst time hasn't reached zero
        for(int j=1; j<pnbr+1; j++)
        {
            if (processPool[j].arrivalTime <= i && burst[j] != 0 )
            {
                burst[j]--;
                // check if the other processes are already arrived and keep them in the waiting queue
                // increment the waiting of other processes
                for(int k=1; k<pnbr+1; k++)
                    if (processPool[k].arrivalTime <= i && burst[k] != 0 )
                        if (k!=j)
                            processPool[k].waitingTime++;
                break;
            }
        }
    }

    // calculate total waiting time and turnaround time for each process
    for(int i = 1; i<pnbr+1; i++) {
        awt += processPool[i].waitingTime;
        processPool[i].turnaroundTime = processPool[i].burstTime + processPool[i].waitingTime;
    }

    // print table
        cout << "Process ID\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time" << endl;
        for(int i = 1; i<pnbr+1; i++) {
            cout << "   " << processPool[i].pid << "\t\t   " << processPool[i].burstTime << "\t\t   " << processPool[i].arrivalTime << "\t\t   " << processPool[i].waitingTime << "\t\t   " << processPool[i].turnaroundTime << endl;
        }
        
    cout << "the average waiting time is: "<< (double)awt / pnbr << endl;

    cout << "\nThe Gantt Chart" << endl;
    // print table of dashes
    cout << "-";
    for(int i = 1; i<tbt+1; i++)
        cout << "---";
    cout << "\n";

    // print process PID in the gantt chart
    for (int i=1; i<pnbr+1; i++)
        burst[i]= processPool[i].burstTime;
    int temp;
    for(int i=0;i<=tbt;i++)
        for(int j=1;j<pnbr+1;j++)
            if( processPool[j].arrivalTime <= i && burst[j]!=0)
                {
                    if(temp != processPool[j].pid)
                      cout<< "|P" << processPool[j].pid;
                    else
                        cout << "   ";
                      burst[j]--;
                      temp = processPool[j].pid;
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

// function to sort processes according to their burst time
void sortBurst(Process processPool[], unsigned int pnbr) {
    bool match = true;
    Process temp;
    while(match)
    {
        match = false;
        for (int i=1; i<pnbr; i++)
        {
            if (processPool[i].burstTime > processPool[i+1].burstTime)
            {
                temp = processPool[i+1];
                processPool[i+1] = processPool[i];
                processPool[i] = temp;
                match = true;
            }
        }
    }
}

/**
 * 
 * Page deplacement algorithms
 * FIFO, Optimal, Least Used algorithms
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>
#define max 100

using namespace std;
struct cell {
    int refrence[max];
    int  fault;

};

cell frame;

int nbr_frames, nbr_string;
int reference_string[max];
void init();
void fifo(cell);
void opt(cell);
void lru(cell);
int get_index(cell,int);
int get_least_used(cell,int);

int main() {
    cout << "enter the length of the string: ";
    cin >> nbr_string;
    cout<< "enter the reference string : ";
    for(int i=0; i<nbr_string; i++)
        cin >> reference_string[i];

    cout<< "enter the nbr of frames: ";
    cin >> nbr_frames;

    init();
    cell frame1 = frame;
    cell frame2 = frame;
    cout<< "\nthe fifo algorithm is: \n\n";
    fifo(frame);
    cout <<"\nthe optimal placement algorithm is: \n\n";
    opt(frame1);
    cout <<"\nthe least used placement algorithm is: \n\n";
    lru(frame2);
    return 0;
}

void init() {
    for(int i=0; i<nbr_frames; i++)
    {
        frame.refrence[i] = -1;
        frame.fault = 0;
    }
}

void fifo(cell frame) {
    int j = 0, i = 0;
    bool temp ;

    while( j< nbr_string)
    {
        temp = false;
        for(int k=0; k<nbr_frames; k++)
            if ( reference_string[j] == frame.refrence[k])
		temp = true;
        if (!temp)
        {
            frame.refrence[i] = reference_string[j];
            frame.fault++;
            i++;
            cout<<"PF N# "<<frame.fault<<" --> ";
        }

	j++;
	if ( i == nbr_frames)
	    i = 0;
	for(int k =0; k<nbr_frames; k++) {
	    cout<<frame.refrence[k]<<" ";
	}
	    cout<<endl;
    }

}

void opt(cell frame) {
    int  j = 0, temp = 0, dummy = 0;

    for(int i = 0 ; i < nbr_string ; i++ )
    {
        dummy = 0;
        if ( temp >= nbr_frames )
        {
            for(int k = 0; k < nbr_frames ; k++)
                if ( reference_string[i] == frame.refrence[k] )
                    dummy++;
            if(dummy == 0)
            {
                int u = get_index(frame,i);
                frame.refrence[u] = reference_string[i];
                frame.fault++;
                cout<<"PF N# "<<frame.fault<<" --> ";
            }
        }
        else
        {
            frame.refrence[temp] = reference_string[i];
            frame.fault++;
            cout<<"PF N# "<<frame.fault<<" --> ";
        }

        temp++;
        for(int k =0; k<nbr_frames; k++)
            cout<<frame.refrence[k]<<" ";
            cout<<endl;
    }
}


int get_index(cell frame, int i ) {
    int temp = 0;

    for(int k = i ; k < nbr_string ; k++ )
        for(int j = 0 ; j < nbr_frames ; j ++ )
            if ( reference_string[k] == frame.refrence[j] )
            {
                temp++;
                if (temp == nbr_frames)
                    return j;

                break;
            }
    return 0;

}

void lru(cell frame) {
    int  j = 0, temp = 0, dummy = 0;

    for(int i = 0 ; i < nbr_string ; i++ )
    {
        dummy = 0;
        if ( temp >= nbr_frames )
        {
            for(int k = 0; k < nbr_frames ; k++)
                if ( reference_string[i] == frame.refrence[k] )
                    dummy++;
            if(dummy == 0)
            {
                int u = get_least_used(frame,i);
                frame.refrence[u] = reference_string[i];
                frame.fault++;
                cout<<"PF N# "<<frame.fault<<" --> ";
            }
        }
        else
        {
            frame.refrence[temp] = reference_string[i];
            frame.fault++;
            cout<<"PF N# "<<frame.fault<<" --> ";
        }
        temp++;
        for(int k =0; k<nbr_frames; k++)
            cout<<frame.refrence[k]<<" ";
            cout<<endl;

    }

}

int get_least_used(cell frame,int i) {
    int temp = 0;
    bool referenced[max] ;
    for(int i = 0 ; i < nbr_frames ; i++ )
        referenced[i] = false;

    for(int w = i-1 ; w >= 0 ; w-- )
        for(int j = 0 ; j < nbr_frames ; j++ )
        {
            if ( reference_string[w] == frame.refrence[j] && !referenced[j]  )
            {
                temp++;
                referenced[j] = true;
                if (temp == nbr_frames)
                    return j;

                break;
            }
        }

}

/**
 * 
 * Page deplacement algorithms
 * FIFO, Optimal, Least Used algorithms
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <iostream>

using namespace std;

int length,frcount,page[30],frame[10]; // change

void OPT();
void FIFO();
void LRU();

int main() {
    int i,ch;
    cout << "Enter the length of reference string: ";
    cin >> length;
    cout << "Enter reference string: ";
    for(i=0;i<length;i++)
	cin >> page[i];
    cout << "Enter number of frames: ";
    cin >> frcount;
	do {
	    cout << "\n***** MENU *****\n";
	    cout << "\n1)FIFO";
	    cout << "\n2)OPTIMAL";
	    cout << "\n3)LRU";
	    cout << "\n4)Exit";
	    cout << "\n========>> Choice:";
	    cin >> ch;
	    switch(ch) {
		case 1:
		    FIFO();
		    break;
		case 2:
		    OPT();
		    break;
		case 3:
		    LRU();
		    break;
	    }
	} while(ch!=4);

}

void FIFO() {
    int i,f=0,r=0,s=0,fault=0,flag=0,num,frfault[10],tmp=0;
    // initialize
    for(i=0;i<frcount;i++)
	frame[i]=-1;
    while(s<length) {
	flag=0;
	num=page[s];
	for(i=0;i<frcount;i++) {
	    if(num==frame[i]) {
		s++;
		flag=1;
		break;
	    }
	}
	if(flag==0) {
	    if(r<frcount) {
		frame[r]=page[s];
		r++;
		s++;
		fault++;
	    }
	    else {
		if(f<frcount) {
		    frame[f]=page[s];
		    s++;
		    f++;
		    fault++;
		}
		else
		    f=0;
	    }
	    frfault[s-1] = 1;
	}

	// print result
	cout << "\n";
	for(i=0;i<frcount;i++) {
	    cout << frame[i] <<  " ";
	}
	if(frfault[s-1] == 1 && tmp !=fault)
	    cout << "  No " << fault;
	tmp=fault;
    }
    cout << "\nPage Faults [#] = " << fault;

}

void OPT() {
    int count[10],i,j,k=0,fault=0,flag,temp,current,c,max,m,cnt,p,x,frfault[10];
    // initialize
    for(i=0;i<frcount;i++) {
	count[i]=0;
	frame[i]=-1;
    }
    for(i=0;i<length;i++) {
	flag=0;
	temp=page[i];
	for(j=0;j<frcount;j++) {
	    if(temp==frame[j]) {
		flag=1;
		break;
	    }
	}
	if((flag==0)&&(k<frcount)) {
	    fault++;
	    frame[k]=temp;
	    k++;
	    frfault[i] = 1;
	}
	else if((flag==0)&&(k==frcount)) {
	    fault++;
	    frfault[i] = 1;
	    for(cnt=0;cnt<frcount;cnt++) {
		current=frame[cnt];
		for(c=i;c<length;c++) {
		    if(current!=page[c])
		    count[cnt]++;
		    else
			break;
		}
	    }
	    max=0;
	    for(m=0;m<frcount;m++) {
		if(count[m]>max) {
		    max=count[m];
		    p=m;
		}
	    }
	    frame[p]=temp;
	}

	// print result
	cout << "\n";
	for(x=0;x<frcount;x++) {
	    cout << frame[x] <<  " ";
	}
	if(frfault[i] == 1)
	    cout << "  No " << fault;
    }
    cout << "\nPage Faults [#] = " << fault;

}

void LRU() {
    int count[10],i,j,k=0,fault=0,flag,temp,current,c,max,m,cnt,p,x,frfault[10];
    // initialize
    for(i=0;i<frcount;i++) {
	count[i]=0;
	frame[i]=-1;
    }
    for(i=0;i<length;i++) {
	flag=0;
	temp=page[i];
	for(j=0;j<frcount;j++) {
	    if(temp==frame[j]) {
		flag=1;
		break;
	    }
	}
	// calculation of the begining and fault check
	if((flag==0)&&(k<frcount)) {
	    fault++;
	    frame[k]=temp;
	    k++;
	    frfault[i] = 1;
	}
	else if((flag==0)&&(k==frcount)) {
	    fault++;
	    frfault[i] = 1;
	    for(cnt=0;cnt<frcount;cnt++) {
		current=frame[cnt];
		for(c=i;c>0;c--) {
		    if(current!=page[c])
			count[cnt]++;
		    else
			break;
		}
	    }
	    max=0;
	    for(m=0;m<frcount;m++) {
		if(count[m]>max) {
		    max=count[m];
		    p=m;
		}
	    }
	    frame[p]=temp;
	}

	// print result
	cout << "\n";
	for(x=0;x<frcount;x++) {
	    cout << frame[x] <<  " ";
	}
	if(frfault[i] == 1)
	    cout << "  No " << fault;
    }
    cout << "\nPage Faults [#] = " << fault;
}

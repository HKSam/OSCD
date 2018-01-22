#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
using namespace std;

struct PCB{
    string Name;
    PCB * pcb;
    unsigned int runTime;
    unsigned int runPriorit;
    bool runStatus;
};

class mainPcb{
private:
    PCB pcb1,pcb2,pcb3,pcb4,pcb5,headPcb;
public:
    void initialPcb();
    void shufflePcb();
    void runPcb();
    void showPcb();
};

void mainPcb::initialPcb(){
    cout<<"==========welcome to PCB scheduling algorithm==========\n";
    cout<<"Plz insert name for the 5 PCB\n";
    cin>>pcb1.Name>>pcb2.Name>>pcb3.Name>>pcb4.Name>>pcb5.Name;
    cout<<"Plz insert run time for the 5 PCB(no small than 0)\n";
    cin>>pcb1.runTime>>pcb2.runTime>>pcb3.runTime>>pcb4.runTime>>pcb5.runTime;
    cout<<"Plz insert priority for the 5 PCB(no small than 0 and its run time)\n";
    cin>>pcb1.runPriorit>>pcb2.runPriorit>>pcb3.runPriorit>>pcb4.runPriorit>>pcb5.runPriorit;
    cout<<"Setting pcb status...\n";
    if (pcb1.runTime!=0) {pcb1.runStatus=1;}
    if (pcb2.runTime!=0) {pcb2.runStatus=1;}
    if (pcb3.runTime!=0) {pcb3.runStatus=1;}
    if (pcb4.runTime!=0) {pcb4.runStatus=1;}
    if (pcb5.runTime!=0) {pcb5.runStatus=1;}
    cout<<"Setting pcb sequence...\n";
    pcb1.pcb=&pcb2;pcb2.pcb=&pcb3;pcb3.pcb=&pcb4;pcb4.pcb=&pcb5;pcb5.pcb=&pcb1;headPcb.pcb=&pcb1;
    cout<<"Initialise successfully...\n";
}

void mainPcb::shufflePcb(){
    int num=5;
    while(headPcb.pcb->runTime==0&&num!=0) {
        headPcb.pcb=headPcb.pcb->pcb;
        num--;
    }
    PCB exchangePcb=headPcb;//???
    PCB oldheadPcb=headPcb;//???
    headPcb.pcb=headPcb.pcb->pcb;
    while (headPcb.pcb!=oldheadPcb.pcb) {
        if (headPcb.pcb->runPriorit>exchangePcb.pcb->runPriorit&&headPcb.pcb->runStatus==1) {
            exchangePcb.pcb=headPcb.pcb;
        }
        headPcb.pcb=headPcb.pcb->pcb;
    }
    headPcb=exchangePcb;
    cout<<"Suffle successfully...\n";
}

void mainPcb::runPcb(){
    cout<<"Start poccessing...\n";
    shufflePcb();
    while (headPcb.pcb->runStatus) {
        headPcb.pcb->runPriorit--;
        headPcb.pcb->runTime--;
        if (headPcb.pcb->runTime==0) {
            headPcb.pcb->runStatus=0;
        }
        sleep(1);
        cout<<"Run\t"<<headPcb.pcb->Name<<"\tone time\n";
        showPcb();
        shufflePcb();
    }
    cout<<"End poccessing...\n";
}
void mainPcb::showPcb(){
    cout<<"PCB status as follows(Name|runTime|runPriority|runStatus)\n";
    cout<<pcb1.Name<<"\t"<<pcb1.runTime<<"\t"<<pcb1.runPriorit<<"\t"<<pcb1.runStatus<<"\n";
    cout<<pcb2.Name<<"\t"<<pcb2.runTime<<"\t"<<pcb2.runPriorit<<"\t"<<pcb2.runStatus<<"\n";
    cout<<pcb3.Name<<"\t"<<pcb3.runTime<<"\t"<<pcb3.runPriorit<<"\t"<<pcb3.runStatus<<"\n";
    cout<<pcb4.Name<<"\t"<<pcb4.runTime<<"\t"<<pcb4.runPriorit<<"\t"<<pcb4.runStatus<<"\n";
    cout<<pcb5.Name<<"\t"<<pcb5.runTime<<"\t"<<pcb5.runPriorit<<"\t"<<pcb5.runStatus<<"\n";
}

int main(int argc, const char * argv[]) {
    // insert code here...
    mainPcb testpcb;
    testpcb.initialPcb();
    testpcb.runPcb();
    return 0;
}

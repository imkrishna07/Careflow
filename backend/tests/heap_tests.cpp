#include "MaxHeap.h"
#include <cassert>
#include <iostream>
Patient p(std::string id,int sev,long time){Patient x;x.patientID=id;x.severity=sev;x.arrivalEpoch=time;return x;}
int main(){MaxHeap h;h.insertPatient(p("a",2,1));h.insertPatient(p("b",5,3));h.insertPatient(p("c",5,2));h.insertPatient(p("d",1,0));assert(h.invariant());assert(h.extractMax().patientID=="c");assert(h.updateSeverity("d",5));assert(h.peek()->patientID=="d");assert(h.removePatient("a"));assert(!h.searchPatient("a"));assert(h.invariant());assert(h.extractMax().patientID=="d");assert(h.extractMax().patientID=="b");h.insertPatient(p("z",3,9));h.insertPatient(p("y",3,9));assert(h.extractMax().patientID=="y");bool duplicate=false;try{h.insertPatient(p("z",4,1));}catch(...){duplicate=true;}assert(duplicate);std::vector<Patient> v;for(int i=0;i<100;++i)v.push_back(p(std::to_string(i),i%5+1,i));h.build(v);assert(h.invariant());while(h.size()){h.extractMax();assert(h.invariant());}std::cout<<"Heap tests passed\n";}

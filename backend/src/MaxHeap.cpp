#include "MaxHeap.h"
#include <stdexcept>
bool MaxHeap::higher(const Patient&a,const Patient&b){ if(a.severity!=b.severity)return a.severity>b.severity; if(a.arrivalEpoch!=b.arrivalEpoch)return a.arrivalEpoch<b.arrivalEpoch; return a.patientID<b.patientID; }
void MaxHeap::swapAt(size_t a,size_t b){std::swap(heap[a],heap[b]);positions[heap[a].patientID]=a;positions[heap[b].patientID]=b;}
void MaxHeap::heapifyUp(size_t i){while(i){size_t p=(i-1)/2;if(!higher(heap[i],heap[p]))break;swapAt(i,p);i=p;}}
void MaxHeap::heapifyDown(size_t i){for(;;){size_t l=2*i+1,r=l+1,b=i;if(l<heap.size()&&higher(heap[l],heap[b]))b=l;if(r<heap.size()&&higher(heap[r],heap[b]))b=r;if(b==i)break;swapAt(i,b);i=b;}}
void MaxHeap::build(const std::vector<Patient>& v){heap=v;positions.clear();for(size_t i=0;i<heap.size();++i)positions[heap[i].patientID]=i;if(heap.size()>1)for(size_t i=heap.size()/2;i-->0;)heapifyDown(i);}
void MaxHeap::insertPatient(const Patient&p){if(positions.count(p.patientID))throw std::invalid_argument("Duplicate patient ID");heap.push_back(p);positions[p.patientID]=heap.size()-1;heapifyUp(heap.size()-1);}
Patient MaxHeap::extractMax(){if(heap.empty())throw std::runtime_error("No patients waiting");Patient out=heap[0];positions.erase(out.patientID);if(heap.size()==1){heap.pop_back();return out;}heap[0]=heap.back();heap.pop_back();positions[heap[0].patientID]=0;heapifyDown(0);return out;}
const Patient* MaxHeap::peek()const{return heap.empty()?nullptr:&heap[0];}
const Patient* MaxHeap::searchPatient(const std::string&id)const{auto it=positions.find(id);return it==positions.end()?nullptr:&heap[it->second];}
bool MaxHeap::removePatient(const std::string&id){auto it=positions.find(id);if(it==positions.end())return false;size_t i=it->second,last=heap.size()-1;positions.erase(it);if(i==last){heap.pop_back();return true;}heap[i]=heap[last];heap.pop_back();positions[heap[i].patientID]=i;if(i&&higher(heap[i],heap[(i-1)/2]))heapifyUp(i);else heapifyDown(i);return true;}
bool MaxHeap::updateSeverity(const std::string&id,int s){if(s<1||s>5)return false;auto it=positions.find(id);if(it==positions.end())return false;size_t i=it->second;int old=heap[i].severity;heap[i].severity=s;if(s>old)heapifyUp(i);else if(s<old)heapifyDown(i);return true;}
std::vector<Patient> MaxHeap::displayPatients()const{auto copy=*this;std::vector<Patient> out;out.reserve(heap.size());while(copy.size())out.push_back(copy.extractMax());return out;}
bool MaxHeap::invariant()const{if(positions.size()!=heap.size())return false;for(size_t i=0;i<heap.size();++i){auto p=positions.find(heap[i].patientID);if(p==positions.end()||p->second!=i)return false;if(i&&higher(heap[i],heap[(i-1)/2]))return false;}return true;}

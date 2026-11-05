#pragma once
#include "Patient.h"
#include <vector>
#include <unordered_map>
#include <string>
class MaxHeap {
  std::vector<Patient> heap;
  std::unordered_map<std::string,size_t> positions;
  static bool higher(const Patient&, const Patient&);
  void swapAt(size_t,size_t); void heapifyUp(size_t); void heapifyDown(size_t);
public:
  void build(const std::vector<Patient>&);
  void insertPatient(const Patient&);
  Patient extractMax();
  const Patient* peek() const;
  const Patient* searchPatient(const std::string&) const;
  bool removePatient(const std::string&);
  bool updateSeverity(const std::string&,int);
  std::vector<Patient> displayPatients() const;
  size_t size() const { return heap.size(); }
  bool invariant() const;
};

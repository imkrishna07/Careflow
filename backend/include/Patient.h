#pragma once
#include <string>
#include <cstdint>
struct Patient {
  std::string patientID, name, gender, condition, emergencyCategory, arrivalTime, treatmentTime;
  int age=0, severity=1, originalSeverity=0;
  std::int64_t arrivalEpoch=0, waitSeconds=0;
};

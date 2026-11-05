#include "Database.h"
#include <cassert>
#include <cstdio>
#include <iostream>
int main(){const char* path="/tmp/careflow-database-test.sqlite";std::remove(path);Patient waiting;waiting.patientID="ER-W1";waiting.name="Wait Person";waiting.age=31;waiting.gender="Other";waiting.condition="Test condition";waiting.severity=4;waiting.arrivalTime="2026-11-06 10:00:00";waiting.emergencyCategory="General";waiting.arrivalEpoch=1793959200;Patient done=waiting;done.patientID="ER-T1";done.name="Treated Person";done.treatmentTime="2026-11-06 10:12:00";done.waitSeconds=720;{Database db(path);db.save({waiting},{done});}{Database reopened(path);std::vector<Patient>w,t;reopened.load(w,t);assert(w.size()==1&&w[0].patientID=="ER-W1");assert(t.size()==1&&t[0].patientID=="ER-T1");assert(t[0].treatmentTime=="2026-11-06 10:12:00"&&t[0].waitSeconds==720);}std::remove(path);std::cout<<"SQLite persistence tests passed\n";}

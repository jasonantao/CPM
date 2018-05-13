//Partial WOrking Implementation COde
//Jason Antao


#ifndef TASKS_H
#define TASKS_H

#include <iostream>
#include "task.h"
#include "matrix.h"

const int MAX_NUMBER_TASKS = 1000;             // Including Task 0 and Task N+1
const int MAX_PSF_LINE_LENGTH = 100;

// Array of tasks, indexed by task identifier

class Tasks {
 public:
  int  numberOfTasks() const;
  int  largestTaskNumber() const;
  int  readFile(const char filename[]);   // Reads file into _tasks array

  Tasks criticalPath();                   // TODO FOR ASSIGNMENT; Not const, since you may wish to record it in the private data
  float pathLength(const Tasks& t) const; // TODO FOR ASSIGNMENT      
  float slack(const Task& t) const;       // TODO FOR ASSIGNMENT
  
  Task operator()(const int id) const;
  void operator=(const Task& t);





//Constructor Class Below
  Tasks();                                // Construct Tasks; task array tasks are set to errorTask
 ~Tasks();                                // _numberOfTasks set to -1;
 private:
  friend std::ostream& operator<<(std::ostream& os, const Tasks& t);

  bool readTask(const char line[], const char psfFile[], const int psfLineNumber);
  bool readDependencies(const char line[], const char psfFile[], const int psfLineNumber);
  
   // TODO FOR ASSIGNMENT: Add data as necessary; a matrix class will be needed
  LowerTriangularMatrix _adj;
  LowerTriangularMatrix _time;

  float* _maxTime;
  int* _maxPath;

  int  _numberOfTasks;
  int  _largestTaskNumber;
  Task _tasks[MAX_NUMBER_TASKS+1];
};

#endif

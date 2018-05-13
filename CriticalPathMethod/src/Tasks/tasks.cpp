//////////////////////////////////////////////////////////////////////
//
// Class Tasks:

//Jason Antao
//Minimal WOrking Product

//Worth for what it is, for bonus percentage upto 8%

#include "invariant.h"
#include "tasks.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#define TASKS_INVARIANT(LOC) INVARIANT_TEST(_numberOfTasks < 0, LOC)

int Tasks::numberOfTasks() const {
  TASKS_INVARIANT("Tasks::numberOfTasks");
  return _numberOfTasks;
}

int Tasks::largestTaskNumber() const {
  TASKS_INVARIANT("Tasks::largestTaskNumber");
  return _largestTaskNumber;
}

Task Tasks::operator()(const int id) const {      // This returns info about a task; it does not allow change of a task
  TASKS_INVARIANT("Tasks::largestTaskNumber");
  if (id < 0 || id > _largestTaskNumber)
    return Task();
  else
    return _tasks[id];
}

#define SKIP_WHITESPACE do {                                                                                                                 \
	  int i = 0;                                                                                                                         \
	  while ((line[i] == ' ') || (line[i] == '\t') || (line[i] == '\n') || (line[i] == '\r'))                                            \
	    ++i;                                                                                                                             \
	  if (line[i] != 0) {                                                                                                                \
	    cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl; \
	    exit(-1);                                                                                                                        \
	  }                                                                                                                                  \
        } while(0)


int Tasks::readFile(const char psfFile[]) {       
  TASKS_INVARIANT("Tasks::readFile()");
  ifstream infile;
  infile.open(psfFile);
  if (!infile.is_open()) {
    cerr << "Tasks::readFile(): unable to open file: " << psfFile << "; exiting" << endl;
    exit(-1);
  }
  enum PSF_STATE { START, TASKS, DEPENDENCIES };
  PSF_STATE state = START;
  bool done = false;
  int psfLineNumber = 0;
  while (!done) {
    ++psfLineNumber;
    char line[MAX_PSF_LINE_LENGTH];
    if (!infile.getline(line, MAX_PSF_LINE_LENGTH)) {       // Get next line
      if (strlen(line) == MAX_PSF_LINE_LENGTH - 1) {        // If line is max length, this is why we had a problem
	cerr << "Tasks::readFile(): Maximum line length (" << MAX_PSF_LINE_LENGTH << ") exceeded at line " << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      else if (infile.eof()) {                     // If not, probably at end of file
	done = true;
      }
      else {                                       // Weird; no idea what happened
	cerr << "Tasks::readFile(): Unexpected file read error occurred at line " << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
    }
    switch (state) {
    case START:
      switch (line[0]) {
      case '%':                  // Comment; ignore rest of line
	break;

      case 't':                  // Start of "Tasks"
      case 'T':
	// Verify, then switch to TASKS state (will accept text after "Tasks" provided it is seprated by whitespace)
	if ((strncasecmp(line, "Tasks", 5) == 0) && (line[5] == 0 || line[5] == ' ' || line[5] == '\t'))
	  state = TASKS;
	else {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;

      case ' ':                  // Gonna be nice and skip the line if it is all whitespace
      case '\t':
      case '\n':
      case '\r':
	SKIP_WHITESPACE;
	break;
	
      case 0:                    // Empty line; skip it
	break;

      default:
	cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      break;
  //Creating a case for the various tasks as listed and with discussions on PIAZZA

    case TASKS:
      switch (line[0]) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':                  


	if (!readTask(line, psfFile, psfLineNumber)) {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;
	
      case 'd':                  


      case 'D':

	if ((strncasecmp(line, "Dependencies", 12) == 0) && (line[12] == 0 || line[12] == ' ' || line[12] == '\t'))
	  state = DEPENDENCIES;
	else {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;

      case '%':                  // Comment; ignore rest of line
	break;

      case ' ':                  // Gonna be nice and skip the line if it is all whitespace
      case '\t':
      case '\n':
      case '\r':
	SKIP_WHITESPACE;
	break;
	
      case 0:                    // Empty line; skip it
	break;

      default:
	cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      break;

    case DEPENDENCIES:
      switch (line[0]) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':                  // Some task description
	if (!readDependencies(line, psfFile, psfLineNumber)) {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;
 
      case '%':                  // Comment; ignore rest of line
	break;

      case ' ':                  // Gonna be nice and skip the line if it is all whitespace
      case '\t':
      case '\n':
      case '\r':
	SKIP_WHITESPACE;
	break;
	
      case 0:                    // Empty line; skip it
	break;

      default:
	cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      break;
     
    default:
      cerr << "Tasks::readFile(): Unknown state while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
      exit(-1);
    }
  }
  // Now add Project Initiation and Project Completion
  _tasks[0] = Task(0);
  _largestTaskNumber++;
  _tasks[_largestTaskNumber] = Task(_largestTaskNumber);
  return psfLineNumber;
}

bool Tasks::readTask(const char line[], const char psfFile[], const int psfLineNumber) {
  // ID , Expected , Best , Worst , Name
  int id;
  float expected;
  float best;
  float worst;
  char  name[MAX_TASK_NAME_LENGTH] = {0};
  int rc = sscanf(line, "%d , %f , %f , %f , %255c", &id, &expected, &best, &worst, name);
  if (rc != 5) {
      cerr << "Tasks::readFile(): Unable to parse line while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
    exit(-1);
  }
  if (id > 0 && id < MAX_NUMBER_TASKS && _tasks[id].isError()) {
    _tasks[id] = Task(id, expected, best, worst, name);
    _numberOfTasks++;
    if (id > _largestTaskNumber)
      _largestTaskNumber = id;
  }
  else {
    cerr << "invalid id" << endl;    // Should output some error message here; for now:
    return false;
  }
  return true;
}

// There is no error checking in this, so if the PSF file is messed up, everything is messed up ...

bool Tasks::readDependencies(const char line[], const char psfFile[], const int psfLineNumber) {


  const char* pLine = line;
  int id = atoi(pLine);
  while (*pLine) {
    if (*pLine == ',') {
      if (!(_tasks[id].addDependency(atoi(pLine+1))))  // Need a better error output here
	return false;
    }
    ++pLine;
  } 
  return true;
} 

Tasks Tasks::criticalPath(){

  //I believe this is a working implementation
  //Implements critical path. 

   LowerTriangularMatrix HolderMatrixLocal(_numberOfTasks+1);
   HolderMatrixLocal.zero();
   _adj = HolderMatrixLocal;
   Tasks critical;

//Need the maxtime component from the identifier
   critical._maxTime = new float[_numberOfTasks+1];
   for(int i = 0;i< _numberOfTasks+1;i++){

     //ONLY IMPLEMENTING TASKS 

  //        int pathLength = 0;
  //  for(int i = 1;_maxPath[pathEnd] != 0;i++){
  //    pathEnd = _maxPath[pathEnd];
  //    path[i] = pathEnd;
  //    pathLength = i; 

     critical._maxTime[i] = 0;
   }
   critical._maxPath = new int[_numberOfTasks+1];


   _maxTime = new float[_numberOfTasks+1];
   for(int i = 0;i< _numberOfTasks+1;i++)
     _maxTime[i] = 0;

   _maxPath = new int[_numberOfTasks+1];
   for(int i = 0;i< _numberOfTasks+1;i++)
     _maxPath[i] = 0;

/////////////////////////////////
//Need to Implement the Following - Remove if doesn't work: test
   for(int i = 0;i< _numberOfTasks+1;i++)
     critical._maxPath[i] = 0;

     //////////////////////////////////////////


   for(int i = 2;i < _numberOfTasks+1;i++){
     for(int j = 1;j < i;j++){
       for(int k = 0;k < _tasks[i]._numberOfDependencies;k++){
	   if(j == _tasks[i]._dependsOn[k])
	     _adj(i,_tasks[i]._dependsOn[k]) = _tasks[_tasks[i]._dependsOn[k]]._expectedTime;
       }

	 if(_adj(i,j) == 0)
	   _adj(i,j) = -1;
     }
   }
  //CAN SET TO NEGATIVE 1 ABOVE FOR MTRIX - TOLD~~~~~~~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   float NumeriHold = 0;
  
   for(int i = 2;i < _numberOfTasks+1;i++){
     for(int j = 1;j < i;j++){
       if(_adj(i,j) != -1){
	 NumeriHold = _adj(i,j);
	 NumeriHold += _maxTime[j];
       }

       if(NumeriHold > _maxTime[i]){
	 _maxTime[i] = NumeriHold;
	 _maxPath[i] = j;
       }
       NumeriHold = 0;
     }
   }
  
   float max = 0;
   int pathEnd = 0;
   for(int i = 0;i < _numberOfTasks;i++){
     if(_maxTime[i] > max){
       max = _maxTime[i];
       pathEnd = i;
     }
   }
   
   int path[_numberOfTasks];
   for(int i = 0;i < _numberOfTasks;i++)
     path[i] = 0;

   path[0] = pathEnd;
   
   int pathLength = 0;
   for(int i = 1;_maxPath[pathEnd] != 0;i++){
     pathEnd = _maxPath[pathEnd];
     path[i] = pathEnd;
     pathLength = i;
   }
   
   for(int i = pathLength,j = 0;i >= 0;j++,i--){
     critical._tasks[j] = _tasks[path[i]];
   }
   
   critical._numberOfTasks = pathLength+1;   
   critical._largestTaskNumber = _largestTaskNumber;
  
   critical._maxPath = _maxPath;   




  //Maximum Time.....


   critical._maxTime = _maxTime;
   return critical;
}

float Tasks::pathLength(const Tasks& t) const{

  //Pretty simple implementation
  //ONLY reqiores max var declaration in order to keep track of length. 

  //Note: I can actually take the identifier from the number of tasks, and subtract 1 on each called increment. 
  //this is the cleanest solution in the contrained timeline
  float pathFinitUGL = 0;
  //Take the maxtime.....
  //
  pathFinitUGL = t._maxTime[t._tasks[t._numberOfTasks-1]._identifier];
  //

  return pathFinitUGL;

}

float Tasks::slack(const Task& t) const{
  float max = 0;
  int pathEnd = 0;
  for(int i = 0;i < _numberOfTasks;i++){
    if(_maxTime[i] > max){
      max = _maxTime[i];
      pathEnd = i;
    }
  }
  
  int path[_numberOfTasks];
  for(int i = 0;i < _numberOfTasks;i++)
    path[i] = 0;
  
  path[0] = pathEnd;
  
  int pathLength = 0;
  for(int i = 1;_maxPath[pathEnd] != 0;i++){
    pathEnd = _maxPath[pathEnd];
    path[i] = pathEnd;
    pathLength = i;
  }
  
  for(int i = 0;i < pathLength+1;i++){
    if(path[i] == t._identifier)
      return 0;
  }
  return max - _maxTime[t._identifier];
}

Tasks::Tasks() {
  _numberOfTasks = 0;
  _largestTaskNumber = 0;
  
}

Tasks::~Tasks() {
  TASKS_INVARIANT("Tasks::~Tasks()");
  _numberOfTasks = -1;
}

std::ostream& operator<<(std::ostream& os, const Tasks& t) {
  if (t._numberOfTasks < 0) {
    cerr << "ostream& operator<<(): attempting to print deleted list of Tasks; exiting" << endl;
    exit(-1);
  }
  for (int i = 0; i <= t._largestTaskNumber; ++i)
    if (!t._tasks[i].isError())
      os << t._tasks[i] << endl;
#ifdef DEBUG
    else
      os << i << ": error task" << endl;
#endif
  return os;
}
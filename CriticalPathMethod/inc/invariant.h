//Partial WOrking Implementation COde
//Jason Antao


#ifndef INVARIANT_H
#define INVARIANT_H

#include <iostream>
#include <stdlib.h>

#define INVARIANT_FAILURE(LOC) do { \
    std::cerr << LOC << ": Invariant Failure; Aborting" << std::endl;	\
    abort(); \
  } while (0)

#define INVARIANT_TEST(TEST, LOC) do {  \
    if ((TEST)) {		   \
      INVARIANT_FAILURE(LOC);      \
    }                              \
  } while(0)

#endif

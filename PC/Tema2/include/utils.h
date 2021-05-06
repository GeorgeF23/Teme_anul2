#ifndef _UTILS_H
#define _UTILS_H 1

#include <stdio.h>
#include <stdlib.h>

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while(0)
	
#define MESSAGE_LENGTH 1600

#endif

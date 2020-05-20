#ifndef __ENABLE_DEBUG_H__
#define __ENABLE_DEBUG_H__

/**
 * Enable printing for debugging errors
 */
//#define DEBUG

/**
 * Enable Stupid Mode
 * Stupid Mode replaces string comparison with generating a random
 * int between 1 and 3 (inclusive). These corrispond with either
 * Accept, Disagree, Unrelated
 */
//#define STUPID_MODE
#ifdef STUPID_MODE
#include <cstdlib>
#include <time.h>
#endif

/**
 * Enable accuracy mode to check the read file against validataion.csv
 */
//#define ACCURACY

#endif


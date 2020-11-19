/*****************************************
 * Maria Martinez. 17-11-05
 * Util functions for DMAnalysis.
 *********************************************/
#ifndef __DM__UTIL__HH__
#define __DM__UTIL__HH__

#include <fstream>
#include <iostream>
#include <stdio.h>
using namespace std;


#define  DataDir "/home/maria/DMAnalysis/haloData"

// Vectorial sum. Add (mod2,ph2) to (*mod1, *ph1) .
// Output in (*mod1, *ph1)
// Angles in Radians
void DMAddVect (double *mod1, double *ph1, double mod2, double ph2);

// Given a number of counts, get max number of counts to
// a Confidence level
// Uses poisson o gauss statistic, depending on the 
// number of counts (n<10-> poisson, n>10 -> gauss
// Inputs: n  -> number of counts
//         CL -> confidence level (for poisson, only 90 and 95)
// Output: nmax -> max number of counts (n+delta*sqrt(n), delta
//                 computed for the CL)
void DMGetMaxCountsCL(double n, double CL, double * nmax);

// Auxiliar: Parse shell variables
std::string DMParseShellVars(char * filename);

#endif

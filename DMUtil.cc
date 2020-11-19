/*****************************************
 * Maria Martinez. 17-11-05
 * Util functions for DMAnalysis.
 *********************************************/

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "DMUtil.hh"
#include "DMPhysConstants.hh"

using namespace std;


// Vectorial sum. Add (mod2,ph2) to (*mod1, *ph1) .
// Output in (*mod1, *ph1)
// Angles in Radians
void DMAddVect (double *mod1, double *ph1, double mod2, double ph2)
{
  if ((*mod1) == 0) 
  {
    if (mod2 != 0) 
    {
      (*mod1)=mod2; 
      (*ph1)=ph2; 
    }
    return;
  }

  if ((mod2) == 0) return;

  if ( (*ph1) == ph2) {(*mod1) += mod2; return;}

  double cos1 = cos(*ph1);
  double sin1 = sin(*ph1);
  double cos2 = cos(ph2);
  double sin2 = sin(ph2);
  double vs1 = (*mod1)*cos1+mod2*cos2;
  double vs2 = (*mod1)*sin1+mod2*sin2;

  (*mod1) = sqrt(vs1*vs1 + vs2*vs2);

  *ph1 = asin (vs2 / (*mod1) );

  if (vs1<0) (*ph1) = PI - (*ph1);

  if ((*ph1)<0 ) (*ph1) += TWOPI;

  //while (abs(*ph1) > TWOPI)
 // {
  //  if ((*ph1)>0) (*ph1) -= TWOPI;
   // else (*ph1) += TWOPI;
  //}

}

// Given a number of counts, get max number of counts to
// a Confidence level
// Uses poisson o gauss statistic, depending on the 
// number of counts (n<10-> poisson, n>10 -> gauss
// Inputs: n  -> number of counts
//         CL -> confidence level (for poisson, only 90 and 95)
// Output: nmax -> max number of counts (n+delta*sqrt(n), delta
//                 computed for the CL)
void DMGetMaxCountsCL(double n, double CL, double * nmax)
{
  int i=0; double x0, x1, y0, y1;
  double CLGauss [][2] = { { 78.8 , 0.8} , { 84.1 , 1  } , { 88.5 , 1.2} , 
                           { 90.  , 1.28} , { 91.9 , 1.4} , { 94.5 , 1.6} , 
                           { 95.  , 1.64} , { 96.4 , 1.8} , { 97.5 , 1.96} , 
                           { 97.7 , 2  } , { 98.6 , 2.2} , { 99.2 , 2.4} ,
                           { 99.5 , 2.58} , { 99.7 , 2.8} , { 99.8 , 3} , 
                           { 99.9 , 3.2} , { 99.95 , 3.29} , { 99.99 , 3.8} , 
                           { 99.995 , 3.89} };
  int CLGaussDim = 19;
  double CLPoisson_90 [] = {2.30, 3.89, 5.32, 6.68, 7.99, 9.27, 
                            10.53, 11.77, 12.99, 14.21, 15.41};
  double CLPoisson_95 [] = {3.00, 4.74, 6.30, 7.75, 9.15, 10.51, 
                            11.84, 13.15, 14.43, 15.71, 16.96};
  int CLPoissonDim = 11;
  double delta;
  if (n>10)
  {
    // Gaussian aproximation. look in the array. 
    // If it not exists, interpolate
    
    x0 = 0; y0 = 0;
    for (i=0; i<CLGaussDim; i++)
    {
      if (CLGauss[i][0]==CL) 
      {
        delta = CLGauss[i][1];
        (*nmax) = n + delta * sqrt (n);
        return;
      }
      if (CLGauss[i][0]>CL) break;
    } 
    if (i>0) 
    {
      x0=CLGauss[i-1][0]; y0=CLGauss[i-1][0];
      x1=CLGauss[i][0]; y1=CLGauss[i][0];
      delta = (CL-x0) / (x1-x0) * (y1-y0) + y0;
      (*nmax) = n + delta * sqrt (n);
      return;
    }
  }
  
  // Poission distribution
  i = (int)(rint(n)); // round to nearest integer
  if (CL==90) (*nmax) = CLPoisson_90[i];
  else if (CL==95) (*nmax) = CLPoisson_95[i];
  else if (CL==0) (*nmax) = n;
  else  cout << "CL not implemented " << endl;
  return ;
}


std::string DMParseShellVars(char * filename)
{
  string str (filename);

  string inivar ("$");
  string endvar ("/");
  size_t found;
  size_t end=0;

  std::stringstream output (stringstream::out);

  // different member versions of find in the same order as above:
  do 
  {
    found=str.find(inivar, end);
    if (found!=std::string::npos)
    {
      // VAR FOUND
      // output previous
      output << str.substr(end, found-end).c_str();
      end=str.find(endvar, found);
      if (end==std::string::npos) end= str.length();
      
      // output var content
      char * auxVar = getenv(str.substr(found+1, end-found-1).c_str());
      if(auxVar) output << auxVar;
      //else std::cout << "variable vacia" << std::endl;
      
    }
  } while (found!=std::string::npos);

  output << str.substr(end, found-end).c_str();

  return output.str();
}

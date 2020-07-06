#include "DPex.h" // header file (class prototype). 
#include <rng/RNG.h> // pseudo-random number generators (unif, expon, normal).
#include <util/nainf.h> // "na" and "inf" functions.

#include <JRmath.h> // R math library with basic functions.
#include <cmath> // C library for standard math operations.

using std::vector; // "vector" format from "std" required in the code

namespace jags {
namespace pexm { // module namespace

// The constructor function also calls
// the constructor of the base class taking as aguments:
// - name of the distribution node (as in the BUGS code).
// - number of arguments of that node.
DPex::DPex() : VectorDist("dpex", 2)
{}

// Check if the given parameter values are in the allowed parameter space.
bool DPex::checkParameterValue (vector<double const *> const &parameters,
                                vector<unsigned int> const &lengths) const
{
    double const * lam = parameters[0];
    double const * a = parameters[1];
    int size = lengths[0]; // number of lambdas

    int testlam = (lam[0] < 0)? 1 : 0;
    int testa = (a[0] != 0)? 1 : 0;
    for(int i=1; i < size; ++i) {
       testlam = testlam + ((lam[i] < 0)? 1 : 0);
       testa = testa + ((a[i] < 0)? 1 : 0) + ((a[i-1] >= a[i])? 1 : 0);
    }

    return (testlam==0 && testa==0);
}

// Calculate the log-density. Arguments:
// "x" = value at which to evaluate the pdf.
// "length" = size of the array "x" (if 1, "x" is a scalar).
// "parameters" = vector of parameters values of the distribution.
// "lengths" = vector of parameter lengths in "parameters"
//             (e.g. [2,3] means size param1 = 2, size param2 = 3).
double DPex::logDensity(double const *x, unsigned int length, PDFType type,
                        vector<double const *> const &parameters,
                        vector<unsigned int> const &lengths,
                        double const *lower, double const *upper) const
{
    double const * lam = parameters[0]; 
    double const * a = parameters[1]; // grid: (a0=0,a1], (a1,a2],...,(ak,Inf)
    int size = lengths[0]; // number of lambdas

    int n = size-1;
    for(int i=0; i < (size-1); ++i) {
        if(*x <= a[i+1]){ n = i; break; }
    }

    double Ht = 0;
    if(n > 0) {
        for(int i=0; i < n; ++i) {
          Ht = Ht + lam[i] * (a[i+1] - a[i]);
        }
    }
    if(lam[n]==0){ return log(0.0001)-(Ht +lam[n] * (*x -a[n])); }
    else{ return log(lam[n])-(Ht +lam[n] * (*x -a[n])); } // if( lam[n] > 0 )
}

// Draw a random sample from the distribution. Arguments:
// "x" = array to which the sample values are written.
// "length" = size of the array x (if 1, x is a scalar).
// "parameters" = vector of parameter values of the distribution.
// "lengths" = vector of lengths of the arrays in "parameters".
void DPex::randomSample(double *x, unsigned int length,
                        std::vector<double const *> const &parameters,
                        std::vector<unsigned int> const &lengths,
                        double const *lower, double const *upper,
                        RNG *rng) const
{
  double const * lam = parameters[0];
  double const * a = parameters[1]; // grid
  int size = lengths[0]; // number of lambdas
  int n; double Ht; double lo = 0; double up = 1;

  if(lower){
      n = size-1;
      for(int i=0; i < (size-1); ++i) {
         if(*lower <= a[i+1]){ n = i; break; }
      }
      Ht = 0;
      if(n > 0) {
        for(int i=0; i < n; ++i) {
          Ht = Ht + lam[i] * (a[i+1] - a[i]);
        }
      }
      Ht = Ht + lam[n] * (*lower - a[n]);
      lo = 1-exp(-Ht);
  }
  if(upper){
      n = size-1;
      for(int i=0; i < (size-1); ++i) {
         if(*upper <= a[i+1]){ n = i; break; }
      }
      Ht = 0;
      if(n > 0) {
        for(int i=0; i < n; ++i) {
          Ht = Ht + lam[i] * (a[i+1] - a[i]);
        }
      }
      Ht = Ht + lam[n] * (*upper - a[n]);
      up = 1-exp(-Ht);
  }

  if((up-lo)<0.0001){lo = 0; up = 1;}

  // F(t)= 1-S(t)= 1-exp{-H(t)}, H(t)= -log(1-F(t))
  double w = -log(1-runif(lo, up, rng));
  double Htprev = 0;
  n = size-1;
  for(int i=0; i < (size-1); ++i) {
     Ht = Htprev + lam[i]*(a[i+1]-a[i]);
     if(w <= Ht){ n = i; break; }
     Htprev = Ht;
  }
  if(lam[n]==0){ *x = a[n] + (w-Htprev)/0.0001; }
  else{ *x = a[n] + (w-Htprev)/lam[n]; } // if( lam[n] > 0)
}

// Return a typical value of the distribution. 
// The meaning depends on the distribution (can be: mean, median or mode).
// "x" = array to which the typical values are written.
// "length" = size of the array x (if 1, x is a scalar).
// "parameters" = vector of parameter values of the distribution.
// "lengths" = vector of lengths of the arrays in "parameters".
void DPex::typicalValue(double *x, unsigned int length,
                        std::vector<double const *> const &parameters,
                        std::vector<unsigned int> const &lengths,
                        double const *lower, double const *upper) const
{
  double const * lam = parameters[0];
  double const * a = parameters[1];
  double w = -log(0.5); // H(t) related to the median
  int size = lengths[0]; // number of lambdas

  double Ht;
  double Htprev = 0;
  int n = size-1;
  for(int i=0; i < (size-1); ++i) {
     Ht = Htprev + lam[i]*(a[i+1]-a[i]);
     if(w <= Ht){ n = i; break; }
     Htprev = Ht;
  }
  if(lam[n]==0){ *x = a[n] + (w-Htprev)/0.0001; }
  else{ *x = a[n] + (w-Htprev)/lam[n]; } // if( lam[n] > 0 )
}

// Indicator: distribution can be bounded.
bool DPex::canBound() const
{
  return true;
}

// Check if the distribution is discrete valued.
bool DPex::isDiscreteValued(vector<bool> const &mask) const
{
  return false;
}

// Check if upper/lower limits of the support of the distribution are fixed.
bool DPex::isSupportFixed(vector<bool> const &fixmask) const
{
  return true;
}

// Check if the values in "lengths" are consistent; size(lambda)=size(grid)?
bool DPex::checkParameterLength(vector<unsigned int> const &lengths) const
{
  return lengths[0] == lengths[1];
}

// Set the size of "*x".
// In some distributions, this can be computed based on the values in "lengths",
// for example, the size of mu in a Multiv.Normal.
unsigned int DPex::length(vector<unsigned int> const &lengths) const
{
    return 1; // size of the array "*x" (length = 1 means "scalar")
}

// Returns the support of the unbounded distribution
void DPex::support(double *lower, double *upper, unsigned int length,
                   vector<double const *> const &par,
                   vector<unsigned int> const &lengths) const
{
  for (unsigned int i = 0; i < length; ++i) {
    lower[i] = 0;
    upper[i] = JAGS_POSINF;
  }
}

}}

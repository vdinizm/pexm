#include "DPexFun.h"
#include <cmath>

using std::vector;

namespace jags {
namespace pexm {

    DPexFun::DPexFun() : ScalarVectorFunction("dpex", 3)
    {}

    double DPexFun::scalarEval(std::vector<double const *> const &args,
                               std::vector<unsigned int> const &dims) const
    {
      double const * x = args[0]; // x[0] > 0 = a[0].
      double const * lam = args[1];
      double const * a = args[2];

      int size = dims[1];

      int n = size-1;
      for(int i=0; i < (size-1); ++i){
         if(x[0] <= a[i+1]){ 
           n = i; break; 
           }
      }

      double Ht = 0;
      if(n > 0){
        for(int i=0; i < n; ++i) {
          Ht = Ht + lam[i] * (a[i+1] - a[i]);
        }
      }
      // Remark: remove "exp" below, if the "log-density" is the target output.
      if(lam[n]==0){ return exp( log(0.0001)-(Ht+lam[n] * (x[0]-a[n])) ); } 
      else{ return exp( log(lam[n])-(Ht+lam[n] * (x[0]-a[n])) ); }  // if( lam[n] > 0 ) 
    }

    bool DPexFun::isScale(vector<bool> const &mask, vector<bool> const &fix) const
    {
      return true;
    }

}}

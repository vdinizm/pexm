#include "QPexFun.h"
#include <cmath>

using std::vector;

namespace jags {
namespace pexm {

    QPexFun::QPexFun () : ScalarVectorFunction ("qpex", 3)
    {}

    double QPexFun::scalarEval (std::vector<double const *> const &args,
                               std::vector<unsigned int> const &dims) const
    {
      double const * x = args[0];  // x in (0,1).
      double const * lam = args[1];
      double const * a = args[2];

      int size = dims[1];

      // F(t) = 1-exp{-H(t)}, x = 1-exp{-H(t)}.
      // Therefore, H(t) = -log(1-x)
      double w = -log(1-x[0]);
      double Ht;
      double Htprev = 0;
      int n = size-1;
      for(int i=0; i < (size-1); ++i) {
         Ht = Htprev + lam[i]*(a[i+1]-a[i]);
         if(w <= Ht){ n = i; break; }
         Htprev = Ht;
      }
      if(lam[n]==0){ return a[n]+(w-Htprev)/0.0001; }
      else{ return a[n]+(w-Htprev)/lam[n]; } // if( lam[n] > 0 )
    }

    bool QPexFun::isScale(vector<bool> const &mask, vector<bool> const &fix) const
    {
      return true;
    }

}}

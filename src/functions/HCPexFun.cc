#include "HCPexFun.h"
#include <cmath>

using std::vector;

namespace jags {
namespace pexm {

    HCPexFun::HCPexFun () : ScalarVectorFunction ("hcpex", 3)
    {}

    double HCPexFun::scalarEval (std::vector<double const *> const &args,
                                 std::vector<unsigned int> const &dims) const
    {
      double const * x = args[0]; // x[0] > 0 = a[0].
      double const * lam = args[1];
      double const * a = args[2];

      int size = dims[1];

      int n = size-1;
      for(int i=0; i < (size-1); ++i) {
         if(x[0] <= a[i+1]){ n = i; break; }
      }

      // Compute the cumulative hazard H(.) at x.
      // Sum of previous rectangles is 0 for "n = 0" [x in (a0=0,a1]].
      double Ht = 0;
      if(n > 0) {
        for(int i=0; i < n; ++i) {
          Ht = Ht + lam[i] * (a[i+1] - a[i]);
        }
      }
      Ht = Ht + lam[n] * (x[0] - a[n]);
      return Ht;
    }

    bool HCPexFun::isScale(vector<bool> const &mask, vector<bool> const &fix) const
    {
      return true;
    }

}}

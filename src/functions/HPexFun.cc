#include "HPexFun.h"
#include <cmath>

using std::vector;

namespace jags {
namespace pexm {

    HPexFun::HPexFun () : ScalarVectorFunction ("hpex", 3)
    {}

    double HPexFun::scalarEval (std::vector<double const *> const &args,
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

      // Compute the hazard h(.) at x.
      return lam[n];
    }

    bool HPexFun::isScale(vector<bool> const &mask, vector<bool> const &fix) const
    {
      return true;
    }

}}

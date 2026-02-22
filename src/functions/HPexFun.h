#ifndef FUNC_HPEXFUN_H_
#define FUNC_HPEXFUN_H_
#include <function/ScalarVectorFunction.h>

namespace jags {
namespace pexm {

    /** T ~ PE Distribution:
        Compute the hazard for a given positive real number. */
    class HPexFun : public ScalarVectorFunction
    {
        public:
          HPexFun ();
          double scalarEval(std::vector<double const *> const &args,
                            std::vector<unsigned long> const &dims) const override;
          bool isScale(std::vector<bool> const &mask,
                       std::vector<bool> const &fix) const override;
    };

}}

#endif /* FUNC_HPEXFUN_H_ */

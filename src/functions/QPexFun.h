#ifndef FUNC_QPEXFUN_H_
#define FUNC_QPEXFUN_H_
#include <function/ScalarVectorFunction.h>

namespace jags {
namespace pexm {

    /** T ~ PE Distribution:
        Compute the quantile for a given probability. */
    class QPexFun : public ScalarVectorFunction
    {
        public:
          QPexFun ();
          double scalarEval(std::vector<double const *> const &args,
                            std::vector<unsigned long> const &dims) const override;
          bool isScale(std::vector<bool> const &mask,
                       std::vector<bool> const &fix) const override;
    };

}}

#endif /* FUNC_QPEXFUN_H_ */

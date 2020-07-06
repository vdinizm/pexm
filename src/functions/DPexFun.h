#ifndef FUNC_DPEXFUN_H_
#define FUNC_DPEXFUN_H_
#include <function/ScalarVectorFunction.h>

namespace jags {
namespace pexm {

    /** T ~ PE Distribution:
        Compute the pdf for a given t > 0. */
    class DPexFun : public ScalarVectorFunction
    {
        public:
          DPexFun();
          double scalarEval(std::vector<double const *> const &args,
                            std::vector<unsigned int> const &dims) const;
          bool isScale(std::vector<bool> const &mask,
                       std::vector<bool> const &fix) const;
    };

}}

#endif /* FUNC_DPEXFUN_H_ */

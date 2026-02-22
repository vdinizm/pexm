#ifndef FUNC_HCPEXFUN_H_
#define FUNC_HCPEXFUN_H_
#include <function/ScalarVectorFunction.h>

namespace jags {
namespace pexm {

    /** T ~ PE Distribution:
        Compute the cumulative hazard for a given positive real number. */
    class HCPexFun : public ScalarVectorFunction
    {
        public:
          HCPexFun ();
          double scalarEval(std::vector<double const *> const &args,
                            std::vector<unsigned long> const &dims) const override;
          bool isScale(std::vector<bool> const &mask,
                       std::vector<bool> const &fix) const override;
    };

}}

#endif /* FUNC_HCPEXFUN_H_ */

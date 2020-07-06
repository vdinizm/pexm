#ifndef FUNC_PPEXFUN_H_
#define FUNC_PPEXFUN_H_
#include <function/ScalarVectorFunction.h>

namespace jags {
namespace pexm {

    /** T ~ PE Distribution:
        Compute the cdf for a given positive real number. */
    class PPexFun : public ScalarVectorFunction
    {
        public:
          PPexFun ();
          double scalarEval(std::vector<double const *> const &args,
                            std::vector<unsigned int> const &dims) const;
          bool isScale(std::vector<bool> const &mask,
                       std::vector<bool> const &fix) const;
    };

}}

#endif /* FUNC_PPEXFUN_H_ */

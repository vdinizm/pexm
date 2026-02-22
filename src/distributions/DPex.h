#ifndef DPEX_H_
#define DPEX_H_

#include <distribution/VectorDist.h> // JAGS vector distribution base

namespace jags {
namespace pexm {

class DPex : public VectorDist // vector distribution class
{
  public:
    DPex(); // constructor
    double logDensity(double const *x, PDFType type,
                      std::vector<double const *> const &parameters,
                      std::vector<unsigned long> const &lengths) const override;
    void randomSample(double *x, 
                      std::vector<double const *> const &parameters,
                      std::vector<unsigned long> const &lengths,
                      RNG *rng) const override;
    /** Check if the given parameter values are in the allowed parameter space */
    bool checkParameterValue(std::vector<double const*> const &parameters,
                             std::vector<unsigned long> const &lengths) const override;
    /** Check if the distribution is discrete valued */
    bool isDiscreteValued(std::vector<bool> const &mask) const override;
    /** Check if upper/lower limits of the support of the distribution are fixed */
    bool isSupportFixed(std::vector<bool> const &fixmask) const override;
    /** Check if the values in "lengths" are consistent; size(lambda)=size(grid)? */
    bool checkParameterLength(std::vector<unsigned long> const &lengths) const override;
    /** Identify the size of the array "*x" (length = 1 means "scalar") */
    unsigned long length(std::vector<unsigned long> const &lengths) const override;
    /** Returns the support of the unbounded distribution */
    void support(double *lower, double *upper, 
                 std::vector<double const *> const &parameters,
                 std::vector<unsigned long> const &lengths) const override;
};

}}

#endif /* DPEX_H_ */

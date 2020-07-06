#ifndef DPEX_H_
#define DPEX_H_

#include <distribution/VectorDist.h> // JAGS vector distribution base

namespace jags {
namespace pexm {

class DPex : public VectorDist // vector distribution class
{
  public:
    DPex(); // constructor
    double logDensity(double const *x, unsigned int length, PDFType type,
                      std::vector<double const *> const &parameters,
                      std::vector<unsigned int> const &lengths,
                      double const *lower, double const *upper) const;
    void randomSample(double *x, unsigned int length,
                      std::vector<double const *> const &parameters,
                      std::vector<unsigned int> const &lengths,
                      double const *lower, double const *upper,
                      RNG *rng) const;
    void typicalValue(double *x, unsigned int length,
                      std::vector<double const *> const &parameters,
                      std::vector<unsigned int> const &lengths,
                      double const *lower, double const *upper) const;
    /** Check if the given parameter values are in the allowed parameter space */
    bool checkParameterValue(std::vector<double const*> const &parameters,
                             std::vector<unsigned int> const &lengths) const;
    /** Indicate whether the distribution can be bounded */
    bool canBound() const;
    /** Check if the distribution is discrete valued */
    bool isDiscreteValued(std::vector<bool> const &mask) const;
    /** Check if upper/lower limits of the support of the distribution are fixed */
    bool isSupportFixed(std::vector<bool> const &fixmask) const;
    /** Check if the values in "lengths" are consistent; size(lambda)=size(grid)? */
    bool checkParameterLength(std::vector<unsigned int> const &lengths) const;
    /** Identify the size of the array "*x" (length = 1 means "scalar") */
    unsigned int length(std::vector<unsigned int> const &lengths) const;
    /** Returns the support of the unbounded distribution */
    void support(double *lower, double *upper, unsigned int length,
                 std::vector<double const *> const &parameters,
                 std::vector<unsigned int> const &lengths) const;
};

}}

#endif /* DPEX_H_ */

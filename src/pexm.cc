#include <module/Module.h> // JAGS module base class

#include "distributions/DPex.h" // PE distribution class
#include "functions/DPexFun.h" // PE function class
#include "functions/PPexFun.h" 
#include "functions/QPexFun.h" 
#include "functions/HCPexFun.h" 
#include "functions/HPexFun.h" 

namespace jags{
namespace pexm { // module namespace

class PEXModule : public Module { // module class
  public:
    PEXModule(); // constructor
    ~PEXModule(); // destructor
};

// Constructor function
PEXModule::PEXModule() : Module("pexm") {
  insert(new DPex); // inherited function to load objects in JAGS
  insert(new DPexFun);
  insert(new PPexFun);
  insert(new QPexFun);
  insert(new HCPexFun);
  insert(new HPexFun);
}

// Destructor function
PEXModule::~PEXModule() {
  std::vector<Distribution*> const &dvec = distributions();
  for (unsigned int i = 0; i < dvec.size(); ++i) {
    delete dvec[i]; // delete all instantiated distribution objects
  } 
  std::vector<Function*> const &fvec = functions();
  for (unsigned int i = 0; i < fvec.size(); ++i) {
    delete fvec[i]; // delete all instantiated function objects
  } 
}

}} // end namespaces definitions

jags::pexm::PEXModule _pexm_module;

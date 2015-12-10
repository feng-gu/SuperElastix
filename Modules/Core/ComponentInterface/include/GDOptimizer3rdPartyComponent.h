#ifndef GDOptimizer3rdPartyComponent_h
#define GDOptimizer3rdPartyComponent_h

#include "ComponentBase.h"
#include "Interfaces.hxx"
#include "Example3rdPartyCode.h"
#include "Metric3rdPartyWrapper.h"
#include <string.h>

namespace elx
{

  class GDOptimizer3rdPartyComponent : 
    public Implements<
      Accepting< MetricValueInterface, MetricDerivativeInterface >,
      Providing< OptimizerUpdateInterface>
    >
  {
  public:
    GDOptimizer3rdPartyComponent();
    virtual ~GDOptimizer3rdPartyComponent();
    Example3rdParty::GDOptimizer3rdParty* theImplementation;
    Metric3rdPartyWrapper* MetricObject;
    //virtual int ConnectFrom(const char *, ComponentBase*);
    int Set(MetricValueInterface*);
    int Set(MetricDerivativeInterface*);
    int Update();
  };
} //end namespace elx
#endif // #define GDOptimizer3rdPartyComponent_h
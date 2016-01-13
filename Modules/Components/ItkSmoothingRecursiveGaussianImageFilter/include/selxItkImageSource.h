#ifndef selxItkImageSource_h
#define selxItkImageSource_h

#include "ComponentBase.h"
#include "Interfaces.h"
#include <string.h>
#include "elxMacro.h"
namespace selx
{
  class ItkImageSourceComponent : 
    public Implements<
    Accepting<>,
    Providing< SourceInterface, itkImageSourceInterface >
    >
  {
  public:
    elxNewMacro(ItkImageSourceComponent, ComponentBase);

    ItkImageSourceComponent();
    virtual ~ItkImageSourceComponent();

    typedef itk::ImageSource<itk::Image<double, 3>> ItkImageSourceType;
    

    ItkImageSourceType::Pointer GetItkImageSource();
    bool ConnectToOverlordSource(itk::Object::Pointer);

    //int Update();
    //virtual bool MeetsCriteria(const CriteriaType &criteria);
    virtual bool MeetsCriterion(const CriterionType &criterion);    
    //static const char * GetName() { return "GDOptimizer3rdPartyComponent"; } ;
    static const char * GetDescription() { return "ItkImageSource Component"; };
  private:
    ItkImageSourceType::Pointer m_Source;
  };
} //end namespace selx
#endif // #define GDOptimizer3rdPartyComponent_h
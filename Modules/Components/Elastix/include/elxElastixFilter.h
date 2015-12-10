#ifndef ElastixComponent_h
#define ElastixComponent_h

// ITK
#include "itkImageSource.h"

// Elastix
#include "elxElastixMain.h"

// SuperElastix
#include "elxMacro.h"
#include "elxParameterObject.h"

namespace selx {

template< typename TFixedImage,
          typename TMovingImage >
class ElastixFilter : public itk::ImageSource< TFixedImage >
{
public:

  elxNewMacro( ElastixFilter, itk::ImageSource );

  typedef elastix::ElastixMain                          ElastixMainType;
  typedef ElastixMainType::Pointer                      ElastixMainPointer;
  typedef std::vector< ElastixMainPointer >             ElastixMainVectorType;
  typedef ElastixMainType::ObjectPointer                ElastixMainObjectPointer;
  typedef ElastixMainType::FlatDirectionCosinesType     FlatDirectionCosinesType;
  typedef ElastixMainType::ArgumentMapType              ArgumentMapType;
  typedef ArgumentMapType::value_type                   ArgumentMapEntryType;

  typedef itk::ProcessObject::DataObjectIdentifierType  DataObjectIdentifierType;
  typedef ElastixMainType::DataObjectContainerType      DataObjectContainerType;
  typedef ElastixMainType::DataObjectContainerPointer   DataObjectContainerPointer;

  typedef ParameterObject::ParameterMapListType         ParameterMapListType;
  typedef ParameterObject::ParameterMapType             ParameterMapType;
  typedef ParameterObject::ParameterValuesType          ParameterValuesType;
  typedef typename ParameterObject::Pointer             ParameterObjectPointer;
  typedef typename ParameterObject::ConstPointer        ParameterObjectConstPointer;

  typedef typename TFixedImage::Pointer                 FixedImagePointer;
  typedef typename TMovingImage::Pointer                MovingImagePointer;

  void SetFixedImage( FixedImagePointer fixedImage );
  void SetFixedImage( DataObjectContainerPointer fixedImage );
  void SetMovingImage( MovingImagePointer movingImage );
  void SetMovingImage( DataObjectContainerPointer movingImage );
  void SetFixedMask( FixedImagePointer fixedMask );
  void SetMovingMask( MovingImagePointer movingMask );

  void SetParameterObject( ParameterObjectPointer parameterObject );
  ParameterObjectConstPointer GetTransformParameters( void ) const;

  itkSetMacro( FixedPointSetFileName, std::string );
  itkGetConstMacro( FixedPointSetFileName, std::string );
  void DeleteFixedPointSet( void ) { this->SetFixedPointSetFileName( std::string() ); };

  itkSetMacro( MovingPointSetFileName, std::string );
  itkGetConstMacro( MovingPointSetFileName, std::string );
  void DeleteMovingPointSet( void ) { this->SetMovingPointSetFileName( std::string() ); };

  itkSetMacro( LogToConsole, bool );
  itkGetConstMacro( LogToConsole, bool );
  itkBooleanMacro( LogToConsole );

  itkSetMacro( LogToFile, std::string );
  itkGetConstMacro( LogToFile, std::string );
  void LogToFileOff( void ) { this->SetLogToFile( std::string() ); };

protected:

  void GenerateData( void ) ITK_OVERRIDE;

private:

  ElastixFilter();

  // TODO: When set to true, ReleaseDataFlag should also touch these input containers
  DataObjectContainerPointer m_FixedImageContainer;
  DataObjectContainerPointer m_MovingImageContainer;
  DataObjectContainerPointer m_FixedMaskContainer;
  DataObjectContainerPointer m_MovingMaskContainer;

  std::string m_FixedPointSetFileName;
  std::string m_MovingPointSetFileName;

  bool m_LogToConsole;
  std::string m_LogToFile;

};

} // namespace selx

#ifndef ITK_MANUAL_INSTANTIATION
#include "elxElastixFilter.hxx"
#endif

#endif // ElastixFilter_h
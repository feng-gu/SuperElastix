/*=========================================================================
 *
 *  Copyright Leiden University Medical Center, Erasmus University Medical 
 *  Center and contributors
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "selxElastixComponent.h"

namespace selx
{
  template<int Dimensionality, class TPixel>
  ElastixComponent< Dimensionality, TPixel>::ElastixComponent()
  {
    m_theItkFilter = TheItkFilterType::New();

    // TODO: Due to some issues with Criteria being propagated as elastix settings, I need to empty the selxparameterObject.
    selxParameterObjectPointer selxparameterObject = selxParameterObjectType::New();
    selxparameterObject->SetParameterMap("rigid");
    this->m_theItkFilter->SetParameterObject(selxparameterObject);

    m_theItkFilter->LogToConsoleOn();
    //m_ParameterObject->SetParameterMap("rigid");

    //TODO: instantiating the filter in the constructor might be heavy for the use in component selector factory, since all components of the database are created during the selection process.
    // we could choose to keep the component light weighted (for checking criteria such as names and connections) until the settings are passed to the filter, but this requires an additional initialization step.
  }

  template<int Dimensionality, class TPixel>
  ElastixComponent< Dimensionality, TPixel>::~ElastixComponent()
  {
  }

  template<int Dimensionality, class TPixel>
  int ElastixComponent< Dimensionality, TPixel>::Set(itkImageSourceFixedInterface<Dimensionality, TPixel>* component)
  {
    auto other = component->GetItkImageSourceFixed();
    // connect the itk pipeline
    this->m_theItkFilter->SetFixedImage(other->GetOutput());
    return 1;
  }

  template<int Dimensionality, class TPixel>
  int ElastixComponent< Dimensionality, TPixel>::Set(itkImageSourceMovingInterface<Dimensionality, TPixel>* component)
  {
    auto other = component->GetItkImageSourceMoving();
    // connect the itk pipeline
    this->m_theItkFilter->SetMovingImage(other->GetOutput());
    return 1;
  }


  //Since elastixFilter is not a true itkfilter we cannot use itkImageSourceInterface (yet)
  /*template<int Dimensionality, class TPixel>
  typename ElastixComponent< Dimensionality, TPixel>::ItkImageSourcePointer ElastixComponent< Dimensionality, TPixel>::GetItkImageSource()
  {

    return (ItkImageSourcePointer) this->m_theItkFilter;
  }
  */

  template<int Dimensionality, class TPixel>
  typename ElastixComponent< Dimensionality, TPixel>::ItkImagePointer ElastixComponent< Dimensionality, TPixel>::GetItkImage()
  {
    // We cannot just call return this->m_theItkFilter->GetOutput(), since the network is generally not ready for execution during the handshake
  return this->m_OutputImage;
  }
  


  template<int Dimensionality, class TPixel>
  void ElastixComponent< Dimensionality, TPixel>::RunRegistration(void)
  {
    //this->m_theItkFilter->Update();
    this->m_OutputImage = this->m_theItkFilter->GetOutput();

    typename TransformixFilterType::Pointer transformixFilter;
    transformixFilter = TransformixFilterType::New();
    // In the current transformix filter an input image is required even if we want a deformation field only.
    transformixFilter->SetInputImage(this->m_theItkFilter->GetOutput());
    
    transformixFilter->SetTransformParameterObject(this->m_theItkFilter->GetTransformParameterObject());
    //transformixFilter->SetOutputDirectory(dataManager->GetOutputDirectory());
    transformixFilter->ComputeDeformationFieldOn();
    transformixFilter->LogToConsoleOn();
    transformixFilter->LogToFileOn();
    transformixFilter->Update();
    //ImageFileWriterType::Pointer writer = ImageFileWriterType::New();
    //writer->SetFileName(dataManager->GetOutputFile("Euler2DTransformixResultImage.nii"));
    //writer->SetInput(transformixFilter->GetOutput());
    //writer->Update();

  }


  template<int Dimensionality, class TPixel>
  bool
    ElastixComponent< Dimensionality, TPixel>
    ::MeetsCriterion(const CriterionType &criterion)
  {
    bool hasUndefinedCriteria(false);
    bool meetsCriteria(false);
    if (criterion.first == "ComponentProperty")
    {
      meetsCriteria = true;
      for (auto const & criterionValue : criterion.second) // auto&& preferred?
      {
        if (criterionValue != "SomeProperty")  // e.g. "GradientDescent", "SupportsSparseSamples
        {
          meetsCriteria = false;
        }
      }
    }
    else if (criterion.first == "Dimensionality") //Supports this?
    {
      meetsCriteria = true;
      for (auto const & criterionValue : criterion.second) // auto&& preferred?
      {
        if (std::stoi(criterionValue) != Dimensionality)
        {
          meetsCriteria = false;
        }
      }

    }
    else if (criterion.first == "PixelType") //Supports this?
    {
      meetsCriteria = true;
      for (auto const & criterionValue : criterion.second) // auto&& preferred?
      {
        if (criterionValue != Self::GetPixelTypeNameString())
        {
          meetsCriteria = false;
        }
      }

    }
    else if (criterion.first == "RegistrationPreset") //Supports this?
    {
      // Temporary solution: RegistrationSettings: rigid, nonrigid, etc overwrite the current selxparameterObject.
      // Warning: the order of Criteria matters, since selxparameterObject may be overwritten
      // Warning: this probably fails because the Criteria map entries are processed in arbitrary order.

      selxParameterObjectPointer selxparameterObject = selxParameterObjectType::New();

      meetsCriteria = true;
      for (auto const & transformtype : criterion.second) // auto&& preferred?
      {
        //this->m_ParameterObject->AddParameterMap(transformtype, const unsigned int numberOfResolutions = 3u, const double finalGridSpacingInPhysicalUnits = 10.0);
        selxparameterObject->SetParameterMap(transformtype);
        
        try
        {
          this->m_theItkFilter->SetParameterObject(selxparameterObject);
        }
        catch (itk::ExceptionObject & err)
        {
          std::cout << err;
          //TODO log the error message?
          meetsCriteria = false;
        }
      }

    }
    else
    {
      // temporary solution: pass all SuperElastixComponent parameters as is to elastix. This should be defined in deeper hierarchy of the criteria, but for now we have a flat mapping only.
      selxParameterObjectPointer selxparameterObject = this->m_theItkFilter->GetParameterObject();
      selxparameterObject->GetParameterMap(0)[criterion.first] = criterion.second;
      this->m_theItkFilter->SetParameterObject(selxparameterObject);
      meetsCriteria = true;
    }
    return meetsCriteria;
  }

} //end namespace selx
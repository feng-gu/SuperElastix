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

#include "selxDisplacementFieldItkImageFilterSink.h"

namespace selx
{
  template<int Dimensionality, class TPixel>
  DisplacementFieldItkImageFilterSinkComponent< Dimensionality, TPixel>::DisplacementFieldItkImageFilterSinkComponent()
  {
    this->m_Sink = nullptr;
    this->m_SinkWriter = nullptr;
  }

  template<int Dimensionality, class TPixel>
  DisplacementFieldItkImageFilterSinkComponent< Dimensionality, TPixel>::~DisplacementFieldItkImageFilterSinkComponent()
  {
  }

  template<int Dimensionality, class TPixel>
  int DisplacementFieldItkImageFilterSinkComponent< Dimensionality, TPixel>::Set(DisplacementFieldItkImageSourceInterface<Dimensionality, TPixel>* other)
  {
    if (this->m_SinkWriter == nullptr)
    {
      itkExceptionMacro("SinkComponent needs to be initialized by ConnectToOverlordSink()");
    }
    
    this->m_SinkWriter->SetInput(other->GetDisplacementFieldItkImageSource()->GetOutput());
    return 0;
  }

  template<int Dimensionality, class TPixel>
  bool DisplacementFieldItkImageFilterSinkComponent< Dimensionality, TPixel>::ConnectToOverlordSink(itk::Object::Pointer object)
  {
    bool anySuccessfulCast = false;
    this->m_Sink = dynamic_cast<itk::ProcessObject*>(object.GetPointer());
    anySuccessfulCast = this->m_Sink ? true : anySuccessfulCast;
    this->m_SinkWriter = dynamic_cast<itk::ImageFileWriter<itk::Image<itk::Vector<TPixel, Dimensionality>, Dimensionality>>*>(object.GetPointer());
    anySuccessfulCast = this->m_SinkWriter ? true : anySuccessfulCast;
    return anySuccessfulCast;
  }

  template<int Dimensionality, class TPixel>
  bool DisplacementFieldItkImageFilterSinkComponent< Dimensionality, TPixel>::MeetsCriterion(const ComponentBase::CriterionType &criterion)
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
    if (criterion.first == "IsVectorField")
    {
      meetsCriteria = true;
      for (auto const & criterionValue : criterion.second) // auto&& preferred?
      {
        if (criterionValue != "True")  // e.g. "GradientDescent", "SupportsSparseSamples
        {
          meetsCriteria = false;
        }
      }
    }
    return meetsCriteria;
  }

} //end namespace selx
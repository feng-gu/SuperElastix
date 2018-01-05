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

#include "selxTypeList.h"

//Component group ItkImageRegistrationMethodv4
#include "selxItkImageRegistrationMethodv4Component.h"
#include "selxItkANTSNeighborhoodCorrelationImageToImageMetricv4Component.h"
#include "selxItkMeanSquaresImageToImageMetricv4Component.h"
#include "selxItkGradientDescentOptimizerv4Component.h"
#include "selxItkGaussianExponentialDiffeomorphicTransformComponent.h"
#include "selxItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent.h"
#include "selxItkAffineTransformComponent.h"
#include "selxItkTransformDisplacementFilterComponent.h"
#include "selxItkResampleFilterComponent.h"
#include "selxItkTransformSourceComponent.h"
#include "selxItkTransformSinkComponent.h"

namespace selx
{
using ModuleItkImageRegistrationMethodv4Components = selx::TypeList<
  ItkImageRegistrationMethodv4Component< 2, float, double >,
  ItkANTSNeighborhoodCorrelationImageToImageMetricv4Component< 2, float >,
  ItkMeanSquaresImageToImageMetricv4Component< 2, float, double >,
  ItkGradientDescentOptimizerv4Component< double >,
  ItkGaussianExponentialDiffeomorphicTransformComponent< double, 2 >,
  ItkGaussianExponentialDiffeomorphicTransformParametersAdaptorsContainerComponent< 2, double >,
  ItkAffineTransformComponent< double, 2 >,
  ItkTransformDisplacementFilterComponent< 2, float, double >,
  ItkResampleFilterComponent< 2, float, double >,
  ItkTransformSourceComponent< 2, double >,
  ItkTransformSinkComponent< 2, double >
  >;
}
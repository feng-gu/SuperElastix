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

#include "selxBlueprint.h"
#include "selxBlueprintImpl.h"

namespace selx
{

Blueprint
::Blueprint()
{
  this->m_Blueprint = BlueprintPointer( new BlueprintImpl() );
}

void
Blueprint
::SetBlueprint( BlueprintImpl & blueprint )
{
  this->Modified();
  this->m_Blueprint = BlueprintPointer( &blueprint );
}


BlueprintImpl &
Blueprint
::GetBlueprint( void)
{
  if( this->m_Blueprint )
  {
    return *this->m_Blueprint;
  }
  else
  {
    itkExceptionMacro( "BlueprintImpl not set." )
  }
}


bool
Blueprint
::SetComponent( ComponentNameType name, ParameterMapType parameterMap )
{
  this->Modified();
  return this->m_Blueprint->SetComponent( name, parameterMap );
}


Blueprint::ParameterMapType
Blueprint
::GetComponent( ComponentNameType componentName ) const
{
  return this->m_Blueprint->GetComponent( componentName );
}


bool
Blueprint
::DeleteComponent( ComponentNameType componentName )
{
  this->Modified();
  return this->m_Blueprint->DeleteComponent( componentName );
}


Blueprint::ComponentNamesType
Blueprint::GetComponentNames( void ) const
{
  return this->m_Blueprint->GetComponentNames();
}


bool
Blueprint
::SetConnection( ComponentNameType upstream, ComponentNameType downstream, ParameterMapType parameterMap )
{
  this->Modified();
  return this->m_Blueprint->SetConnection( upstream, downstream, parameterMap );
}


Blueprint::ParameterMapType
Blueprint
::GetConnection( ComponentNameType upstream, ComponentNameType downstream ) const
{
  return this->m_Blueprint->GetConnection( upstream, downstream );
}


bool
Blueprint
::DeleteConnection( ComponentNameType upstream, ComponentNameType downstream )
{
  this->Modified();
  return this->m_Blueprint->DeleteConnection( upstream, downstream );
}


bool
Blueprint
::ComponentExists( ComponentNameType componentName ) const
{
  return this->m_Blueprint->ComponentExists( componentName );
}


bool
Blueprint
::ConnectionExists( ComponentNameType upstream, ComponentNameType downstream ) const
{
  return this->m_Blueprint->ConnectionExists( upstream, downstream );
}


bool
Blueprint
::ComposeWith( Blueprint& other)
{
  this->Modified();
  return this->m_Blueprint->ComposeWith( other.GetBlueprint() );
}


Blueprint::ComponentNamesType
Blueprint
::GetOutputNames( const ComponentNameType name ) const
{
  return this->m_Blueprint->GetOutputNames( name );
}


Blueprint::ComponentNamesType
Blueprint
::GetInputNames( const ComponentNameType name ) const
{
  return this->m_Blueprint->GetInputNames( name );
}


void
Blueprint
::Write( const std::string filename )
{
  this->m_Blueprint->Write( filename );
}
} // namespace selx

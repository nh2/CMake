/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2001 Insight Consortium
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * The name of the Insight Consortium, nor the names of any consortium members,
   nor of any contributors, may be used to endorse or promote products derived
   from this software without specific prior written permission.

  * Modified source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "cmMSProjectGenerator.h"
#include "cmDSWMakefile.h"
#include "cmDSPMakefile.h"
#include "cmCacheManager.h"

cmMSProjectGenerator::cmMSProjectGenerator()
{
  m_DSWMakefile = 0;
  m_DSPMakefile = 0;
  BuildDSWOn();
}

void cmMSProjectGenerator::GenerateMakefile()
{
  if(m_BuildDSW)
    {
    m_DSWMakefile = new cmDSWMakefile(m_Makefile);
    m_DSWMakefile->OutputDSWFile();
    }
  else
    {
    m_DSPMakefile = new cmDSPMakefile(m_Makefile);
    m_DSPMakefile->OutputDSPFile();
    }
}

cmMSProjectGenerator::~cmMSProjectGenerator()
{
  delete m_DSPMakefile;
  delete m_DSWMakefile;
}

void cmMSProjectGenerator::SetLocal(bool local)
{
  m_BuildDSW = !local;
}

void cmMSProjectGenerator::ComputeSystemInfo()
{
  // now load the settings
  if(!cmCacheManager::GetInstance()->GetCacheValue("CMAKE_ROOT"))
    {
    cmSystemTools::Error(
      "CMAKE_ROOT has not been defined, bad GUI or driver program");
    return;
    }
  std::string fpath = 
    cmCacheManager::GetInstance()->GetCacheValue("CMAKE_ROOT");
  fpath += "/Templates/CMakeWindowsSystemConfig.cmake";
  m_Makefile->ReadListFile(NULL,fpath.c_str());
}

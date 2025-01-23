///////////////////////////////////////////////////////////////////////
// Reporter - Report Creation and Representation Library
// Copyright © 1999-2025  Washington State Department of Transportation
//                        Bridge and Structures Office
//
// This library is a part of the Washington Bridge Foundation Libraries
// and was developed as part of the Alternate Route Project
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the Alternate Route Library Open Source License as published by 
// the Washington State Department of Transportation, Bridge and Structures Office.
//
// This program is distributed in the hope that it will be useful, but is distributed 
// AS IS, WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
// or FITNESS FOR A PARTICULAR PURPOSE. See the Alternate Route Library Open Source 
// License for more details.
//
// You should have received a copy of the Alternate Route Library Open Source License 
// along with this program; if not, write to the Washington State Department of 
// Transportation, Bridge and Structures Office, P.O. Box  47340, 
// Olympia, WA 98503, USA or e-mail Bridge_Support@wsdot.wa.gov
///////////////////////////////////////////////////////////////////////

#include <Reporter\ReporterLib.h>

#include <Reporter\RcImage.h>
#include <Reporter\RcVisitor.h>
#include <sstream>

rptRcImage::rptRcImage() :
rptReportContent(),
m_FileName( _T("Unspecified") ),
m_Align(Bottom),
m_Float(None)
{
}

rptRcImage::rptRcImage(const std::_tstring& fileName,rptRcImage::Align align,rptRcImage::Float flt):
rptReportContent(),
m_FileName( fileName ),
m_Align(align),
m_Float(flt)
{
}

rptRcImage::rptRcImage(const rptRcImage& rOther) :
rptReportContent(rOther)
{
   m_FileName = rOther.m_FileName;
   m_PictureDescription = rOther.m_PictureDescription;
   m_Align = rOther.m_Align;
   m_Float = rOther.m_Float;
}

rptRcImage::~rptRcImage()
{
}

rptRcImage& rptRcImage::operator= (const rptRcImage& rOther)
{
   if( this != &rOther )
   {
      m_FileName = rOther.m_FileName;
      m_PictureDescription = rOther.m_PictureDescription;
      m_Align = rOther.m_Align;
      m_Float = rOther.m_Float;
   }

   return *this;
}

void rptRcImage::Accept( rptRcVisitor& rVisitor )
{
#if defined _DEBUG
   // test to make sure the file exists
   WIN32_FIND_DATA findData;
   HANDLE handle = ::FindFirstFile(m_FileName.c_str(),&findData);
   CHECK(handle != INVALID_HANDLE_VALUE);
   if ( handle != INVALID_HANDLE_VALUE )
      ::FindClose(handle);
#endif
   rVisitor.VisitRcImage( this );
}

rptReportContent* rptRcImage::CreateClone() const
{
   return new rptRcImage( *this );
}

//======================== ACCESS     =======================================

const std::_tstring& rptRcImage::GetFileName() const
{
   return m_FileName;
}

void rptRcImage::SetFileName(const std::_tstring& fileName)
{
   m_FileName = fileName;
}

const std::_tstring& rptRcImage::GetPictureDescription() const
{
   return m_PictureDescription;
}

void rptRcImage::SetPictureDescription(const std::_tstring& rPictureDescription)
{
   m_PictureDescription = rPictureDescription;
}

void rptRcImage::SetImageAlignment(rptRcImage::Align a)
{
   m_Align = a;
}

rptRcImage::Align rptRcImage::GetImageAlignment() const
{
   return m_Align;
}

void rptRcImage::SetImageFloat(rptRcImage::Float flt)
{
   m_Float = flt;
}

rptRcImage::Float rptRcImage::GetImageFloat() const
{
   return m_Float;
}

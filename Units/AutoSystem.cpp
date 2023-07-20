///////////////////////////////////////////////////////////////////////
// Units - Unit conversion and system unit management service
// Copyright © 1999-2023  Washington State Department of Transportation
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

#include <Units\UnitsLib.h>
#include <Units\AutoSystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace WBFL::Units;

AutoSystem::AutoSystem() :
m_Mass( System::GetMassUnit() ),
m_Length( System::GetLengthUnit() ),
m_Time( System::GetTimeUnit() ),
m_Temperature( System::GetTemperatureUnit() ),
m_Angle( System::GetAngleUnit() )
{
}

AutoSystem::~AutoSystem()
{
   System::SetMassUnit( m_Mass );
   System::SetLengthUnit( m_Length );
   System::SetTimeUnit( m_Time );
   System::SetTemperatureUnit( m_Temperature );
   System::SetAngleUnit( m_Angle );
}

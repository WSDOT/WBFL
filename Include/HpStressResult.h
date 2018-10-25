#ifndef INCLUDED_IFACE_HPSTRESSRESULT_H_
#define INCLUDED_IFACE_HPSTRESSRESULT_H_

/*****************************************************************************
INTERFACE
   IHpStressResult

   High performance Interface for summing stress results

DESCRIPTION
   High performance Interface for summing stress results
*****************************************************************************/
// {3C16525E-3DAA-40dd-829F-BA5837234733}
DEFINE_GUID(IID_IHpStressResult, 
0x3c16525e, 0x3daa, 0x40dd, 0x82, 0x9f, 0xba, 0x58, 0x37, 0x23, 0x47, 0x33);
interface IHpStressResult : IUnknown
{
	STDMETHOD(HpSumResults)(/*[in]*/CollectionIndexType num, /*[in]*/double* Vals)=0;
	STDMETHOD(HpSetResults)(/*[in]*/CollectionIndexType num, /*[in]*/double* Vals)=0;
};


// {54500FA6-A0F5-46bc-A710-69F85446E389}
DEFINE_GUID(IID_IHpSectionStressResult, 
0x54500fa6, 0xa0f5, 0x46bc, 0xa7, 0x10, 0x69, 0xf8, 0x54, 0x46, 0xe3, 0x89);
interface IHpSectionStressResult : IUnknown
{
	STDMETHOD(HpSumResults)(/*[in]*/CollectionIndexType numLeft, /*[in]*/double* leftVals, /*[in]*/CollectionIndexType numRight, /*[in]*/double* rightVals)=0;
	STDMETHOD(HpSetResults)(/*[in]*/CollectionIndexType numLeft, /*[in]*/double* leftVals, /*[in]*/CollectionIndexType numRight, /*[in]*/double* rightVals)=0;
};




#endif
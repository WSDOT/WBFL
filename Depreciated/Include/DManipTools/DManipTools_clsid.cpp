#ifdef __cplusplus
extern "C"{
#endif 

//// {B7B9C36E-FEAF-43BB-8907-C98A0EF3224E}
//DEFINE_GUID(LIBID_WBFLDManipTools,
//0xB7B9C36E,0xFEAF,0x43BB,0x89,0x07,0xC9,0x8A,0x0E,0xF3,0x22,0x4E);

DEFINE_GUID(IID_iDataPointDrawStrategy, 
0xe1c61a80, 0x115f, 0x4281, 0x92, 0x6f, 0x4f, 0x7a, 0x65, 0xad, 0x33, 0x2a);

DEFINE_GUID(IID_iDataPointEvents, 
0xd49292f4, 0x24f4, 0x482b, 0xb3, 0xc4, 0xc, 0x47, 0x2, 0xfe, 0x9a, 0x4b);

// {3E920A2D-BE1E-4e85-B4A5-A1875B387CF7}
DEFINE_GUID(IID_iDataSet2d, 
0x3e920a2d, 0xbe1e, 0x4e85, 0xb4, 0xa5, 0xa1, 0x87, 0x5b, 0x38, 0x7c, 0xf7);

// {F1FA6B3B-08E7-46f0-A350-BD6D2BEDCF01}
DEFINE_GUID(IID_iGraphXyDisplayObject, 
0xf1fa6b3b, 0x8e7, 0x46f0, 0xa3, 0x50, 0xbd, 0x6d, 0x2b, 0xed, 0xcf, 0x1);

// {FD4134B6-D588-4e3a-9158-FCAA773E82E5}
DEFINE_GUID(IID_iLegendDisplayObject, 
0xfd4134b6, 0xd588, 0x4e3a, 0x91, 0x58, 0xfc, 0xaa, 0x77, 0x3e, 0x82, 0xe5);

// {E3BD88F7-D54B-4058-A350-900E97D13176}
DEFINE_GUID(IID_iSymbolLegendEntry, 
0xe3bd88f7, 0xd54b, 0x4058, 0xa3, 0x50, 0x90, 0xe, 0x97, 0xd1, 0x31, 0x76);

// {55504B51-10F4-4c2e-9E61-974B2E38396C}
DEFINE_GUID(IID_iLegendEntry, 
0x55504b51, 0x10f4, 0x4c2e, 0x9e, 0x61, 0x97, 0x4b, 0x2e, 0x38, 0x39, 0x6c);

// {460711D6-1BC2-4545-99F5-EBF249AF8417}
DEFINE_GUID(IID_iGraphXyDataProvider, 
0x460711d6, 0x1bc2, 0x4545, 0x99, 0xf5, 0xeb, 0xf2, 0x49, 0xaf, 0x84, 0x17);

// {12761816-B9BD-4f41-9BFB-8713C252C3DB}
DEFINE_GUID(IID_iDataPointFactory, 
0x12761816, 0xb9bd, 0x4f41, 0x9b, 0xfb, 0x87, 0x13, 0xc2, 0x52, 0xc3, 0xdb);

// {4B929127-C494-44af-B4A6-1DB9A3143067}
DEFINE_GUID(IID_iPolyLineDisplayObject, 
0x4b929127, 0xc494, 0x44af, 0xb4, 0xa6, 0x1d, 0xb9, 0xa3, 0x14, 0x30, 0x67);

// {02F9ADCE-5FCF-4519-9783-6C78A1483E35}
DEFINE_GUID(IID_iHorzCurveDisplayObject, 
0x2f9adce, 0x5fcf, 0x4519, 0x97, 0x83, 0x6c, 0x78, 0xa1, 0x48, 0x3e, 0x35);

///////////////////////////////////////////////////////////////////////////////////
//
//// {341A682F-5B58-4f63-8190-88BF3970FB45}
//DEFINE_GUID(CLSID_PolyLineDisplayObject, 
//0x341a682f, 0x5b58, 0x4f63, 0x81, 0x90, 0x88, 0xbf, 0x39, 0x70, 0xfb, 0x45);
//
//// {7DBA44AA-1542-4470-8719-21580A6822B5}
//DEFINE_GUID(CLSID_HorzCurveDisplayObject, 
//0x7dba44aa, 0x1542, 0x4470, 0x87, 0x19, 0x21, 0x58, 0xa, 0x68, 0x22, 0xb5);
//
//// {06C90828-5269-4b98-97E6-AECDDF4B0764}
//DEFINE_GUID(CLSID_GraphXyDisplayObject, 
//0x6c90828, 0x5269, 0x4b98, 0x97, 0xe6, 0xae, 0xcd, 0xdf, 0x4b, 0x7, 0x64);
//
//// {4792CF33-B6FD-423F-90DE-314356A22848}
//DEFINE_GUID(CLSID_DataSet2d,
//0x4792CF33,0xB6FD,0x423F,0x90,0xDE,0x31,0x43,0x56,0xA2,0x28,0x48);
//
//// {C2EC59B5-BAA1-437d-89CB-19AD85ED9F04}
//DEFINE_GUID(CLSID_LegendDisplayObject, 
//0xc2ec59b5, 0xbaa1, 0x437d, 0x89, 0xcb, 0x19, 0xad, 0x85, 0xed, 0x9f, 0x4);
//
//// {951403BB-85F3-4443-8EE9-4FFDB338F3F5}
//DEFINE_GUID(CLSID_LegendEntry,
//0x951403BB,0x85F3,0x4443,0x8E,0xE9,0x4F,0xFD,0xB3,0x38,0xF3,0xF5);
//
//// {D7C33DA2-EE8F-49a1-9A13-8653809262E9}
//DEFINE_GUID(CLSID_DManipToolsDisplayObjectFactory, 
//0xd7c33da2, 0xee8f, 0x49a1, 0x9a, 0x13, 0x86, 0x53, 0x80, 0x92, 0x62, 0xe9);
//
//// {0462D6DF-25DB-4fa0-B8B2-7B855A702A99}
//DEFINE_GUID(CLSID_GraphXyDataProvider, 
//0x462d6df, 0x25db, 0x4fa0, 0xb8, 0xb2, 0x7b, 0x85, 0x5a, 0x70, 0x2a, 0x99);

// declarations so we can support uuidof
struct __declspec(uuid("{F1FA6B3B-08E7-46f0-A350-BD6D2BEDCF01}")) iGraphXyDisplayObject;
struct __declspec(uuid("{3E920A2D-BE1E-4e85-B4A5-A1875B387CF7}")) iDataSet2d;
struct __declspec(uuid("{FD4134B6-D588-4e3a-9158-FCAA773E82E5}")) iLegendDisplayObject;
struct __declspec(uuid("{55504B51-10F4-4c2e-9E61-974B2E38396C}")) iLegendEntry;
struct __declspec(uuid("{E3BD88F7-D54B-4058-A350-900E97D13176}")) iSymbolLegendEntry;
struct __declspec(uuid("{460711D6-1BC2-4545-99F5-EBF249AF8417}")) iGraphXyDataProvider;
struct __declspec(uuid("{12761816-B9BD-4f41-9BFB-8713C252C3DB}")) iDataPointFactory;
struct __declspec(uuid("{4B929127-C494-44af-B4A6-1DB9A3143067}")) iPolyLineDisplayObject;
struct __declspec(uuid("{02F9ADCE-5FCF-4519-9783-6C78A1483E35}")) iHorzCurveDisplayObject;

#ifdef __cplusplus
}
#endif

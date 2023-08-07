#ifndef _LBAMLIVELOADERCP_H_
#define _LBAMLIVELOADERCP_H_






template <class T>
class CProxyDVehicularAnalysisContextEvents : public IConnectionPointImpl<T, &IID_IVehicularAnalysisContextEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLiveLoadChanged(LiveLoadModelType lltype)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = __super::m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = __super::m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVehicularAnalysisContextEvents> events(sp);
         if ( events )
            events->OnLiveLoadChanged(lltype);
		}
	}
	VOID Fire_OnStiffnessResponseChanged(ChangeScopeType scope, PoiIDType poiID)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = __super::m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = __super::m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<IVehicularAnalysisContextEvents> events(sp);
         if ( events )
            events->OnStiffnessResponseChanged(scope, poiID);
		}
	}
};


template <class T>
class CProxyDLiveLoadConfigurationEvents : public IConnectionPointImpl<T, &IID_ILiveLoadConfigurationEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	VOID Fire_OnLiveLoadConfigurationChanged(ILiveLoadConfiguration * config)
	{
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = __super::m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = __super::m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
         CComQIPtr<ILiveLoadConfigurationEvents> events(sp);
         if ( events )
            events->OnLiveLoadConfigurationChanged(config);
		}
	}
};
#endif

//////////////////////////////////////////////////////////////////////////////
// CProxyIRoadwayDataEvents
template <class T>
class CProxyIRoadwayDataEventSink : public IConnectionPointImpl<T, &IID_IRoadwayDataEvents, CComDynamicUnkArray>
{
public:

//IRoadwayDataEvents : IUnknown
public:
	HRESULT Fire_OnRoadwayChanged()
	{
		T* pT = (T*)this;

		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IRoadwayDataEvents* pIRoadwayDataEvents = reinterpret_cast<IRoadwayDataEvents*>(*pp);
				pIRoadwayDataEvents->OnRoadwayDataChanged();
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

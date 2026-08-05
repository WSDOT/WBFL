Graphing {#WBFL_EAF_Graphing}
================================
An Agent integrates with the graphing system via `WBFL::EAF::IAgentGraphingIntegration`,
registering and unregistering in `IntegrateWithGraphing`.

`IEAFGraphManager::AddGraphBuilder` (`Include\EAF\EAFGraphManager.h`) registers a new
`WBFL::Graphing::GraphBuilder`-derived graph, by value or by taking ownership of a `unique_ptr`:
~~~
GET_IFACE(IEAFGraphManager, pGraphMgr);
pGraphMgr->AddGraphBuilder(std::make_unique<CMyGraphBuilder>());
~~~
`RemoveGraphBuilder` unregisters a graph by name and hands ownership back to the caller.

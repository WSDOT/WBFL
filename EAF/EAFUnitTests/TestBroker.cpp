#include "pch.h"
#include "CppUnitTest.h"
#include <initguid.h>
#include <EAF\Broker.h>
#include <EAF\Agent.h>
#include <EAF\EventSinkManager.h>
#include <AgentTools.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace WBFL::EAF;


namespace EAFUnitTests
{
	struct Checks
	{
		int nInitCalled = 0;
		int nRegisterInterfacesCalled = 0;
		int nOnTestCalled = 0;
	};

	static bool bAgent1Destroyed = false;
	static bool bAgent2Destroyed = false;

// {F06C2C74-0D1B-488B-963A-6084268D4769}
DEFINE_GUID(IID_Interface1,
	0xf06c2c74, 0xd1b, 0x488b, 0x96, 0x3a, 0x60, 0x84, 0x26, 0x8d, 0x47, 0x69);
class Interface1
{
public:
	virtual void Fn() = 0;
};

// {559C71D2-8FCD-4359-AAFE-C7A55120BEE2}
DEFINE_GUID(IID_Interface2,
	0x559c71d2, 0x8fcd, 0x4359, 0xaa, 0xfe, 0xc7, 0xa5, 0x51, 0x20, 0xbe, 0xe2);
class Interface2
{
public:
	virtual void Test() = 0;
};

class Interface2Events
{
public:
	virtual void OnTest() = 0;
};

// {9F310F84-2E6E-47C2-A5FE-7483477F1D6B}
DEFINE_GUID(IID_Interface3,
	0x9f310f84, 0x2e6e, 0x47c2, 0xa5, 0xfe, 0x74, 0x83, 0x47, 0x7f, 0x1d, 0x6b);
class Interface3
{
public:
	virtual void Test3() = 0;
};

class Interface3Events
{
public:
	virtual void OnTest3(int) = 0;
};

template <typename P>
class Interface2EventsCallback : public WBFL::EAF::EventSinkManager<Interface2Events>
{
public:
	void Fire_OnTest()
	{
	   for (auto& [id, sink] : this->m_EventSinks)
	   {
		  auto callback = sink.lock();
		  callback->OnTest();
	   }
	}
};

template <typename P>
class Interface3EventsCallback : public WBFL::EAF::EventSinkManager<Interface3Events>
{
public:
	void Fire_OnTest3()
	{
	   for (auto& [id, sink] : this->m_EventSinks)
	   {
		  auto callback = sink.lock();
		  callback->OnTest3(10);
	   }
	}
};

// {C2064CBF-59E5-4C73-BDE9-D9FEE9E44323}
DEFINE_GUID(CLSID_Agent1,
	0xc2064cbf, 0x59e5, 0x4c73, 0xbd, 0xe9, 0xd9, 0xfe, 0xe9, 0xe4, 0x43, 0x23);
class Agent1 : public Agent, // Agent1 is an Agent
	public Interface1, // it implements Interface1
	public Interface2Events, // and it is a listener for events broadcast when functions on Interface2 are called
	public Interface3Events
{
public:
	Checks checks;
	~Agent1()
	{
		bAgent1Destroyed = true;
	}

	std::_tstring GetName() const override { return _T("Agent1"); }
	bool RegisterInterfaces() override
	{
		checks.nRegisterInterfacesCalled++;
		return REGISTER_INTERFACE(Interface1);
	}

	bool Init() override
	{
	   Agent::Init();
		checks.nInitCalled++;
		m_Iface2Cookie = REGISTER_EVENT_SINK(Interface2Events);
		m_Iface3Cookie = REGISTER_EVENT_SINK(Interface3Events);
		return true;
	}

	bool ShutDown() override
	{
		UNREGISTER_EVENT_SINK(Interface3Events,m_Iface2Cookie);
		UNREGISTER_EVENT_SINK(Interface2Events,m_Iface2Cookie);
		return true;
	}

	CLSID GetCLSID() const override { return CLSID_Agent1; }

	void Fn() override
	{
		GET_IFACE(Interface2,iface2);
		iface2->Test();
	}

	void OnTest() override
	{
		checks.nOnTestCalled++;
	}

	void OnTest3(int value) override
	{
		checks.nOnTestCalled++;
	}

private:
	IDType m_Iface2Cookie;
	IDType m_Iface3Cookie;
};

// {32EF75EA-7CE6-4D31-8B31-2F9DF8A08494}
DEFINE_GUID(CLSID_Agent2,
	0x32ef75ea, 0x7ce6, 0x4d31, 0x8b, 0x31, 0x2f, 0x9d, 0xf8, 0xa0, 0x84, 0x94);
class Agent2 : public Agent,
	public Interface2,
	public Interface3,
	public Interface2EventsCallback<Agent2>,
	public Interface3EventsCallback<Agent2>
{
public:
	Checks checks;

	~Agent2()
	{
		bAgent2Destroyed = true;
	}

	std::_tstring GetName() const override { return _T("Agent2"); }

	bool RegisterInterfaces() override
	{
		checks.nRegisterInterfacesCalled++;
		REGISTER_INTERFACE(Interface2);
		REGISTER_INTERFACE(Interface3);
		return true;
	}

	bool Init() override
	{
	   Agent::Init();
	   checks.nInitCalled++;
		return true;
	}

	CLSID GetCLSID() const override { return CLSID_Agent2; }

	void Test() override {
		Fire_OnTest();
	}

	void Test3() override {
		Fire_OnTest3();
	}
};

TEST_CLASS(TestBroker)
	{
	public:
		
		TEST_METHOD(Test)
		{
			// This test class simulates a Document class
			// Create a broker and add agents. Using AddAgent
			// instead of broker->LoadAgents() because that would require
			// external DLLs and dynamic object creation.
		    auto checker = std::make_shared<BrokerChecker>();
			auto broker = std::make_shared<Broker>(checker);
			auto agent1 = std::make_shared<Agent1>();
			auto agent2 = std::make_shared<Agent2>();

			// Add the agents to the broker
			Assert::IsTrue(broker->AddAgent(agent1).first);
			Assert::IsTrue(broker->AddAgent(agent2).first);

			// Once all agents are loaded/added, they are initialized.
			// This is when the agents register their interfaces and
			// register callbacks if they want to receive events
			Assert::IsTrue(broker->InitAgents());

			// Test an interface lookup.
			// Scope this so iface goes out of scope as if it is being called from within an agent function
			{
			   GET_IFACE2(broker, Interface1, iface);
			   
			   GET_IFACE2(broker, Interface1, iface1);
				Assert::IsTrue(iface1 != nullptr);
				iface1->Fn();

				GET_IFACE2(broker, Interface2, iface2);
				std::shared_ptr<Interface2> if2(iface2);

				GET_IFACE2(broker, Interface3,iface3);
				Assert::IsTrue(iface3 != nullptr);
				iface3->Test3();
#if defined _DEBUG
				Assert::IsFalse(iface.IsUsed());
				iface = nullptr;
#endif
			}

			// When a document is closing, it shutdowns the broker
			broker->ShutDown();
			broker = nullptr;

			Assert::IsTrue(checker->bBrokerDestroyed);

			Assert::IsTrue(agent1->checks.nInitCalled == 1);
			Assert::IsTrue(agent1->checks.nRegisterInterfacesCalled == 1);
			Assert::IsTrue(agent1->checks.nOnTestCalled == 2);

			Assert::IsTrue(agent2->checks.nInitCalled == 1);
			Assert::IsTrue(agent2->checks.nRegisterInterfacesCalled == 1);
			Assert::IsTrue(agent2->checks.nOnTestCalled == 0);

			// Done with the agents, set the shared_ptrs to null. This should
			// be the last pointer holding the agents so they will be destroyed
			agent1 = nullptr;
			Assert::IsTrue(bAgent1Destroyed);

			agent2 = nullptr;
			Assert::IsTrue(bAgent2Destroyed);

			for (auto& ac : checker->AgentCheckers)
			{
			   Assert::IsTrue(ac.second->bInitCalled);
			   Assert::IsTrue(ac.second->bDestroyed);
			}
		}
	};
}

Component Object Model {#WBFL_EAF_COM}
======================
The EAF provides a component object model similar to Microsoft COM. For many years the Microsoft COM API was used in this library. However, elevated privelages where required for develops to register components with Component Categories. The WSDOT Information Technology Division determined this to be an unacceptable security vulnerability. For this reason, an equivalent replacement was developed.

ComponentObject creation information is registered with the ComponentManager which serves as both a registry of Component Category information and Component Object information.

## Initilizing the Component Manager
The EAF framework loads manifest files into the ComponentManager, which in turn defines the component registration information. The ComponentManager loads each DLL implementing a ComponentModule, as defined in the manifest file. When the DLL loads, the ComponentModule is initialized with its Object Entry Map. The Object Entry Map defines a mapping between a CLSID and a C++ class type. 

## Instantiating Component Objects
The ComponentManager serves as a centralized object factory. When your application needs to create an instance of a ComponentObject, it calls one of the ComponentManager::CreateComponent methods. The ComponentManager finds the DLL that implements the component and calls is "create_class_object" method. The create_class_object method is implemented on the ComponentModuleMgr class and is automatically
part of your DLL when linking to the WBFLEAF.lib library. There are rare instances with "create_class_object" method isn't available. In those cases, a DLL can implement the alternative EAFGetClassObject method.

## Component Categories
Some objects, like the Agents, can be registered with a Component Category. When the Broker objects loads all of the agents for an application, it is provided a Category Identifier (CATID), and it creates instances of all objects registered as being a member of that category.

## Manifest File Recommends

### Creating a manifest file
The recommend method of creating a manifest file is programmatically. Initial the ComponentManager with component records and use the ComponentManager::Save function. Manifest files should be named <Type>.Manifest.<Application> where Type is the type of manifest (such as Application, Extensions, Plugins) and Application is the name of the application (such as BridgeLink, PGSuper, BEToolbox). Manifest entries should specify either the DLL name, without path, or the fully qualified path to the DLL. Relative paths should not be used.

### Search path for manifest files and DLLs
Use the ComponentManager::Load function to load the manifest. The Load function takes the manifest file extension (.Manifest.<Application>) and searchs for all files for the application. The search path starts with the application's folder (folder of the EXE), then searches directores defined on the application search path.

The application search path is defined as an environment variable named <APPLICATION>_PATH. Where <APPLICATION> is the name of the application taken from the m_pszApp variable on the CWinApp derived class. This enviroment variable will contain one or more semi-colon separated paths.

## Examples
The best examples are the Agents and Beams in the PGSuper project.
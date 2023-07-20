# Setting up a Visual Studio Unit Test project for WBFL

This process document details the steps for setting up a new Visual Studio unit test project.

## Creating the test project
In the Solution Explorer window, right click on the WBFL Solution and select Add > New Project...

Search for "Native Unit Test Project" or use the filters with the settings C++, Windows, and Test to find the "Native Unit Test Project". Press [Next].

Enter the name of the test project in the Project Name field. The convention we are using is *ProjectName*UnitTests where *ProjectName* is the name of the DLL to be tested (without the WBFL prefix).

Set the location to X:\ARP\WBFL\\*ProjectName* (substitute your drive letter for X).

Check the project to be created in setting. It should read something like "F:\ARP\WBFL\Math\MathUnitTests\" if *ProjectName* is Math.

Press [Create].

## Configuring the Project
The default project isn't quite ready to be used. It needs to be configured for the WBFL build environment.

### Project Properties
In the Property Manager window, locate your new test project. Expand the project node.

Right click on your test project and select Remove for the "Debug | Win32" and "Release | Win32" folders. WBFL only supports x64 builds.

Right click on your test project and select Add Existing Property Sheet. Navigate to X:\ARP\WBFL (substitute your drive letter for X) and select WBFL.props. Press [Open].

### Output Directory
In the Solution Explorer window, locate your new test project. Right click on the new test project and select Properties. Set the Configuration to "All Configurations" and set the Platform to "x64".

Set Configuration Properties > General > Output Directory to $(ARPDIR)\WBFL\RegFreeCOM\$(Platform)\$(Configuration)\

Press [OK]

### References
The test project needs to reference the DLL project to ensure the tests are built when the DLL is updated. In the Solution Explorer window, find the test project and right click on the References node. Select Add Reference... Check the box for the DLL project. Press [OK]

> There is sometimes an error with this step. To get past the error, save the Solution and exit Visual Studio. Restart and open the WBFL project and try again.

### Include the test DLL main header file into the test project
Open the pch.h header file and #include the main header file for the DLL that is being tested. The main header file typically has the same name as the project. For example, for the Math project add the following:

~~~
#include <Math/Math.h>
~~~

## Create Test Cases
Visual Studio creates a default file with the same name as your test project. This file has a default test class and test method. This file isn't particularly useful. We generally create one test class for each class exported from the DLL. The tests are implemented in a file named Test*classname*.cpp. In the Solution Explorer, rename the default test file for the first class to be tested. Change the TEST_CLASS() to Test*classname*. Rename the default TEST_METHOD and create new TEST_METHODs to test the class. Create a new file and TEST_CLASS for each class to be tested.
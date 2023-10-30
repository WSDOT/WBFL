# WBFL Examples
This folder contains example programs for the WBFL services.

## Creating new C++ Examples
C++ examples are stored in the VC folder. The folders generally follow the name of the WBFL library with subfolders for each example.

Typically, examples will be created as a console application. The default console application from Visual Studio works well.

There are two set up activities required to add the WBFL properties set to the project.

### WBFL Property Sheet
1. Select View > Property Manager
2. Right click on the solution name at the top of the Property Manager window and select "Add Existing Property Sheet".
3. In the /ARP/WBFL folder, select the WBFL.props file


### Output Directory
The output directory indicates where the resulting executable file is stored. It is easiest to put the EXE in the common WBFL folder.

1. Select View > Solution Explorer
2. Right click on the project name and select Properties.
3. Select "All Configurations"
4. Expand "Configuration Properties" and select "General"
5. Set the "Output Directory" to \$(ARPDIR)/WBFL/RegFreeCom/\$(Platform)/\$(Configuration)/

Your example project should now work with WBFL.
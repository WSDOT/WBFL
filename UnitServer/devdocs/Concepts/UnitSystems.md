Unit Systems {#WBFL_UnitServer_UnitSystems}
================
The WBFL Unit Server encapsulates all the functionality you need for managing unit mode, display units, and unit conversions in its unit system objects. For Single Document Interface (SDI) applications use the UnitSystem object. For Multiple Document Interface (MDI) applications, use the AppUnitSystem and DocUnitSystem objects.

SDI Applications
-----------------
The UnitSystem object provides access to a DisplayUnitMgr object, a UnitModeController object, and a UnitServer object. In the initialization routine for your application create a UnitSystem object.

MDI Applications
-----------------
MDI applications are a little more complex than SDI applications. In an MDI application there can be only one set of internal units defined by the UnitServer and one set of display units defined by the display unit manager, but each document can have a different unit mode. Because of this, the services provided by the UnitSystem object in SDI applications are divided between an AppUnitSystem object and a DocUnitSystem object for MDI applications. The AppUnitSystem object takes care of the unit server and the display units manager. The DocUnitSystem object takes care of the unit mode.

Create an AppUnitSystem object in the initialization routine for your application. Then, for each document you create, create a DocUnitSystem object and associated it with the AppUnitSystem object.
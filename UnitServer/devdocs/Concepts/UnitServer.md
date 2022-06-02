Unit Servers {#WBFL_UnitServer_UnitServer}
================
The UnitServer object is at the heart of the WBFL Unit Server component. The unit server object manages the base units for an application or component and provides unit conversion services.

In our world of component based programming, one of the primary goals is to create solutions with reusable components. Many of the components that perform engineering computations require numbers to be in a specified unit system. The problem, by way of example, is Component A expects inputs and gives outputs in Kips and Feet. Component B expects inputs and gives outputs in Kilonewtons and Meters. To build an application that uses Component A and Component B, you will have to coordinate the unit conversions. The WBFL Unit Server solves this problem by allowing Component A and Component B to communicate with you in the system of units you specify.

Developing Applications
--------------------------
When developing applications, you must create an instance of and maintain a UnitServer object. Typically this is done indirectly with a UnitSystem or AppUnitSystem object (for SDI or MDI applications, respectively). The first order of business is to configure the unit server by setting the base units for your application. To do this, simply call the SetBaseUnits method. The base units are the internal units that your application will use internally. For instance, internal units might be "kg", "m", "sec", "Celcius", and "Radians". All other units of measure will be derived from these basic units. Force is mass times acceleration so force will be kg*m/s^2, or Newtons. See the Custom Base Units example for details.

Components that can be configured to communicate in the internal units of your application must support the ISupportUnitServer interface. To establish this communication, QueryInterface on the component for the ISupportUnitServer interface and supply the component with a reference to your UnitServer object. If the component does not support the ISupportUnitServer interface or if you do not supply the component with a reference to your UnitServer object, the component will expect data in the unit system it specifies.

Developing Components
-----------------------
If you are developing a component and want to support the seemless communication of data between the application and your component, implement the ISupportUnitServer interface. The calling application will provide your component with a UnitServer object that you use to convert all incoming and outgoing data to the unit of measure the caller wants. As a component developer, you don't need to know the exact units of measure the caller wants, the UnitServer will handle the details of the unit conversions for you.
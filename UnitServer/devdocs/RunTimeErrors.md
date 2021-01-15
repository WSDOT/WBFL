Runtime Errors {#WBFL_UnitServer_RuntimeErrors}
===============

The following errors may occur at runtime.

Error | Description
------|------------
App Unit System Not Set | Your DocUnitSystem object does not have an AppUnitSystem object associated with it. Before you can call many of the methods on a DocUnitSystem object, you must assign a AppUnitSystem object to its AppUnitSystem property.
Bad Display Unit Group | You have supplied a Display Unit Group name that is incorrect. Because the display unit managers are fully configurable by you we cannot provide a listing of display unit groups. Check the spelling of the display unit group name.
Bad Unit Tag | You have supplied a unit tag that is incorrect. Because the unit object in the unit server are fully configurable by you we cannot provide a listing of the value unit tags. Check the spelling of the unit tag.
Base Unit Type | You have specified a unit type that is not currently recognized by the unit server. Check the spelling of the unit type.
Base Units Set | The SetBaseUnits method can only be called once per instance of the UnitServer object.
Default Not Found | The default display unit for the current unit mode could not be found. Every unit group should have a default display unit for US and SI units. Make sure all DisplayUnitGroup objects have default display units specified.
Group Already Defined | You attemped to create a DisplayUnitGroup that already exists. Check the spelling and use a unique name for each display unit group.
Unit Type Mismatch | You have attempted to convert a number using two different unit types. For example, Length cannot be converted to Force.
Unit Type Already Defined | You attempted to create a unit type that already exists in the unit server.

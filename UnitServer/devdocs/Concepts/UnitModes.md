Unit Modes {#WBFL_UnitServer_UnitModes}
================
Engineering applications typically provide a choice of English (US) or SI (metric) units to work with. Well designed applications allow the user to change the system of units on the fly.

The WBFL Unit Server provides support for English and SI unit modes. The main component is the UnitModeController object. The unit model controller manages an application's unit mode state, provides a pre-built unit mode editing interface, and broadcasts an event whenever the unit mode changes.

The UnitModeController can be used by itself, but it is typically used in conjunction with a display unit manager. The display unit manager listens for unit change events and adjusts the default display units accordingly. The portions of your application that present unit-values to the user need not know what the current unit mode is. All you need to know is how to convert a value in base units to the currently display units and back again. The unit mode controller and the display unit manager take care of the rest.
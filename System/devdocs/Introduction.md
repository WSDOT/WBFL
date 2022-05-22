WBFL System {#WBFL_System}
========================
The WBFL System Library provides low level system-wide services such as string manipulation, date and time, debugging and logging, and more.

System
------
The classes in the System namespace are an eclectic collection of useful low level utility classes.

Debug
-----
The classes in the Debug namespace provide debugging, logging, and other diagnostic tools

\todo Add more information and examples for the diagnostic services.

Diagnostic macros for checking:

    PRECONDITION[X]  Used to check values you don't have direct control over
    CHECK[X]         Used to check values you do have direct control over
    ASSERTVALID[X]   Calls you class's AssertValid() method
    WATCH[X]         Output a tracing text stream
    WARN[X]          Output a warning text stream

Based on the following switches:

    __PRECONDITION  When defined enables PRECONDITION
    __CHECK         When defined enables CHECK
    __ASSERTVALID   When defined enables ASSERTVALID
    __WATCH         When defined enables WATCH
    __WARN          When defined enables WARN

ASSERTVALID, WATCH, and WARN are always compiled out of release builds.
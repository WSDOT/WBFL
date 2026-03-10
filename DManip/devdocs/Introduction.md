\mainpage
# Introduction {#DManip}

This is the Direct Manipulation (DManip) library. This library provides services that allow direct, on screen, manipulation of graphical objects by the end user. This library extends the MFC CScrollView class with the CDisplayView class. CDisplayView provides display object management services as well as view interaction services such as zooming and panning.

## Display View
The display view is a canvas for drawing display objects. The display works in the coordinate space of real world engineering models. It handles all the necessary mappings between model coordinates and the logical coordinates of the window. The display view does all the work necessary to be a view in an MFC application. All of the work dealing with interactions, such as mouse clicks and key presses, are delegated to the display manager. 

## Display Manager
The display manager controls the display and coordinates the user interactions by forwarding events to display objects, executing tasks, and managing display lists.

## Display Objects
Display objects are the graphical entites on the screen that represent the engineering model and they are what the user interacts with. Interactions include clicking, dragging, and double clicking. These user interactions are all mapped to application specific event handlers.

Everything you see in the Display View is a display object. Some of the display objects are Point, Line, and Text Block. Some of the display objects are connectable and some are connectors.

A display object can be selected by clicking on it, an editing window can be activated by double clicking on it, and an context menu can be opened by right clicking on it. A display object can be repositioned on the screen by drag and drop. The possibilities are endless.

## More Information
This topics provide additional information

\subpage events

\subpage drawing_strategies

\subpage coordinates

\subpage dnd

\subpage connectables

\subpage tools

\subpage tasks
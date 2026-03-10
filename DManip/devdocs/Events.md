# Events {#events}

The DManip framework customizes the standards Windows events, such as mouse clicks and key presses. CDisplayView is a standard MFC CView-derived (actually CScrollView-derived) class, so it uses the regular MFC command processing framework. So, everything you know about event-driven programming with MFC applies to the DManip framework. However, the DManip framework extends the event processing to make user interaction with graphical representations of an engineering model easier for you as a developer.

## Event Routing
Events arrive at the CDisplayView (or your subclass of CDisplayView) by normal MFC event processing. The CDisplayView then routes to the Display Manager and the following occurs:

1) The Display Manager first updates the selection state of display objects. Clicking the mouse on an object may select it. Selecting one object may unselect a previously selected object. The Display Manager then finds all the display objects at the location where the event occured (i.e. the location where a mouse click occurred) and routes the event to those display object in order until one of them processes the event.
2) The Display Object first routes the event to its event sink, if it has one. If it does not have an event sink, or the event sink does not process the event, the Display Object calls its default event processing functions. By default, these event processing functions do nothing. Specialized (subclassed) Display Objects can provide application specific event processing.
3) If the Display Objects do not process the event, the Display Manager routes the event to it's event sink, if it has one.
4) If the event was not processed by the Display Manager the Display View routes the event to a default event handler on the CDisplayView class. By default, these event handlers do nothing. Your derived CDisplayView-class can provide processing by overriding the virtual function event handlers.
5) If the event has not been processed, it is passed along to the CScrollView to resume normal MFC event processing.

The DManip framework provides many opportunities for an application to process events and provide customized user interactions with engineering models.

## Event Sinks
There are two types of event sinks in the DManip library; objects that implement the `iDisplayMgrEvents` interface and objects that implement the `iDisplayObjectEvents` interface. 

These two types of event sinks are very similar. The both have functions that get called by the framework when events occur, such as Left Button Down, Key Down and Mouse Move. The `iDisplayObjectsEvents` interface includes additional functions that get called when a display object is changed, it is moved by dragging, and it is selected or unselected.

The DManip library does not have default event sinks. If an application needs an event sink, it must be created by deriving a new class from `iDisplayManagerEvents` or `iDisplayObjectEvents` that provides implementations for all the pure virtual functions. The application must create an instance of the event sink and call the `RegisterEventSink()` method on Display Manager or Display Object.


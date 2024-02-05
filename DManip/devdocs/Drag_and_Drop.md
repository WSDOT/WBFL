# Drag and Drop {#dnd}
The WBFL DManip framework encapsulates the dreary details of OLE Drag and Drop into a realitively easy to use system. The application developer only needs to worry about which objects can be dragged, where they can be dropped, and what data is transmitted during the drag and drop operation. The framework takes care of the rest.

# Packing your Data in a Drag/Drop Operation
When a display object is dragged from one application to another, data about the display object must accompany the dragged object. You can dig into OLE Drag and Drop if you want the details. In order to package custom data with the display object you must associate a DragData object with a DisplayObject. To accomplish this, create an object that implements the iDragData interface and assign it to the DragData property of a display object's iDraggable interface.

The framework will call PrepareForDrag on your DragData object just before the drag/drop operation begins. Take this opportunity to package any custom data into the DragDataSink object. The DragDataSink essentially stores your custom data in a way that it is available when the drop occurs.

The framework will call OnDrop on your DragData object after the display object is dropped. Take this opportunity to unpackage your custom data from the DragDataSource. The DragDataSource provides you access to the data you stored in the DragDataSink.

# Controlling Where Display Objects can be Dropped
The meaning of a drag/drop operation is defined by the context of the operation. The application developer must decide where the various types of display objects can be dropped.

By creating an object that implements the iDropSite interface, you can define what can be dropped on a display object. If a display object is a drop site, assign your custom drop site object to its DropSite property. When display objects are dragged over the drop site, the framework will call into your custom DropSite object to learn if the dragged objects can be dropped.

The CDisplayView class also has a virtual method that you can override to tell the framework if particular display objects can be dropped on the "whitespace" in the display view.
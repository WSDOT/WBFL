Factories {#WBFL_COGO_Factories}
============

All of the collection objects in the WBFL COGO library create instances of the items that they contain. To make this method of creation flexible, the collections use factory objects. The job of a factory object is to &quot;manufacture&quot; or create a new instance of an object. The collections can create custom versions of objects if they are supplied with a custom factory.

The COGO Model and COGO Engine objects also create geometric items and use factory objects to do so.
 
You can define your own factory objects to create customized versions of the geometric items.

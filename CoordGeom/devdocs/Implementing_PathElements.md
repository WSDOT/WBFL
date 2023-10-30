# Implementing PathElement objects{#WBFL_COGO_Implementing_path_element_objects}
`PathElement` is an abstract class that forms the basis for the geometric elements that make up `Alignment` and `Path` objects. Typical path elements are linear segments and horizontal curves.

The most common path elements are already implemented in this library. If in the future, new path elements are needed, this topic will help developers understand the requirements for implementing a `PathElement` subclass.

The basic requirements are:
1. Concrete path element classes must inherit from the `PathElement` abstract base class.
2. The base class manages the parent `Path` object in \ref WBFL_COGO_Parent_Child. When a path element is added to an `Alignment` or `Path`, it's `SetPath()` is called. Your path element can access it's parent path with the `GetPath()` method.
3. Path element constructors must be private to enforce the requirement they must be created on the heap and managed as `std::shared_ptr<>` in their \ref WBFL_COGO_Parent_Child. Use factory methods to create class instances.
4. All of the pure virtual methods defined in `PathElement` must be implemented. Use the `PathElement::AdjustOffset()` function in the implementation of `LocatePoint()`. See previously implemented `LocatePoint()` methods for examples.
5. All methods that modify the geometry of a path element must call `PathElement::OnPathElementChanged()`. This method signals to the parent `Alignment` or `Path` object that any cached information must be updated. Examples are parameter setting method of your class, such as `MyPathElement::SetStartPoint(p)`, and your implementation of the `Move()` and `Offset()` methods.

> NOTE: If new path elements are created, the `Model` class and `PathElementType` enumeration class will likely need updating as well. The `Model` class will need a container for the new path element type and the `Model::CreateAlignment` and `Model::CreatePath` methods will need new code to create instances of the new path element type.
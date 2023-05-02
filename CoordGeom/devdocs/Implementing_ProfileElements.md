# Implementing ProfileElement objects{#WBFL_COGO_Implementing_profile_element_objects}

`ProfileElement` is an abstract class that forms the basis for the geometric elements that make up `Profile` objects. Typical profile elements are linear segments and vertical curves.

The most common profile elements are already implemented in this library. If in the future, new profile elements are needed, this topic will help developers understand the requirements for implementing a `ProfileElement` subclass.

The basic requirements are:
1. Concrete profile element classes must inherit from the `ProfileElement` abstract base class.
2. The base class manages the parent `Profile` object in \ref WBFL_COGO_Parent_Child. When a profile element is added to a `Profile`, it's `SetProfile()` is called. Your profile element can access it's parent profile with the `GetProfile()` method.
3. Profile element constructors must be private to enforce the requirement they must be created on the heap and managed as `std::shared_ptr<>` in their \ref WBFL_COGO_Parent_Child. Use factory methods to create class instances.
4. All of the pure virtual methods defined in `ProfileElement` must be implemented. 
5. All methods that modify the geometry of a profile element must call `ProfileElement::OnProfileElementChanged()`. This method signals to the parent `Profile` object that any cached information must be updated. Examples are parameter setting method of your class, such as `MyProfileElement::SetStartPoint(p)`.

> NOTE: If new profile elements are created, the `Model` class and `ProfileElementType` enumeration class will likely need updating as well. The `Model` class will need a container for the new profile element type and the `Model::CreateProfile` method will need new code to create instances of the new profile element type.
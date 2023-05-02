# Parent Child Relationships {#WBFL_COGO_Parent_Child}

There are parent-child relationships between many objects in this library. An example is `Alignment` is parent to `Profile`. That is to say, `Alignment` objects own `Profile` objects.

Child objects generally need access to their parent object. `Profile` needs to know which `Alignment` object it is related to so it can call `Alignment` methods.

From an implementation persepctive, `Alignment` needs a pointer to the `Profile` objects it owns and `Profile` needs a pointer to it's parent `Alignment`. This creates a circular reference. Using `std::shared_ptr<>` in both `Alignment` and `Profile` results in memory leaks. `Alignment` cannot be deleted until all of its `Profile` objects release their `std::shared_ptr<Alignment>` pointer which will not happoen until the `Alignment` releases its `std::shared_ptr<Profile>` pointers. So, in the end, the `Alignment` and `Profile` objects are never deleted.

To prevent the memory leaks, the parent class has `std::shared_ptr<>` ojbects for its child classes and the child class has a `std::weak_ptr<>` to the parent class. In order for the parent class to provide the child class with a weak pointer to itself, the parent class must inherit from `std::enable_shared_from_this<>` and all instances of the parent class object must be created as a `std::shared_ptr<>`.

To enforce the required that parent class objects must be created as a `std::shared_ptr<>` the parent class' constructors are made private and static factory methods are defined. The factory methods force the object to be created on the heap and be managed by a `std::shared_ptr<>` object.

The following example shows how the `Alignment` and `Profile` objects are created and associated with one another.

~~~
auto alignment = Alignment::Create(); // creates a std::shared_ptr<Alignment>
auto profile = Profile::Create(); // creates a std::shared_ptr<Profile>
IDType ID = 10; // the profile ID for later look ups

alignment.AddProfile(ID,profile); 
// internally the alignment object calls profile->SetAlignment(weak_from_this()); to create the parent-child association and provide Profile with a weak pointer to itself
~~~

To prevent clients of this library from assigning random `Alignment` objects to `Profile` objects, `Profile::SetAlignment()` is a private method. The only way `Alignment` can call a private method of the `Profile` class is to be a friend class. However, this opens up all of the protected and private methods of `Profile` to `Alignment`. This is generally undesirable. The \ref WBFL_COGO_pImpl_Idiom is used in this library to remedy the undesired side effects of the friend class declaration.

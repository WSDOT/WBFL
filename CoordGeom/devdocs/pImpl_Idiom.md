# pImpl Idiom {#WBFL_COGO_pImpl_Idiom}

This topic describes how and why the *pImpl* idiom is used in this library. It does not describe what the *pImpl* idiom is or how to implement it. See the Implementation Notes section of the main WBFL Implementor's Documentation for a general description of the *pImpl* idiom.

## When to use the pImpl idiom in this library
The *pImpl* idiom is used in the implementation of several classes in this library. Specifically, use the *pImpl* idiom when creating classes that have a friend class.

## Why is the pImpl idiom used in this library
In C++ friend classes can access all of the protected and private data members and functions of a class. There are cases in this library where the friend relationship needs to be restricted to very specific functions. The *pImpl* idiom allows the methods that the friend class should not have access to be hidden in the implementation object.

## Usage example
As an example, the *pImpl* idiom is used in the `Alignment` and `Profile` classes. `Alignment` needs to call the private method `Profile::SetAligment` (see \ref WBFL_COGO_Parent_Child) but `Alignment` should not have access to any other private methods or data of `Profile`. The `Profile` class uses the `ProfileImpl` class for it's implementation. The `ProfileImpl` class has private methods which are not accessible to `Alignment`. This prevents `Alignment` from altering `Profile` in unintended ways.
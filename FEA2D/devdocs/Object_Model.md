# Object Model {#WBFL_FEA2D_Object_Model}

The following diagram shows the high-level relationships between the classes in FEA2D. It's worth keeping close at hand when working with the engine.

```mermaid
classDiagram
    Model "1" *-- "0..*" Joint : owns
    Model "1" *-- "0..*" Member : owns
    Model "1" *-- "0..*" Loading : owns
    Model "1" *-- "0..*" POI : owns
    Loading "1" *-- "0..*" JointLoad : owns
    Loading "1" *-- "0..*" JointDisplacement : owns
    Loading "1" *-- "0..*" PointLoad : owns
    Loading "1" *-- "0..*" DistributedLoad : owns
    Loading "1" *-- "0..*" MemberStrain : owns
    Member ..> Joint : refers to by ID\n(start/end)
    POI ..> Member : refers to by ID
    JointLoad ..> Joint : refers to by ID
    JointDisplacement ..> Joint : refers to by ID
    PointLoad ..> Member : refers to by ID
    DistributedLoad ..> Member : refers to by ID
    MemberStrain ..> Member : refers to by ID
```

Every joint, member, loading, and load is created through - and owned by - the object above it in this diagram (see @ref WBFL_FEA2D_Using_this_library); nothing but `Model` is ever created directly. A `Member` refers to its start and end `Joint` by ID rather than owning them, since a `Joint` is typically shared by more than one member - the same by-ID reference pattern is used everywhere else a load needs to point at the joint or member it's applied to.

# On-Demand Computation {#WBFL_FEA2D_On_Demand_Computation}

If you have browsed `WBFL::FEA2D::Model`'s public interface, you'll have noticed there is no `Analyze()` or `Solve()` method. The engine performs analysis only on an as-needed basis. A basic flow for client code looks like this:

@image html ModelBuildingProcess.gif

The basic idea is that you can request results at any time, and the engine automatically brings itself up to date first if it needs to. You must, of course, first build a valid model and apply loads to it before asking for results.

## How this works

Every `ComputeXxx` result method on `Model` (`ComputeJointDeflections`, `ComputeMemberForces`, `ComputePOIDeflections`, etc.) calls an internal `EnsureAnalyzed()` step first:

* If the structure changed since the last analysis (a joint, member, or release was added, removed, or modified), the global stiffness matrix `[K]` is re-factored.
* Regardless of whether the structure changed, only the load cases (`Loading`s) whose loads actually changed since they were last solved are re-solved. Because `[K][d]=[F]`, `[K]` only needs factoring once per structural change - every `Loading` after that is a cheap back-substitution against the already-factored matrix, not a full re-factorization.
* Everything else is served from a cache.

This means the cost of calling a `ComputeXxx` method depends only on what's actually stale, not on how many joints, members, or load cases the model has accumulated. Building a large model with many load cases and only asking for results from one of them is cheap; it's not necessary (or possible) to defer analysis into a single explicit call the way you might with a batch solver.

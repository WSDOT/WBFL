Solution Method and Sign Convention {#WBFL_RCSection_SolutionMethod}
========================================================
WBFL::RCSection::MomentCapacitySolver::Solve() (and everything built on top of it - MomentCurvatureSolver, AxialInteractionCurveSolver, MomentInteractionCurveSolver) varies the location of the neutral axis until the resultant internal force equals the externally applied axial force `Fz`. The `SolutionMethod` parameter controls what stays fixed while that search happens.

Solution Method
----------------
WBFL::RCSection::MomentCapacitySolver::SolutionMethod has four values:

* **FixedCurvature** - the curvature (`k_or_ec`) of the section is held fixed. The solver searches for the strain at the neutral axis reference line that satisfies equilibrium. This is what MomentCurvatureSolver uses internally, stepping curvature from zero until a material strain limit is exceeded.
* **FixedCompressionStrain** - the strain (`k_or_ec`) at the extreme compression fiber is held fixed (typically the material's crushing strain, e.g. -0.003).
* **FixedTensionStrain** - the strain (`k_or_ec`) at the extreme tension fiber is held fixed (typically a material's rupture or crack-localization strain).
* **FixedStrain** - the strain `k_or_ec` is held fixed at a specific location in the section, given by `strainLocation` (the perpendicular distance from a line through (0,0) parallel to the neutral axis). This is the most general case - useful, for example, when checking capacity at the strain corresponding to 0.80fy in a particular layer of reinforcement.

`FixedCompressionStrain` and `FixedTensionStrain` are convenience cases of `FixedStrain` where the location is implicitly the extreme compression or tension fiber of the section.

Sign Convention
----------------
The location of the neutral axis is varied until the resultant internal force is equal to the external force `Fz`. Compression is assumed to be on the left side of the neutral axis. For typical bending about the X-axis, use a neutral axis angle of 0.0 for positive moment (compression top - tension bottom) and PI (180 deg) for negative moment (tension top - compression bottom).

"Positive moments" (compression top - tension bottom) have **negative** values. The resultant compression force (C) is negative and the resultant tension force (T) is positive. At equilibrium, `T + C = 0`, so `C = -T`.

Assume the point (0,0) is at the bottom of the girder. The resultant tension and compression forces act at `Yt` and `Yc`, respectively, with `Yc > Yt > 0`. Therefore:
\f[ M_n = C \cdot Y_c + T \cdot Y_t = -T \cdot Y_c + T \cdot Y_t = T \cdot (Y_t - Y_c) \f]
Since `Yc > Yt`, `(Yt - Yc) < 0`, and `T > 0`, the product is negative - confirming "negative moments" (tension top - compression bottom) have **positive** values.

This inverted convention is easy to trip over when writing new code against this library - a positive-moment (sagging) capacity check will produce a negative `Mn`.

Capacity Limits
-----------------
`FixedCompressionStrain` and `FixedTensionStrain` (and, indirectly, the interaction-curve solvers) rely on the section's tension and compression capacity limits - the force/moment state at zero curvature (uniform strain) in pure tension or pure compression, respectively. These are exposed via WBFL::RCSection::MomentCapacitySolver::GetTensionLimit() and WBFL::RCSection::MomentCapacitySolver::GetCompressionLimit(), each returning a WBFL::RCSection::CapacityLimit. A target `Fz` outside this range cannot be solved and results in an XRCSection being thrown.

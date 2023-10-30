Slice Growth Factor {#WBFL_RCSection_SliceGrowthFactor}
========================================================
GeneralSection objects are discretized into fiber based "slices". Slice heights do not need to be uniform. Comptational efficiency can be gained, without loss of accuracy, using larger slices in areas where a material stress-strain model is constant.

For a conventional reinforced concrete section model, it is advantagous to have thinner slices in the compression region and wider (and thus fewer) slices in the tension region because the tension region does not contribute to capacity.

The slice growth factor causes the height of each slice will get progressively larger (or smaller) over the depth of the section. The slices heights are such that the height of the last slice is a multiple of the height of the first slice. The slice heights vary linearly.

* \f$H\f$ = overall height of the section
* \f$N\f$ = number of slices
* \f$g\f$ = slice growth factor (less than 1 slices get thinner, greater than 1 slices get wider, equal to 1 all slices are the same height)
* \f$h_i\f$ = height of the \f$i^{th}\f$ slice
* \f$h_0\f$ = height of the first slice

The height of the first slice is
\f[ h_0 = \frac{H}{N + \left(\frac{g-1}{N-1}\right)\frac{(N-1)^2 + (N-1)}{2}} \f]

The height of all subsequent slices are
\f[ h_i = \left[1 + \left(\frac{g-1}{N-1}\right)i \right]h_0 \f]
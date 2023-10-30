Stability {#WBFL_Stability}
===========================
The WBFL Stability Library lateral stability analysis utilities for precast-prestressed concrete girders.

Stability analysis is based on "Recommended Practice for Lateral Stability of Precast, Prestressed Concrete Bridge Girders", 1st Edition, PCI, CB-02-16-E.

The Stability library can analyze hanging girders, seated girders, and girders seated at one end.

Unit Tests
==========
The Stability unit tests may fail due to the WBFLFem2d library. The WBFLFem2d library is used to perform structural analysis.

The WBFLFem2d library is a COM library and the components must be registered to create instances at runtime. If there are failed unit tests in the StabilityUnitTests project, select the WBFLFem2d project in the Solution Explorer, then select Tools > RegSvr to register the COM components.

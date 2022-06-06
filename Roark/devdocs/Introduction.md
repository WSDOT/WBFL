WBFL Roark Beams {#WBFL_Beams}
========================
The WBFL Roark Beams Library provides structural analysis services for simple beams.

Many of the beams in this library are based on "Formulas For Stress and Strain 4th Edition R.J. Roark", Table III pp 104-113

Class Naming Convension:
      Class Names are of the form [C|P|F][C|P|F]{loadtype}
	  
      where :
	  
      [C|P|F] = Cantilever, Pinned, or Fixed end support
      the first one is for the left support and the second for the right
      support.
	  
      {loadtype} can be EndLoad, IntermediateLoad,UniformLoad,PartUniformLoad,
      LeftTriangle,PartLeftTriangle,RightTriangle,PartRightTriangle,
      EndCouple,IntermediateCouple,CenterLoad, or CenterCouple

      Example:  PFRightTriangle - Pinned-Fixed beam with a right triangle load. See Loading 25.
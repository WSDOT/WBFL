# Performance {#WBFL_FEA2D_Performance}

FEA2D is designed to be a lightweight, efficient component. There are a couple of things worth thinking about to get the best performance out of it.

## Joint Numbering

The engine uses a banded-Cholesky based solver and does not optimize bandwidth prior to solution. This means it's up to the client program to create models with as little bandwidth as possible: the goal is to minimize the maximum difference between joint IDs across the members in the model. Joint numbering matters; member numbering does not.

Here is an example of a structure using a poor joint numbering scheme:

@image html NodeNumberingBad.gif

And the same model with an optimal joint numbering scheme:

@image html NodeNumberingGood.gif

## Use POIs Instead of Joints for Capturing Results

There are two ways to get force and displacement results at a given location in a `Member`: place a `Joint` there, or place a `POI` there. As the numbering example above illustrates, every `Joint` you add increases the bandwidth of the system matrix and slows the solution. Getting results at a `POI` is much cheaper than adding a `Joint` for the same purpose - the only reason to prefer a `Joint` is if you already need one there for another reason (e.g. it's a real connection point in the structure).

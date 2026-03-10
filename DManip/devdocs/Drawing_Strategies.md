# Drawing Strategies {#drawing_strategies}

The DManip framework has very few display object types. Basic display objects such as Point and Line do most of the work.

When a Display Object draws itself on the screen, it uses a Drawing Strategy. This is an implementation of the Strategy pattern. 

The drawing strategy objects provide a customizable means to create application specific renderings of display objects.

There are a few pre-build drawing strategies for lines and points. There are line drawing stratigies the can draw a line as a rectangle or parallellogram. There are point drawing strategies that can draw a point as a target symbol, simple circle or square, or a complex polygon shape.
# Writing Numeric Expressions in Number-Line Order {#WBFL_Number_Line_Order}

Organize numeric tests so that they follow the points on a numberline. In general, structure your numeric tests so that you have comparisons line

~~~
MinElmts <= i && i <= MaxElmts
i < MinElmts || MaxElmts < i
~~~

The idea is to order the elements left to right, from smallest to largest. In the first line, _MinElmts_ and _MaxElmts_ are the two endpoints, so they go at the ends. The variable _i_ is supposed to be between them, so it goes in the middle. In the second example, you're testing whether _i_ is ouside the range, so _i_ goes on the outside of the test at either end and _MinElmts_ and _MaxElmts_ go on the inside. This approach maps easily to a visual image of the comparison.

![](NumberLineVisualization.png)

If you're testing _i_ against MinElmts only, the position of _i_ varies depending on where _i_ is when the test is successful. If _i_ is supposed to be smaller, you'll have a test like

~~~
while ( i < MinElmts) ...
~~~

But if _i_ is supposed to be larger, you'll have a test like

~~~
while (MinElmts < i) ...
~~~

This approach is clearer than tests like

~~~
i < MinElmts && MaxElmts < i
~~~

which give the reader no help in visualizing what is being tested.

See Code Complete, Steve McConnell, Microsoft Press, pp376-377

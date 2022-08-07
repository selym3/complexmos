# complexmos

Complex function graphing calculator built with Dear ImGui

## Plotting Modes

There are two visualizers for complex functions. Each visualizer uses the function specified by `f(z) =` in the settings widget.

### Color Plot

![color plot](images/color-plot.png)

The color plot mode will treat points on the graph as complex numbers and plug them into the complex function specified by `f` in the settings widget. The magntiude and argument of the output of `f(z)` will be plotted as a color by using the `HSV` color format, where the argument is the hue and the magnitude is the value (colors are always fully saturated).

The `max magntiude` settings can scale down the brightness of the graph.

### Graph

![graph](images/graph.png)

The graph mode will plot a circle with a radius specified by `radius` on a 2D complex plane. It will take some number of evenly-spaced points on the circle (specified by `points`) and plug them into `f`. The output of the circle after being plugged into `f` will also be plotted.

This mode is like looking at a slice of the graph, so even though complex functions require 4-Dimensions to view fully, this mode fits on a 2D comlpex plane.

## To Implement

* pan / zoom for Color Plot
* determine + color where function goes off to infinity in Color Plot
* automatically determine what a good value of max magntiude is in Color Plot
* add performance options in Color Plot

# Drawing rectangles

[Next](https://github.com/jptr218/jui/blob/main/man/input.md)
###
[Previous](https://github.com/jptr218/jui/blob/main/man/text.md)

Since a window with just text is also boring, let's add some color to it. We can start by adding the following line before the `deploy()` function is called:
```
w.strokeRect(20, 20, 100, 100, jui_color(40, 200, 200));    //Draw a rectangle
```

However, you might not want just an out line of a rectangle. Maybe you want a full rectangle? Well in that case, add this line before the `deploy()` function is called:
```
w.fillRect(20, 20, 100, 100, jui_color(40, 200, 200));      //Fills a rectangle
```
Next chapter, we will start using JUI's input system.

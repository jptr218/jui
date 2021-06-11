# Drawing rectangles

[next]("https://google.com")
[previous]("https://google.com")

If you've followed the previous chapter, you should have a blank window. Since blank windows are boring, let's add some life to it. We can start by adding the following line before the `deploy()` function is called:
```
w.strokeRect(20, 20, 100, 100, jui_color(40, 200, 200));    //Draw a rectangle
```

However, you might not want just an out line of a rectangle. Maybe you want a full rectangle? Well in that case, add this line before the `deploy()` function is called:
```
w.fillRect(20, 20, 100, 100, jui_color(40, 200, 200));      //Fills a rectangle
```

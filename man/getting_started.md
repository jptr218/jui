# Getting started

[Next](https://github.com/jptr218/jui/blob/main/man/drawing_rectangles.md)

In order to create your first ever JUI application, you will need to set the correct Visual Studio c++ paths. To do this, **right click on your project, select properties -> VC++ directories, and set the include path and the library path to the folder extracted from the ZIP**.

Once you have done that, you can start writing your code. Start off by opening a new jui_window object:
```
#include <jui.h>        //Use JUI interface
using namespace jui;

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);    //Hide console window
    jui_window w("Getting started with JUI");   //Create jui window
}
```

The code above won't actually do much. In order to get your window to display properly, you need to **deploy it**. Add the following line to do that:
```
w.deploy();                                 //Deploy window
```
Asuming you've setup the library correctly, you should get a new blank window appear on your screen. Next tutorial, we will start drawing onto it.

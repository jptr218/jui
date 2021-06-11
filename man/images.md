# Drawing images

[Next](https://github.com/jptr218/jui/blob/main/man/overview.md)
###
[Previous](https://github.com/jptr218/jui/blob/main/man/input.md)

In order to start drawing images onto your JUI window, you must first [create a resources file](https://docs.microsoft.com/en-us/cpp/windows/how-to-create-a-resource-script-file?view=msvc-160). Once you have that set up with the image/s you would like to draw, you can use the following code to draw them:
```
#include <jui.h>        //Use JUI interface
#include "resource.h"   //Use resources header
using namespace jui;

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);                         //Hide console window

    jui_window w("Getting started with JUI");                        //Create window
    w.image(MAKEINTRESOURCEA(YOUR_IMAGE_HERE), 20, 20, 100, 100);    //Draw image
    w.deploy();                                                      //Deploy window
}
```
And with just those few lines of code, you can start rendering images to your JUI window! In the final chapter, there is an overview over all the functions and types JUI offers.

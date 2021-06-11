# Getting input

[Next](https://google.com)
###
[Previous](https://github.com/jptr218/jui/blob/main/man/drawing_rectangles.md)

The 3 main ways of capturing user input in JUI are:
- buttons
- textboxes
- dropdowns

Let's start with buttons. To capture button presses, use the following code:
```
#include <jui.h>        //Use JUI interface
using namespace jui;

void buttonHandler(int args) {
    MessageBoxA(NULL, "You pressed the button!", "Getting started with JUI", NULL); //Display message when button pressed
}

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);                    //Hide console window

    jui_window w("Getting started with JUI");                   //Create window
    jui_elem button = w.button("Click me!", 20, 20, 100, 30);   //Create a button
    w.onEvent(button, buttonHandler);                           //Set the button handler
    w.deploy();                                                 //Deploy window
}
```

As useful as buttons might be, they aren't enough to create a functioning UI. So, let's use this code to get textboxes and dropdowns:

```
#include <jui.h>        //Use JUI interface
using namespace jui;

jui_window w("Getting started with JUI");                       //Create window
jui_elem textBox;
jui_elem dropdown;

void buttonHandler(int args) {
    const char* textVal = w.getTextBoxVal(textBox);      //Retrieve value of textbox
    const char* dropDwnVal = w.getDropdownVal(dropdown); //Retrieve value of dropdown

    MessageBoxA(NULL,("You entered " + std::string(textVal) + " and " + dropDwnVal + "!").c_str(), "Getting started with JUI", NULL); //Display message
}

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);                    //Hide console window

    //Initialize dropdown options:
    const char* dropDwnOpts[5] = { "One", "Two", "Three", "Four", "Five" };

    textBox = w.textbox("Text input", 15, 20, 150, 30);          //Create a textbox
    dropdown = w.dropdown(dropDwnOpts, 5, 185, 20, 200, 30);     //Create a dropdown
    jui_elem button = w.button("Get inputs", 15, 70, 100, 30);    //Create a button
    w.onEvent(button, buttonHandler);                            //Set the button handler
    w.deploy();                                                  //Deploy window
}
```

In the next chapter, we will start drawing images to the window.

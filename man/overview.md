# JUI overview

[Previous](https://github.com/jptr218/jui/blob/main/man/images.md)

## All types:
```
jui_color(r, g, b);                                                                                 //Used to specify colors
jui_arg(int i, const char* s);                                                                      //Used behind the scenes to process user commands
jui_instruction();                                                                                  //Also used behind the scenes to process user commands
jui_window(const char* wname, int wtype, RECT wrect, COLORREF bg, HICON icon, HCURSOR cursor);      //Used to create windows
```

## All functions:
```
void setErrorMode(int mode);                                                                            //Used to set the current level of error reporting
void jui_window::deploy();                                                                              //Used to deploy a JUI window
void jui_window::close();                                                                               //Used to close a JUI window
void jui_window::strokeRect(int x, int y, int width, int height, jui_color color);                      //Used to draw the outline of a rectangle
void jui_window::fillRect(int x, int y, int width, int height, jui_color color);                        //Used to fill a rectangle
void jui_window::clear();                                                                               //Used to clear a window
jui_elem jui_window::button(const char* text, int x, int y, int width, int height);                     //Used to draw a button
void jui_window::text(const char* v, int x, int y, int size, const char* font);                         //Used to draw text
jui_elem jui_window::textbox(const char* pHolder, int x, int y, int width, int height);                 //Used to create textboxes
jui_elem jui_window::dropdown(const char** opts, int oLen, int x, int y, int width, int itmHeight);     //Used to create dropdowns
void jui_window::image(const char* img, int x, int y, int width, int height);                           //Used to draw images
void jui_window::onEvent(jui_elem e, jui_cb cb, int forceSet = 0);                                      //Used to set event handlers
char* jui_window::getTextBoxVal(jui_elem e);                                                            //Used to get values of textboxes
char* jui_window::getDropdownVal(jui_elem e);                                                           //Used to get values of dropdowns
```

## All constants:
```
#define JUI_WINDOW_NORMAL 0       ----
#define JUI_WINDOW_FULLSCREEN 1       |         
#define JUI_WINDOW_MINIMIZED 2        |       
#define JUI_WINDOW_STATIC 3           |-----  Used to specify the desired type of window
#define JUI_WINDOW_BLANK 4            |   
#define JUI_WINDOW_HIDDEN 5           |    
#define JUI_WINDOW_INVALID 6      -----     

#define JUI_ERRORS_NONE 0   ---|___    Used to specify the level of error reporting
#define JUI_ERRORS_ALL 1    ---|
```

#include <Windows.h>
#include <iostream>
#include <vector>
#include <functional>

#define JUI_WINDOW_NORMAL 0
#define JUI_WINDOW_FULLSCREEN 1
#define JUI_WINDOW_MINIMIZED 2
#define JUI_WINDOW_STATIC 3
#define JUI_WINDOW_BLANK 4
#define JUI_WINDOW_HIDDEN 5
#define JUI_WINDOW_INVALID 6

#define JUI_INSTRUCTION_STROKERECT 0
#define JUI_INSTRUCTION_FILLRECT 1
#define JUI_INSTRUCTION_CLS 2
#define JUI_INSTRUCTION_BUTTON 3
#define JUI_INSTRUCTION_TEXT 4
#define JUI_INSTRUCTION_TEXTBOX 5
#define JUI_INSTRUCTION_DROPDOWN 6
#define JUI_INSTRUCTION_IMG 7

#define JUI_ERRORS_NONE 0
#define JUI_ERRORS_ALL 1

#define jui_cb std::function<void(int)>
#define jui_elem int

namespace jui {
    void error(std::string message);

    struct jui_color {
        int r;
        int g;
        int b;
    };

    struct jui_arg {
        int i;
        const char* s;
        jui_arg(int ii = NULL, const char* ss = NULL) {
            i = ii;
            s = ss;
        }
    };

    struct jui_instruction {
        int op;
        std::vector<jui_arg> args;
    };

    class jui_window {
        public:
            const char* name;
            int type;
            HWND hwnd;
            RECT rect;
            COLORREF bg;
            std::vector<jui_instruction> jui_drawbuf;

            std::vector<HWND> buttons;
            std::vector<HWND> textboxes;
            std::vector<HWND> dropdowns;

            static std::vector<jui_cb> eCbs;

            jui_window(const char* wname, int wtype = JUI_WINDOW_NORMAL, RECT wrect = { 500, 500, 800, 800 }, COLORREF bg = RGB(255, 255, 255), HICON icon = NULL, HCURSOR cursor = LoadCursor(nullptr, IDC_ARROW));
            void strokeRect(int x, int y, int width, int height, jui_color color);
            void fillRect(int x, int y, int width, int height, jui_color color);
            void clear();
            jui_elem button(const char* text, int x, int y, int width, int height);
            void text(const char* v, int x, int y, int size, const char* font);
            jui_elem textbox(const char* pHolder, int x, int y, int width, int height);
            jui_elem dropdown(const char** opts, int oLen, int x, int y, int width, int itmHeight);
            void image(const char* img, int x, int y, int width, int height);
            void deploy();
            void close();
            void closeAllWindows();
            void onEvent(jui_elem e, jui_cb cb, int forceSet = 0);
            char* getTextBoxVal(jui_elem e);
            char* getDropdownVal(jui_elem e);
            static LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    };

    void setErrorMode(int mode);
}

extern jui::jui_window* cWin;
extern int wLen;
extern std::vector<std::pair<jui_elem, jui_cb>> eQueue;
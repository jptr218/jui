#include "pch.h"
#include "jui.h"

using namespace std;

void jui::jui_window::strokeRect(int x, int y, int width, int height, jui_color color) {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_STROKERECT;

    vector<jui::jui_arg> a;
    a.push_back(jui_arg(x));
    a.push_back(jui_arg(y));
    a.push_back(jui_arg(width));
    a.push_back(jui_arg(height));
    a.push_back(jui_arg(color.r));
    a.push_back(jui_arg(color.g));
    a.push_back(jui_arg(color.b));

    i.args = a;
    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);
}

void jui::jui_window::fillRect(int x, int y, int width, int height, jui_color color) {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_FILLRECT;

    vector<jui::jui_arg> a;
    a.push_back(jui_arg(x));
    a.push_back(jui_arg(y));
    a.push_back(jui_arg(width));
    a.push_back(jui_arg(height));
    a.push_back(jui_arg(color.r));
    a.push_back(jui_arg(color.g));
    a.push_back(jui_arg(color.b));

    i.args = a;
    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);
}

void jui::jui_window::clear() {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_CLS;

    vector<jui::jui_arg> a;
    i.args = a;

    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);
}

jui_elem jui::jui_window::button(const char* text, int x, int y, int width, int height) {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_BUTTON;

    vector<jui::jui_arg> a;
    a.push_back(jui_arg(0, text));
    a.push_back(jui_arg(x));
    a.push_back(jui_arg(y));
    a.push_back(jui_arg(width));
    a.push_back(jui_arg(height));
    i.args = a;

    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);

    int id = wLen;
    wLen++;
    return id;
}

void jui::jui_window::text(const char* v, int x, int y, int size, const char* font) {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_TEXT;

    vector<jui::jui_arg> a;
    a.push_back(jui_arg(0, v));
    a.push_back(jui_arg(x));
    a.push_back(jui_arg(y));
    a.push_back(jui_arg(size));
    a.push_back(jui_arg(0, font));
    i.args = a;

    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);
}

jui_elem jui::jui_window::textbox(const char* pHolder, int x, int y, int width, int height) {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_TEXTBOX;

    vector<jui::jui_arg> a;
    a.push_back(jui_arg(0, pHolder));
    a.push_back(jui_arg(x));
    a.push_back(jui_arg(y));
    a.push_back(jui_arg(width));
    a.push_back(jui_arg(height));
    i.args = a;

    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);

    int id = wLen;
    wLen++;
    return id;
}

jui_elem jui::jui_window::dropdown(const char** opts, int oLen, int x, int y, int width, int itmHeight) {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_DROPDOWN;

    vector<jui::jui_arg> a;
    a.push_back(jui_arg(oLen));
    for (int j = 0; j < oLen; j++) {
        a.push_back(jui_arg(0, opts[j]));
    }
    a.push_back(jui_arg(x));
    a.push_back(jui_arg(y));
    a.push_back(jui_arg(width));
    a.push_back(jui_arg(itmHeight));
    i.args = a;

    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);

    int id = wLen;
    wLen++;
    return id;
}

void jui::jui_window::image(const char* img, int x, int y, int width, int height) {
    jui::jui_instruction i;
    i.op = JUI_INSTRUCTION_IMG;

    vector<jui::jui_arg> a;
    a.push_back(jui_arg(0, img));
    a.push_back(jui_arg(x));
    a.push_back(jui_arg(y));
    a.push_back(jui_arg(width));
    a.push_back(jui_arg(height));
    i.args = a;

    jui_drawbuf.push_back(i);
    UpdateWindow(hwnd);
}

void jui::jui_window::onEvent(jui_elem e, jui_cb cb, int forceSet) {
    if (eCbs.size() > 0 || forceSet) {
        eCbs[e] = cb;
    }
    else {
        eQueue.push_back(pair<jui_elem, jui_cb>(e, cb));
    }
}

char* jui::jui_window::getTextBoxVal(jui_elem e) {
    char* o = new char[MAX_PATH];
    GetDlgItemTextA(hwnd, e, o, MAX_PATH);
    return o;
}

char* jui::jui_window::getDropdownVal(jui_elem e) {
    return getTextBoxVal(e);
}
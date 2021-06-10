#include "pch.h"
#include "jui.h"

using namespace std;

jui::jui_window* cWin;
int wLen;
std::vector<std::pair<jui_elem, jui_cb>> eQueue;

int eMode = JUI_ERRORS_ALL;
vector<jui_cb> jui::jui_window::eCbs = vector<jui_cb>();

void jui::setErrorMode(int mode) {
    eMode = mode;
}

void jui::error(string message) {
    if (eMode == JUI_ERRORS_ALL) {
        MessageBoxA(NULL, message.c_str(), "JUI", MB_ICONERROR);
    }
}

LPCWSTR getWstr(const char* str)
{
    int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, str, strlen(str), NULL, 0);
    if (bufferlen == 0)
    {
        return 0;
    }
    LPWSTR widestr = new WCHAR[bufferlen + 1];
    ::MultiByteToWideChar(CP_ACP, 0, str, strlen(str), widestr, bufferlen);
    widestr[bufferlen] = 0;
    return widestr;
}

jui::jui_window::jui_window(const char* wname, int wtype, RECT wrect, COLORREF wbg, HICON icon, HCURSOR cursor) {
    if (cWin != nullptr) {
        error("You cannot create multiple windows.");
        return;
    }else if (type > 5) {
        error("Invalid window type");
        return;
    }

    wLen = 0;
    name = wname;
    type = wtype;
    rect = wrect;
    bg = wbg;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = jui::jui_window::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = NULL;
    wcex.hCursor = cursor;
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(bg);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = getWstr(wname);
    wcex.hIconSm = icon;
    RegisterClassExW(&wcex);

    cWin = this;
}

void jui::jui_window::deploy() {
    DWORD cwArgs = WS_OVERLAPPEDWINDOW;
    switch (type) {
        case JUI_WINDOW_FULLSCREEN:
            cwArgs = WS_MAXIMIZE | WS_CAPTION;
        case JUI_WINDOW_MINIMIZED:
            cwArgs = WS_MINIMIZE | WS_CAPTION;
        case JUI_WINDOW_STATIC:
            cwArgs = WS_SYSMENU | WS_CAPTION;
        case JUI_WINDOW_BLANK:
            cwArgs = 0;
    }

    hwnd = CreateWindowW(getWstr(name), getWstr(name), cwArgs, 800, 400, 400, 400, nullptr, nullptr, GetModuleHandle(NULL), nullptr);
    if (!hwnd)
    {
        error("Failed to create window");
        type = JUI_WINDOW_INVALID;
        return;
    }

    switch (type) {
        case JUI_WINDOW_MINIMIZED:
            ShowWindow(hwnd, 11);
        case JUI_WINDOW_HIDDEN:
            ShowWindow(hwnd, 0);
        default:
            ShowWindow(hwnd, 1);
    }
    UpdateWindow(hwnd);

    for (pair<jui_elem, jui_cb> eH : eQueue) {
        onEvent(eH.first, eH.second, 1);
    }

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void jui::jui_window::closeAllWindows() {
    for (HWND h : buttons) {
        DestroyWindow(hwnd);
    }
    for (HWND h : textboxes) {
        DestroyWindow(hwnd);
    }
    for (HWND h : dropdowns) {
        DestroyWindow(hwnd);
    }
}

void jui::jui_window::close() {
    closeAllWindows();
    CloseWindow(hwnd);
    cWin = NULL;
}
#include "pch.h"
#include "jui.h"

void draw(jui::jui_window* w) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(w->hwnd, &ps);
    HFONT f;
    BITMAP bm;
    HDC hdcMem;
    HBITMAP hBm;
    HGDIOBJ oBm;

    for (jui::jui_instruction i : w->jui_drawbuf) {
        RECT r;
        switch (i.op) {
        case JUI_INSTRUCTION_STROKERECT:
            r = { i.args[0].i, i.args[1].i, i.args[0].i + i.args[2].i, i.args[1].i + i.args[3].i };
            FrameRect(hdc, &r, CreateSolidBrush(RGB(i.args[4].i, i.args[5].i, i.args[6].i)));
            break;
        case JUI_INSTRUCTION_FILLRECT:
            r = { i.args[0].i, i.args[1].i, i.args[0].i + i.args[2].i, i.args[1].i + i.args[3].i };
            FillRect(hdc, &r, CreateSolidBrush(RGB(i.args[4].i, i.args[5].i, i.args[6].i)));
            break;
        case JUI_INSTRUCTION_CLS:
            r = { 0, 0, w->rect.right, w->rect.bottom };
            FillRect(hdc, &r, CreateSolidBrush(w->bg));

            w->closeAllWindows();
            w->buttons.clear();
            w->textboxes.clear();
            w->dropdowns.clear();
            break;
        case JUI_INSTRUCTION_BUTTON:
            w->buttons.push_back(CreateWindowA("button", i.args[0].s, WS_VISIBLE | WS_CHILD, i.args[1].i, i.args[2].i, i.args[3].i, i.args[4].i, w->hwnd, (HMENU)w->eCbs.size(), NULL, NULL));
            w->eCbs.push_back(NULL);
            break;
        case JUI_INSTRUCTION_TEXT:
            f = CreateFontA(i.args[3].i, (float)i.args[3].i * (float)0.55, 0, 0, FW_DONTCARE, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, i.args[4].s);
            r = { i.args[1].i, i.args[2].i, w->rect.bottom - i.args[1].i, w->rect.right - i.args[2].i };
            SelectObject(hdc, f);
            DrawTextA(hdc, i.args[0].s, strlen(i.args[0].s), &r, DT_LEFT | DT_TOP);
            break;
        case JUI_INSTRUCTION_TEXTBOX:
            w->textboxes.push_back(CreateWindowA("Edit", i.args[0].s, WS_VISIBLE | WS_CHILD, i.args[1].i, i.args[2].i, i.args[3].i, i.args[4].i, w->hwnd, (HMENU)w->eCbs.size(), NULL, NULL));
            w->eCbs.push_back(NULL);
            r = { i.args[1].i - 1, i.args[2].i - 1, i.args[1].i + i.args[3].i + 1, i.args[2].i + i.args[4].i + 1 };
            FrameRect(hdc, &r, CreateSolidBrush(BLACK_BRUSH));
            break;
        case JUI_INSTRUCTION_DROPDOWN:
            w->dropdowns.push_back(CreateWindowA("COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD, i.args[i.args[0].i + 1].i, i.args[i.args[0].i + 2].i, i.args[i.args[0].i + 3].i, w->rect.bottom - i.args[i.args[0].i + 2].i, w->hwnd, (HMENU)w->eCbs.size(), NULL, NULL));
            w->eCbs.push_back(NULL);
            SendMessageA(w->dropdowns[w->dropdowns.size() - 1], CB_SETITEMHEIGHT, (WPARAM)0, (LPARAM)i.args[i.args[0].i + 4].i);
            for (int j = 0; j < i.args[0].i; j++) {
                SendMessageA(w->dropdowns[w->dropdowns.size() - 1], CB_ADDSTRING, (WPARAM)0, (LPARAM)i.args[j + 1].s);
            }
            SendMessageA(w->dropdowns[w->dropdowns.size() - 1], CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
            break;
        case JUI_INSTRUCTION_IMG:
            hdcMem = CreateCompatibleDC(hdc);
            if ((hBm = LoadBitmapA(GetModuleHandle(NULL), i.args[0].s)) == NULL) {
                jui::error("The specified image could not be found.");
            }
            oBm = SelectObject(hdcMem, hBm);

            GetObject(hBm, sizeof(bm), &bm);
            BitBlt(hdc, i.args[1].i, i.args[2].i, i.args[3].i, i.args[4].i, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, oBm);
            DeleteDC(hdcMem);
            break;
        }
    }

    EndPaint(w->hwnd, &ps);
}

LRESULT __stdcall jui::jui_window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_PAINT:
            draw(cWin);
            break;
        case WM_COMMAND:
            switch (HIWORD(wParam)) {
                case BN_CLICKED:
                    if (eCbs[wParam] != NULL) {
                        eCbs[wParam](0);
                    }
                    break;
            default:
                break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
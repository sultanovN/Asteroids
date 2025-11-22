#define WIN32_LEAN_AND_MEAN
#include "Engine.h"
#include "TinkerWindows.h"
//#include <windows.h>
#include <stdlib.h>
#include <assert.h>

uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] = { 0 };

void PixelDraw(int x, int y, uint32_t Color)
{
    buffer[y][x] = Color;
}

void PixelDraw(int x, int y, Color c)
{
    buffer[y][x] = c.fullColor;
}

void DrawRectangle(float LocationX, float LocationY, float SizeX, float SizeY, uint32_t Color)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            if ((x >= LocationX && (x <= LocationX + SizeX)) && (y >= LocationY && (y <= LocationY + SizeY)))
            {
                PixelDraw(x, y, Color);
            }
        }
}

void DrawSprite(int x, int y, const Surface& s, Color Chroma)
{
    const int width = s.GetWidth();
    const int height = s.GetHeight();
    if (0 <= x < SCREEN_WIDTH && 0 <= y < SCREEN_HEIGHT)
    {
        for (int sx = 0; sx < width; sx++)
            for (int sy = 0; sy < height; sy++)
            {
                if (!(s.GetPixel(sx, sy).fullColor == Chroma.fullColor))
                {
                    PixelDraw(x + sx, y + sy, s.GetPixel(sx, sy));
                }
            }
    }
}
 
void DrawSprite(int x, int y, const Entity& ent, const Surface& s, Color Chroma)
{
    /*assert(ent.GetLocation().X >= 0);
    assert(ent.GetLocation().X + ent.GetSize().X <= ent.GetSize().X);
    assert(ent.GetLocation().Y >= 0);
    assert(ent.GetLocation().Y + ent.GetSize().Y <= ent.GetSize().Y);*/
    for (int sx = ent.GetLocation().X; sx < ent.GetLocation().X + ent.GetSize().X; sx++)
        for (int sy = ent.GetLocation().Y; sy < ent.GetLocation().Y + ent.GetSize().Y; sy++)
        {
            if (!(s.GetPixel(sx, sy).fullColor == Chroma.fullColor))
            {
                PixelDraw(x + sx - ent.GetLocation().X, y + sy - ent.GetLocation().Y, s.GetPixel(sx, sy));
            }
        }
}

void DrawSpriteNonChroma(int x, int y, const Surface& s)
{
    const int width = s.GetWidth();
    const int height = s.GetHeight();
    for (int sx = 0; sx < width; sx++)
        for (int sy = 0; sy < height; sy++)
        {
            PixelDraw(x + sx, y + sy, s.GetPixel(sx, sy));
        }
}

void DrawSpriteNonChroma(int x, int y, const Entity& ent, const Surface& s)
{
    assert(ent.GetLocation().X >= 0);
    assert(ent.GetLocation().X + ent.GetSize().X <= ent.GetSize().X);
    assert(ent.GetLocation().Y >= 0);
    assert(ent.GetLocation().Y + ent.GetSize().Y <= ent.GetSize().Y);
    for (int sx = ent.GetLocation().X; sx < ent.GetLocation().X + ent.GetSize().X; sx++)
        for (int sy = ent.GetLocation().Y; sy < ent.GetLocation().Y + ent.GetSize().Y; sy++)
        {
            PixelDraw(x + sx - ent.GetSize().X, y + sy - ent.GetSize().Y, s.GetPixel(sx, sy));
        }
}

const char* GameWindowName = "Space Shooter";

static HINSTANCE hinst = 0;
static DWORD ticks = 0;
static bool is_active = true;
static POINT cursor_pos;
static bool quited = false;
static LARGE_INTEGER qpc_frequency = { 0 };
static LARGE_INTEGER qpc_ref_time = { 0 };

bool is_window_active()
{
    return is_active;
}

void clear_buffer()
{
    memset(buffer, 0, sizeof(buffer));
}

bool is_key_pressed(int button_vk_code)
{
    return is_active && (GetAsyncKeyState(button_vk_code) & 0x8000);
}

bool is_mouse_button_pressed(int mouse_button_index)
{
    if (!is_active)
        return false;

    if (mouse_button_index == 0)
        return GetAsyncKeyState(VK_LBUTTON) != 0;

    if (mouse_button_index == 1)
        return GetAsyncKeyState(VK_RBUTTON) != 0;

    return false;
}

int get_cursor_x()
{
    return cursor_pos.x;
}

int get_cursor_y()
{
    return cursor_pos.y;
}

void schedule_quit_game()
{
    quited = true;
}

static void CALLBACK update_proc(HWND hwnd)
{
    if (quited)
        return;

    is_active = GetActiveWindow() == hwnd;

    GetCursorPos(&cursor_pos);
    ScreenToClient(hwnd, &cursor_pos);

    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);

    float dt = float((unsigned long)(t.QuadPart - qpc_ref_time.QuadPart)) / qpc_frequency.QuadPart;
    if (dt > 0.1f)
        dt = 0.1f;

    act(dt);

    if (!quited)
    {
        draw();
        RedrawWindow(hwnd, NULL, 0, RDW_INVALIDATE | RDW_UPDATENOW);
    }

    qpc_ref_time = t;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        BITMAPINFOHEADER bih;
        bih.biSize = sizeof(bih);
        bih.biWidth = SCREEN_WIDTH;
        bih.biHeight = -SCREEN_HEIGHT;
        bih.biPlanes = 1;
        bih.biBitCount = 32;
        bih.biCompression = BI_RGB;
        bih.biSizeImage = 0;
        bih.biXPelsPerMeter = 96;
        bih.biYPelsPerMeter = 96;
        bih.biClrUsed = 0;
        bih.biClrImportant = 0;
        SetDIBitsToDevice(
            hdc,
            0, 0,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            0, 0,
            0, SCREEN_HEIGHT,
            buffer,
            (BITMAPINFO*)&bih,
            DIB_RGB_COLORS);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_QUIT:
    case WM_DESTROY:
        quited = true;
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    SetProcessDPIAware();
    hinst = hInstance;
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = "GameTemplateWndClass";
    wcex.hIconSm = 0;
    RegisterClassExA(&wcex);

    RECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = SCREEN_WIDTH;
    rect.bottom = SCREEN_HEIGHT;
    AdjustWindowRectEx(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE, 0);

    HWND hwnd = CreateWindowA(wcex.lpszClassName, GameWindowName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    QueryPerformanceFrequency(&qpc_frequency);
    QueryPerformanceCounter(&qpc_ref_time);

    ticks = GetTickCount();
    initialize();

    MSG msg;
    while (!quited)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        update_proc(hwnd);
        Sleep(0);
    }

    finalize();

    return (int)msg.wParam;
}

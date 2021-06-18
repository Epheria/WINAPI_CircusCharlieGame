// WINAPI_DoubleBuffering.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#pragma comment(lib, "msimg32.lib")
#include "framework.h"
#include "WINAPI_DoubleBuffering.h"
#include "GameManager.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void DoubleBuffer(HWND hWnd, HDC hdc);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIDOUBLEBUFFERING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MoveWindow(g_hWnd, 0, 0, 1200, 700, true);
    HDC hdc = GetDC(g_hWnd);
    BitMapManager::GetInstance()->Init(g_hWnd);
    GameManager::GetInstance()->InitPlayer(g_hWnd);
    GameManager::GetInstance()->InitMap(g_hWnd);


    MOVE_STATUS tmp = MOVE_IDLE;
    int x = 0;
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    LONGLONG checkTime, limitTime = GetTickCount64();
    float time = 0;
    int iCheck = 1;
    GameManager::GetInstance()->DrawMap(hdc);

    // 게임 루프.
    while (WM_QUIT != msg.message)
    {

        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            checkTime = GetTickCount64();
            if (limitTime <= checkTime)
            {
                float deltaTime = (checkTime - limitTime) * 0.01f;
                limitTime = checkTime + 10;

                if (GetAsyncKeyState(VK_RIGHT))
                {
                    x = 100 * deltaTime;
                    iCheck = 1;
                    GameManager::GetInstance()->GetPlayer()->UpdatePosX(x);
                }
                else if (GetAsyncKeyState(VK_LEFT))
                {
                    x = 100 * deltaTime;
                    iCheck = -1;
                    GameManager::GetInstance()->GetPlayer()->UpdatePosX(-x);
                }
                else
                    iCheck = 0;

                time += deltaTime;
                if (0.3f <= time)
                {
                    time = 0;
                    switch (tmp)
                    {
                    case MOVE_IDLE:
                        if (iCheck == 1) tmp = MOVE_FRONT;
                        else if (iCheck == -1) tmp = MOVE_BACK;
                        else
                            tmp = MOVE_IDLE;
                        break;
                    default:
                        tmp = MOVE_IDLE;
                    }
                }
                GameManager::GetInstance()->GetPlayer()->UpdateStatus(tmp);

                DoubleBuffer(g_hWnd, hdc);
            }
        }
    }

    //DeleteObject();
    //DeleteObject();
    ReleaseDC(g_hWnd, hdc);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIDOUBLEBUFFERING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIDOUBLEBUFFERING);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = g_hWnd = CreateWindowW(szWindowClass, L"Circus Charlie Game", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height)
{
    BITMAPINFO bm_info;
    ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
    bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bm_info.bmiHeader.biBitCount = 24;
    bm_info.bmiHeader.biWidth = width;
    bm_info.bmiHeader.biHeight = height;
    bm_info.bmiHeader.biPlanes = 1;

    LPVOID pBits;
    return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}

void DoubleBuffer(HWND hWnd, HDC hdc)
{
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);

    HDC backDC = CreateCompatibleDC(hdc);
    HBITMAP backBitmap = CreateDIBSectionRe(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
    HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);

    //HDC memDC = CreateCompatibleDC(hdc);
    //HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, GameManager::GetInstance()->GetPlayer()->GetPlayerImage(Index));
    //TransparentBlt(backDC, 100 + GameManager::GetInstance()->GetPlayer()->GetPosX(), 100, 66, 63, memDC, 0, 0, 66, 63, RGB(255, 0, 255));
    //SelectObject(memDC, oldBitmap);

    GameManager::GetInstance()->GetPlayer()->Draw(backDC);

    //DeleteDC(memDC);
    BitBlt(hdc, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, backDC, 0, 0, SRCCOPY);
    SelectObject(backDC, oldBack);
    DeleteObject(backBitmap);
    DeleteObject(backDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
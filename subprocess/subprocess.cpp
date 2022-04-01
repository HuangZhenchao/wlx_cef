// subprocess.cpp : 定义应用程序的入口点。
//

#include "../wlx_cef/stdafx.h"
#include "MyApp.h"
#include "subprocess.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    // TODO: 在此处放置代码。

    // 初始化全局字符串
    // Structure for passing command-line arguments.
  // The definition of this structure is platform-specific.
  // 传递命令行参数的结构体。
  // 这个结构体的定义与平台相关。
    CefMainArgs main_args(hInstance);

    // Optional implementation of the CefApp interface.
    // 可选择性地实现CefApp接口
    //CefRefPtr<MyApp> app(new MyApp);
    // Execute the sub-process logic. This will block until the sub-process should exit.
    // 执行子进程逻辑，此时会堵塞直到子进程退出。
    int exit_code=CefExecuteProcess(main_args, nullptr, nullptr);
    //CefRefPtr<CefCommandLine> commandLine = CefCommandLine::CreateCommandLine();
    //commandLine->InitFromString(::GetCommandLineW());
    //MessageBox(NULL, commandLine->GetCommandLineString().c_str(), TEXT("subprocess"), MB_OK);
    return exit_code;
}





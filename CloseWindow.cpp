/*---------------------------向指定窗体发送关闭消息-------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int main()
{
    
    //获取窗口句柄
    HWND hWnd = ::FindWindow(NULL,_T("计算器"));
    
    printf("%p\n",hWnd);
    if( hWnd != NULL)
    {
        printf("%d\n",hWnd);
        ::SendMessage(hWnd,WM_CLOSE,0,0);
        return 6;
    }
    return 0;
}
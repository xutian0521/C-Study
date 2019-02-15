/*---------------------------获取和设置鼠标位置-------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int main()
{
    
    //获取窗口句柄
	HWND windowHwnd=FindWindow (NULL, _T("植物大战僵尸中文版") ) ;
	RECT r;

	//获取窗口位置信息
	::GetWindowRect(windowHwnd ,&r);
	printf("x=%d\ny=%d",r.left,r.top);
	system("cls");

	POINT p;
	//获取鼠标位置
	::GetCursorPos(&p);
	printf("%d\n%d\n",p.x,p.y);
	system("cls");
	//设置鼠标位置
	::SetCursorPos(0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    return 0;
}
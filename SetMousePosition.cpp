/*---------------------------��ȡ���������λ��-------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int main()
{
    
    //��ȡ���ھ��
	HWND windowHwnd=FindWindow (NULL, _T("ֲ���ս��ʬ���İ�") ) ;
	RECT r;

	//��ȡ����λ����Ϣ
	::GetWindowRect(windowHwnd ,&r);
	printf("x=%d\ny=%d",r.left,r.top);
	system("cls");

	POINT p;
	//��ȡ���λ��
	::GetCursorPos(&p);
	printf("%d\n%d\n",p.x,p.y);
	system("cls");
	//�������λ��
	::SetCursorPos(0,0);
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
    return 0;
}
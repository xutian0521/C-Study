/*---------------------------��ָ�����巢�͹ر���Ϣ-------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int main()
{
    
    //��ȡ���ھ��
    HWND hWnd = ::FindWindow(NULL,_T("������"));
    
    printf("%p\n",hWnd);
    if( hWnd != NULL)
    {
        printf("%d\n",hWnd);
        ::SendMessage(hWnd,WM_CLOSE,0,0);
        return 6;
    }
    return 0;
}
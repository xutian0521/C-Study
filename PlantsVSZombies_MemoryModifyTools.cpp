/*---------------------------ֲ���ս��ʬ�ڴ��޸���-------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
int main()
{

	int sun;
	int sun1;
	int money;
	int money1;
	
	//��ȡ���ھ��
	HWND WindowH=::FindWindow(NULL,_T("ֲ���ս��ʬ���İ�"));

	//�ж���Ϸ�Ƿ�����
	if (!WindowH)
	{
		printf("��Ϸ��û�п��������ֿ�����Ϸ��");
		Sleep(5000);
		
		exit(0);
	}

	//��ȡ����id
	DWORD processId;
	GetWindowThreadProcessId(WindowH,&processId);

	//�򿪽��̣���ý��̶�дȨ��
	::HANDLE processH=OpenProcess(PROCESS_ALL_ACCESS,false,processId);

	//��ȡ�����ֵ
	::DWORD byread,bywrite,money_read,money_write;
	::LPCVOID pbase=(::LPCVOID)6987456;
	::LPVOID rbuffer=(::LPVOID)&sun;
	::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	pbase=(::LPCVOID)(sun+1896);
	::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	pbase=(::LPCVOID)(sun+21856);
	::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	printf("����%d\n",sun);
	
	//��ȡǮ��ֵ
	::LPCVOID pbase1=(::LPCVOID)6987456;
	::LPVOID rbuffer1=(::LPVOID)&money;
	::ReadProcessMemory(processH,pbase1,rbuffer1,4,&money_read);
	pbase1=(::LPCVOID)(money+2092);
	::ReadProcessMemory(processH,pbase1,rbuffer1,4,&money_read);
	pbase1=(::LPCVOID)(money+40);
	::ReadProcessMemory(processH,pbase1,rbuffer1,4,&money_read);
	printf("Ǯ%d\n",money*10);

	//��ʾ�û�����
	printf("��������� Ǯ��ֵ�ÿո������\n");
	scanf("%d%d",&sun1,&money1);
	money1=money1/10;

	//д�������ֵ
	::LPVOID wbuffer=(::LPVOID)&sun1;
	::WriteProcessMemory(processH,(::LPVOID)pbase,wbuffer,4,&bywrite);

	//д��Ǯ��ֵ
	::LPVOID wbuffer1=(::LPVOID)&money1;
	::WriteProcessMemory(processH,(::LPVOID)pbase1,wbuffer1,4,&money_write);
	
	return 0;
}
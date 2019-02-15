/*---------------------------植物大战僵尸内存修改器-------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
int main()
{

	int sun;
	int sun1;
	int money;
	int money1;
	
	//获取窗口句柄
	HWND WindowH=::FindWindow(NULL,_T("植物大战僵尸中文版"));

	//判断游戏是否运行
	if (!WindowH)
	{
		printf("游戏还没有开启，请现开启游戏！");
		Sleep(5000);
		
		exit(0);
	}

	//获取进程id
	DWORD processId;
	GetWindowThreadProcessId(WindowH,&processId);

	//打开进程，获得进程读写权限
	::HANDLE processH=OpenProcess(PROCESS_ALL_ACCESS,false,processId);

	//读取阳光的值
	::DWORD byread,bywrite,money_read,money_write;
	::LPCVOID pbase=(::LPCVOID)6987456;
	::LPVOID rbuffer=(::LPVOID)&sun;
	::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	pbase=(::LPCVOID)(sun+1896);
	::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	pbase=(::LPCVOID)(sun+21856);
	::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	printf("阳光%d\n",sun);
	
	//读取钱的值
	::LPCVOID pbase1=(::LPCVOID)6987456;
	::LPVOID rbuffer1=(::LPVOID)&money;
	::ReadProcessMemory(processH,pbase1,rbuffer1,4,&money_read);
	pbase1=(::LPCVOID)(money+2092);
	::ReadProcessMemory(processH,pbase1,rbuffer1,4,&money_read);
	pbase1=(::LPCVOID)(money+40);
	::ReadProcessMemory(processH,pbase1,rbuffer1,4,&money_read);
	printf("钱%d\n",money*10);

	//提示用户输入
	printf("输入阳光和 钱的值用空格键隔开\n");
	scanf("%d%d",&sun1,&money1);
	money1=money1/10;

	//写入阳光的值
	::LPVOID wbuffer=(::LPVOID)&sun1;
	::WriteProcessMemory(processH,(::LPVOID)pbase,wbuffer,4,&bywrite);

	//写入钱的值
	::LPVOID wbuffer1=(::LPVOID)&money1;
	::WriteProcessMemory(processH,(::LPVOID)pbase1,wbuffer1,4,&money_write);
	
	return 0;
}
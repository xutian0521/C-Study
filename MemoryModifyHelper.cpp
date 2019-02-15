/*---------------------------内存修改器帮助类库-------------------------------*/

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

class MemoryModifyHelper //一个修改游戏内存的类
{
	int readval;
	LPCVOID pbase;//用来储存要修改内存地址的指针

	public:	HANDLE processH; //用来储存要修改的进程句柄
	public: void OpenGame(char gamename[40])
	{
		//获取窗口句柄
		HWND WindowH=::FindWindow(NULL, gamename);

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

		//打开进程，获得进程读写权限，并获得进程句柄
		processH=OpenProcess(PROCESS_ALL_ACCESS,false,processId);
	}
		//读取进程内存的方法 （重载1）
	public:int ReadMemory(int base,int offset1,int offset2,int offset3)
	{
		::DWORD byread;
		pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset1);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset2);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset3);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		
	
			return readval;
	   }
	   //（重载2）
	public :int ReadMemory(int base,int offset1,int offset2)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset1);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset2);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);

		return readval;
		}
		//（重载3）
	public:int ReadMemory(int base,int offset1)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset1);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);

		return readval;
	}
	//（重载4）
	public:int ReadMemory(int base)
	{
		::DWORD byread;
		pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	
		return readval;
	}
	//获取当前要读写的内存地址偏移后的地址（重载1）
	//即取得当前游戏的（阳光）值动态内存地址
	public :int* ReadMemorybase(int base,int offset1,int offset2)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset1);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset2);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		
		return (int *)pbase;
	}
	//（重载2）
	public :int* ReadMemorybase(int base,int offset1)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset1);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	
		return (int *)pbase;
	}
	//（重载3）
	public :int* ReadMemorybase(int base)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		
		return (int *)pbase;
	}
	//写入进程内存
	public:void WriteMemory(int Write,LPCVOID base)
	{
		DWORD bywrite;
		::LPVOID wbuffer=(::LPVOID)&Write;
		::WriteProcessMemory(processH,(::LPVOID)base,wbuffer,4,&bywrite);
	}


};
//unit test
int main()
{
	MemoryModifyHelper plugin;
	
	char gamename[40]="植物大战僵尸中文版"; //定义字符串储存游戏窗体标题
	plugin.OpenGame(gamename);				//打开游戏
	HANDLE processH=plugin.processH;		//用plugin的processH类取得进程句柄
	
	int sun= plugin.ReadMemory(6987456,1896,21856);//读取阳光的值
	printf("阳光%d\n",sun);
	int money=plugin.ReadMemory(6987456,2092,40);//读取钱的值
	printf("钱%d\n",money*10);
	//提示用户输入
	printf("输入阳光和 钱的值用空格键隔开\n");
	scanf("%d%d",&sun,&money);//获取用户输入int值
	money=money/10;

	int *sunbase= plugin.ReadMemorybase(6987456,1896,21856);//取得当前游戏的阳光值动态内存地址
	plugin.WriteMemory(sun,(::LPCVOID)sunbase);//写入阳光值
	int *moneybase=plugin.ReadMemorybase(6987456,2092,40);//取得当前游戏的钱值动态内存地址
	plugin.WriteMemory(money,(::LPCVOID)moneybase);//写入钱的值

/*

	int sun;
	int sun1;
	int money;
	int money1;
	//获取窗口句柄
	HWND WindowH=::FindWindow(NULL,"植物大战僵尸中文版");

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
*/
    return 0;
}
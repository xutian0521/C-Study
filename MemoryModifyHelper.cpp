/*---------------------------�ڴ��޸����������-------------------------------*/

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

class MemoryModifyHelper //һ���޸���Ϸ�ڴ����
{
	int readval;
	LPCVOID pbase;//��������Ҫ�޸��ڴ��ַ��ָ��

	public:	HANDLE processH; //��������Ҫ�޸ĵĽ��̾��
	public: void OpenGame(char gamename[40])
	{
		//��ȡ���ھ��
		HWND WindowH=::FindWindow(NULL, gamename);

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

		//�򿪽��̣���ý��̶�дȨ�ޣ�����ý��̾��
		processH=OpenProcess(PROCESS_ALL_ACCESS,false,processId);
	}
		//��ȡ�����ڴ�ķ��� ������1��
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
	   //������2��
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
		//������3��
	public:int ReadMemory(int base,int offset1)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset1);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);

		return readval;
	}
	//������4��
	public:int ReadMemory(int base)
	{
		::DWORD byread;
		pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	
		return readval;
	}
	//��ȡ��ǰҪ��д���ڴ��ַƫ�ƺ�ĵ�ַ������1��
	//��ȡ�õ�ǰ��Ϸ�ģ����⣩ֵ��̬�ڴ��ַ
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
	//������2��
	public :int* ReadMemorybase(int base,int offset1)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		pbase=(::LPCVOID)(readval+offset1);
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
	
		return (int *)pbase;
	}
	//������3��
	public :int* ReadMemorybase(int base)
	{
		::DWORD byread;pbase=(::LPCVOID)base;
		::LPVOID rbuffer=(::LPVOID)&readval;
		::ReadProcessMemory(processH,pbase,rbuffer,4,&byread);
		
		return (int *)pbase;
	}
	//д������ڴ�
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
	
	char gamename[40]="ֲ���ս��ʬ���İ�"; //�����ַ���������Ϸ�������
	plugin.OpenGame(gamename);				//����Ϸ
	HANDLE processH=plugin.processH;		//��plugin��processH��ȡ�ý��̾��
	
	int sun= plugin.ReadMemory(6987456,1896,21856);//��ȡ�����ֵ
	printf("����%d\n",sun);
	int money=plugin.ReadMemory(6987456,2092,40);//��ȡǮ��ֵ
	printf("Ǯ%d\n",money*10);
	//��ʾ�û�����
	printf("��������� Ǯ��ֵ�ÿո������\n");
	scanf("%d%d",&sun,&money);//��ȡ�û�����intֵ
	money=money/10;

	int *sunbase= plugin.ReadMemorybase(6987456,1896,21856);//ȡ�õ�ǰ��Ϸ������ֵ��̬�ڴ��ַ
	plugin.WriteMemory(sun,(::LPCVOID)sunbase);//д������ֵ
	int *moneybase=plugin.ReadMemorybase(6987456,2092,40);//ȡ�õ�ǰ��Ϸ��Ǯֵ��̬�ڴ��ַ
	plugin.WriteMemory(money,(::LPCVOID)moneybase);//д��Ǯ��ֵ

/*

	int sun;
	int sun1;
	int money;
	int money1;
	//��ȡ���ھ��
	HWND WindowH=::FindWindow(NULL,"ֲ���ս��ʬ���İ�");

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
*/
    return 0;
}
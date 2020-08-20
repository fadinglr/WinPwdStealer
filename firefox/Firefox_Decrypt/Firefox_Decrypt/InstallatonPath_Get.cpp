#include"Firefox_decrypt.h"
#define MY_BUFSIZE 128 // Arbitrary initial value.
// Dynamic allocation will be used.

constexpr auto Get_failed = "get_InstallationPath Failed";
// ͨ��ע����ȡ����İ�װ·��
string getInstallationPath(){
	HKEY hKey;
	TCHAR szProductType[MY_BUFSIZE];
	DWORD dwBufLen = MY_BUFSIZE;
	LONG lRet;
	// �����Ǵ�ע���, ֻ�д򿪺��������������
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, // Ҫ�򿪵ĸ���
		TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\firefox.exe"), // Ҫ�򿪵����Ӽ�������汾67.0.4 (x64 zh-CN)��
		0, // ���һ��ҪΪ0
		KEY_QUERY_VALUE,	// ָ���򿪷�ʽ,��Ϊ��
		//KEY_QUERY_VALUE|KEY_WOW64_64KEY, // 32λ�����Ҫ��ȡ64λ��ע�����Ҫ�ڴ򿪼�ʱ����Ӳ���KEY_WOW64_64KEY
		&hKey); // �������ؾ��
	if (lRet == ERROR_SUCCESS) // �ж��Ƿ�򿪳ɹ�
	{
		// ��ע���ɹ�
		// ��ʼ��ѯ
		lRet = RegQueryValueEx(hKey, // ��ע���ʱ���صľ��
			TEXT("Path"), //Ҫ��ѯ������,�����װĿ¼��¼������
			NULL, // һ��ΪNULL����0
			NULL,
			(LPBYTE)szProductType, // ����Ҫ�Ķ�����������
			&dwBufLen);
		if (lRet == ERROR_SUCCESS) // �ж��Ƿ��ѯ�ɹ�
		{
			RegCloseKey(hKey);
			printf("dir -> %s\n", (char*)szProductType);
			return (char*)szProductType;
		}
		else
		{
			printf("��ð�װĿ¼ʧ��\n");
			return Get_failed;
		}
	}
	else {
		printf("��ע���ʧ��\n");
		return Get_failed;
	}
}
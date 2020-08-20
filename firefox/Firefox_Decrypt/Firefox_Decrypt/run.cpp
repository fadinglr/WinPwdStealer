#include"Firefox_decrypt.h"
#include<regex>

int main() {
	string installationPath = getInstallationPath();	// ��ȡFirefox�İ�װ·����ͨ��ע���
	HMODULE lib = loadLibrary(installationPath);	// ��̬����nss��(Network Security Services)(���簲ȫ����)�����ض�̬���ӿ��ļ�nss.dll������ģ����
	if (lib == NULL)	// ģ����Ϊ�գ���̬����ʧ��
		return -1;
	dllFunction(lib);	// ��ȡnss���еȻ���Ҫ�õ��ķ���
	string profilePath = getProfilePath();	// ��ȡFirefox�����¼��Ϣ(�û���������)���ļ�logins.json��·��
	SECStatus s = NSS_Init(profilePath.c_str());	// ��ʼ��NSS��
	if (s != SECSuccess) {
		printf("Error when initialization!\n");
	}
	string loginStrings = getBuffer(profilePath);	// ��ȡlogins.json�б���ĵ�¼��Ϣ
	// ������ʽƥ��
	std::regex reHostname("\"hostname\":\"([^\"]+)\"");
	std::regex reUsername("\"encryptedUsername\":\"([^\"]+)\"");
	std::regex rePassword("\"encryptedPassword\":\"([^\"]+)\"");
	std::smatch match;
	string::const_iterator searchStart(loginStrings.cbegin());	// ѭ������
	while (std::regex_search(searchStart, loginStrings.cend(), match, reHostname)) {
		printf("Host\t: %s \n", U2G(match.str(1).c_str()));
		std::regex_search(searchStart, loginStrings.cend(), match, reUsername);
		printf("Username: %s \n", U2G((const char*)decrypt(match.str(1))));	// decrypt�û�����ת�����
		std::regex_search(searchStart, loginStrings.cend(), match, rePassword);
		printf("Password: %s \n", U2G((const char*)decrypt(match.str(1))));	// decrypt���벢ת�����
		searchStart += match.position() + match.length();
		printf("-----------------------------------------\n");
	}
	NSS_Shutdown();	// �ر�NSS��
	//system("PAUSE");
	return 0;
}
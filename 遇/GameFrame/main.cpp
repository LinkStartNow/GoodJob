#include "GameFrame.h"
#include<windowsx.h>

CGameFrame* pGame = nullptr;

extern int wndWidth;
extern int wndHeight;
extern int wndPosX;
extern int wndPosY;
extern const TCHAR* wndTitle;

// ��Ϸ���� �ڻص������д���
// hwnd�����ھ��
// uMsg����ϢID ��Ч�� msg.message
// wParam�� lParam����ϢЯ������Ϣ�������ڼ��̰��µ�����£��жϰ��µ���a����b
LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (pGame->m_MsgMap.count(uMsg)) { // �����ϢID��ӳ����д���
		switch (pGame->m_MsgMap[uMsg].MsgType) {
		case EX_MOUSE: { // case ����һ�㲻�üӴ����ţ������ﲻ�Ӵ����ŵĻ����ܻ�������ʼ��������Ҫ��һ��
			// ���������Ϣ
			// ��ȡ�����
			POINT po{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_MOUSE)(po);
			break;
		}
		case EX_KEY: {
			// ���������Ϣ
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_KEY)(wParam);
			break;
		}
		case EX_CHAR: {
			// �����ַ���Ϣ
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_CHAR)(wParam);
			break;
		}
		case EX_WINDOW: {
			// ��������Ϣ
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_WINDOW)(wParam, lParam);
		}
		}

		// ���»��ƴ��ڣ�����֤��ʱˢ��
		// ������Ӧ���ֶ�����WM_PAINT
		RECT rect{ 0, 0, 600, 600 };
		::InvalidateRect(pGame->m_hWnd, // ����Ч��Ŀ�괰��
			&rect, // ����Ч�Ĵ��ڲ���
			false);

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam); // ���ڲ����ĵ���Ϣ����windowĬ�ϵĴ�����ȥ����
}

int main()
{
	CGameFrame* CreateObject(); // ��������
	pGame = CreateObject();
	//pGame = new CGameFrame;
	//pGame = new CAA;

	// ��ʼ������
	pGame->InitGame(wndWidth, wndHeight, wndPosX, wndPosY, wndTitle);

	while (!pGame->GetQuit()) {
		Sleep(1000); // ��ͣһ��
	}

	puts("�ѳɹ��˳���");
	//pGame->RunMyGame(); // ��Ϊ�ص���������


	// ����
	delete pGame;
	pGame = nullptr;
}
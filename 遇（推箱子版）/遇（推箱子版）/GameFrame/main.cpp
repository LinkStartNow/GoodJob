#include "GameFrame.h"
#include<windowsx.h>

CGameFrame* pGame = nullptr;

extern int wndWidth;
extern int wndHeight;
extern int wndPosX;
extern int wndPosY;
extern const TCHAR* wndTitle;

// 游戏运行 在回调函数中处理
// hwnd：窗口句柄
// uMsg：消息ID 等效于 msg.message
// wParam， lParam：消息携带的信息，比如在键盘按下的情况下，判断按下的是a还是b
LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (pGame->m_MsgMap.count(uMsg)) { // 如果消息ID在映射表中存在
		switch (pGame->m_MsgMap[uMsg].MsgType) {
		case EX_MOUSE: { // case 里面一般不用加大括号，但这里不加大括号的话可能会跳过初始化，所以要加一个
			// 处理鼠标信息
			// 获取坐标点
			POINT po{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_MOUSE)(po);
			break;
		}
		case EX_KEY: {
			// 处理键盘信息
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_KEY)(wParam);
			break;
		}
		case EX_CHAR: {
			// 处理字符信息
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_CHAR)(wParam);
			break;
		}
		case EX_WINDOW: {
			// 处理窗口信息
			(pGame->*pGame->m_MsgMap[uMsg].MsgFunEX_WINDOW)(wParam, lParam);
		}
		}

		// 重新绘制窗口，来保证及时刷新
		// 在这里应当手动触发WM_PAINT
		RECT rect{ 0, 0, 600, 600 };
		::InvalidateRect(pGame->m_hWnd, // 将无效的目标窗口
			&rect, // 将无效的窗口部分
			false);

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam); // 对于不关心的消息，由window默认的处理函数去处理
}

int main()
{
	CGameFrame* CreateObject(); // 函数声明
	pGame = CreateObject();
	//pGame = new CGameFrame;
	//pGame = new CAA;

	// 初始化窗口
	pGame->InitGame(wndWidth, wndHeight, wndPosX, wndPosY, wndTitle);

	while (!pGame->GetQuit()) {
		Sleep(1000); // 暂停一秒
	}

	puts("已成功退出！");
	//pGame->RunMyGame(); // 改为回调函数处理


	// 回收
	delete pGame;
	pGame = nullptr;
}
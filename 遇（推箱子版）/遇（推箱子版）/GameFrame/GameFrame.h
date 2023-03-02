#pragma once

#include <iostream>
#include <Windows.h>
#include <easyx.h>
#include <map>

using namespace std;

LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

// Ϊ�˱��ڶ���map�����ĺ�
#define INIT_MSGMAP(MSGID, MSGTYPE)\
	m_MsgMap[MSGID].MsgType = MSGTYPE;\
	m_MsgMap[MSGID].MsgFun##MSGTYPE = &CGameFrame::ON_##MSGID;

class CGameFrame
{
	// friend��������Ԫ�Ĺؼ��֣���RunGame ������CGameFrame�����ѣ�������RunGame�п���ʹ��CCgameFrame�е�˽�г�Ա
	friend LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

protected:
	HWND m_hWnd; // �����н������ܻ��õ������Ե��趨�ɱ�����
	// ���ھ����ͨ���ñ������ܶ�λ���ô���

private:
	bool m_isQuit;

	typedef void (CGameFrame::* P_FUN_EX_MOUSE)(POINT&);
	typedef void (CGameFrame::* P_FUN_EX_KEY)(WPARAM&);
	typedef void (CGameFrame::* P_FUN_EX_CHAR)(WPARAM&);
	typedef void (CGameFrame::* P_FUN_EX_WINDOW)(WPARAM&, LPARAM&);

	struct Type_Fun
	{
		int MsgType; // ��Ϣ����
		union
		{
			P_FUN_EX_MOUSE MsgFunEX_MOUSE; // �����Ϣ���Ͷ�Ӧ�Ĵ�����ָ��
			P_FUN_EX_KEY MsgFunEX_KEY; // ������Ϣ���Ͷ�Ӧ�Ĵ�����ָ��
			P_FUN_EX_CHAR MsgFunEX_CHAR; // �ַ���Ϣ���Ͷ�Ӧ�Ĵ�����ָ��
			P_FUN_EX_WINDOW MsgFunEX_WINDOW; // ������Ϣ���Ͷ�Ӧ�Ĵ�����ָ��
		};
	};

	map<UINT, Type_Fun> m_MsgMap; // ��Ϣӳ���

	void InitMsgMap()
	{
		// �����Ϣӳ��
		INIT_MSGMAP(WM_LBUTTONDOWN, EX_MOUSE)
		INIT_MSGMAP(WM_KEYDOWN, EX_KEY)
		INIT_MSGMAP(WM_CHAR, EX_CHAR)
		INIT_MSGMAP(WM_CLOSE, EX_WINDOW)
		INIT_MSGMAP(WM_PAINT, EX_WINDOW)
		INIT_MSGMAP(WM_TIMER, EX_WINDOW) // ���Ӷ�ʱ����Ϣ
		INIT_MSGMAP(WM_LBUTTONUP, EX_MOUSE) // �������̧����Ϣ
	}

public:
	CGameFrame()
	{
		m_isQuit = false;
	}

	virtual ~CGameFrame() {}

public:

	// ͨ�ÿɵ��õĺ���
	bool GetQuit()
	{
		return m_isQuit;
	}

	// ��ʼ����Ϸ
	void InitGame(int width, int height, int x, int y, const TCHAR* pTitle)
	{
		m_hWnd = ::initgraph(width, height); // ���ڴ�СΪwidth*height

		::setbkcolor(RGB(255, 255, 255)); // Ĭ�����ñ�����ɫΪ��ɫ

		::cleardevice(); // �����˱���ɫ֮������������Ч

		// ���룺���ھ��������ȷ�����������ĸ����ڣ����ƶ����Ŀ�����ꡢ�ƶ����Ŀ���ߡ��Ƿ����»���
		// �趨���ڳ��ֵ�λ��
		::MoveWindow(m_hWnd, x, y, width, height, true);

		// TCHAR��������ڶ��ֽ��£�TCHAR = char���ڿ��ֽ��£�TCHAR = wchar_t
		// �趨���ڵı���
		::SetWindowText(m_hWnd, pTitle);

		InitMsgMap();

		// �趨���ڵĻص�����
		::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)&RunGame);
		// ���Σ� ���ھ��  ���õ����ͣ�int����ʾ�� �ص������ĵ�ַ


		// ��ʼ��������Ϸ
		Init();
	}

	// �ػ���Ϸ
	//void PaintGame()
	void ON_WM_PAINT(WPARAM& w, LPARAM& l)
	{
		::BeginBatchDraw(); // ��ʼ������ͼ

		::cleardevice(); // �����һ�ε�ͼƬ

		Paint();

		::EndBatchDraw(); // ����������ͼ
	}

	//// ��Ϸ����
	//void RunMyGame()
	//{
	//	ExMessage msg;
	//	while (1) {
	//		// ���ϻ�ȡ��Ϣ
	//		getmessage(&msg); // ��ȡ����������Ϣ

	//		if (msg.message == WM_LBUTTONDOWN) { // �����ȡ����Ϣ������������
	//			POINT po{ msg.x, msg.y };

	//			ON_WM_LBUTTONDOWN(po); // �������������µĺ���
	//		}
	//		else if (msg.message == WM_KEYDOWN) {
	//			ON_WM_KEYDOWN(msg.vkcode);
	//		}
	//	}
	//}

	// �ر���Ϸ
	//void CloseGame()
	void ON_WM_CLOSE(WPARAM&  w, LPARAM& l)
	{
		Close(w, l);
		// �رմ���
		::closegraph();

		m_isQuit = true;
	}

	// ������Ϸ���ֵĺ���

	// ���嶨ʱ��
	virtual void ON_WM_TIMER(WPARAM& w, LPARAM& l) {}

	// ��ʼ��������Ϸ
	virtual void Init() = 0;

	// ������Ϸ���ػ�
	virtual void Paint() = 0;

	virtual void Close(WPARAM& w, LPARAM& l) = 0;

	// ��������������
	virtual void ON_WM_LBUTTONDOWN(POINT& po) {}

	virtual void ON_WM_LBUTTONUP(POINT& po) {}

	// ������̰���
	virtual void ON_WM_KEYDOWN(WPARAM& key) {}

	virtual void ON_WM_CHAR(WPARAM& key) {}
	 
};

#define CREATE_OBJECT(type)\
CGameFrame* CreateObject()\
{\
	return new type;\
}

#define WINDOW_PARAM(WIDTH, HEIGHT, X, Y, TITLE)\
int wndWidth = WIDTH;\
int wndHeight = HEIGHT;\
int wndPosX = X;\
int wndPosY = Y;\
const TCHAR* wndTitle = TITLE;

/*
	ʹ��˵����
		1. GameFrameֻ��һ�����࣬��Ҫͨ���̳ж���һ�����ࣨ������Ϸ�ࣩ����д�������������麯��
		Init()��Paint()��Close(WPARAM w, LPARAM l)

		2. �ھ�����Ϸ��Դ�ļ��У�ʹ�ú� CREATE_OBJECT, WINDOW_PARAM

		3. �������µ���Ϣ������Ϸ����������Ϣ����������������������Ϣ���Ҫ��Ӧ
		������Ϊ ON_�����ϢID������ InitMsgMap ��ʹ�ú� INIT_MSGMAP ���һ����Ϣӳ��
*/
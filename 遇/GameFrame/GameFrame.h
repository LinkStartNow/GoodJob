#pragma once

#include <iostream>
#include <Windows.h>
#include <easyx.h>
#include <map>

using namespace std;

LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

// 为了便于定义map而做的宏
#define INIT_MSGMAP(MSGID, MSGTYPE)\
	m_MsgMap[MSGID].MsgType = MSGTYPE;\
	m_MsgMap[MSGID].MsgFun##MSGTYPE = &CGameFrame::ON_##MSGID;

class CGameFrame
{
	// friend：定义友元的关键字，把RunGame 看做是CGameFrame的朋友，所以在RunGame中可以使用CCgameFrame中的私有成员
	friend LRESULT CALLBACK RunGame(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

protected:
	HWND m_hWnd; // 子类中将来可能会用到，所以得设定成保护的
	// 窗口句柄，通过该变量就能定位到该窗口

private:
	bool m_isQuit;

	typedef void (CGameFrame::* P_FUN_EX_MOUSE)(POINT&);
	typedef void (CGameFrame::* P_FUN_EX_KEY)(WPARAM&);
	typedef void (CGameFrame::* P_FUN_EX_CHAR)(WPARAM&);
	typedef void (CGameFrame::* P_FUN_EX_WINDOW)(WPARAM&, LPARAM&);

	struct Type_Fun
	{
		int MsgType; // 消息类型
		union
		{
			P_FUN_EX_MOUSE MsgFunEX_MOUSE; // 鼠标消息类型对应的处理函数指针
			P_FUN_EX_KEY MsgFunEX_KEY; // 键盘消息类型对应的处理函数指针
			P_FUN_EX_CHAR MsgFunEX_CHAR; // 字符消息类型对应的处理函数指针
			P_FUN_EX_WINDOW MsgFunEX_WINDOW; // 窗口消息类型对应的处理函数指针
		};
	};

	map<UINT, Type_Fun> m_MsgMap; // 消息映射表

	void InitMsgMap()
	{
		// 添加消息映射
		INIT_MSGMAP(WM_LBUTTONDOWN, EX_MOUSE)
		INIT_MSGMAP(WM_KEYDOWN, EX_KEY)
		INIT_MSGMAP(WM_CHAR, EX_CHAR)
		INIT_MSGMAP(WM_CLOSE, EX_WINDOW)
		INIT_MSGMAP(WM_PAINT, EX_WINDOW)
		INIT_MSGMAP(WM_TIMER, EX_WINDOW) // 增加定时器信息
		INIT_MSGMAP(WM_LBUTTONUP, EX_MOUSE) // 增加鼠标抬起信息
	}

public:
	CGameFrame()
	{
		m_isQuit = false;
	}

	virtual ~CGameFrame() {}

public:

	// 通用可调用的函数
	bool GetQuit()
	{
		return m_isQuit;
	}

	// 初始化游戏
	void InitGame(int width, int height, int x, int y, const TCHAR* pTitle)
	{
		m_hWnd = ::initgraph(width, height); // 窗口大小为width*height

		::setbkcolor(RGB(255, 255, 255)); // 默认设置背景颜色为白色

		::cleardevice(); // 更改了背景色之后让它立即生效

		// 传入：窗口句柄（由于确定操作的是哪个窗口）、移动后的目标坐标、移动后的目标宽高、是否重新绘制
		// 设定窗口出现的位置
		::MoveWindow(m_hWnd, x, y, width, height, true);

		// TCHAR：如果是在多字节下，TCHAR = char，在宽字节下，TCHAR = wchar_t
		// 设定窗口的标题
		::SetWindowText(m_hWnd, pTitle);

		InitMsgMap();

		// 设定窗口的回调函数
		::SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)&RunGame);
		// 传参： 窗口句柄  设置的类型（int来表示） 回调函数的地址


		// 初始化具体游戏
		Init();
	}

	// 重绘游戏
	//void PaintGame()
	void ON_WM_PAINT(WPARAM& w, LPARAM& l)
	{
		::BeginBatchDraw(); // 开始批量绘图

		::cleardevice(); // 清除上一次的图片

		Paint();

		::EndBatchDraw(); // 结束批量绘图
	}

	//// 游戏运行
	//void RunMyGame()
	//{
	//	ExMessage msg;
	//	while (1) {
	//		// 不断获取信息
	//		getmessage(&msg); // 获取所有类别的信息

	//		if (msg.message == WM_LBUTTONDOWN) { // 如果获取的信息是鼠标左键按下
	//			POINT po{ msg.x, msg.y };

	//			ON_WM_LBUTTONDOWN(po); // 处理鼠标左键按下的函数
	//		}
	//		else if (msg.message == WM_KEYDOWN) {
	//			ON_WM_KEYDOWN(msg.vkcode);
	//		}
	//	}
	//}

	// 关闭游戏
	//void CloseGame()
	void ON_WM_CLOSE(WPARAM&  w, LPARAM& l)
	{
		Close(w, l);
		// 关闭窗口
		::closegraph();

		m_isQuit = true;
	}

	// 具体游戏部分的函数

	// 具体定时器
	virtual void ON_WM_TIMER(WPARAM& w, LPARAM& l) {}

	// 初始化具体游戏
	virtual void Init() = 0;

	// 具体游戏的重绘
	virtual void Paint() = 0;

	virtual void Close(WPARAM& w, LPARAM& l) = 0;

	// 具体鼠标左键按下
	virtual void ON_WM_LBUTTONDOWN(POINT& po) {}

	virtual void ON_WM_LBUTTONUP(POINT& po) {}

	// 具体键盘按下
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
	使用说明：
		1. GameFrame只是一个父类，需要通过继承定义一个子类（具体游戏类），重写并定义这三个虚函数
		Init()、Paint()、Close(WPARAM w, LPARAM l)

		2. 在具体游戏的源文件中，使用宏 CREATE_OBJECT, WINDOW_PARAM

		3. 如果添加新的信息，在游戏壳中增加消息处理函数，参数的类型与消息类别要对应
		函数名为 ON_后接消息ID，并在 InitMsgMap 中使用宏 INIT_MSGMAP 添加一条消息映射
*/
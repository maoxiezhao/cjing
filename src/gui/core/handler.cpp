#include "handler.h"
#include"core\debug.h"
#include"core\inputEvent.h"
#include"gui\widget\widget.h"
#include"gui\core\dispatcher.h"


namespace gui
{

static std::unique_ptr<class EventHandler> mHandler = nullptr;

/**
*	\brief �¼�������
*
*	event handerά�����ӵ�Dispatcher��ͬʱ����inputevent�������¼���ͬʱ
*	���¼��ַ��������˵�dispatcher
*/
class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	void Connect(Dispatcher* dispatcher);
	void Disconnect(Dispatcher* Dispatcher);

	void Active();
	void HandleEvent(const InputEvent& event);

	/** ���������¼� */
	void KeyBoardKeyDown(const InputEvent& event);
	void KeyBoardKeyUp(const InputEvent& event);

	void Mouse(const ui_event event, const Point2& pos);
	void MouseButtonDown(const Point2& pos, const InputEvent::MouseButton button);
	void MouseButtonUp(const Point2& pos, const InputEvent::MouseButton button);

private:
	std::vector<Dispatcher*> mDispatcher;

};

EventHandler::EventHandler():
	mDispatcher()
{
}

EventHandler::~EventHandler()
{
	mDispatcher.clear();
}

/**
*	\brief ����dispatcher,Dispatcher���뱣֤Ψһ��
*/
void EventHandler::Connect(Dispatcher * dispatcher)
{
	Debug::CheckAssertion(std::find(mDispatcher.begin(), mDispatcher.end(), dispatcher) == mDispatcher.end(),
		"dispatcher had already connected. ");

	mDispatcher.push_back(dispatcher);
}

void EventHandler::Disconnect(Dispatcher * Dispatcher)
{
	auto itr = std::find(mDispatcher.begin(), mDispatcher.end(), Dispatcher);
	Debug::CheckAssertion(itr != mDispatcher.end());

	mDispatcher.erase(itr);

	/** ��ɾ��һ��widget��������widget�ַ�active�¼� */
	Active();
}

void EventHandler::Active()
{
	for (auto dispatcher: mDispatcher)
	{
		//dispatcher->Fire(UI_EVENT_UNKNOW, std::<Widget&>(*dispatcher));
	}
}

/**
*	\brief �����ַ��¼�
*/
void EventHandler::HandleEvent(const InputEvent& event)
{
	InputEvent::KeyEvent keyEvent = event.GetKeyEvent();
	switch (keyEvent.type)
	{
	case InputEvent::EVENT_KEYBOARD_KEYDOWN:
		KeyBoardKeyDown(event);
		break;
	case InputEvent::EVENT_KEYBOARD_KEYUP:
		KeyBoardKeyUp(event);
		break;
	case InputEvent::EVENT_MOUSE_BUTTONDOWN:
		MouseButtonDown({ keyEvent.motion.x, keyEvent.motion.y }, keyEvent.mousebutton);
		break;
	case InputEvent::EVENT_MOUSE_BUTTONUP:
		MouseButtonUp({ keyEvent.motion.x, keyEvent.motion.y }, keyEvent.mousebutton);
		break;
	case InputEvent::EVENT_MOUSE_MOTION:
		Mouse(UI_EVENT_MOUSE_MOTION, { keyEvent.motion.x, keyEvent.motion.y });
		break;
	default:
		break;
	}
}

/**
*	\brief ���̰����¼�
*/
void EventHandler::KeyBoardKeyDown(const InputEvent& event)
{
}

/**
*	\brief �����ɿ��¼�
*/
void EventHandler::KeyBoardKeyUp(const InputEvent& event)
{
}

/**
*	\brief ����¼�����
*/
void EventHandler::Mouse(const ui_event event, const Point2& pos)
{
	std::vector<Dispatcher*> reverseDispatchers;
	std::reverse_copy(mDispatcher.begin(), mDispatcher.end(), reverseDispatchers.begin());

	for (auto& dispatcher : reverseDispatchers)
	{


		// ���widget��pos�У��򴥷��¼�
		if (dispatcher->IsAt(pos))
		{
			dispatcher->Fire(event, dynamic_cast<Widget&>(*dispatcher), pos);
		}
	}
}

/**
*	\brief ��갴���¼�
*/
void EventHandler::MouseButtonDown(const Point2& pos, const InputEvent::MouseButton button)
{
	switch (button)
	{
	case InputEvent::MOUSE_BUTTON_LEFT:
		Mouse(UI_EVENT_MOUSE_LEFT_BUTTON_DOWN, pos);
		break;
	case InputEvent::MOUSE_BUTTON_MIDDLE:
		Mouse(UI_EVENT_MOUSE_MIDDLE_BUTTON_DOWN, pos);
		break;
	case InputEvent::MOUSE_BUTTON_RIGHT:
		Mouse(UI_EVENT_MOUSE_RIGHT_BUTTON_DOWN, pos);
		break;
	}
}

/**
*	\brief ����ɿ��¼�
*/
void EventHandler::MouseButtonUp(const Point2& pos, const InputEvent::MouseButton button)
{
	switch (button)
	{
	case InputEvent::MOUSE_BUTTON_LEFT:
		Mouse(UI_EVENT_MOUSE_LEFT_BUTTON_UP, pos);
		break;
	case InputEvent::MOUSE_BUTTON_MIDDLE:
		Mouse(UI_EVENT_MOUSE_MIDDLE_BUTTON_UP, pos);
		break;
	case InputEvent::MOUSE_BUTTON_RIGHT:
		Mouse(UI_EVENT_MOUSE_RIGHT_BUTTON_UP, pos);
		break;
	}
}

/************ ȫ�ֺ��� *************/
void ConnectDispatcher(Dispatcher * dispatcher)
{
	Debug::CheckAssertion(mHandler != nullptr, 
		"event handler have not exist.");
	Debug::CheckAssertion(dispatcher != nullptr, 
		"the Dispatcher connect to event handler is null.");
	mHandler->Connect(dispatcher);
}

void DisconnectDispatcher(Dispatcher * dispatcher)
{
	Debug::CheckAssertion(mHandler != nullptr, 
		"event handler have not exist.");
	Debug::CheckAssertion(dispatcher != nullptr, 
		"the Dispatcher disconnect to event handler is null.");
	mHandler->Disconnect(dispatcher);
}


}
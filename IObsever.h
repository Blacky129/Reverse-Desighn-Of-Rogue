#pragma once

enum class EVENT_TYPE
{
	NONE_EVENT,
	RERENDER_EVENT
};

class IObserver
{
public:
	virtual ~IObserver() {};

	virtual void onNotify(EVENT_TYPE Event) = 0;
};
#pragma once

#include "IObsever.h"
#include <vector>
#include <algorithm>

class ISubject
{
private:
	std::vector<IObserver*> _Subsribers = {};

public:
	virtual ~ISubject() {};

	void addObserver(IObserver* NewObserver)
	{
		_Subsribers.push_back(NewObserver);
	}

	void removeObserver(IObserver* Observer)
	{
		remove(_Subsribers.begin(), _Subsribers.end(), Observer);
	}

protected:

	void notify(EVENT_TYPE Event)
	{
		for (IObserver* Observer : _Subsribers)
			Observer->onNotify(Event);
	}

};
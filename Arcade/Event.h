#pragma once

/* http://www.dannyb.me/posts/2014/02/creating_event_system_c++/ */

#include <vector>
#include <memory>
#include "EventHandler.h"

using namespace std;

class Event {
	std::vector<std::unique_ptr<EventHandler>> handlers;

	void notifyHandlers() {
		vector<unique_ptr<EventHandler>>::iterator func = this->handlers.begin();
		for (; func != this->handlers.end(); ++func) {
			if (*func != nullptr && (*func)->id != 0) {
				(*(*func))();
			}
		}
	}
public:
	void addHandler(const EventHandler& handler) {
		this->handlers.push_back(unique_ptr<EventHandler>(new EventHandler{ handler }));
	}

	void removeHandler(const EventHandler& handler) {
		vector<unique_ptr<EventHandler>>::iterator to_remove = this->handlers.begin();
		for (; to_remove != this->handlers.end(); ++to_remove) {
			if (*(*to_remove) == handler) {
				this->handlers.erase(to_remove);
				break;
			}
		}
	}

	void operator()() {
		this->notifyHandlers();
	}

	Event& operator+=(const EventHandler& handler) {
		this->addHandler(handler);

		return *this;
	}

	Event& operator+=(const EventHandler::Func& handler) {
		this->addHandler(EventHandler{ handler });

		return *this;
	}

	Event& operator-=(const EventHandler& handler) {
		this->removeHandler(handler);

		return *this;
	}
};

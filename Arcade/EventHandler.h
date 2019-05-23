#pragma once

/* http://www.dannyb.me/posts/2014/02/creating_event_system_c++/ */

#include <functional>

class EventHandler {
public:
	using Func = std::function<void()>;

private:
	Func _func;

public:
	int id;
	static int counter;

	EventHandler() : id{ 0 } {
	}

	EventHandler(const Func& func) : _func{ func } {
		this->id = ++EventHandler::counter;
	}

	void operator()() {
		this->_func();
	}

	void operator=(const EventHandler& func) {
		if (this->_func == nullptr) {
			this->_func = func;
			this->id = ++EventHandler::counter;
		}
		else {
			throw new std::exception();
		}
	}

	bool operator==(const EventHandler& del) {
		return this->id == del.id;
	}
	bool operator!=(nullptr_t) {
		return this->_func != nullptr;
	}
};
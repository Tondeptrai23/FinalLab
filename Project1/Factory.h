#pragma once

#include "Object.h"
#include <map>

template <class T>
class Factory : public Object{
private:
	inline static Factory* _instance = nullptr;
	std::map<std::string, T> _container;

private:
	Factory() {}

public:
	static Factory* getInstance() {
		if (_instance == nullptr) {
			_instance = new Factory<T>();
		}
		return _instance;
	}

	void registerWith(std::string name, T item) {
		_container.insert({name, item});
	}

	T create(std::string type) {
		return _container[type];
	}

	std::string toString() override {
		return "Factory";
	}

	void flush() {
		_container.clear();
	}
};
#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class InputHandlerException :public exception {
public:
	virtual string info() const { return _info; }
	InputHandlerException(string e) {
		_info = e;
	}
	const char* what() const throw ()
	{
		cout << _info << endl;
		return (char*)_info.data();
	}
private:
	string _info;
};

class ShapeNumberException :public InputHandlerException {
public:
	ShapeNumberException(string e) : InputHandlerException(e) {};
	const char* what() const throw ()
	{
		cout << info() << endl;
		return (char*)info().data();
	}
};

class ShapeFormatException :public InputHandlerException {
public:
	ShapeFormatException (int l, string e) :
		InputHandlerException("the " + to_string(l) + "th: " + e) {
	};
	const char* what() const throw ()
	{
		cout << info() << endl;
		return (char*)info().data();
	}
};

class IllegalFormatException :public ShapeFormatException {
public:
	IllegalFormatException(int l, string e) : 
		ShapeFormatException(l, e + ": Illegal input format!") {
	};
	const char* what() const throw ()
	{
		cout << info() << endl;
		return (char*)info().data();
	}
};

class OutRangeException :public ShapeFormatException {
public:
	OutRangeException(int l, string e) :
		ShapeFormatException(l, e + ": Geometric object parameters are out of range!") {
	};
	const char* what() const throw ()
	{
		cout << info() << endl;
		return (char*)info().data();
	}
};

class ShapeRepeatedException :public ShapeFormatException {
public:
	ShapeRepeatedException(int l, string e) :
		ShapeFormatException(l, e + ": Repeated graphics!") {
	};
	const char* what() const throw ()
	{
		cout << info() << endl;
		return (char*)info().data();
	}
};

class calcException :public exception {

};
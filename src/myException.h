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

class ShapeFormatException :public InputHandlerException {
public:
	ShapeFormatException(int l, string e) :
		InputHandlerException("the " + to_string(l) + "th: " + e) {
	};
	const char* what() const throw ()
	{
		cout << info() << endl;
		return (char*)info().data();
	}
};

class ShapeCoverException :public ShapeFormatException {
public:
	ShapeCoverException(int l, string e1, string e2) :
		ShapeFormatException(l, e1 + " : Covered graphics! with " + e2) {
	};
	const char* what() const throw ()
	{
		cout << info() << endl;
		string tmp = info();
		cout << tmp << endl;
		return tmp.data();
	}
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

class IllegalLineException :public ShapeFormatException {
public:
	IllegalLineException(int l, string e) :
		ShapeFormatException(l, e + ": Two points cannot be the same!") {
	};
	const char* what() const throw ()
	{
		cout << info() << endl;
		return (char*)info().data();
	}
};

class CalcException :public exception {
public:
	virtual string info() const { return _info; }
	CalcException(string e) {
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

class FileIOException :public exception {
public:
	virtual string info() const { return _info; }
	FileIOException(string e) {
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
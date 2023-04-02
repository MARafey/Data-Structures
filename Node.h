#pragma once
#include<iostream>
#include<string>
using namespace std;

template <typename T>
class Node
{
public:
	Node(T d = INT_MIN)
	{
		this->val = d;
	}
	Node(const Node<T>& d)
	{
		this->val = d.val;
	}
	bool operator==(Node<T> d)
	{
		if (this->val == d.val)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void operator=(const Node<T>& d)
	{
		this->val = d.val;
	}
	T get()
	{
		return val;
	}
	void display()
	{
		cout << val;
	}
	~Node()
	{
		this->val = 0;
	}

private:
	T val;
};

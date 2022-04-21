#pragma once
template<typename T>
class PriorityKey
{
	int key;
	T value;
public:
	PriorityKey(T val = nullptr, int k = 0) : key(k), value(val) {}

	int getKey() const { return key; }
	const T& getValue() const { return value; }

	void setKey(int k) { key = k; }
	void setValue(T v) { value = v; }
};
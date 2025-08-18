#pragma once

template<typename Key, typename Value>
class TPair
{
public:
	TPair()
		:key(), value()
	{

	}

	TPair(const Key& key, const Value& value)
		:key(key), value(value)
	{

	}

	// 비교 연산자 오버로딩
	bool operator==(const TPair<Key, Value>& other)
	{
		return (key == other.key) && (value == other.value);
	}

	bool operator!=(const TPair<Key, Value>& other)
	{
		return (key != other.key) || (value != other.value);
	}

	bool operator>(const TPair<Key, Value>& other)
	{
		return key > other.key;
	}

	bool operator<(const TPair<Key, Value>& other)
	{
		return key < other.key;
	}

	bool operator>=(const TPair<Key, Value>& other)
	{
		return key >= other.key;
	}

	bool operator<=(const TPair<Key, Value>& other)
	{
		return key <= other.key;
	}

public:
	Key key;
	Value value;
};
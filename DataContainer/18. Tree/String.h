#pragma once

#include <iostream>

class String
{
public:
	String(const char* value = nullptr);
	String(const String& other);
	String(String&& other);
	
	~String();

	String& operator=(const String& other);
	String& operator=(String&& other);
	bool operator==(const String& other);
	String operator+(const String& other);

	friend std::ostream& operator<<(std::ostream& os, const String& string);

private:
	size_t length = 0;
	char* data = nullptr;
};

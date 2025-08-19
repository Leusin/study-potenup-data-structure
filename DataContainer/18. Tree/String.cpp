#include "String.h"

String::String(const char* value)
{
    length = value == nullptr ? 0 : strlen(value);

    if (value == nullptr)
    {
        return;
    }

    int size = (int)length + 1;
    data = new char[size];
    strcpy_s(data, size, value);
}

String::String(const String& other)
    : length(other.length)
{
    int size = (int)length + 1;
    data = new char[size];
    strcpy_s(data, size, other.data);
}

String::String(String&& other)
    : length(other.length)
{
    data = other.data;
    other.data = nullptr;
}

String::~String()
{
    if (data)
    {
        delete[] data;
        data = nullptr;
    }
}

String& String::operator=(const String& other)
{
    length = other.length;

    int size = (int)length + 1;
    data = new char[size];

    strcpy_s(data, size, other.data);

    return *this;
}

String& String::operator=(String&& other)
{
    // TODO: 여기에 return 문을 삽입합니다.
    length = other.length;
    data = other.data;
    other.data = nullptr;

    return *this;
}

bool String::operator==(const String& other)
{
    return strcmp(data, other.data) == 0;
}

String String::operator+(const String& other)
{
    size_t newLength = length + other.length;
    char* newString = new char[newLength + 1];
    
    //문자열 복사
    //strcpy_s(newString, length + 1, data);
    memcpy(newString, data, length);

    // 두 번째 문자열을 기존 문자열 뒤에 연결
    //strcpy_s(newString + length, other.length, other.data);
    //strcat_s(newString, newLength + 1, other.data); 
    memcpy(newString + length, other.data, other.length);
    newString[newLength] = '\0';

    // 새로운 String 객체 생성 및 반환
    String temp(newString);

    // 임시로 할당한 메모리 해제
    delete[] newString;

    return temp;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
    return os << string.data;
}

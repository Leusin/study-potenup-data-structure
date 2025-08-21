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
    // 1. 자가 대입 체크 (선택적이지만 안전한 코드 작성 습관)
    if (this == &other)
    {
        return *this;
    }

    // 2. 기존 메모리 해제
    // 이전에 할당된 메모리를 먼저 해제하지 않으면 메모리 누수가 발생합니다.
    delete[] data;

    // 3. 새 메모리 할당 및 복사
    length = other.length;
    int size = (int)length + 1;
    data = new char[size];
    strcpy_s(data, size, other.data);

    return *this;
}

String& String::operator=(String&& other)
{
    if (this != &other)
    {
        delete[] data; // Delete old memory first!

        length = other.length;
        data = other.data;

        // Leave the source object in a valid, empty state
        other.length = 0;
        other.data = nullptr;
    }
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

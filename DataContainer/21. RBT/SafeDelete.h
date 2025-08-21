#pragma once

// 메모리 해제 함수.
template<typename T>
void SafeDelete(T*& resource)
{
    if (resource)
    {
        delete resource;
        resource = nullptr;
    }
}
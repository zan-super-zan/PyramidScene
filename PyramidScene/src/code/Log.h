#pragma once
#include <iostream>

#ifdef _DEBUG

#define LOG_ERROR(message)do{\
 std::cout << __FILE__ << " ( Line - " << __LINE__ << ")\nInfo: " << message << std::endl; __debugbreak();\
 } while(false)

#define LOG_INFO(message)do{\
 std::cout << __FILE__ << " ( Line - " << __LINE__ << ")\nInfo: " << message << std::endl;\
 } while(false)

#elif NDEBUG
#define LOG_ERROR(message)
#define LOG_INFO(message)
#endif

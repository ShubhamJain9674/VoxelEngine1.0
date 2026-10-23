#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


#include <type_traits>
#include <utility>

#include "time.h"
#include <cassert>
#include <iostream>

const float toRadians = 3.14159265f / 180.0f;


#define internal static


#ifdef _MSC_VER
    #ifdef NDEBUG
        #define ASSERT(x) (void(0))
    #else
	    #define ASSERT(x) do { if (!(x)) __debugbreak(); } while (0)
    #endif
#else
	#define ASSERT(x) do { assert(x); } while(0)
#endif


void GLClearError();

bool GLCheckError(const char* functionName, const char* file, int line);

//NOTES for me :-
/*
* decltype(auto) :           compiler deduces type but reference value is also preserved.

* template<typename Func>	 Make the function generic over callable types.

* decltype(auto)	         Deduce the return type using decltype rules,
                             potentially preserving references.

* Func&& func	             Accept different callable value categories
                             through a forwarding reference.

* if constexpr          	 Choose a branch at compile time.

* std::invoke_result_t<Func> Determine the callable's result type,
                             assuming it can be invoked as specified.

* std::is_void_v<T>	         Check whether a type is void.

* std::forward<Func>(func)() Invoke the callable while preserving its value category.
*/

template<typename Func>
decltype(auto) GLCallImpl(
    Func && func,
    const char* functionName,
    const char* file,
    int line)
{
    GLClearError();

    if constexpr (std::is_void_v<std::invoke_result_t<Func>>)
    {
        std::forward<Func>(func)();

        ASSERT(GLCheckError(functionName, file, line));
    }
    else
    {
        decltype(auto) result = std::forward<Func>(func)();

        ASSERT(GLCheckError(functionName, file, line));

        return result;
    }
}

#define GLCall(x) \
    GLCallImpl([&]() -> decltype(auto) { return (x); }, #x, __FILE__, __LINE__)


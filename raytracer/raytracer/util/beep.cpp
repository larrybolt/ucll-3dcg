#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define LEAN_AND_MEAN
#include <Windows.h>
#else
#include <iostream>
#endif

void beep()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    MessageBeep(MB_ICONINFORMATION);
#else
    std::cout << '\a';
#endif
}

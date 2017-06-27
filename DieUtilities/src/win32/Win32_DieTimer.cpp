#include "DieTimer.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#if !defined(NOMINMAX) && defined(_MSC_VER)
#define NOMINMAX //Required to stop windows.h messing up std::min
#endif
#include <Win32/DieMinWindows.h>
#include <time.h>

namespace dieEngineSDK {
  struct dieTimer::Data
  {
    clock_t zeroClock;
    LARGE_INTEGER startTime;
    LARGE_INTEGER frequency;
  };

  dieTimer::dieTimer() {
    m_pData = new Data();
    reset();
  }
  dieTimer::~dieTimer() {
    delete m_pData;
  }

  void
    dieTimer::reset() {
    QueryPerformanceFrequency(&m_pData->frequency);
    QueryPerformanceCounter(&m_pData->startTime);
    m_pData->zeroClock = clock();
  }

  unsigned long
    dieTimer::dieMilliseconds() {
    LARGE_INTEGER curTimer;
    QueryPerformanceCounter(&curTimer);

    LONGLONG newTime = curTimer.QuadPart - m_pData->startTime.QuadPart;

    //Scale by 1000 for milliseconds
    unsigned long newTicks = static_cast<unsigned long>(1000 * newTime / 
                                                        m_pData->frequency.QuadPart);

    return newTicks;
  }

  unsigned long 
    dieTimer::dieMicroseconds() {
    LARGE_INTEGER curTime;
    QueryPerformanceCounter(&curTime);

    LONGLONG newTime = curTime.QuadPart - m_pData->startTime.QuadPart;

    // Scale by 1000000 for milliseconds
    unsigned long newMicro = static_cast<unsigned long>(1000000 * newTime /
                                                        m_pData->frequency.QuadPart);

    return newMicro;
  }

  unsigned long
    dieTimer::dieMillisecondsCPU() {
    clock_t newClock = clock();
    return static_cast<unsigned long>(static_cast<float>(newClock - m_pData->zeroClock) /
                                     (static_cast<float>(CLOCKS_PER_SEC) / 1000.0f));
  }

  unsigned long
    dieTimer::dieMicrosecondsCPU() {
    clock_t newClock = clock();
    return static_cast<unsigned long>(static_cast<float>(newClock - m_pData->zeroClock) /
                                     (static_cast<float>(CLOCKS_PER_SEC) / 1000000.0f));
  }
}

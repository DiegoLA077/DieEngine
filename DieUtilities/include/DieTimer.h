#pragma once

namespace dieEngineSDK {

  class dieTimer {
   public:
    dieTimer();
    ~dieTimer();

    /*Reset the timer to zero*/
    void reset();

    /*Return time in milliseconds since timer was initialized or last reset*/
    unsigned long dieMilliseconds();

    /*Returns time in microseconds since timer was initialid or last reset*/
    unsigned long dieMicroseconds();

    /**
    *Returns time in milli seconds since timer was initialized or last reset
    *Only CPU timer measured
    */
    unsigned long dieMillisecondsCPU();

    /**
    *Returns time in micro seconds since timer was initialized or last reset
    *Only CPU timer measured
    */
    unsigned long dieMicrosecondsCPU();

    /**
    *Returns time at which the timer was initialized, in milliseconds
    * return time un milliseconds
    */
    unsigned long dieStartMS() const;

   private:
    struct Data;
    Data* m_pData;
  };
}
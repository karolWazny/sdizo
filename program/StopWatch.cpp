#include "StopWatch.h"

StopWatch::StopWatch() {
    QueryPerformanceFrequency(&frequency);
}

void StopWatch::start() {
    QueryPerformanceCounter(&startStamp);
}

void StopWatch::stop() {
    QueryPerformanceCounter(&stopStamp);
    timeElapsedMicrosec.QuadPart = stopStamp.QuadPart - startStamp.QuadPart;
    timeElapsedMicrosec.QuadPart *= 1000000000000;
    timeElapsedMicrosec.QuadPart /= frequency.QuadPart;
}

unsigned long long StopWatch::getLastMeasurmentMicrosec() {
    return timeElapsedMicrosec.QuadPart;
}

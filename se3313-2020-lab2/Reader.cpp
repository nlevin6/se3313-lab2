#include <iostream>
#include "SharedObject.h"
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <thread>

using namespace std;

struct SharedData {
    int elapsedTime;
    int threadNumber;
    int reportNumber;
    mutex semaphore;
    condition_variable cv;
};

int main(void) {
    int sleepTimeSec = 2;
    cout << "I am a reader" << endl;
    Shared<SharedData> sharedMemory("sharedMemory");
    while (true) {
        {
            unique_lock<mutex> lock(sharedMemory->semaphore);
            cout << "| Thread: " << sharedMemory->threadNumber
                 << " | Report: " << sharedMemory->reportNumber
                 << " | Time Passed: " << sharedMemory->elapsedTime
                 << " |"
                 << endl;
        }
        this_thread::sleep_for(chrono::seconds(sleepTimeSec));
    }
    return 0;
}

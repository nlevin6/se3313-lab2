#include <iostream>
#include "SharedObject.h"
#include <unistd.h>

using namespace std;

struct SharedData {
    int elapsedTime;
    int threadNumber;
    int reportNumber;
};

int main(void) {
    int sleepTimeSec = 2;
    cout << "I am a reader" << endl;
    Shared<SharedData> sharedMemory("sharedMemory");
    while (true) {
        cout << "| Thread: " << sharedMemory->threadNumber
             << " | Report: " << sharedMemory->reportNumber
             << " | Time Passed: " << sharedMemory->elapsedTime 
             << " |"
             << endl;
        usleep(sleepTimeSec * 1000000);//a 2 sec nap
    }
    return 0;
}

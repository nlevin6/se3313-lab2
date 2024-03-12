#include <iostream>
#include "SharedObject.h"
#include <unistd.h>
#include "Semaphore.h"

using namespace std;

struct SharedData {
    int elapsedTime;
    int threadNumber;
    int reportNumber;
};

Semaphore locks("r", 1, false);
Semaphore n("n", 1, false);

int main(void) {
    int sleepTimeSec = 2;
    cout << "I am a reader" << endl;
    Shared<SharedData> sharedMemory("sharedMemory");
    
    while (true) {
        n.Wait();
        cout << "| Thread: " << sharedMemory->threadNumber
             << " | Report: " << sharedMemory->reportNumber
             << " | Time Passed: " << sharedMemory->elapsedTime 
             << " |"
             << endl;
        locks.Signal();
        usleep(sleepTimeSec * 1000000); // a 2 sec nap
    }
    return 0;
}

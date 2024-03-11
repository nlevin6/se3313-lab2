#include <iostream>
#include <thread>
#include <chrono>
#include "SharedObject.h"

using namespace std;

struct MyShared {
    int threadId;
    int reportId;
    double elapsedTime;
};

class ReaderThread {
private:
    std::thread theThread;
    bool stopFlag;

public:
    ReaderThread() : stopFlag(false) {}

    void ThreadMain(Shared<MyShared> sharedMemory) {
        cout << "I am a Reader" << endl;

        while (!stopFlag) {
            cout << "Thread ID: " << sharedMemory->threadId << ", Report ID: " << sharedMemory->reportId
                 << ", Elapsed Time: " << sharedMemory->elapsedTime << " seconds." << endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void Start() {
        Shared<MyShared> sharedMemory("sharedMemory");
        theThread = std::thread(&ReaderThread::ThreadMain, this, sharedMemory);
    }

    void Stop() {
        stopFlag = true;
    }

    void Join() {
        theThread.join();
    }
};

int main(void) {
    ReaderThread reader;
    reader.Start();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    reader.Stop();
    reader.Join();

    return 0;
}

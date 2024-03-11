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

class ReaderThread : public Thread {
public:
    virtual long ThreadMain(void) override {
        Shared<MyShared> sharedMemory("sharedMemory");

        cout << "I am a Reader" << endl;

        while (true) {
            cout << "Thread ID: " << sharedMemory->threadId << ", Report ID: " << sharedMemory->reportId
                 << ", Elapsed Time: " << sharedMemory->elapsedTime << " seconds." << endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        return 0;
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

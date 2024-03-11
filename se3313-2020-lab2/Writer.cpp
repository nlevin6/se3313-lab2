#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "SharedObject.h"

using namespace std;

struct MyShared {
    int threadId;
    int reportId;
    double timeSinceLastReport;
};

class WriterThread {
public:
    int threadNum;
    bool flag;
    std::thread theThread;

    WriterThread(int in) : threadNum(in), flag(false) {}

    void ThreadMain(Shared<MyShared> sharedMemory) {
        int reportCount = 0;
        while (true) {
            sharedMemory->threadId = threadNum;
            sharedMemory->reportId = reportCount++;
            sharedMemory->timeSinceLastReport = 0.0;

            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (flag) { // Exit loop to end the thread
                break;
            }
        }
    }

    void StartThread(Shared<MyShared> sharedMemory) {
        theThread = std::thread(&WriterThread::ThreadMain, this, sharedMemory);
    }

    void JoinThread() {
        theThread.join();
    }
};

int main(void) {
    std::cout << "I am a Writer" << std::endl;
    vector<WriterThread*> threads;
    Shared<MyShared> sharedMemory("sharedMemory");

    bool createNewThread = true;
    while (createNewThread) {
        int sleepTime;
        cout << "Do you want to create a new thread? (yes/no): ";
        string userInput;
        cin >> userInput;

        if (userInput == "yes") {
            cout << "Enter the sleep time for the thread (in seconds): ";
            cin >> sleepTime;

            WriterThread* newThread = new WriterThread(threads.size() + 1);
            newThread->StartThread(sharedMemory);
            threads.push_back(newThread);

            cout << "Thread " << threads.size() << " created with sleep time " << sleepTime << " seconds." << endl;
        } else {
            createNewThread = false;
        }
    }

    for (WriterThread* thread : threads) {
        thread->flag = true;
        thread->JoinThread();
        delete thread;
    }

    return 0;
}

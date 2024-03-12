#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <stack>
#include <chrono>
#include "SharedObject.h"
#include "thread.h"
#include "Semaphore.h"

using namespace std;

struct SharedData {
    int elapsedTime;
    int threadNumber;
    int reportNumber;
};

Semaphore locks("r",1,true);
Semaphore n("n",1,true);

class WriterThread : public Thread {
public:
    int thread;
    int report;
    int delay;
    bool flag;

    WriterThread(int thread, int delay, int report)
        : Thread(delay * 1000), thread(thread), report(report), delay(delay) {}

    virtual long ThreadMain(void) override {
        Shared<SharedData> sharedMemory("sharedMemory");
        while (!flag) {
            this->report++;
            auto start = chrono::steady_clock::now();
            std::this_thread::sleep_for(chrono::seconds(delay));
            auto finish = chrono::steady_clock::now();

            int totalTime = chrono::duration_cast<chrono::seconds>(finish - start).count();
            sharedMemory->threadNumber = thread;
            sharedMemory->elapsedTime = totalTime;
            sharedMemory->reportNumber = report;
        }
        return 0;
    }
};

int main(void) {
    int id = 0;
    string choice;
    string delay;

    WriterThread* thread1;

    Shared<SharedData> Shared("sharedMemory", true);
    cout << "I am a Writer" << endl;

    stack<WriterThread*> mystack;  // Ensure the <stack> header is included

    while (true) {
        cout << "Would you like to create a writer thread? (y or n): ";
        getline(cin, choice);
        if (choice == "n") {
            break;
        } else {
            cout << "What would you like the delay time to be?: ";
            getline(cin, delay);
            id++;
            thread1 = new WriterThread(id, stoi(delay), 0);
            mystack.push(thread1);
        }
    }
    while (!mystack.empty()) {
        thread1 = mystack.top();
        thread1->flag = true;
        delete thread1;
        mystack.pop();
    }
    return 0;
}

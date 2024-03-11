#include <iostream>
#include <thread>
#include "thread.h"
#include "SharedObject.h"

using namespace std

	struct MyShared
{
	int threadId;
	int reportId;
	double timeSinceLastReport;
};

int main(void)
{
	std::cout << "I am a Writer" << std::endl;
	vector<WriterThread*> threads;
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
            newThread->Start();
            threads.push_back(newThread);

            cout << "Thread " << threads.size() << " created with sleep time " << sleepTime << " seconds." << endl;
        } else {
            createNewThread = false;
        }
    }

    for (WriterThread* thread : threads) {
        thread->flag = true;
        thread->Join();
        delete thread;
    }

	return 0;
}

class WriterThread : public Thread {
public:
	int threadNum;
	bool flag;

	WriterThread(int in) : Thread(8 * 1000) {
		this->threadNum = in;
	}

	virtual long ThreadMain(void) override {
		// declare shared memory var so this thread can access it
		Shared<MyShared> sharedMemory("sharedMemory");
		int reportCounter = 0;
		while (true) {
			sharedMemory->threadId = threadNum;
			sharedMemory->reportId = reportCount++;
			sharedMemory->elapsedTime = 0.0;

			std::this_thread::sleep_for(std::chrono::seconds(1));
			if (flag) { // Exit loop to end the thread
				break;
			}
		}
		return 0;
	}
};

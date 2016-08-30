#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>


class Semaphore {
	
	
private:
	std::mutex m_mutex;
	std::condition_variable m_cv;

	
};

class BoundedBuffer {
	std::mutex m_mutex;
	std::condition_variable m_notFull_cv;
	std::condition_variable m_notEmpty_cv;

	int BUFFER_SIZE = 10;
	std::vector<int*> buffer;

public:
	BoundedBuffer() {};

	void Deposit(int* item) {
		std::unique_lock<std::mutex> lock(m_mutex);
		while (buffer.size() >= BUFFER_SIZE) {
			std::cout << "Buffer No Longer Full: "  << std::endl;
			m_notFull_cv.wait(lock);
		}

		buffer.push_back(item);
		m_notEmpty_cv.notify_all();
	}
	int* Retrieve() {
		std::unique_lock<std::mutex> lock(m_mutex);
		while (buffer.size() == 0) {
			std::cout << "Buffer No Longer Empty: " << std::endl;
			m_notEmpty_cv.wait(lock);
		}
		int* newItem = buffer.back();
		buffer.pop_back();
		m_notFull_cv.notify_all();

		return newItem;
	}
};

BoundedBuffer buffer;
std::vector<int*> m_ints;
class Producer {
public:
	void produce() {
		while (true) {
			int* i;
			if (m_ints.size() != 0) {
				i = m_ints.back();
			}
			m_ints.pop_back();
			buffer.Deposit(i);
		}
	}
};

class Consumer {
public:
	void consume() {
		while (true) {
			int* i = buffer.Retrieve();
			m_ints.push_back(i);
		}
	}
};
void produce() {
	while (true) {
		int i;
		if (m_ints.size() != 0) {
			i = *m_ints.back();
			std::cout << "Producing: " << i << std::endl;
			m_ints.pop_back();
			buffer.Deposit(&i);
		}
		
	}
}
void consume() {
	while (true) {
		int i = *buffer.Retrieve();
		std::cout << "Consuming: " << i << std::endl;
		i++;
		//m_ints.push_back(&i);
	}
}
int main(void) {
	for (int i = 0; i < 250; i++) {
		m_ints.push_back(new int(i));
	}
	//Producer* p;
	//Consumer* c;
	/*std::thread threads[10];
	for (int i = 0; i < 8; i++) {
		threads[i] = std::thread(consume);
	}
	for (int i = 8; i < 10; i++) {
		threads[i] = std::thread(produce);
	}
	for (auto& th : threads) {
		th.join();
	}*/

	int const consumerThreads = 7;
	int const producerThreads = 3;
	std::thread cThreads[consumerThreads];
	std::thread pThreads[producerThreads];

	for (int i = 0; i < consumerThreads; i++) {
		cThreads[i] = std::thread(consume);
	}

	for (int i = 0; i < producerThreads; i++) {
		pThreads[i] = std::thread(produce);
	}
	for (auto& th : cThreads) {
		th.join();
	}
	for (auto& th : pThreads) {
		th.join();
	}

	/*std::thread cThread(consume);
	std::thread pThread(produce);

	cThread.join();
	pThread.join();*/
	return 0;
}
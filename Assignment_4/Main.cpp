#include <iostream>
#include <chrono>

#define MAX_SIZE 1000
#define RUNS 100

using namespace std;
int * initArray();
bool findA(int, int[]);
bool findB(int, int[]);

template<typename TimeT = std::chrono::milliseconds>
struct measure
{
	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>	
			(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};


int main() {

	int *item = initArray();
	double findATotal = 0.0;
	double findBTotal = 0.0;
	

	for (int i = 0; i < RUNS; i++) {
		/*cout << "Time taken for find A: " << measure<std::chrono::nanoseconds>::execution(findA, 650, item) << std::endl;
		cout << "Time taken for find B: " << measure<std::chrono::nanoseconds>::execution(findB, 650, item) << std::endl;*/
		findATotal += measure<std::chrono::nanoseconds>::execution(findA, 800, item);
		findBTotal += measure<std::chrono::nanoseconds>::execution(findB, 800, item);
	}

	cout << "Average time taken for find A: " << findATotal / RUNS << endl;
	cout << "Average time taken for find b: " << findBTotal / RUNS << endl;
	
}

int * initArray() {
	static int item[MAX_SIZE];
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_SIZE; ++i) {
		item[i] = i;
		//cout << item[i] << endl;
	}
	return item;
}

bool findA(int testValue, int item[MAX_SIZE]) {
	bool found = false; 
	int i = 0; 
	while ((!found) && (i < sizeof(item))) {
		if (item[i] == testValue)
			found = true;
		else
			i++;
	}
	return found;
}

bool findB(int testValue, int item[MAX_SIZE]) {
	int initialValue = item[sizeof(item) - 1]; 
	item[sizeof(item) - 1] = testValue;
	int i = 0; 

	while (item[i] != testValue) {
		i++;
	}

	item[sizeof(item) - 1] = initialValue; 
	
	return i < sizeof(item) - 1 || testValue == initialValue;
}

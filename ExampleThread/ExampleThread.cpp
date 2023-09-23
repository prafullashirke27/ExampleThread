// ExampleThread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <mutex>
#include <StlLock.h>

HANDLE g_hEvent = nullptr;

int count = 0;

std::mutex mu;

DWORD WINAPI printEven(LPVOID lparam)
{


	while (count < 100)
	{

		if (count % 2 == 0)
		{
			std::lock_guard<std::mutex> lk(mu);
			WaitForSingleObject(g_hEvent, 0);

			std::cout << "EVEN\t" << count << std::endl;

			count++;


			SetEvent(g_hEvent);
		}
	}







	return 0;
}


DWORD WINAPI printOdd(LPVOID lparam)
{

	while (count < 100)
	{

		//std::scoped_lock<std::mutex> lock(mu);
		if (count % 2 == 1)
		{
			std::lock_guard<std::mutex> lk(mu);
			WaitForSingleObject(g_hEvent, 0);

			std::cout << "ODD\t" << count << std::endl;

			count++;


			SetEvent(g_hEvent);
		}
	}


	return 0;
}


int main()
{
	g_hEvent = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("WriteEvent")  // object name
	);

	HANDLE handle1 = CreateThread(NULL, 0, printEven, 0, 0, 0);
	HANDLE handle2 = CreateThread(NULL, 0, printOdd, 0, 0, 0);

	HANDLE arrayOfHANDLE[] = { handle1, handle2 };

	WaitForMultipleObjects(2, arrayOfHANDLE, TRUE, INFINITE);



	std::cout << "END" << std::endl;
	return 0;
}


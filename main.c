#include <stdio.h>
#include <Windows.h>

#define SLEEP_TIME 10

int startingNum;
HANDLE mutex;

DWORD WINAPI ThreadRun(LPVOID lpParam)
{
	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
	{
		return 1;
	}

	int threadId = (int)lpParam + startingNum;

	while (TRUE)
	{
		if (WaitForSingleObject(mutex, INFINITE) == WAIT_OBJECT_0)
		{
			printf("%s%d%s", "Thread ", threadId, " Wants to print\n");
			printf("%s%d%s", "Thread ", threadId, " Has Mutex\n");
			printf("%s%d%s", "Thread ", threadId, " Releases Mutex now...\n");
			ReleaseMutex(mutex);
		}

		Sleep(SLEEP_TIME);

	}

	return 0;
}

int main(int argc, char **argv)
{
	if (3 == argc)
	{
		size_t threadCount = atoi(argv[1]);
		startingNum = atoi(argv[2]);

		HANDLE *threadArray = malloc(threadCount * sizeof(HANDLE));
		DWORD *threadIdArray = malloc(threadCount * sizeof(DWORD));

		mutex = CreateMutex(NULL, FALSE, "mMutex");

		for (size_t i = 0; i < threadCount; i++)
		{
			threadArray[i] = CreateThread(NULL, 0, ThreadRun, (void*)i, 0, &threadIdArray[i]);
		}

		printf("All threads are done...\n");

		for (size_t i = 0; i < threadCount; i++)
		{
			CloseHandle(threadArray[i]);
		}

	}
	else
	{
		printf("Use <Program> <N> <C> (N - Thread Count, C - Starting Number)\n");
	}

	getchar();
}
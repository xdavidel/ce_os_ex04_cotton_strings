#include <stdio.h>
#include <Windows.h>

#define SLEEP_TIME 10
#define GENERAL_MUTEX_NAME "gMutex"
#define LOCAL_MUTEX_NAME "lMutex"
#define MUTEX_NAME_LENGTH 7

int startingNum;
HANDLE mutex;
char mutexName[MUTEX_NAME_LENGTH];

HANDLE GetOrCreateMutex()
{
	HANDLE m = OpenMutex(SYNCHRONIZE, TRUE, GENERAL_MUTEX_NAME);
	if(NULL == m)
	{
		m = CreateMutex(NULL, FALSE, LOCAL_MUTEX_NAME);
		strcpy_s(mutexName, MUTEX_NAME_LENGTH, LOCAL_MUTEX_NAME);
	}
	else
	{
		strcpy_s(mutexName, MUTEX_NAME_LENGTH, GENERAL_MUTEX_NAME);
	}
	return m;
}

DWORD WINAPI ThreadRun(LPVOID lpParam)
{
	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if(hStdout == INVALID_HANDLE_VALUE)
	{
		return 1;
	}

	int threadId = (int)lpParam + startingNum;

	while(TRUE)
	{
		if(WaitForSingleObject(mutex, INFINITE) == WAIT_OBJECT_0)
		{
			printf("%s%d%s", "Thread ", threadId, " Wants to print\n");
			printf("%s%d%s%s%c", "Thread ", threadId, " Has Mutex ", mutexName, '\n');
			printf("%s%d%s", "Thread ", threadId, " Releases Mutex now...\n");
			ReleaseMutex(mutex);
		}

		Sleep(SLEEP_TIME);

	}

	return 0;
}

int main(int argc, char **argv)
{
	if(argc >= 3)
	{
		size_t threadCount = atoi(argv[1]);
		startingNum = atoi(argv[2]);

		HANDLE *threadArray = malloc(threadCount * sizeof(HANDLE));
		DWORD *threadIdArray = malloc(threadCount * sizeof(DWORD));

		mutex = GetOrCreateMutex();

		for(size_t i = 0; i < threadCount; i++)
		{
			threadArray[i] = CreateThread(NULL, 0, ThreadRun, (void*)i, 0, &threadIdArray[i]);
		}

		if(argc >= 4)
		{
			while(TRUE) {}
		}
		else
		{
			getchar();

			for(size_t i = 0; i < threadCount; i++)
			{
				CloseHandle(threadArray[i]);
			}
		}
	}
	else
	{
		printf("Use <Program> <N> <C> (N - Thread Count, C - Starting Number)\n");
		getchar();
	}

	return 0;

}
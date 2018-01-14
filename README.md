# Cotton Strings

## Introduction
Threads and fibres could be created from different sources, whether it’s cotton, or anything else.
Moreover they can be colored and used in different techniques, for different reasons.
We are going to practice a little bit of that.

## Make it count
The task is quite basic, all we need to do is create a program that receives threads count N, and
starting number C as parameters, and creates N threads that each of them prints to the console
screen it’s numeric name, and sleeps for a predefined interval (e.g. 10 milliseconds).
The numeric name is made of starting number + current thread number (C+i)
For instance, if the program is executed with 2 as a parameter and 5 as the starting number - there
should be 2 threads created, that each of them prints “Thread N+C” (N stands for thread number)
to the screen at it’s turn. The output should look something like:
	* Thread 6
	* Thread 7
	* Thread 6
	* Thread 7
As the threads sleep for the same predefined interval. The printing should be very well organized..
right? Test it, and make sure it happens! Doesn’t matter how many threads are requested, we
shouldn’t be having scrambled text as output. The order of printing doesn’t matter.

## Remarks
- Only usage of WinAPI is allowed. You can use C-library for input/output only.
- Code should be organized, and API should be used as needed, go thoroughly through the
remarks sections and make sure you are supporting edge cases and failures.

## Your Submission
Please submit the necessary code files, well-documented (and not the whole solution).
Raise your thread!

## References
- Your previous lesson.
- MSDN
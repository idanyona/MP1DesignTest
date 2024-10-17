#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

volatile int stop_thread = 0;

void add_timespec(struct timespec *ts, int delay_ms)
{
    ts->tv_nsec += delay_ms * 1000000L;  // Convert milliseconds to nanoseconds

    // Handle overflow in nanoseconds
    if (ts->tv_nsec >= 1000000000L)
    {
        ts->tv_sec += ts->tv_nsec / 1000000000L;
        ts->tv_nsec %= 1000000000L;
    }
}

// Communication thread function with fixed-rate loop
void* communication_thread(void* arg)
{
    struct timespec next_cycle;
    int cycle_time_ms = 100; // Cycle time in milliseconds (fixed-rate)

    // Get current time
    clock_gettime(CLOCK_MONOTONIC, &next_cycle);

    while (!stop_thread)
    {
        // Handle communication (replace this with actual communication logic)
        printf("Handling communication...\n");

        // Calculate the next cycle time
        add_timespec(&next_cycle, cycle_time_ms);

        // Sleep until the next cycle
        if (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_cycle, NULL) != 0)
        {
            perror("clock_nanosleep failed");
            break;
        }
    }

    printf("Communication thread stopped.\n");
    return NULL;
}



int main(int argc, char **argv)
{
	std::cout << "Hello OpenSTLinux World!\n";

	pthread_t thread_id;
	pthread_attr_t thread_attr;
	struct sched_param sched_param;

	// Initialize thread attributes
	pthread_attr_init(&thread_attr);

	// Set thread to use real-time FIFO scheduling
	pthread_attr_setschedpolicy(&thread_attr, SCHED_FIFO);

	// Set desired thread priority (higher value means higher priority)
	sched_param.sched_priority = 10;  // Change this value based on the system
	pthread_attr_setschedparam(&thread_attr, &sched_param);

	// Enable explicit scheduling
	pthread_attr_setinheritsched(&thread_attr, PTHREAD_EXPLICIT_SCHED);

	// Create the communication thread with the defined attributes
	if (pthread_create(&thread_id, &thread_attr, communication_thread, NULL) != 0)
	{
		perror("Failed to create thread");
		return 1;
	}



	// Destroy thread attributes object
	pthread_attr_destroy(&thread_attr);

	// Main program logic (simulate some processing, then stop after 5 seconds)
//	sleep(5);

//	// Signal the thread to stop
//	stop_thread = 1;
//
//	// Wait for the communication thread to finish
//	pthread_join(thread_id, NULL);

	pthread_detach(thread_id);

	while (1)
	{

	}

	printf("Main program exiting.\n");
	return 0;

}

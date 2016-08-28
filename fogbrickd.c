/* This is fogbrick, a daemon to eat CPU time.

There is NO REASON YOU SHOULD EVER USE THIS.

This daemon does NOTHING USEFUL

It is created solely as an artifact to appease a hideous bureaucracy.

If you, poor soul, ever use this, it is at YOUR OWN RISK

ABANDON ALL HOPE, YE WHO ENTER HERE

License: MIT
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *wasteTime(void *arg){
	/* This function does NOTHING USEFUL */
	int i = 0;
	int j = 0;
	pthread_t id = pthread_self();

	printf("\nThread launched!\n");

	while (i < 1){
		j++;
		j--;
	}
	return NULL;
}

int getCPUCount(){
	int cpucount = 0;
	cpucount = sysconf(_SC_NPROCESSORS_ONLN);
	return cpucount;
	}

int main(int argc, char* argv[]){
	pid_t process_id = 0; //Needed for daemonization
	pid_t sid = 0; //This too
	pthread_t tid[64]; //Maximum 64 threads. If you need more....
	int threads = 0; //Start at 0 threads
	int count = 0; //This counts CPUs
	int err = 0; //Error value
	int busywork = 0; //Thrash value
	//Daemonize first - standard fork method
	process_id = fork();
	if (process_id < 0){
		printf("Fork failed!\n");
		exit(1);
		}
	if (process_id > 0){
		printf("Process ID of child process %d\n", process_id);
		exit(0);
		}
	// Now that it's a daemon, get to 'work'
	count = getCPUCount(); //Count how many CPUs we have
	printf("This system has %i CPUs\n", count);
	printf("Starting %i spinlocks!\n", count);
	while (threads <= count){ //Make one thread for each CPU
		usleep(1);
		err = pthread_create(&(tid[threads]), NULL, &wasteTime, NULL);
		threads++;
		}
	while (err == 0){ //If the pthread borks, we'll quit, otherwise spinlock
		busywork++;
		busywork--;
		}
	return 0;
	}

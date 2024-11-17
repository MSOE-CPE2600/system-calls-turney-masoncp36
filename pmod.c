// Chance Mason, System Calls, CPE 2600 morning

//pmod.c


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>
#include <errno.h>

int main() {
    // Get the current process ID
    pid_t pid = getpid(); 

    // Get the current priority
    int current_priority = getpriority(PRIO_PROCESS, pid);
    if (current_priority == -1 && errno != 0) {
        perror("getpriority");
        return 1;
    }

    // Reduce the priority by 10
    // Lower priority value means higher priority
    int new_priority = current_priority + 10; 
    if (setpriority(PRIO_PROCESS, pid, new_priority) == -1) {
        perror("setpriority");
        return 1;
    }

    printf("Priority reduced by 10. New priority: %d\n", new_priority);

    // Sleep for 1,837,272,638 nanoseconds
    struct timespec ts;
    // 1 second
    ts.tv_sec = 1; 
    // 837,272,638 nanoseconds
    ts.tv_nsec = 837272638; 

    if (nanosleep(&ts, NULL) == -1) {
        perror("nanosleep");
        return 1;
    }

    // Print goodbye message
    printf("Goodbye!\n");

    return 0;
}
// Chance Mason, System Calls, CPE 2600 morning

// pinfo.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <string.h>
#include <sys/resource.h>

const char* get_scheduler_policy_name(int policy) {
    switch (policy) {
        case SCHED_OTHER:
            return "SCHED_OTHER";
        case SCHED_FIFO:
            return "SCHED_FIFO";
        case SCHED_RR:
            return "SCHED_RR";
#ifdef SCHED_BATCH
        case SCHED_BATCH:
            return "SCHED_BATCH";
#endif
#ifdef SCHED_IDLE
        case SCHED_IDLE:
            return "SCHED_IDLE";
#endif
#ifdef SCHED_DEADLINE
        case SCHED_DEADLINE:
            return "SCHED_DEADLINE";
#endif
        default:
            return "UNKNOWN";
    }
}

int main(int argc, char* argv[]) {
    pid_t pid;
    if (argc == 2) {
        pid = atoi(argv[1]);
    } else {
        pid = getpid(); // Current process
    }

    // Reset errno
    errno = 0;
    // Get priority
    int priority = getpriority(PRIO_PROCESS, pid);
    // Error checking
    if (priority == -1 && errno != 0) {
        perror("getpriority");
        return 1;
    }

    // Get scheduling policy
    int policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    //change into readable string
    const char* policy_name = get_scheduler_policy_name(policy);
    if (strcmp(policy_name, "UNKNOWN") == 0) {
        fprintf(stderr, "Error: Unknown scheduling policy\n");
        return 1;
    }

    printf("Input PID: %d\n", pid);
    printf("Current Process ID: %d\n", getpid());
    printf("Priority of process with PID %d: %d\n", pid, priority);
    printf("Scheduling Method: %s\n", policy_name);

    return 0;
}
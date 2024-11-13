// Chance Mason, System Calls, CPE 2600 morning

// info.c

#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <limits.h>
#include <sys/sysinfo.h>

int main(int argc, char* argv[])
{
    struct timespec current_time;
    struct utsname unameData;
    char hostname[HOST_NAME_MAX + 1];

    //get current time
    if (clock_gettime(CLOCK_REALTIME, &current_time) == -1)
    {
        perror("clock_gettime");
        return -1;
    }
    //get time in nanoseconds
    long long nanoseconds = (long long)current_time.tv_sec * 1000000000LL + current_time.tv_nsec;
    nanoseconds = nanoseconds % 86400000000000;

    //check unameData
    if (uname(&unameData) != 0)
    {
        perror("uname");
        return -1;
    }

    //get the host name
    if (gethostname(hostname, sizeof(hostname)) == -1) 
    {
        perror("gethostname");
        return -1;
    }

    //get the number of available processors
    int nprocs = get_nprocs();

    if (nprocs == -1) {
        perror("get_nprocs");
        return -1;
    }

    //get memory page size
    int page_size = getpagesize();

    // Get the total number of physical pages
    long num_pages = sysconf(_SC_PHYS_PAGES);

    if (num_pages == -1) {
        perror("sysconf");
        return -1;
    }

    //calculate the total physical memory in bytes
    long long total_memory = (long long)(page_size * num_pages);

    //get the number of available (free) pages
    long free_pages = sysconf(_SC_AVPHYS_PAGES);

    if (free_pages == -1) {
        perror("sysconf");
        return -1;
    }

    //calculate the amount of free memory in bytes
    long long free_memory = (long long)page_size * free_pages;

    //print time
    printf("Current time of day in nanoseconds: %lld\n", nanoseconds);
    //print system network name
    printf("System network name: %s\n", hostname);
    //print operating system name
    printf("Operating system name: %s\n", unameData.sysname);
    //print operating system release
    printf("Operating system release: %s\n", unameData.release);
    //print operating system version
    printf("Operating system version: %s\n", unameData.version);
    //print system hardware type
    printf("System's hardware type: %s\n", unameData.machine);
    //print the number of processors
    printf("Number of CPUs: %d\n", nprocs);
    //print the total physical memory
    printf("Total physical memory: %lld bytes\n", total_memory);
    //print the amount of free memory
    printf("Total free memory: %lld bytes\n", free_memory);    

    return 0;
}
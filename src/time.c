#include <stdio.h>
#include <time.h>

void time_sleep(int seconds, int milliseconds)
{
    struct timespec rem;
    struct timespec req = {
        seconds,
        (milliseconds % 1000) * 1000000 
    };

    // Apparently the response lets us know success/failure?
    int response = nanosleep(&req , &rem);
}

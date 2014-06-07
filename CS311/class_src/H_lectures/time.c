#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char ** argv){
    
    time_t t = time(NULL);
    
    struct tm *gmt;
    struct tm *local;
    
    char time_string[100];
    
    printf("time = %d\n", time);
    
    gmt = gmtime(&t);
    local = localtime(&t);
    
    //           struct tm {
    //           int tm_sec;         /* seconds */
    //           int tm_min;         /* minutes */
    //           int tm_hour;        /* hours */
    //           int tm_mday;        /* day of the month */
    //           int tm_mon;         /* month */
    //           int tm_year;        /* year */
    //           int tm_wday;        /* day of the week */
    //           int tm_yday;        /* day in the year */
    //           int tm_isdst;       /* daylight saving time */
    //       };
    
    printf("Seconds:\t%d\n", local->tm_sec);
    printf("Minutes:\t%d\n", local->tm_min);
    printf("Hours:\t\t%d\n", local->tm_hour);
    printf("Day of month: \t%d\n",local->tm_mday);
    printf("Month: \t\t%d\n", local->tm_mon);
    printf("Year: \t\t%d\n", local->tm_year + 1900);
    printf("Day of week: \t%d\n", local->tm_wday);
    printf("Day of year: \t%d\n", local->tm_yday);
    printf("Is DST? \t%d\n", local->tm_isdst);
    
    printf("\n\n");
    
    printf("Seconds:\t%d\n", gmt->tm_sec);
    printf("Minutes:\t%d\n", gmt->tm_min);
    printf("Hours:\t\t%d\n", gmt->tm_hour);
    printf("Day of month: \t%d\n",gmt->tm_mday);
    printf("Month: \t\t%d\n", gmt->tm_mon);
    printf("Year: \t\t%d\n", gmt->tm_year + 1900);
    printf("Day of week: \t%d\n", gmt->tm_wday);
    printf("Is DST? \t%d\n", gmt->tm_isdst);
    
    strftime(time_string, 100, "%T", local);
    printf("Time: %s\n", time_string);
    
    return 0;
}

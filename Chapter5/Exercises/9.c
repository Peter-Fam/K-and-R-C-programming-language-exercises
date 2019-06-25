#include <stdio.h>
/* Exercise 9
 * Page: 114
 * Rewrite the routines day_of_year and month_day with pointers
 * instead of indexing.
 * */
static int daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = (int)(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if ((month < 1) || (month > 12)) {
        return -1;
    } else {
        if ((day < 1) || (day > *(*(daytab + leap) + month))) {
            return -1;
        }
    }

    for (i = 1; i < month; i++) {
        day += *(*(daytab + leap) + i);
    }
    return day;
}
/* month+day: set month, day from day of year*/
void month_day(int year, int yearday, int *month, int *pday) {
    int i, leap;

    if (yearday <= 365) {
        leap = (int)(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        for (i = 1; yearday > *(*(daytab + leap) + i); i++) {
            yearday -= *(*(daytab + leap) + i);
        }
        *month = i;
        *pday  = yearday;
    }
}
int main(void) {
    int month = -1, day = -1;
    month_day(1994, 234, &month, &day);
    printf("%d, %d\n", month, day);
    return 0;
}

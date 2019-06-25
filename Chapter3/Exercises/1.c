/*
 * Exercise 1
 * Page: 58
 * Our binary search makes two tests inside the loop,
 * when one would suffice (at the price of more tests outside).
 * Write a version with only one test inside the loop and
 * measure the difference in run-time.
 * */
int binsearch(int x, int v[], int n) {
    int low, high, mid;

    mid  = 0;
    low  = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid]) {
            high = mid; /*since v[mid] might be x
           it's not removed from the searching range*/
        } else {
            low = mid + 1;
        }
    } /* while exit only when high equal low
         so in case of a find v[high] = v[low] = x
         */
    if (x == v[high]) {
        return high;
    } else {
        return -1;
    }
}
int main(void) {
    return 0;
}

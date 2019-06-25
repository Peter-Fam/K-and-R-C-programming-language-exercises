/*
 * Exercise: 9
 * Page: 168
 * Functions like isupper can be implemented to save space or to save time,
 * Explore both possiblilties
 * */
/*
 * there are two possible interpertation to this exercise,
 * either it means the memory/speed trade off of functions and macros
 * or the actual implemenation of the function as they can be implemented either
 * using calucaltion or look up tables
 * */
#define isupper_cm(c) ((c) >= 'A' && (c) <= 'Z')
#define isupper_ltm(c) isupper_lookup[c]
int isupper_lookup[256] = {0};
int isupper_c(char c) {
    return c >= 'A' && c <= 'Z';
}
int isupper_lt(char c) {
    return isupper_lookup[c];
}
int main(void) {
    return 0;
}

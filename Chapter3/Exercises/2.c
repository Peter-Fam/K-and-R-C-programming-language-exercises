/*
 * Exercise 2
 * Page: 60
 * Write a function escape(s,t) that converts characters like
 * newline and tab into visible escape sequences like \n and \t
 * as it copies the string t to s . Use a switch . Write a
 * function for the other direction as well, converting escape
 * sequences into the real characters.
 * */
void escape(char s[], const char t[]) {
    int i, j;
    for (i = 0, j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\\':
            s[j++] = '\\';
            s[j++] = '\\';
            break;
        default:
            s[j++] = t[i];
        }
    }
}
void descape(char s[], const char t[]) {
    int i, j;
    i = 0;
    j = 0;
    while (t[i] != '\0') {
        if (t[i] == '\\') {
            switch (t[i + 1]) {
            case '\\':
                s[j++] = '\\';
                break;
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            default:
                s[j++] = t[i + 1];
            }
            i += 2;
        } else {
            s[j++] = t[i++];
        }
    }
    s[j] = t[i];
}
int main(void) {
    return 0;
}

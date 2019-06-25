#include <ctype.h>
#include <stdio.h>
#include <string.h>
/*
 * Exercise 20
 * Page: 126
 * Expand dcl to handle declarations with function argument types , qualifiers
 * like const, and so on
 * */
/*
 * Basically, this exercise is implementing the grammer described in Appendix
 * A.8 (declarations) more or less
 * */
/*
 * so expanding dcl as it is will be too problematic with all the global
 * variables and simple string handling
 * so a complete rewrite is better */
/*
 * storage-class-specifier:
 *      auto
 *      regisiter
 *      static
 *      extern
 *      typedef         // only here for syntactic convenience
 *
 * */
static const char *const storage_class_specifiers[] = {
    "auto", "register", "static", "extern", "typedef",
};
static const size_t sc_size = sizeof(storage_class_specifiers) / sizeof(char *);
/*
 * type-specifier:
 *      void
 *      char
 *      short
 *      int
 *      long
 *      float
 *      double
 *      signed
 *      unsigend
 * */
static const char *const type_specifiers[] = {"void",   "char",   "short",
                                              "int",    "long",   "float",
                                              "double", "signed", "unsigned"};
static const size_t ts_size = sizeof(type_specifiers) / sizeof(char *);
enum TS_E {
    VOID     = 1 << 0u,
    CHAR     = 1 << 1u,
    SHORT    = 1 << 2u,
    INT      = 1 << 3u,
    LONG     = 1 << 4u,
    FLOAT    = 1 << 5u,
    DOUBLE   = 1 << 6u,
    SIGNED   = 1 << 7u,
    UNSIGNED = 1 << 8u,
};
/*
 * type-qualifier:
 *      volatile
 *      const
 * */
static const char *const type_qualifiers[] = {
    "volatile",
    "const",
};
static const size_t tq_size = sizeof(type_qualifiers) / sizeof(char *);

/*
 * declaration:
 *      declaration-specifers declarator;
 *
 * */
static int declaration(char declaration[], int len, int function_declaration);
/*
 * declaration-specifers:
 *      storage-class-specifier decalaration-specifiers_optional
 *      type-specifier decalaration-specifiers_optional
 *      type-qualifier decalaration-specifiers_optional
 *
 *
 * */
static int decl_specifers(char specifiers_str[], int len, int sc_check,
                          unsigned int ts_check, int tq_check);
/*
 * declarator:
 *      pointer direct-declarator
 * */
static int dcl(char dcl_str[], int len);
/*
 *      pointer:
 *           * type-qualifier-list
 *           * type-qualifier-list pointer_optional
 * */
static int pointer(char pointer_str[], int len);
/*
 *           type-qualifier-list:
 *                type-qualifier
 *                type-qualifier-list type-qualifier
 *
 * */
static int type_qualifiers_list(char type_qualifiers_str[], int len);
/*
 * direct-declartor:
 *      identifier
 *      ( declarator )
 *      direct-declarator [ constant-expression_optional ]
 *      direct-declarator ( parameter-list_optional )
 * */
static int direct_dcl(char direct_dcl_str[], int len);
/*
 * parameter-list:
 *      declaration
 *      parameter-list , declaration
 *
 * */
static int parameter_list(char parameter_list_str[], int len);
/*
 * identifier:
 *      _ or letters followed by _ , letters or  numbers
 *
 * */
static int identifier(char identifier_str[], int len);
#define MAXTOKEN 1000
#define MAXLEN 10000
static int get_line(/*@out@*/ char s[], int lim);
static char out[MAXLEN * 3] = "";

int main(void) {
    char line[MAXLEN] = "";
    int len           = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        line[len - 1] = '\0';
        if (declaration(line, len - 1, 0) == 1) {
            printf("Syntax Error\n");
        } else {
            printf("%s\n", out);
        }
        printf("\n");
        printf("--------------------------%s\n", line);
        printf("\n");
        out[0] = '\0';
    }
    return 0;
}
static int isblankstr(char *str, int len);
static int arraycmp(const char *const array[], int array_size, char *arg);
static int isvalid_type_specifier(int match, unsigned int ts_check);
static int declaration(char declaration[], int len, int function_declaration) {
    char *split_ptr = declaration;
#ifdef NDEBUG
    printf("DECL: ||%.*s||", len, declaration);
#endif
    int decl_specifers_check = 0;
    if (isblankstr(split_ptr, len) == 1) {
        return 0;
    }
    do {
        const char *result = NULL;
        int match          = 0;
        while (isspace(*split_ptr)) {
            split_ptr++;
            len--;
        }
        if ((match = arraycmp(storage_class_specifiers, (int)sc_size,
                              split_ptr)) >= 0) {
            if (function_declaration == 1) {
                printf(
                    "Error: storage class specifier in function declarator\n");
                return 1;
            }
            result = storage_class_specifiers[match];
        } else if ((match = arraycmp(type_specifiers, (int)ts_size,
                                     split_ptr)) >= 0) {
            result = type_specifiers[match];
        } else if ((match = arraycmp(type_qualifiers, (int)tq_size,
                                     split_ptr)) >= 0) {
            result = type_qualifiers[match];
        } else {
            decl_specifers_check = 0;
        }
        if (result != NULL) {
            split_ptr += strlen(result);
            len -= strlen(result);
            if (isspace(*split_ptr) || *split_ptr == '\0') {
                decl_specifers_check = 1;
            } else {
                decl_specifers_check = 0;
                if (*split_ptr != '(') {
                    split_ptr -= strlen(result);
                    len += strlen(result);
                }
            }
        }
    } while (decl_specifers_check == 1);
    if (isblankstr(split_ptr, len) == 1) {
        printf("Error: Unknown Identifier\n");
        return 1;
    }
    int error = 0;
    error     = dcl(split_ptr, len);
    error |= decl_specifers(declaration, split_ptr - declaration, 0, 0, -1);
    return error;
}
static int decl_specifers(char specifiers_str[], int len, int sc_check,
                          unsigned int ts_check, int tq_check) {
    char *split_ptr    = specifiers_str;
    int storgage_class = 0;
    if (isblankstr(split_ptr, len) == 1) {
        if (!(ts_check & (VOID | DOUBLE | FLOAT | INT | CHAR))) {
            strcat(out, "int ");
        }
        return 0;
    }
    int match          = 0;
    const char *result = NULL;
    while (isspace(*split_ptr)) {
        split_ptr++;
        len--;
    }
    if ((match = arraycmp(storage_class_specifiers, (int)sc_size, split_ptr)) >=
        0) {
        if (sc_check == 1) {
            printf("Error: too Many storage class specifiers\n");
            return 1;
        } else {
            storgage_class = 1;
            result         = storage_class_specifiers[match];
            sc_check       = 1;
        }
    } else if ((match = arraycmp(type_specifiers, (int)ts_size, split_ptr)) >=
               0) {
        if (!isvalid_type_specifier(match, ts_check)) {
            printf("Error: incompatable Type specifiers\n");
            return 1;
        } else {
            result = type_specifiers[match];
            ts_check |= 1 << (unsigned int)match;
        }
    } else if ((match = arraycmp(type_qualifiers, (int)tq_size, split_ptr)) >=
               0) {
        if (match == tq_check) {
            printf("Error: Repeating Type Qualifier\n");
            return 1;
        } else {
            result   = type_qualifiers[match];
            tq_check = match;
        }
    } else {
        return 1;
    }
    if (result != NULL) {
        if (storgage_class == 1) {
            char temp[MAXLEN] = "";
            strcpy(temp, out);
            sprintf(out, "%s %s", result, temp);
        } else {
            strcat(out, result);
            strcat(out, " ");
        }
        split_ptr += strlen(result);
        return decl_specifers(split_ptr, (int)(len - strlen(result)), sc_check,
                              ts_check, tq_check);
    }
    return 1;
}
static int dcl(char dcl_str[], int len) {
    char *split_ptr   = dcl_str;
    int pointer_check = 0;
    if (isblankstr(split_ptr, len) == 1) {
        return 0;
    }
    do {
        int match = 0;
        while (isspace(*split_ptr) || *split_ptr == '*') {
            split_ptr++;
            len--;
        }
        if ((match = arraycmp(type_qualifiers, (int)tq_size, split_ptr)) >= 0) {
            split_ptr += strlen(type_qualifiers[match]);
            if (isspace(*split_ptr) || *split_ptr == '\0' ||
                *split_ptr == '*') {
                len -= strlen(type_qualifiers[match]);
                pointer_check = 1;
            } else {
                pointer_check = 0;
                if (*split_ptr != '(') {
                    split_ptr -= strlen(type_qualifiers[match]);
                }
            }
        } else {
            pointer_check = 0;
        }
    } while (pointer_check == 1);
    int error = 0;
    error     = direct_dcl(split_ptr, len);
    error |= pointer(dcl_str, split_ptr - dcl_str);
    return error;
}
static int pointer(char pointer_str[], int len) {
    char *split_ptr = pointer_str;
    if (isblankstr(split_ptr, len) == 1) {
        return 0;
    }
    while (isspace(*split_ptr)) {
        split_ptr++;
        len--;
    }
    if (*split_ptr == '*') {
        split_ptr++;
        pointer_str = split_ptr;
        len--;
    } else {
        printf("Error: Unknown Pointer Error\n");
        return 1;
    }
    while (*split_ptr != '*' && len > 0) {
        split_ptr++;
        len--;
    }
    int error = 0;
    error     = type_qualifiers_list(pointer_str, split_ptr - pointer_str);
    strcat(out, "pointer to ");
    error |= pointer(split_ptr, len);
    return error;
}
static char *reverse_matchfind(char *str, char *str_end, char set[3]) {
    int paran = 0;
    while (str <= str_end) {
        if (*str_end == set[1]) {
            paran++;
        } else if (*str_end == set[0]) {
            paran--;
        }
        if (paran == 0) {
            return str_end;
        }
        str_end--;
    }
    return NULL;
}
static int direct_dcl(char direct_dcl_str[], int len) {
#ifdef NDEBUG
    printf("DIRECT_DCL:||%.*s||\n", len, direct_dcl_str);
#endif
    char *split_ptr = direct_dcl_str;
    /* handling empty string */
    if (isblankstr(direct_dcl_str, len) == 1) {
        printf("Error: Unknown Identifier\n");
        return 1;
    }
    /* skipping blanks */
    while (isspace(*split_ptr) == 1) {
        split_ptr++;
        len--;
    }
    /* checking for functions/arrays and function parameters */
    char *identifier_ptr_check = strpbrk(split_ptr, "()[],");
    /* if none is found or outside the scope of the direct dcl then it's a
     * identifier */
    if (identifier_ptr_check == NULL ||
        identifier_ptr_check - split_ptr >= len) {
        return identifier(split_ptr, len);
    }

    /*trimming trailling white space */
    char *str_end_ptr = split_ptr + len - 1;
    while (isspace(*str_end_ptr)) {
        str_end_ptr--;
        len--;
    }

    if (*str_end_ptr == ')') { /* a function or (dcl)*/
        char *matching_paran = reverse_matchfind(split_ptr, str_end_ptr, "()");
        if (matching_paran == NULL) {
            printf("Error: Unbalanced paranethesis\n");
        } else if (matching_paran != split_ptr) { /* a function */
            int error = 0;
            error     = direct_dcl(split_ptr, matching_paran - split_ptr);
            strcat(out, "function taking (");
            error |= parameter_list(matching_paran + 1,
                                    str_end_ptr - matching_paran - 1);
            strcat(out, ") ");
            strcat(out, "returning ");
            return error;
        } else { /* (dcl) */
            /* skipping the () */
            if (isblankstr(split_ptr + 1, str_end_ptr - split_ptr - 1) == 1) {
                /* blank dcl in this context is invalid */
                printf("Error: Unknown Identifier\n");
                return 1;
            }
            /*skipping the () */
            return dcl(split_ptr + 1, str_end_ptr - split_ptr - 1);
        }
    } else if (*str_end_ptr == ']') { /* array index */
        char *matching_brackets =
            reverse_matchfind(split_ptr, str_end_ptr, "[]");
        if (matching_brackets == NULL) {
            printf("Error: Unbalanced brackets\n");
        } else if (matching_brackets != split_ptr) { /* array */
            int error = 0;
            len -= matching_brackets - split_ptr;
            error = direct_dcl(split_ptr, matching_brackets - split_ptr);
            matching_brackets++; /*skipping the [ */
            len--;
            while (matching_brackets != str_end_ptr--) {
                /* only digits and spaces are allowed inside an array index */
                if (!isspace(*str_end_ptr) && !isdigit(*str_end_ptr)) {
                    printf("Error: Invalid Array Index\n");
                    return 1;
                }
            }
            strcat(out, "array [");
            strncat(out, matching_brackets, len - 1);
            strcat(out, "] of ");
            return error;
        } else { /* array with no identifer */
            printf("Error: Array Index with No Identifier\n");
        }
    } else { /* any other error */
        printf("Error: Invalid Direct Declaration\n");
        return 1;
    }
    return 1;
}
static int parameter_list(char parameter_list_str[], int len) {
    char *split_ptr = parameter_list_str;
    if (isblankstr(split_ptr, len) == 1) {
        return 0;
    }
#ifdef NDEBUG
    printf("PARAM_LIST:||%.*s||\n", len, parameter_list_str);
#endif
    while (*split_ptr != ',' && len > 0) {
        split_ptr++;
        len--;
    }
    int error = 0;
    error = declaration(parameter_list_str, split_ptr - parameter_list_str, 1);
    strcat(out, ", ");
    error |= parameter_list(split_ptr + 1, len - 1);
    return error;
}
static int isvalid_identifier(char *str, int len) {
    if (isalpha(*str) || *str == '_') {
        while (--len > 0) {
            if (!(isalnum(*str) || *str == '_')) {
                return 0;
            } else if (isspace(*str)) {
                return 1;
            }
        }
    } else {
        return 0;
    }
    return 1;
}

static int identifier(char identifier_str[], int len) {
    char *str_ptr = identifier_str;
    while (isblankstr(str_ptr, len) == 1) {
        printf("\n Error: Unknown Identifier\n");
        return 1;
    }
    while (isspace(*str_ptr)) {
        str_ptr++;
        len--;
    }
    if (isvalid_identifier(str_ptr, len) == 1) {
        strncat(out, str_ptr, len);
        strcat(out, ": ");
        return 0;
    } else {
        printf("Error: InValid Identifier\n");
        return 1;
    }
}
static int type_qualifiers_list(char type_qualifiers_str[], int len) {
    if (isblankstr(type_qualifiers_str, len) == 1) {
        return 0;
    }
    strncat(out, type_qualifiers_str, len);
    strcat(out, " ");
    return 0;
}
static int arraycmp(const char *const array[], int array_size, char *arg) {
    int result = -1;
    int i      = 0;
    for (i = 0; i < array_size; i++) {
        if (strncmp(array[i], arg, strlen(array[i])) == 0) {
            result = i;
            break;
        }
    }
    return result;
}
static int isblankstr(char *str, int len) {
    int result = 1;
    int i      = 0;
    for (i = 0; i < len; i++) {
        if ((!isspace(str[i]))) {
            result = 0;
            break;
        }
    }
    return result;
}
static int isvalid_type_specifier(int match, unsigned int ts_check) {
    enum TS_E matched = (int)(1 << (unsigned int)match);
    /* handles repeated types */
    if (ts_check & matched) {
        return 0;
    }
    /* void handling */
    if (ts_check & VOID) {
        return 0;
    }
    if ((ts_check & VOID) && (matched & VOID)) {
        return 0;
    }
    /* incompatible types length */
    if ((ts_check & (LONG | SHORT | CHAR | FLOAT)) &&
        (matched & (LONG | SHORT | CHAR | FLOAT))) {
        return 0;
    }
    /* incompatible type sign */
    if ((ts_check & (SIGNED | UNSIGNED | FLOAT | DOUBLE)) &&
        (matched & (SIGNED | UNSIGNED | FLOAT | DOUBLE))) {
        return 0;
    }
    /* incompatible types type */
    if ((ts_check & (INT | FLOAT | DOUBLE | CHAR)) &&
        (matched & (INT | FLOAT | DOUBLE | CHAR))) {
        return 0;
    }
    /* long double exception */
    if ((ts_check & (DOUBLE | SHORT | CHAR)) &&
        (matched & (DOUBLE | SHORT | CHAR))) {
        return 0;
    }

    return 1;
}

int get_line(char s[], int lim) {
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != (int)'\n') {
        s[i++] = (char)c;
    }
    if (c == (int)'\n') {
        s[i++] = (char)c;
    }
    s[i] = '\0';
    return i;
}

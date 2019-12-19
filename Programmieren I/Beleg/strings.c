/**
 * Deklariert alle Basisfunktionen zum bearbeiten von char Arrays.
 *
 * @author Vincent Nadoll
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "strings.h"

/**
 * Entfernt alle führenden und folgenden Leerzeichen eines Strings.
 * 
 * @param str String mit führenden und folgenden Leerzeichen
 * @return String ohne führende und folgende Leerzeichen
 */
char *trim(char *str) {
    char *tail;

    /* Entfernt alle führenden Leerzeichen */
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    tail = str + strlen(str) - 1;

    /* Entfernt alle folgenden Leerzeichen */
    while (tail > str && isspace((unsigned char)*tail)) tail--;
    *(tail + 1) = 0;

    return str;
}

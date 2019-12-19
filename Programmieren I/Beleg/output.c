/**
 * Deklariert die Fuktionen zur Terminalausgabe.
 *
 * @author Vincent Nadoll
 */
#include <stdio.h>
#include <stdarg.h>
#include "entry.h"
#include "input.h"
#include "output.h"

/**
 * Stellt die Einträge der verketteten Liste in der Konsole dar
 * 
 * @param head Head der verketteten Liste von Einträgen
 */
void printTable(ENTRY *head) {
    int i;
    ENTRY *current;

    current = head;

    printf("\n\n");
    printf(" %2s | %-20s %-20s %20s\n", "ID", "Nachname", "Vorname", "Telefonnummer");

    /* Horizonzale Linie im Terminal */
    printf("\033[90m");
    for (i = 0; i < 69; i++) printf("%c", '-');
    printf("\033[0m\n");

    if (current) {
        while (current) {
            printf(" %2d | %-20.20s %-20.20s %20.20s\n",
                   current->id,
                   current->lastName,
                   current->firstName,
                   current->number);

            current = current->next;
        }
    }
    else printf(" Keine Ergebisse\n");

    printf("\n");
}

/**
 * Schreibt Debug-Informationen in das Termial.
 * Wird nur angezeigt, wenn beim Kompilieren -DDEBUG übergeben wird
 * 
 * @param message Informationsnachricht
 * @param ... Argumente wie bei #printf()
 */
void info(const char *message, ...)
{
#ifdef DEBUG
    va_list args;

    printf("\033[96m");
    va_start(args, message);
    printf("info::");
    vprintf(message, args);
    va_end(args);
    printf("\033[0m\n");
#endif
}

/**
 * Schreibt eigene Fehlermeldungen in das Termial.
 * 
 * @param message Fehlermeldung
 * @param ... Argumente wie bei #printf()
 */
void error(const char *message, ...)
{
    va_list args;

    printf("\033[91m");
    va_start(args, message);
    printf("info::");
    vprintf(message, args);
    va_end(args);
    printf("\033[0m\n");
}

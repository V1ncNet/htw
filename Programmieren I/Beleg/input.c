/**
 * Deklariert alle Funktionen, die die Benutzereingaben verabeiten.
 * 
 * @author Vincent Nadoll
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "strings.h"
#include "entry.h"
#include "input.h"
#include "output.h"

int inck(char *, char *);
void addEntry(int);
void editEntry(void);
void deleteEntry(void);
void findEntries(void);
void sortEntries(void);

/**
 * Validiert die Benutzereingaben.
 * 
 * @param str     zu überprüfender String
 * @param pattern Regex Pattern
 * @return 1, wenn str auf das Pattern matcht; ansonsten 0
 * 
 * https://stackoverflow.com/a/1085120
 */
int inck(char *str, char *pattern) {
    int match;
    regex_t regex;

    if (regcomp(&regex, pattern, 0)) {
        error("Regex konnte nicht kompiliert werden");
        exit(-1);
    }

    match = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (match == REG_NOERROR) return 1;
    else if (match == REG_NOMATCH) return 0;
    else {
        error("Bei der Validierung ist ein Feher aufgetreten");
        exit(-1);
    }
}

/**
 * Fragt die Daten für den neuen Eintrag in der Konsole ab und ruft anschließend phonelibentry#insert auf
 * 
 * @param id ID des neue Eintrags. Beim Bearbeiten eines Eintrags ist die ID des alten Eintrags. Bei
 *           neuem Eintrag ist die ID -1
 */
void addEntry(int id) {
    int c;
    char *lastName, *firstName, *number;

    printf("\n");
    printf("%15s: ", "Nachname");
    fgets(vBuf, sizeof vBuf, stdin);
    vBuf[strlen(vBuf) - 1] = 0;
    lastName = malloc(strlen(vBuf) + 1);
    if (!lastName) {
        error("Speicher konnte nicht zugewiesen werden");
        exit(-1);
    }
    strcpy(lastName, vBuf);
    info("Nachname: '%s'", lastName);

    printf("%15s: ", "Vorname");
    fgets(vBuf, sizeof vBuf, stdin);
    vBuf[strlen(vBuf) - 1] = 0;
    firstName = malloc(strlen(vBuf) + 1);
    if (!firstName) {
        error("Speicher konnte nicht zugewiesen werden");
        exit(-1);
    }
    strcpy(firstName, vBuf);
    info("Vorname: '%s'", firstName);

    printf("%15s: ", "Telefonnummer");
    fgets(vBuf, sizeof vBuf, stdin);
    vBuf[strlen(vBuf) - 1] = 0;
    number = malloc(strlen(vBuf) + 1);
    if (!number) {
        error("Speicher konnte nicht zugewiesen werden");
        exit(-1);
    }
    strcpy(number, vBuf);
    info("Telefonnummer: '%s'", number);

    /* Eingabevalidierung */
    if (!inck(lastName, "^[A-ZÄÖÜ][A-Za-z_ -äöüß]*$") || !inck(firstName, "^[A-ZÄÖÜ][A-Za-z_ -äöüß]*$") || !inck(number, "^0[0-9_ ]*$")) {
        printf("\nEin Name darf nur Buchstaben und Bindestriche enthalten.\nDer Vorname muss mit einen Großbuchstaben beginnen.\n");
        printf("Die Telefonnummer darf nur Ziffern enthalten und muss mit einer 0 beginnen.");

        free(lastName);
        free(firstName);
        free(number);

        while ((c = getchar()) != '\n' && c != EOF) { }
        addEntry(id);

        return;
    }

    head = insert(id, lastName, firstName, number, head);
}

/**
 * Fragt die ID des zu bearbeitenden Eintrags ab. Anschließend wird der Eintrag aus der verketteten Liste gelöscht und ein neuer Eintrag mit
 * der ID des alten angelegt.
 */
void editEntry(void) {
    int c, id;
    ENTRY *tmp;

    printf("\n");
    printf("Welcher Eintrag soll bearbeitet werden (ID)? ");
    if (scanf("%d", &id)) {
        tmp = search4Id(id, head);
        if (tmp) {
            /* "Pseudobearbeiten" Eintrag wird gelöscht und mit der selben ID neu eingefügt */
            delete (tmp, head);
            while ((c = getchar()) != '\n' && c != EOF) { }
            addEntry(id);
        }
    }
    else printf("Der eingegebene Wert ist keine ganze Zahl\n");
}

/**
 * Fragt die ID des zu löschenden Eintrags ab, sucht nach dem Eintrag anhand der ID und ruft anschließend phonelibentry#delete auf.
 */
void deleteEntry(void) {
    int c, id;
    ENTRY *tmp;

    printf("\n");
    printf("Welcher Eintrag soll gelöscht werden (ID)? ");
    if (scanf("%d", &id)) {
        while ((c = getchar()) != '\n' && c != EOF) { }
        tmp = search4Id(id, head);
        if (tmp) head = delete (tmp, head);
    }
    else
        printf("Der eingegebene Wert ist keine ganze Zahl\n");
}

/**
 * Fragt die zu suchende Eigenschaft in der Konsole ab. Ruft phonelibentry#search4Str auf. Anschließend werden die Suchergebnisse in der
 * Konsole dargestellt.
 */
void findEntries(void) {
    char *searchStr;

    printf("\n");
    printf("Nachname, Vorname oder Telefonnummer: ");
    fgets(vBuf, sizeof vBuf, stdin);
    vBuf[strlen(vBuf) - 1] = 0;
    searchStr = malloc(strlen(vBuf) + 1);
    if (!searchStr) {
        error("Speicher konnte nicht zugewiesen werden");
        exit(-1);
    }
    strcpy(searchStr, vBuf);
    info("Suche nach '%s'", searchStr);

    /* Stellt nur gefundenen Ergebnisse dar */
    printTable(search4Str(trim(searchStr), head));
}

/**
 * Fragt den Benutzer nach der zu suchenden Eigenschaft eines Eintrags ab und ruft phonelibentry#insertionsort auf.
 */
void sortEntries(void) {
    printf("\n");
    printf("Nach Nachname, Vorname oder ID sortieren (n/v/i): ");
    fgets(vBuf, sizeof vBuf, stdin);
    switch (vBuf[0]) {
        case 'n':
        case 'N':
            head = insertionSort(head, (SORTBY)lastName);
            break;
        case 'v':
        case 'V':
            head = insertionSort(head, (SORTBY)firstName);
            break;
        case 'i':
        case 'I':
            head = insertionSort(head, (SORTBY)id);
            break;
        default:
            sortEntries();
            break;
    }
}

/**
 * "Hauptmenü" Fragt den Benutzer, was er/sie tun möchte
 */
void getUserInput(void) {
    printf("Eingabe (h für Hilfe): ");
    fgets(vBuf, sizeof vBuf, stdin);
    switch (vBuf[0]) {
        case 'h':
        case 'H':
            printf("\n");
            printf("\033[1mAuswahlmöglichkeiten\033[0m\n");
            printf("\t%-3s %s\n", "l", "Listet alle Einträge");
            printf("\t%-3s %s\n", "a", "Fügt einen neun Eintag hinzu");
            printf("\t%-3s %s\n", "e", "Bearbeitet einen Eintrag");
            printf("\t%-3s %s\n", "d", "Löscht einen Eintrag");
            printf("\t%-3s %s\n", "s", "Sortiert alle Einträge");
            printf("\t%-3s %s\n", "f", "Sucht nach Name und Telefonnummer");
            printf("\t%-3s %s\n", "q", "Beendet das Programm");
            printf("\n");
            getUserInput();
            break;
        case 'l':
        case 'L':
            printTable(head);
            getUserInput();
            break;
        case 'a':
        case 'A':
            addEntry(-1);
            printTable(head);
            getUserInput();
            break;
        case 'e':
        case 'E':
            editEntry();
            printTable(head);
            getUserInput();
            break;
        case 'd':
        case 'D':
            deleteEntry();
            printTable(head);
            getUserInput();
            break;
        case 'f':
        case 'F':
            findEntries();
            getUserInput();
            break;
        case 's':
        case 'S':
            sortEntries();
            printTable(head);
            getUserInput();
            break;
        case 'q':
        case 'Q':
            break;
        default:
            getUserInput();
            break;
    }
}

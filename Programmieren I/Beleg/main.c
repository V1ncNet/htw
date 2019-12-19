/**
 * Deklariert die main-Funktion, initialisiert die Liste der Einträge mit NULL und ruft die Setup-Funktionen, sowie die Close-Fuktionen auf.
 * 
 * @author Vincent Nadoll
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strings.h"
#include "entry.h"
#include "input.h"
#include "output.h"

void parseCSV(void);
void save(void);

const char *db = "phonebook.csv";

int main(void) {
    head = NULL;

    parseCSV();

    head = insertionSort(head, (SORTBY)id);
    printTable(head);
    getUserInput();

    save();
    freeAll(head);

    return 0;
}

/**
 * Liest die Daten der CSV Datei ein und erstellt eine verkettete Liste von Einträgen.
 */
void parseCSV(void) {
    int i, id;
    char *value, *lastName, *firstName, *number;
    FILE *data;

    info("Öffne '%s'", db);
    data = fopen(db, "rt");
    if (!data) {
        error("Datei konnte nicht gelesen werden");
        exit(-1);
    }

    /* Iteriert über alle Zeilen der CSV Datei */
    while (fgets(vBuf, sizeof vBuf, data) != NULL) {
        value = trim(strtok(vBuf, ","));
        if (!value || value[0] == 0x0) {
            error("ID konnte nicht gelesen werden. Der Wert ist NULL oder leer.");
            exit(-1);
        }
        id = atoi(value);

        value = trim(strtok(NULL, ","));
        if (!value || value[0] == 0x0) {
            error("Nachname konnte nicht gelesen werden. Der Wert ist NULL oder leer.");
            exit(-1);
        }
        lastName = malloc(strlen(value) + 1);
        strcpy(lastName, value);

        value = trim(strtok(NULL, ","));
        if (!value || value[0] == 0x0) {
            error("Vorname konnte nicht gelesen werden. Der Wert ist NULL oder leer.");
            exit(-1);
        }
        firstName = malloc(strlen(value) + 1);
        strcpy(firstName, value);

        value = trim(strtok(NULL, ","));
        if (!value || value[0] == 0x0) {
            error("Telefonnummer konnte nicht gelesen werden. Der Wert ist NULL oder leer.");
            exit(-1);
        }
        /* Das letzte Zeichen in value wird mit 0 ersetzt */
        for (i = 0; i < strlen(value); i++) {
            if (value[i] == 0xa) { /* Test ob Zeichen bei i gleich \n ist */
                value[i] = 0;
            }
        }
        number = malloc(strlen(value) + 1);
        strcpy(number, value);

        head = insert(id, lastName, firstName, number, head);
    }

    /* fseek(data, 0L, SEEK_SET); */
    fclose(data);
}

/**
 * Speichert alle Einträge der verkettenten Liste in der CSV Datei
 */
void save(void) {
    FILE *data;
    ENTRY *current;

    data = fopen(db, "wt");
    if (!data) {
        error("Datei konnte nicht gelesen werden");
        exit(-1);
    }

    /* Sortiert die Einträge vor dem Abspeichern nach ID */
    current = insertionSort(head, 0);
    while (current) {
        fprintf(data, "%d,%s,%s,%s\n",
                current->id,
                current->lastName,
                current->firstName,
                current->number);

        current = current->next;
    }

    fclose(data);
}

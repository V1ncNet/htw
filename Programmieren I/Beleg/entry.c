/**
 * Deklariert die Funktionen, die mit der Liste interagieren/verwalten.
 * 
 * @author Vincent Nadoll
 */
#define _GNU_SOURCE /* Damit <string.h> #strcasestr zur Verfügung stellt */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"
#include "entry.h"
#include "input.h"
#include "output.h"

int nextId(ENTRY*);

/**
 * Iteriert über head und gibt die höchste ID zuürck.
 * 
 * @param head Head der verketteten Liste von Einträgen
 * @return ID
 */
int nextId(ENTRY *head) {
    ENTRY *current = head;

    while (current) {
        int current = head->id;
        int next = nextId(head->next);

        if (current > next) {
            return current;
        } else {
            return next;
        }
    }

    return -1;
}

/**
 * Fügt einen neuen Eintrag zur Liste hinzu.
 * 
 * @param id        neue ID
 * @param lastName  neuer Nachname
 * @param firstName neuer Vorname
 * @param number    neue Telefonnumer
 * @param next      head der verketteten Liste von Einträgen
 * @return Head der verketteten Liste von Einträgen des neuer Listeneintrags
 */
ENTRY *insert(int id, char *lastName, char *firstName, char *number, ENTRY *next) {
    ENTRY *newEntry = (ENTRY*)malloc(sizeof(ENTRY));

    if (!newEntry) {
        error("Speicher konnte nicht zugewiesen werden");
        exit(-1);
    }

    if (id < 0) {
        id = nextId(next) + 1;
    }

    newEntry->id = id;

    newEntry->lastName = (char*)malloc(strlen(lastName) + 1);
    newEntry->firstName = (char*)malloc(strlen(firstName) + 1);
    newEntry->number = (char*)malloc(strlen(number) + 1);

    memset(newEntry->lastName, 0, strlen(lastName) + 1);
    memset(newEntry->firstName, 0, strlen(firstName) + 1);
    memset(newEntry->number, 0, strlen(number) + 1);

    strcpy(newEntry->lastName, lastName);
    strcpy(newEntry->firstName, firstName);
    strcpy(newEntry->number, number);

    newEntry->next = next;
    next = newEntry;

    info("#%d, %s %s (%s) eingefügt", newEntry->id, newEntry->firstName, newEntry->lastName, newEntry->number);
    return newEntry;
}

/**
 * Sucht nach einem String im Telefonverzeichnis.
 * 
 * @param str  Suchstring
 * @param head Head der verketteten Liste von Einträgen
 * @return Alle Sucheergebnisse als verketteten Liste von Einträgen
 */
ENTRY *search4Str(char *str, ENTRY *head) {
    ENTRY *current, *found;

    current = head;
    found = NULL;

    /* Iteriert über alle Einträge und erzeugt eine neue Liste */
    while (current) {
        /* Vergeleicht den String mit aktuellen Nummer, Nachname oder Vorname */
        if (strcasestr(current->number, str) || strcasestr(current->lastName, str)  || strcasestr(current->firstName, str))
            found = insert(current->id, current->lastName, current->firstName, current->number, found);

        current = current->next;
    }

    if (found) {
        return found;
    }

    info("Keine Treffer für '%s'", str);
    return NULL;
}

/**
 * Sucht nach einer ID im Telefonverzeichnis.
 *
 * @param id   ID nach der gesucht werden soll
 * @param head Head der verketteten Liste von Einträgen
 * @return Das Suchergebnis
 */
ENTRY *search4Id(int id, ENTRY *head) {
    ENTRY *current;

    current = head;
    while (current) {
        if (current->id == id) return current;
        
        current = current->next;
    }
    
    info("Keine Treffer für ID=%d", id);
    return NULL;
}

/**
 * Löscht einen Eintrag.
 * 
 * @param entry Der zu löschende Eintrag
 * @param head  Head der verketteten Liste von Einträgen
 * @return Head der verketteten Liste von Einträgen ohne den zu löschenden Eintrag 
 */
ENTRY *delete(ENTRY *entry, ENTRY *head) {
    /* TODO: entry ist schon das letzte Element */
    ENTRY *current, *last, *tmp;

    if (!entry) {
        error("Eintrag darf nicht null sein");
        return NULL;
    }

    /* Wenn der zu löschende Eintrag gleich der erste Eintrag der verketteten Liste ist */
    if (entry == head) {
        head = head->next;
        entry->next = NULL;
        
        if (entry == head) head = NULL;

        free(entry);

        return head;
    }

    /* Wenn der zu löschende Eintrag der letzte Eintrag der verketteten Liste ist */
    if (!entry->next) {
        current = head;
        last = NULL;
        
        while (current->next) {
            last = current;
            current = current->next;
        }
        
        if (last) last->next = NULL;
        if (current == head) head = NULL;
        
        free(current);

        return head;
    }

    /* Wenn der zu löschende Eintrag innerhalb der Liste liegt. */
    current = head;
    while (current) {
        if (current->next == entry) break;
        current = current->next;
    }

    if (current) {
        tmp = current->next;
        current->next = tmp->next;
        tmp->next = NULL;

        free(tmp);
    }
    
    return head;
}

/**
 * Insertionsort über den Head der verketteten Liste von Einträgen.
 * 
 * @param head Head der verketteten Liste von Einträgen
 * @param Art  Art nach der sortiert werden soll
 * @return sortierter Head der verketteten Liste von Einträgen
 */
ENTRY *insertionSort(ENTRY *head, SORTBY sort) {
    ENTRY *x, *y, *e;
    
    x = head;
    head = NULL;
    
    if (sort == 0) { /* Sortierung anhand der IDs */
        info("Insertionsort über IDs");
        while (x) {
            e = x;
            x = x->next;
            if (head) {
                if (e->id > head->id) {
                    y = head;
                    while ((y->next) && (e->id > y->next->id)) y = y->next;
                    e->next = y->next;
                    y->next = e;
                } else {
                    e->next = head;
                    head = e ;
                }
            } else {
                e->next = NULL;
                head = e ;
            }
        }
    } else if (sort == 1) { /* Sortierung anhand der Nachnamen */
        info("Insertionsort über Nachnamen");
        while (x) {
            e = x;
            x = x->next;
            if (head) {
                if (strcmp(e->lastName, head->lastName) > 0) {
                    y = head;
                    while ((y->next) && (strcmp(e->lastName, y->next->lastName) > 0)) y = y->next;
                    e->next = y->next;
                    y->next = e;
                } else {
                    e->next = head;
                    head = e ;
                }
            } else {
                e->next = NULL;
                head = e ;
            }
        }
    } else if (sort == 2) { /* Sortierung anhand der Vornamen */
        info("Insertionsort über Vornamen");
        while (x) {
            e = x;
            x = x->next;
            if (head) {
                if (strcmp(e->firstName, head->firstName) > 0) {
                    y = head;
                    while ((y->next) && (strcmp(e->firstName, y->next->firstName) > 0)) y = y->next;
                    e->next = y->next;
                    y->next = e;
                } else {
                    e->next = head;
                    head = e ;
                }
            } else {
                e->next = NULL;
                head = e ;
            }
        }
    }

    return head;
}

/**
 * Leert den allokierten Speicher.
 * 
 * @param head Head der verketteten Liste von Einträgen
 */
void freeAll(ENTRY *head) {
    ENTRY *current, *tmp;

    if (head) {
        current = head->next;
        head->next = NULL;

        while (current) {
            tmp = current->next;
            
            free(current);

            current = tmp;
        }
    }
}

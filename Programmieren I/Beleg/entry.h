/**
 * Definiert die ENTRY-Struktur und bietet Prototypen zum verarbeiten von Einträgen an.
 * 
 * @author Vincent Nadoll
 */

/**
 * Element der vergetteten Liste von Einträgen
 * 
 * @param id ID des Eintrags
 * @param lastName Nachname der Person
 * @param firstName Vorname der Person
 * @param numer Telefonnummer der Person
 * @param next Pointer auf das nächste Elemente der verketteten Liste
 */
typedef struct node {
    int id;
    char *lastName;
    char *firstName;
    char *number;
    struct node *next;
} ENTRY;

/* Enum mit Sortiermöglichkeiten */
typedef enum {
    id,
    lastName,
    firstName
} SORTBY;

ENTRY *head; /* Head der verketteten Liste als globale Variable */

ENTRY *insert(int id, char *lastName, char *firstName, char *number, ENTRY *head);
ENTRY *insertionSort(ENTRY *head, SORTBY sort);
ENTRY *search4Str(char *str, ENTRY *head);
ENTRY *search4Id(int id, ENTRY *head);
ENTRY *delete (ENTRY *entry, ENTRY *head);
void freeAll(ENTRY *current);

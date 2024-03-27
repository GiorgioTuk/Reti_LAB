#include <stdio.h>
#include "database.h"

//funzioni print
void printIndexNodeString(IndexNodeString* node);
void printIndexNodeInt(IndexNodeInt* node);
void printDatabase(Database *database);


int main() {
    // Inizializza il database
    Database myDatabase = {NULL, NULL, NULL, NULL};

    // Crea alcune persone
    Persona persona1 = {"Mario", "Rossi", "Via Roma 1", 30};
    Persona persona2 = {"Luigi", "Verdi", "Via Milano 2", 25};
    //Persona persona3 = {"Anna", "Bianchi", "Via Napoli 3", 28};
    Persona persona3 = {"Sara", "Dindas", "Via chiapperugia 7", NULL};

    // Inserisce le persone nel database
    insert(&myDatabase, &persona1);
    insert(&myDatabase, &persona2);
    insert(&myDatabase, &persona3);

    // Idealmente, qui vorresti stampare il contenuto del database o fare delle ricerche
    // per testare che l'inserimento sia avvenuto correttamente.
    // Poiché le funzioni di stampa e ricerca non sono implementate,
    // questa parte è omessa.
    printf("Contenuto del Database dopo l'inserimento:\n");
    printDatabase(&myDatabase);

    Persona* ricerca = findByName(&myDatabase, "Sara");
    Persona* ricerca1 = findBySurname(&myDatabase, "Rossi");
    Persona* ricerca2 = findByAddress(&myDatabase, "Via Roma 1");
    Persona* ricerca3 = findByAge(&myDatabase, 30);

    printf("nome: %s, cognome: %s, address: %s, age: %d\n", ricerca->name, ricerca->surname, ricerca->address, ricerca->age);
    printf("nome: %s, cognome: %s, address: %s, age: %d\n", ricerca1->name, ricerca1->surname, ricerca1->address, ricerca1->age);
    printf("nome: %s, cognome: %s, address: %s, age: %d\n", ricerca2->name, ricerca2->surname, ricerca2->address, ricerca2->age);
    printf("nome: %s, cognome: %s, address: %s, age: %d\n", ricerca3->name, ricerca3->surname, ricerca3->address, ricerca3->age);

    return 0;
}

void printIndexNodeString(IndexNodeString* node) {
    if (node != NULL) {
        printIndexNodeString(node->left);
        printf("%s\n", node->value);
        printIndexNodeString(node->right);
    }
}

void printIndexNodeInt(IndexNodeInt* node) {
    if (node != NULL) {
        printIndexNodeInt(node->left);
        printf("%d\n", node->value);
        printIndexNodeInt(node->right);
    }
}

void printDatabase(Database *database) {
    printf("Name Index:\n");
    printIndexNodeString(database->name);
    printf("\nSurname Index:\n");
    printIndexNodeString(database->surname);
    printf("\nAddress Index:\n");
    printIndexNodeString(database->address);
    printf("\nAge Index:\n");
    printIndexNodeInt(database->age);
}

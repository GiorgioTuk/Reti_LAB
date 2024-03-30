#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

/*
In questa implementazione non gestisco il caso di valori duplicati.
La logica dietro l'implemntazione delle funzioni è la seguente:

1. inserimento -> gli alberi generati dall'inserimento di stringhe e interi sono ordinati rispettivamente:
    - In base all'ordine lessicografico le stringhe di ordine minore vengono messe nel sotto albero sinistro,
      quelle di ordine maggiore vengono messe nel sotto albero destro
    - Come punto sopra ma per gli interi
2. Ricerca -> Ricarca stringhe e valori con la stessa logica dell'inserimento
*/

//funzioni per inserire nodi nei vari alberi
IndexNodeString* insertIndexNodeString(IndexNodeString* node, char* value, Persona* persona);
IndexNodeInt* insertIndexNodeInt(IndexNodeInt* node, int value, Persona* persona);

//funzioni helper
Persona* findByNameHelper(IndexNodeString* node, char* name);
Persona* findBySurnameHelper(IndexNodeString* node, char* surname);
Persona* findByAddressHelper(IndexNodeString* node, char* address);
Persona* findByAgeHelper(IndexNodeInt* node, int age);

IndexNodeString* insertIndexNodeString(IndexNodeString* node, char* value, Persona* persona) {
    if (node == NULL) {
        node = (IndexNodeString*)malloc(sizeof(IndexNodeString));
        node->value = strdup(value);
        node->left = node->right = NULL;
        node->persona = persona;  // Collega il nodo a Persona
        return node;
    } else if (strcmp(value, node->value) < 0) {
        node->left = insertIndexNodeString(node->left, value, persona);
    } else if (strcmp(value, node->value) > 0) {
        node->right = insertIndexNodeString(node->right, value, persona);
    }
    return node;
}

IndexNodeInt* insertIndexNodeInt(IndexNodeInt* node, int value, Persona* persona) {
    if (node == NULL) {
        node = (IndexNodeInt*)malloc(sizeof(IndexNodeInt));
        node->value = value;
        node->left = node->right = NULL;
        node->persona = persona; // Collega il nodo a Persona
        return node;
    } else if (value < node->value) {
        node->left = insertIndexNodeInt(node->left, value, persona);
    } else if (value > node->value) {
        node->right = insertIndexNodeInt(node->right, value, persona);
    }
    
    return node;
}
// Inserisce una nuova Persona nel database
void insert(Database * database, Persona * persona) {
    database->name = insertIndexNodeString(database->name, persona->name, persona);
    database->surname = insertIndexNodeString(database->surname, persona->surname, persona);
    database->address = insertIndexNodeString(database->address, persona->address, persona);
    database->age = insertIndexNodeInt(database->age, persona->age, persona);

}

//FIND BY NAME
Persona* findByNameHelper(IndexNodeString* node, char* name) {
    if (node == NULL) {
        return NULL; // Nome non trovato
    }
    int cmp = strcmp(name, node->value);
    if (cmp < 0) {
        return findByNameHelper(node->left, name); // Cerca a sinistra
    } else if (cmp > 0) {
        return findByNameHelper(node->right, name); // Cerca a destra
    } else {
        return node->persona; // Nome trovato, restituisce il puntatore a Persona
    }
}

Persona* findByName(Database * database, char * name) {
    return findByNameHelper(database->name, name);
}

//FIND BY SURNAME
Persona* findBySurnameHelper(IndexNodeString* node, char* surname) {
    if (node == NULL) {
        return NULL; // Nome non trovato
    }
    int cmp = strcmp(surname, node->value);
    if (cmp < 0) {
        return findBySurnameHelper(node->left, surname); // Cerca a sinistra
    } else if (cmp > 0) {
        return findBySurnameHelper(node->right, surname); // Cerca a destra
    } else {
        return node->persona; // Nome trovato, restituisce il puntatore a Persona
    }
}

Persona* findBySurname(Database * database, char * surname) {
    return findBySurnameHelper(database->surname, surname);
}

//FIND BY ADDRESS
Persona* findByAddressHelper(IndexNodeString* node, char* address) {
    if (node == NULL) {
        return NULL; // Nome non trovato
    }
    int cmp = strcmp(address, node->value);
    if (cmp < 0) {
        return findByAddressHelper(node->left, address); // Cerca a sinistra
    } else if (cmp > 0) {
        return findByAddressHelper(node->right, address); // Cerca a destra
    } else {
        return node->persona; // Nome trovato, restituisce il puntatore a Persona
    }
}

Persona* findByAddress(Database * database, char * address) {
    return findByAddressHelper(database->address, address);
}

//FIND BY AGE
Persona* findByAgeHelper(IndexNodeInt* node, int age) {
    if (node == NULL) {
        return NULL; // Età non trovata
    }
    
    if (age < node->value) {
        return findByAgeHelper(node->left, age); // Cerca nel sottoalbero sinistro
    } else if (age > node->value) {
        return findByAgeHelper(node->right, age); // Cerca nel sottoalbero destro
    } else {
        return node->persona;
    }
}

Persona* findByAge(Database * database, int age) {
    return findByAgeHelper(database->age, age);
}
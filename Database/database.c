#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
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
    // Non inserire duplicati o gestisci come preferisci
    return node;
}

IndexNodeInt* insertIndexNodeInt(IndexNodeInt* node, int value, Persona* persona) {
    if (node == NULL) {
        node = (IndexNodeInt*)malloc(sizeof(IndexNodeInt));
        node->value = value;
        node->left = node->right = NULL;
        node->persona = persona; // Collegamento diretto al record Persona
        return node;
    } else if (value < node->value) {
        node->left = insertIndexNodeInt(node->left, value, persona);
    } else if (value > node->value) {
        node->right = insertIndexNodeInt(node->right, value, persona);
    }
    // Gestione dei duplicati omessa per brevità
    return node;
}
// Inserisce una nuova Persona nel database
void insert(Database * database, Persona * persona) {
    // Implementazione dell'inserimento qui
    // Nota: Questo pseudocodice mostra come iniziare. Dovrai implementare la logica per
    // aggiungere il nodo agli alberi degli indici, gestendo i casi in cui l'albero è vuoto
    // e quando non lo è, seguendo le regole di un albero binario di ricerca.
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
        // Età trovata, restituisce il puntatore a Persona
        // Questo presuppone che ci sia al massimo una Persona per ogni età. Se ci sono più persone
        // con la stessa età, questa implementazione restituirà solo la prima trovata.
        return node->persona;
    }
}

Persona* findByAge(Database * database, int age) {
    return findByAgeHelper(database->age, age);
}






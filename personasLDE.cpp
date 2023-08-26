#include "../include/personasLDE.h"

struct doubleNode {
    TPersona persona;
    doubleNode* next;
    doubleNode* prev;
};

struct rep_personasLDE {
    doubleNode* start;
    doubleNode* end;
    nat sum;
};

TPersonasLDE crearTPersonasLDE(){
    TPersonasLDE p = new rep_personasLDE;
    p->start = NULL;
    p->end = NULL;
    p->sum = 0;
    return p;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos) {

    doubleNode* ptr = new doubleNode;
    ptr->persona = persona;
    ptr->next = NULL;
    ptr->prev = NULL;

    if (personas->start == NULL) { 
        personas->start = ptr;
        personas->end = ptr;

    } else if (pos == 1) { 
        ptr->next = personas->start;
        personas->start->prev = ptr;
        personas->start = ptr;

    } else {
        doubleNode* iter = personas->start;
        nat amount = 1;

        while (amount < pos && iter != NULL) {
            iter = iter->next;
            amount++;
        }

        if (iter == NULL) {
            personas->end->next = ptr;
            ptr->prev = personas->end;
            personas->end = ptr;

        } else { 
            ptr->next = iter;
            ptr->prev = iter->prev;
            iter->prev->next = ptr;
            iter->prev = ptr;

        }
    }
    personas->sum++;
}

void liberarTPersonasLDE(TPersonasLDE &personas){
    doubleNode* ptr;

    while (personas->start != NULL) {
        ptr = personas->start;
        personas->start = personas->start->next;
        liberarTPersona(ptr->persona);
        delete ptr;
    }
    delete personas->start;
    personas->start = NULL;
    personas->end = NULL;

    delete personas;
    personas = NULL;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    if (personas->start != NULL) {

        doubleNode* iter = personas->start;
        while (iter != NULL) {
            imprimirTPersona(iter->persona);
            iter = iter->next;
        }
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    return personas->sum;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas->start != NULL) {
        if (personas->start == personas->end) {
            doubleNode* toRemove = personas->start;

            personas->start = NULL;
            personas->end = NULL;

            liberarTPersona(toRemove->persona);
            delete toRemove;
            toRemove = NULL;
            personas->sum--;

        } else {
            doubleNode* toRemove = personas->start;

            personas->start = personas->start->next;
            liberarTPersona(toRemove->persona);
            delete toRemove;
            toRemove = NULL;
            personas->sum--;
        }
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){

    if (personas->end != NULL) {
        if (personas->start == personas->end) {
            doubleNode* toRemove = personas->end;
            personas->end = NULL;
            personas->start = NULL;

            liberarTPersona(toRemove->persona);
            delete toRemove;
            toRemove = NULL;
            personas->sum--;

        } else {
            doubleNode* toRemove = personas->end;
            personas->end = personas->end->prev;
            personas->end->next = NULL;

            liberarTPersona(toRemove->persona);
            delete toRemove;
            toRemove = NULL;
            personas->sum--;
        }
        
    }
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    doubleNode* iter = personas->start;
    bool res = false;
    if (personas == NULL) {
        res = false;
    } else {
        while (iter != NULL) {
            if (idTPersona(iter->persona) == id) {
                res = true;
            }
            iter = iter->next;
        }
    }
    return res;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    TPersona pessoa = NULL;
    doubleNode* iter = personas->start;
    if (personas == NULL) {
        pessoa = NULL;
    } else {
        while (iter != NULL) {
            if (idTPersona(iter->persona) == id) {
                pessoa = iter->persona;
            }
            iter = iter->next;
        }
    }
    return pessoa;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2) {
    TPersonasLDE newDLL = crearTPersonasLDE();

    if (personas1->start == NULL) {
        if (personas2->start == NULL) {
            delete newDLL;
            return NULL;
        }

        newDLL->start = personas2->start;
        newDLL->end = personas2->end;
        newDLL->sum = personas2->sum;

    } else if (personas2->start == NULL) {
        newDLL->start = personas1->start;
        newDLL->end = personas1->end;
        newDLL->sum = personas1->sum;

    } else {
        newDLL->start = personas1->start;
        personas1->end->next = personas2->start;
        personas2->start->prev = personas1->end;
        newDLL->end = personas2->end;
        newDLL->sum = personas1->sum + personas2->sum;

    }

    delete personas1;
    delete personas2;

    return newDLL;
}

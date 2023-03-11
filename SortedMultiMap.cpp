#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->head = nullptr;
    this->rel = r;
}
//best theta(1) ;worst theta(n^2) ;average O(n^2)
void SortedMultiMap::add(TKey c, TValue v) {
    SLLNode *currentn = this->head;
    SLLNode *prevn = nullptr;
    if (this->head == nullptr) {
        SLLNode *newn = new SLLNode;
        newn->info = c;
        newn->value = new SLLValues;
        newn->value->info = v;           //daca lista e goala
        newn->value->next = nullptr;
        newn->next = nullptr;
        this->head = newn;
    }
    else {
        bool added_node= false;
        while (currentn!= nullptr && rel(currentn->info,c)) {
            if(currentn->info==c){
                bool added= false;
                SLLValues *current_value = currentn->value;
                while (current_value->next!= nullptr){
                    if (current_value->info==v){
                        added= true;
                        break;
                    }
                    current_value=current_value->next;
                }
                if(!added){
                    SLLValues *new_value=new SLLValues;  //daca trebuie adaugata doar valoarea
                    new_value->info=v;
                    new_value->next= nullptr;
                    current_value->next=new_value;
                    added_node= true;
                }

            }
            prevn = currentn;
            currentn=currentn->next;
        }

        if (!added_node) {
            if (currentn== nullptr && rel(prevn->info, c) == true) {
                SLLNode *newn = new SLLNode;
                newn->info = c;
                newn->value = new SLLValues;   //daca trebuie adaugata o pereche la sf
                newn->value->info = v;
                newn->value->next = nullptr;
                newn->next = nullptr;
                prevn->next = newn;

            } else {
                SLLNode *newn = new SLLNode;
                newn->info = c;
                newn->value = new SLLValues;
                newn->value->info = v;
                newn->value->next = nullptr; //daca trebuie adaugata o pereche la mijloc sau pe prima pozitie
                newn->next = currentn;
                if(prevn== nullptr)
                    this->head = newn;
                else
                    prevn->next=newn;

            }
        }
    }
}
//best theta(1) ;worst theta(n) ;average:O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> liste;
    SLLNode *currentn = this->head;
    if (this->head == nullptr) return  liste;

    while (currentn->info != c and currentn->next != nullptr)
        currentn = currentn->next;


    if (currentn->info == c) {
        SLLValues *current_value = currentn->value;
        while (current_value!= nullptr){
            liste.push_back(current_value->info);
            current_value=current_value->next;
        }
    }

    return liste;
}
//best theta(1) ;worst theta(n^2) ;average O(n^2)
bool SortedMultiMap::remove(TKey c, TValue v) {
    SLLNode *currentn = this->head;
    SLLNode *prevn = nullptr;

    while (currentn != nullptr) {
        if (currentn->info==c) {
            SLLValues *current_value=currentn->value;
            SLLValues *prev_value= nullptr;
            bool found= false;
            while (current_value!= nullptr) {
                if (current_value->info == v){   //cautam valoarea care trebuie stearsa
                    found=true;
                    break;
                }
                prev_value=current_value;
                current_value=current_value->next;
            }
            if(found) {
                if (prev_value == nullptr) {
                    if (prevn == nullptr && current_value->next == nullptr) {
                        delete current_value;
                        this->head = this->head->next; //delete perechea<k,v> daca e pe prima pozitie ->in totalitate
                        delete currentn;
                        return true;
                    } else if (current_value->next != nullptr) {
                            currentn->value = current_value->next;
                            delete current_value;
                            return true;

                    } else if (prevn != nullptr && current_value->next== nullptr) {
                        delete current_value;
                        prevn->next = currentn->next;
                        delete currentn;
                        return true;
                    }
                }
            }

        }
        prevn = currentn;
        currentn = currentn->next;
    }

    return false;
}

//best theta(1) ;worst theta(n) ;average O(n)
int SortedMultiMap::size() const {
    int ct = 0;
    SLLNode *currentn = this->head;
    while (currentn != nullptr) {
        SLLValues *currentv = currentn->value;
        while (currentv != nullptr) {
            ct++;
            currentv = currentv->next;
        }
        currentn = currentn->next;
    }
    return ct;
}
//best worst average theta(1)
bool SortedMultiMap::isEmpty() const {
    if (this->head == nullptr)
        return true;

    return false;
}
//best worst average theta(1)
SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}
//best theta(1) ;worst theta(n^2); average O(n^2)
SortedMultiMap::~SortedMultiMap() {
    SLLNode *to_delete = this->head;

    while (this->head!=nullptr) {
        SLLValues *v_h = this->head->value;
        SLLValues *to_d = this->head->value;
        this->head = this->head->next;

        while (v_h != nullptr) {
            v_h = v_h->next;
            delete to_d;
            to_d = v_h;
        }

        delete to_delete;
        to_delete = this->head;
    }
}

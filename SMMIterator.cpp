#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	index_key=map.head;
    if(index_key!= nullptr){
        index_values=map.head->value;
    }else {
        index_values= nullptr;
    }
}
//best,worst,average theta(1)
void SMMIterator::first(){
    index_key=map.head;
    if(index_key!= nullptr){
        index_values=map.head->value;
    }else {
        index_values= nullptr;
    }
}
//best,worst,average theta(1)
void SMMIterator::first_k() {
    index_key=map.head;
}
//best,worst,average theta(1)
void SMMIterator::next(){
    if(valid()){
        if(index_values->next!= nullptr)
            index_values=index_values->next;
        else {
            index_key = index_key->next;
            if (valid())
            index_values = index_key->value;
        }
    }else{
        throw exception();
    }
}
//best,worst,average theta(1)
void SMMIterator::next_k() {
    if(valid_k())
        index_key=index_key->next;
    else
        throw exception();
}
//best,worst,average theta(1)
bool SMMIterator::valid() const{
	if(index_key!= nullptr && index_values!= nullptr)
        return true;
	return false;
}
//best,worst,average theta(1)
bool SMMIterator::valid_k() const {
    if(index_key!= nullptr)
        return true;
    return false;
}
//best,worst,average theta(1)
TElem SMMIterator::getCurrent() const{
	if(valid())
         return make_pair(index_key->info,index_values->info);
    throw exception();
}
//best,worst,average theta(1)
TKey SMMIterator::getCurrent_k() const {
    if(valid_k())
        return index_key->info;
    throw exception();
}



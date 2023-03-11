#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	SLLNode* index_key;
    SLLValues* index_values;


public:
	void first();
    void first_k();
	void next();
    void next_k();
	bool valid() const;
    bool valid_k() const;
   	TElem getCurrent() const;
       TKey getCurrent_k() const;
};


#pragma once
#include "Table.h"

class HashTable : public Table
{
protected:
    virtual size_t HashFunc(const Key key);
public:
    HashTable(): Table(){
        
    }
};
#pragma once 
#include"ArrayTable.h"

class ScanTable: public ArrayTable{
    public:
    ScanTable():ArrayTable(){}
    ScanTable(size_t size):ArrayTable(size){}
    virtual PDataValue FindRecord(Key key);
    virtual void DelRecotd(Key key);
    virtual void InsRecord(Key key, PDataValue value);
};
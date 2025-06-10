#pragma once 
#include "TabRecord.h"

class Table{
protected:
    size_t _dataCount;
    int _efficiency;
public:
    Table() {_dataCount=0; _efficiency = 0;}
    virtual ~Table() {}

    size_t GetDataCount()const {return _dataCount;}
    int GetEfficiency() const {return _efficiency;}
    bool IsEmpty()const {return _dataCount == 0;}
    virtual bool IsFull() const = 0;

    virtual bool Reset() = 0;
    virtual bool IsTabEnded() const = 0;
    virtual bool GoNext() = 0;

    virtual Key GetKey() const = 0;
    virtual PDataValue GetValue() const = 0;

    virtual PDataValue FindRecord(Key key) = 0;
    virtual void DelRecotd(Key key) = 0;
    virtual void InsRecord(Key key, PDataValue value)= 0;
    
};
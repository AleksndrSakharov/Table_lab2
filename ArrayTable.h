#pragma once
#include "Table.h"

enum DataPos {First, Last, Current};
using PTabRecord = TabRecord*;

class ArrayTable: public Table{
protected:
    size_t _tabSize;
    size_t _curPos;
    PTabRecord* _records;
public:
    ArrayTable(){
        _tabSize = 25;
        _curPos = 0;
        _records = new PTabRecord[_tabSize];
    }

    ArrayTable(size_t tabSize){
        _tabSize = tabSize;
        _records = new PTabRecord[_tabSize];
        for(size_t i = 0; i < _tabSize; i++){
            _records[i] = nullptr;
        }
        _curPos = 0;
    }
    ~ArrayTable() {
        for(size_t i = 0; i < _dataCount; i++){
            delete _records[i];
        }
        delete[] _records;
    }

    size_t GetSizeTable(){
        return _tabSize;
    }
    virtual bool IsFull() const{
        return _dataCount >= _tabSize;
    }

    virtual Key GetKey() const{
        return GetKey(DataPos::Current);
    }
    virtual PDataValue GetValue() const{
        return GetValue(DataPos::Current);
    }

    virtual Key GetKey(DataPos position) const;
    virtual PDataValue GetValue(DataPos position) const;
    virtual void DelRecotd(Key key) = 0;
    virtual void InsRecord(Key key, PDataValue value)= 0;

    virtual bool Reset();
    virtual bool IsTabEnded() const;
    virtual bool GoNext();

    virtual bool SetCurrentPos(size_t pos);
    size_t GetCurrentPos() const;

    friend class SortTable;
    
};

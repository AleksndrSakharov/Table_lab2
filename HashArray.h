#pragma once
#include "HashTable.h"
#include "ArrayTable.h"
#include "TabRecord.h"

class HashArray : public HashTable {
protected: 
    size_t _tabSize;
    size_t _hashStep;
    PTabRecord* _records;
    size_t _currPos;
    long _freePos;
    PTabRecord _mark;
    size_t GetNExtPos(size_t pos){
        return (pos + _hashStep) % _tabSize;
    }
public:
    HashArray(size_t size = 100, size_t hashStep = 7);
    ~HashArray();

    bool IsFull() const override;
    bool Reset() override;
    bool IsTabEnded() const override;
    bool GoNext() override;

    Key GetKey() const override;
    PDataValue GetValue() const override;

    PDataValue FindRecord(Key key) override;
    void DelRecotd(Key key) override;
    void InsRecord(Key key, PDataValue value) override;

};
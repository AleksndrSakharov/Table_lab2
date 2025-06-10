#pragma once
#include <list>
#include "HashArray.h"

class HashListArray : public HashTable
{
private:
    size_t _tabSize;
    size_t _curList;
    std::list<PTabRecord>::iterator _curElem;
    std::list<PTabRecord>* _lists;
public:
    HashListArray(size_t tabSize);
    ~HashListArray();

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
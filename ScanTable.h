#pragma once 
#include"ArrayTable.h"
#include <ctime>
#include <random>
#include <unordered_set>
using namespace std;



class ScanTable: public ArrayTable{
    // private:
    unordered_set<Key> myset;
    public:
    // void FillMySet(TabRecord** tabs);
    ScanTable():ArrayTable(){}
    ScanTable(size_t size):ArrayTable(size){}
    void ResetEff();
    virtual PDataValue FindRecord(Key key);
    PDataValue FindRecordRand(int cnt, Key tkey);
    virtual void DelRecord(Key key);
    virtual void InsRecord(Key key, PDataValue value);
};
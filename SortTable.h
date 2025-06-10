#pragma once
#include "ScanTable.h"


enum SortMethod {Insert, Merge, Quick};

class SortTable : public ScanTable
{
public:
    SortMethod _sortMethod;
    void InsertSort(PTabRecord *data, size_t count);

    void MergeSort(PTabRecord *data, size_t count);
    void MergeSorter(PTabRecord* &data, PTabRecord* &buffer, size_t size);
    void MergeData(PTabRecord* &data, PTabRecord* &buffer, size_t n1, size_t n2);

    void QuickSort(PTabRecord *data, size_t count);
    void QuickSplit(PTabRecord *data, size_t count, size_t& pivot);
    void ResetEff();
    void SortData();

public:
    SortTable() : ScanTable(){
        _tabSize = 25;
    }

    SortTable(size_t tabSize) : ScanTable(tabSize){
        _tabSize = tabSize;
    }
    SortTable(const ScanTable& st);

    SortTable& operator=(const ScanTable& st);

    SortMethod GetSortMethod() const{
        return _sortMethod;
    }
    void SetSortMethod(SortMethod sortMethod) {
        _sortMethod = sortMethod;
    }

    virtual PDataValue FindRecord(Key key) override;
    virtual void DelRecord(Key key) override;
    virtual void InsRecord(Key key, PDataValue value) override;
};
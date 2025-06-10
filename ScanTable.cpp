#include"ScanTable.h"

PDataValue ScanTable::FindRecord(Key key){
    int i = 0;
    for(i; i < _dataCount; i++){
        if(key == _records[i]->_key){
            break;
        }
    }
    _efficiency = i+1;
    if(i < _dataCount){
        _curPos = i;
        return _records[i]->_data;
    }
    return nullptr;
}
void ScanTable::DelRecotd(Key key){
    if(FindRecord(key) == nullptr) throw "!!!";
    delete _records[_curPos];
    _records[_curPos] = _records[_dataCount - 1];
    _records[--_dataCount] = nullptr;
    Reset();
}
void ScanTable::InsRecord(Key key, PDataValue data){
    if(IsFull()){
        throw "Table is Full";
    }
    _records[_dataCount++] = new TabRecord(key, data);
}
#include "HashArray.h"

HashArray::HashArray(size_t size, size_t hashStep){
    _tabSize = size;
    _hashStep = hashStep;
    _records = new PTabRecord[_tabSize];
    for (size_t i = 0; i < _tabSize; i++){
        _records[i] = nullptr;
    }
    _mark = new TabRecord();
}

HashArray::~HashArray(){
    for (size_t i = 0; i < _tabSize; i++){
        delete _records[i];
    }
    delete [] _records;
    delete _mark;
}

bool HashArray::IsFull() const{
    return _dataCount >= _tabSize;
}

bool HashArray::Reset(){
    _currPos = 0;
    while (_currPos < _dataCount){
        if (_records[_currPos] != nullptr && _records[_currPos] != _mark){
            break;
        }
        else _currPos++;
    }
    return IsTabEnded();
}

bool HashArray::IsTabEnded() const{
    return _currPos == _tabSize;
}

bool HashArray::GoNext(){
    if (IsTabEnded()){
        return false;
    }
    while (++_currPos < _tabSize){
        if (_records[_currPos] != nullptr && _records[_currPos] != _mark){
            break;
        }
    }
    return IsTabEnded();
}

Key HashArray::GetKey() const{
    if (_currPos >= _tabSize) return "";
    return _records[_currPos]->GetKey();
}

PDataValue HashArray::GetValue() const{
    if (_currPos >= _tabSize) return nullptr;
    return _records[_currPos]->GetData();
}

PDataValue HashArray::FindRecord(Key key){
    _efficiency = 0;
    _freePos = -1;
    PDataValue tmp = nullptr;
    _currPos = HashFunc(key) % _tabSize;
    for (size_t i = 0; i < _tabSize; i++){
        _efficiency++;
        if (_records[_currPos] == nullptr) break;
        else{
            if (_records[_currPos] == _mark) {
                if (_freePos == -1) _freePos = _currPos;
                
            }
            else{
                if (_records[_currPos]->GetKey() == key){
                    tmp = _records[_currPos]->GetData();
                    break;
                }
            }
        }
        _currPos = GetNExtPos(_currPos);
    }
    return tmp;
}

void HashArray::InsRecord(Key key, PDataValue data){
    if (IsFull()) throw "Table is Full";
    PDataValue tmp = FindRecord(key);
    if (tmp != nullptr) throw "Dublicate";
    if (_freePos != -1) _currPos = _freePos;
    _records[_currPos] = new TabRecord(key, data);
    _dataCount++;
}

void HashArray::DelRecotd(Key key){
    if (!(FindRecord(key))) throw "No value";
    delete _records[_currPos];
    _records[_currPos] = _mark;
    _dataCount--;
}


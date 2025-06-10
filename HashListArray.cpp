#include "HashListArray.h"

bool HashListArray::IsFull() const{
    try{
        PTabRecord tmp = new TabRecord("", nullptr);
    }
    catch (const char* ) {
        return true;
    }
    return false;
}

HashListArray::HashListArray(size_t tabSize) {
    _tabSize = tabSize;
    _lists = new std::list<PTabRecord>[tabSize];
    _efficiency = 0;
    _curList = 0;
}

HashListArray::~HashListArray(){
    for (size_t i = 0; i < _tabSize; i++){
        for (auto rec: _lists[i]) {
            delete rec;
        }
    }
    delete [] _lists;
}

bool HashListArray::GoNext() {
    if (!IsTabEnded()){
        bool flg = false;
        while (_lists[_curList].empty()){
            _curElem = _lists[_curList].begin();
            _curList += 1;
            flg = true;
        }
        if (!flg){
            _curElem++;
        }
        if (_curElem == _lists[_curList].end()){
            _curList += 1;
            _curElem = _lists[_curList].begin();
        }
    }
    return IsTabEnded();
}

bool HashListArray::Reset(){
    _curList = 0;
    _curElem = _lists[_curList].begin();
    return IsTabEnded();
}

bool HashListArray::IsTabEnded() const{
    return _curList ==  _tabSize;
}

PDataValue HashListArray::FindRecord(Key key){
    _curList = HashFunc(key) % _tabSize;
    _efficiency = 0;
    PDataValue tmp = nullptr;
    auto list = _lists[_curList];
    for (auto current=list.begin(); current != list.end(); current++){
        _efficiency++;
        if ((*current)->GetKey() == key){
            _curElem = current;
            tmp = (*current)->GetData();
            break;
        }
    }
    return tmp;
}
void HashListArray::DelRecotd(Key key){
    PDataValue tmp = FindRecord(key);
    if (tmp == nullptr) throw "No record";
    else{
        _dataCount--;
        _lists[_curList].erase(_curElem);
    }
}
void HashListArray::InsRecord(Key key, PDataValue value){
    if (IsFull()){
        throw "No memory";
    }
    PDataValue tmp = FindRecord(key);
    if (tmp != nullptr){
        throw "Record dublication";
    }
    _dataCount++;
    _lists[_curList].push_front(new TabRecord(key,value));
}

Key HashListArray::GetKey() const{
    if (_curList >= _tabSize){
        return "";
    }
    return (*_curElem)->GetKey();
}
PDataValue HashListArray::GetValue() const{
    if (_curList >= _tabSize){
        return nullptr;
    }
    return (*_curElem)->GetData();
}


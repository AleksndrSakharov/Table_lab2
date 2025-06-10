#include"ScanTable.h"

// void ScanTable::FillMySet(TabRecord** tabs){


// }

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

PDataValue ScanTable::FindRecordRand(int cnt, Key tkey){
    Key key = "key_" + std::to_string(rand() % cnt);
    int k = 0;
    while (true){
        Key key = "key_" + std::to_string(rand() % cnt);
        k++;
        if(myset.find(key) == myset.end() && key == tkey){
            myset.insert(key);
            break;
        }
    }
    _efficiency += k;
    if(k < _dataCount){
        _curPos = k;
        return _records[k]->_data;
    }
    return nullptr;
}


void ScanTable::DelRecord(Key key){
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

void ScanTable::ResetEff(){
    _efficiency = 0;
}
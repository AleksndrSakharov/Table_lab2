#include"ArrayTable.h"

Key ArrayTable::GetKey(DataPos position) const{
    if(!IsEmpty()){
        switch (position)
        {
        case DataPos::First:
            return _records[0]->_key;
        case DataPos::Current:
            return _records[_curPos]->_key;
        case DataPos::Last:
            return _records[_dataCount - 1]->_key;
        default:
            break;
        }
    }
    return"";
}
PDataValue ArrayTable::GetValue(DataPos position) const{
    if(!IsEmpty()){
        switch (position)
        {
        case DataPos::First:
            return _records[0]->_data;
        case DataPos::Current:
            return _records[_curPos]->_data;
        case DataPos::Last:
            return _records[_dataCount - 1]->_data;
        default:
            break;
        }
    }
    return nullptr;
}
bool ArrayTable::Reset(){
    _curPos = 0;
    return IsTabEnded();
}

bool ArrayTable::IsTabEnded() const{
    return _curPos >= _dataCount;
}
bool ArrayTable::GoNext(){
    if(!IsTabEnded()){
        _curPos++;
    }
    return IsTabEnded();
}
bool ArrayTable::SetCurrentPos(size_t pos){
    _curPos = pos < _dataCount ? pos : 0;
    return IsTabEnded();
}
size_t ArrayTable::GetCurrentPos() const{
    return _curPos;
}
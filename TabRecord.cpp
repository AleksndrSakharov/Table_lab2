#include "TabRecord.h"

PDataValue TabRecord::GetCopy(){
    PDataValue tmp = new TabRecord(_key, _data);
    return tmp;
}
const void TabRecord::Print(std::ostream& os)const{
    os << _key << _data << std::endl;
}
TabRecord& TabRecord::operator=(const TabRecord& tr){
    _key = tr._key;
    _data = tr._data;
    return *this;
}
bool TabRecord::operator==(const TabRecord& tr) const{
    return (_key == tr._key)&(_data == tr._data);
}
bool TabRecord::operator<(const TabRecord& tr) const{
    return (_key < tr._key)&(_data < tr._data);
}
 bool TabRecord::operator>(const TabRecord& tr) const{
    return (_key > tr._key)&(_data > tr._data);
}
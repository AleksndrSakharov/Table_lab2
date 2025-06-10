#include "HashTable.h"

size_t HashTable::HashFunc(const Key key){
    size_t HashValue = 0x811c9dc5;
    size_t size = key.size();
    for (char b : key){
        HashValue = (HashValue * 0x01000193) & 0xFFFFFFFF;
        HashValue ^= b;
    }
    return HashValue;
}
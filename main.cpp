#include "TestKitTable.h"



int main() {
    TabRecord** testRecords = generateTestRecords();
    
    TestScanTable(testRecords);

    TestSortTable();
    for (int i = 0; i < count; i++) {
        delete testRecords[i];
    }
    delete[] testRecords;
    
    return 0;
}
#include "TestKitTable.h"



int main() {
    srand(time(NULL));
    TestKitTable testkit =  TestKitTable();
    
    testkit.TestScanTable();

    testkit.TestSortTable();
   
    return 0;
}
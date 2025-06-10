#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <limits>
#include "SortTable.h"
#include "ScanTable.h"
#include "TabRecord.h"
#include "Marks.h"

const int count = 10000;

TabRecord** generateTestRecords() {
    std::srand(std::time(NULL));
    TabRecord** records = new TabRecord*[count];
    
    for (int i = 0; i < count; i++) {
        Key key = "key_" + std::to_string(i + 1);
        PDataValue val = new Marks(1, 2, 3, 4, 5);
        records[i] = new TabRecord(key, val);
    }
    
    for (int i = 0; i < count; i++) {
        int swapWith = rand() % count;
        Key temp = records[i]->GetKey();
        records[i]->SetKey(records[swapWith]->GetKey());
        records[swapWith]->SetKey(temp);
    }
    
    return records;
}

void FillTable(ScanTable &table, TabRecord** records) {
    for (int i = 0; i < count; i++) {
        table.InsRecord(records[i]->GetKey(), records[i]->GetData());
    }
}



void TestScanTable(TabRecord** testRecords) {
    std::cout << "\n----ScanTable----" << std::endl;
    
    ScanTable scanTable(count);
    auto insertStart = std::chrono::high_resolution_clock::now();
    FillTable(scanTable, testRecords);
    auto insertEnd = std::chrono::high_resolution_clock::now();
    
    int totalSearchefficiency = 0;
    int maxSearchefficiency = 0;
    int minSearchefficiency = std::numeric_limits<int>::max();
    auto searchStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        scanTable.FindRecord(testRecords[i]->GetKey());
        int efficiency = scanTable.GetEfficiency();
        totalSearchefficiency += efficiency;
        if (efficiency > maxSearchefficiency) maxSearchefficiency = efficiency;
        if (efficiency < minSearchefficiency) minSearchefficiency = efficiency;
    }
    auto searchEnd = std::chrono::high_resolution_clock::now();
    
    ScanTable delTable(count);
    FillTable(delTable, testRecords);
    int totalDelefficiency = 0;
    int maxDelefficiency = 0;
    int minDelefficiency = std::numeric_limits<int>::max();
    auto delStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        delTable.DelRecotd(testRecords[i]->GetKey());
        int efficiency = delTable.GetEfficiency();
        totalDelefficiency += efficiency;
        if (efficiency > maxDelefficiency) maxDelefficiency = efficiency;
        if (efficiency < minDelefficiency) minDelefficiency = efficiency;
    }
    auto delEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Insert Time: " 
              << std::chrono::duration<double, std::milli>(insertEnd - insertStart).count() 
              << " ms" << std::endl;
              
    std::cout << "Search Time: " 
              << std::chrono::duration<double, std::milli>(searchEnd - searchStart).count() 
              << " ms" << std::endl;
    std::cout << "Search Efficiency:" << std::endl;
    std::cout << "  Max efficiency: " << maxSearchefficiency << std::endl;
    std::cout << "  Min efficiency: " << minSearchefficiency << std::endl;
    std::cout << "  Avg efficiency: " << static_cast<double>(totalSearchefficiency)/count << std::endl;
    
    std::cout << "Delete Time: " 
              << std::chrono::duration<double, std::milli>(delEnd - delStart).count() 
              << " ms" << std::endl;
    std::cout << "Delete Efficiency:" << std::endl;
    std::cout << "  Max efficiency: " << maxDelefficiency << std::endl;
    std::cout << "  Min efficiency: " << minDelefficiency << std::endl;
    std::cout << "  Avg efficiency: " << static_cast<double>(totalDelefficiency)/count << std::endl;
}

void TestSortTable() {
    std::cout << "\n----SortTable---" << std::endl;
    SortMethod methods[] = {Insert, Merge, Quick};
    std::string methodsNames[] = {"Insert", "Merge", "Quick"};
    for (int i = 0; i < 3; i++) {
        TabRecord** testRecords = generateTestRecords();
        std::cout << "\nMethod: " <<methodsNames[i]<<" Sort" << std::endl;
        SortTable table(count);
        table.SetSortMethod(methods[i]);
        
        auto insertStart = std::chrono::high_resolution_clock::now();
        FillTable(table, testRecords);
        auto insertEnd = std::chrono::high_resolution_clock::now();
        
        table.ResetEff();
        auto sortStart = std::chrono::high_resolution_clock::now();
        table.SortData();
        auto sortEnd = std::chrono::high_resolution_clock::now();
        int sortefficiency = table.GetEfficiency();
        
        table.ResetEff();
        auto searchStart = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < count; j++) {
            table.FindRecord(testRecords[j]->GetKey());
        }
        auto searchEnd = std::chrono::high_resolution_clock::now();
        int searchefficiency = table.GetEfficiency();
        
        std::cout << "Insert Time: " 
                  << std::chrono::duration<double, std::milli>(insertEnd - insertStart).count() 
                  << " ms" << std::endl;
        
        std::cout << "Sort Time: " 
                  << std::chrono::duration<double, std::milli>(sortEnd - sortStart).count() 
                  << " ms" << std::endl;
        std::cout << "Sort efficiency: " << sortefficiency << std::endl;
        
        std::cout << "Search Time: " 
                  << std::chrono::duration<double, std::milli>(searchEnd - searchStart).count() 
                  << " ms" << std::endl;
    }
}
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <limits>
#include "SortTable.h"
#include "ScanTable.h"
#include "TabRecord.h"
#include "Marks.h"

const int count = 40000;
const int countfind = 4000;
const int countdel = 40000;

class TestKitTable
{
private:
    TabRecord** _testRecords;
public:
    TestKitTable(){
        _testRecords = generateTestRecords();
    }

    TabRecord** generateTestRecords() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
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

    void TestScanTable() {
        std::cout << "\n----ScanTable----" << std::endl;
        
        ScanTable scanTable(count);
        scanTable.ResetEff(); 
        auto insertStart = std::chrono::high_resolution_clock::now();
        FillTable(scanTable, _testRecords);
        auto insertEnd = std::chrono::high_resolution_clock::now();
        int insertEfficiency = scanTable.GetEfficiency();
        
        int totalSearchEfficiency1 = 0;
        int maxSearchEfficiency1 = 0;
        // scanTable.FillMySet(_testRecords);
        int minSearchEfficiency1 = std::numeric_limits<int>::max();
        auto searchStart1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < countfind; i++) {
            scanTable.ResetEff();
            scanTable.FindRecord(_testRecords[rand() % count]->GetKey());
            int efficiency = scanTable.GetEfficiency();
            totalSearchEfficiency1 += efficiency;
            if (efficiency > maxSearchEfficiency1) maxSearchEfficiency1 = efficiency;
            if (efficiency < minSearchEfficiency1) minSearchEfficiency1 = efficiency;
        }
        auto searchEnd1 = std::chrono::high_resolution_clock::now();
        
        int totalSearchEfficiency2 = 0;
        int maxSearchEfficiency2 = 0;
        int minSearchEfficiency2 = std::numeric_limits<int>::max();
        auto searchStart2 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < countfind; i++) {
            scanTable.ResetEff();
            scanTable.FindRecordRand(count, _testRecords[rand() % count]->GetKey());
            int efficiency = scanTable.GetEfficiency();
            totalSearchEfficiency2 += efficiency;
            if (efficiency > maxSearchEfficiency2) maxSearchEfficiency2 = efficiency;
            if (efficiency < minSearchEfficiency2) minSearchEfficiency2 = efficiency;
        }
        auto searchEnd2 = std::chrono::high_resolution_clock::now();

        ScanTable delTable(countdel);
        FillTable(delTable, _testRecords);
        int totalDelefficiency = 0;
        int maxDelefficiency = 0;
        int minDelefficiency = std::numeric_limits<int>::max();
        auto delStart = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < countdel; i++) {
            delTable.ResetEff();
            delTable.DelRecord(_testRecords[i]->GetKey()); 
            int efficiency = delTable.GetEfficiency();
            totalDelefficiency += efficiency;
            if (efficiency > maxDelefficiency) maxDelefficiency = efficiency;
            if (efficiency < minDelefficiency) minDelefficiency = efficiency;
        }
        auto delEnd = std::chrono::high_resolution_clock::now();

        std::cout << "Insert Time: " 
                  << std::chrono::duration<double, std::milli>(insertEnd - insertStart).count() 
                  << " ms" << std::endl;
        std::cout << "Insert Efficiency: " << insertEfficiency << std::endl;
        
        std::cout << "Search Time: " 
                  << std::chrono::duration<double, std::milli>(searchEnd1 - searchStart1).count() 
                  << " ms" << std::endl;
        std::cout << "Search Efficiency:" << std::endl;
        std::cout << "  Max efficiency: " << maxSearchEfficiency1 << std::endl;
        std::cout << "  Min efficiency: " << minSearchEfficiency1 << std::endl;
        std::cout << "  Avg efficiency: " << static_cast<double>(totalSearchEfficiency1)/count << std::endl;
        
        std::cout << "SearchRand Time: " 
                  << std::chrono::duration<double, std::milli>(searchEnd2 - searchStart2).count() 
                  << " ms" << std::endl;
        std::cout << "SearchRand Efficiency:" << std::endl;
        std::cout << "  Max efficiency: " << maxSearchEfficiency2 << std::endl;
        std::cout << "  Min efficiency: " << minSearchEfficiency2 << std::endl;
        std::cout << "  Avg efficiency: " << static_cast<double>(totalSearchEfficiency2)/count << std::endl;

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
            std::cout << "\nMethod: " << methodsNames[i] << " Sort" << std::endl;
            SortTable table(count);
            table.SetSortMethod(methods[i]);
            
            table.ResetEff();
            auto insertStart = std::chrono::high_resolution_clock::now();
            FillTable(table, _testRecords);
            auto insertEnd = std::chrono::high_resolution_clock::now();
            int insertEfficiency = table.GetEfficiency();
            
            table.ResetEff();
            auto sortStart = std::chrono::high_resolution_clock::now();
            table.SortData();
            auto sortEnd = std::chrono::high_resolution_clock::now();
            int sortEfficiency = table.GetEfficiency();
            
            int totalSearchEff = 0;
            int minSearchEff = std::numeric_limits<int>::max();
            int maxSearchEff = 0;
            table.ResetEff();
            auto searchStart = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < countfind; j++) {
                table.ResetEff();
                table.FindRecord(_testRecords[rand() % count]->GetKey());
                int eff = table.GetEfficiency();
                totalSearchEff += eff;
                if (eff < minSearchEff) minSearchEff = eff;
                if (eff > maxSearchEff) maxSearchEff = eff;
            }
            auto searchEnd = std::chrono::high_resolution_clock::now();
            
            SortTable delTable(countdel);
            delTable.SetSortMethod(methods[i]);
            FillTable(delTable, _testRecords);
            delTable.SortData();
            
            int totalDelEff = 0;
            int minDelEff = std::numeric_limits<int>::max();
            int maxDelEff = 0;
            auto delStart = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < countdel; j++) {
                delTable.ResetEff();
                delTable.DelRecord(_testRecords[j]->GetKey());
                int eff = delTable.GetEfficiency();
                totalDelEff += eff;
                if (eff < minDelEff) minDelEff = eff;
                if (eff > maxDelEff) maxDelEff = eff;
            }
            auto delEnd = std::chrono::high_resolution_clock::now();
            
            std::cout << "Insert Time: " 
                      << std::chrono::duration<double, std::milli>(insertEnd - insertStart).count() 
                      << " ms" << std::endl;
            std::cout << "Insert Efficiency: " << insertEfficiency << std::endl;
            
            std::cout << "Sort Time: " 
                      << std::chrono::duration<double, std::milli>(sortEnd - sortStart).count() 
                      << " ms" << std::endl;
            std::cout << "Sort Efficiency: " << sortEfficiency << std::endl;
            
            std::cout << "Search Time: " 
                      << std::chrono::duration<double, std::milli>(searchEnd - searchStart).count() 
                      << " ms" << std::endl;
            std::cout << "Search Efficiency:" << std::endl;
            std::cout << "  Max efficiency: " << maxSearchEff << std::endl;
            std::cout << "  Min efficiency: " << minSearchEff << std::endl;
            std::cout << "  Avg efficiency: " << static_cast<double>(totalSearchEff)/count << std::endl;
            
            std::cout << "Delete Time: " 
                      << std::chrono::duration<double, std::milli>(delEnd - delStart).count() 
                      << " ms" << std::endl;
            std::cout << "Delete Efficiency:" << std::endl;
            std::cout << "  Max efficiency: " << maxDelEff << std::endl;
            std::cout << "  Min efficiency: " << minDelEff << std::endl;
            std::cout << "  Avg efficiency: " << static_cast<double>(totalDelEff)/count << std::endl;
        }
    }

    ~TestKitTable(){
        for (int i = 0; i < count; i++) {
            delete _testRecords[i];
        }
        delete[] _testRecords;
    }
};
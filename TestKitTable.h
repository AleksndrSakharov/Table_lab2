#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <limits>
#include <fstream>
#include <filesystem>
#include "SortTable.h"
#include "ScanTable.h"
#include "TabRecord.h"
#include "Marks.h"

const int count = 3000;
const int countfind = 2;
const int countdel = 3000;

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
        int x = 0;
        int y = 0;
        int z = 0;
        for (int i = 0; i < count; i++) {
            std::mt19937 rng(std::random_device{}());
            Key key = GenerateFIO(x, y, z);
            z++;
            if (z >= patronymics.size()){
                z = 0;
                y++;
                if (y >= names.size()){
                    y = 0;
                    x++;
                    if (x >= surnames.size()) x = 0;
                }
            }

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

     std::vector<std::string> surnames = {
        "Ivanov", "Petrov", "Sidorov", "Smirnov", "Kuznetsov", "Popov", "Vasilyev", "Sokolov", "Mikhailov", "Fedorov",
        "Morozov", "Volkov", "Alekseev", "Lebedev", "Semenov", "Egorov", "Pavlov", "Kozlov", "Stepanov", "Nikolaev",
        "Orlov", "Andreev", "Makarov", "Nikitin", "Zhukov", "Solovyov", "Borisov", "Yakovlev", "Grigoryev", "Romanov",
        "Vorobyev", "Sergeev", "Karpov", "Gusev", "Titov", "Kiselev", "Maltsev", "Bykov", "Tikhonov", "Zaitsev",
        "Vinogradov", "Bogdanov", "Savelyev", "Mitin", "Chernov", "Kudryavtsev", "Baranov", "Danilov", "Kalinin", "Belov",
        "Komarov", "Krylov", "Korolev", "Efimov", "Sorokin", "Shubin", "Kabanov", "Markov", "Nikiforov", "Ignatov",
        "Maslov", "Konovalov", "Filatov", "Samoylov", "Gerasimov", "Frolov", "Ulyanov", "Drozdov", "Kulikov", "Belyaev",
        "Ponomarev", "Antipov", "Zverev", "Denisov", "Rodionov", "Anisimov", "Klimov", "Avdeev", "Gromov", "Korneev",
        "Babenko", "Loginov", "Kuzmin", "Fadeev", "Prokofiev", "Znamensky", "Belkin", "Polyakov", "Reshetnikov", "Panin",
        "Shcherbakov", "Bobrov", "Zolotov", "Timofeev", "Chistyakov", "Yashin", "Babkin", "Zadorozhny", "Troitsky", "Suvorov"
    };

    std::vector<std::string> names = {
        "Aleksandr", "Dmitry", "Maxim", "Sergey", "Andrey", "Alexey", "Ivan", "Nikolay", "Yuri", "Viktor",
        "Vladimir", "Artem", "Pavel", "Oleg", "Egor", "Vyacheslav", "Ilya", "Roman", "Kirill", "Stepan",
        "Anatoly", "Timur", "Denis", "Grigory", "Fedor", "Vasiliy", "Gennady", "Stanislav", "Konstantin", "Valery",
        "Boris", "Leonid", "Mikhail", "Arkady", "Valentin", "German", "Yaroslav", "Nazar", "Bogdan", "Savely",
        "Ruslan", "Semyon", "Artur", "Eduard", "Albert", "Ostap", "Anton", "Ignat", "Yan", "Mark",
        "Aleksey", "Vitaly", "Vsevolod", "Rodion", "Miron", "David", "Gleb", "Tikhon", "Lev", "Nikita",
        "Platon", "Andrian", "Arseny", "Demid", "Yakov", "Matvey", "Taras", "Timofey", "Stepan", "Vladislav",
        "Danila", "Zahar", "Frol", "German", "Arkhip", "Danil", "Saveliy", "Filipp", "Artyom", "Vadim",
        "Yevgeny", "Ignatiy", "Kir", "Lavr", "Makar", "Orest", "Rodion", "Severin", "Trofim", "Ustin",
        "Yulian", "Avgust", "Borislav", "Gavriil", "Innokentiy", "Klim", "Nazar", "Prokhor", "Rostislav", "Svyatoslav"
    };

    std::vector<std::string> patronymics = {
        "Aleksandrovich", "Dmitrievich", "Maximovich", "Sergeevich", "Andreevich", "Alexeevich", "Ivanovich", "Nikolaevich", "Yurievich", "Viktorovich",
        "Vladimirovich", "Artemovich", "Pavlovich", "Olegovich", "Egorovich", "Vyacheslavovich", "Ilyich", "Romanovich", "Kirillovich", "Stepanovich",
        "Anatolievich", "Timurovich", "Denisovich", "Grigoryevich", "Fedorovich", "Vasilevich", "Gennadievich", "Stanislavovich", "Konstantinovich", "Valerievich",
        "Borisovich", "Leonidovich", "Mikhailovich", "Arkadievich", "Valentinovich", "Germanovich", "Yaroslavovich", "Nazarovich", "Bogdanovich", "Savelievich",
        "Ruslanovich", "Semenovich", "Arturovich", "Eduardovich", "Albertovich", "Ostapovich", "Antonovich", "Ignatovich", "Yanovich", "Markovich",
        "Alekseevich", "Vitalievich", "Vsevolodovich", "Rodionovich", "Mironovich", "Davidovich", "Glebovich", "Tikhonovich", "Lvovich", "Nikitich",
        "Platonovich", "Andrianovich", "Arsenievich", "Demidovich", "Yakovlevich", "Matveevich", "Tarasovich", "Timofeevich", "Stepanovich", "Vladislavovich",
        "Danilovich", "Zaharovich", "Frolovich", "Germanovich", "Arkhipovich", "Danilovich", "Savelievich", "Filippovich", "Artyomovich", "Vadimovich",
        "Evgenievich", "Ignatievich", "Kirovich", "Lavrovich", "Makarovich", "Orestovich", "Rodionovich", "Severinovich", "Trofimovich", "Ustinovich",
        "Yulianovich", "Avgustovich", "Borislavovich", "Gavriilovich", "Innokentievich", "Klimovich", "Nazarovich", "Prokhorovich", "Rostislavovich", "Svyatoslavovich"
    };

        std::string GenerateRandomSurname() { 
            return surnames[rand() % surnames.size()];      
        }

        std::string GenerateRandomName() {
            return names[rand() % names.size()];      
        }

        std::string GenerateRandomPatronymic() { 
            return patronymics[rand() % patronymics.size()];      
        }

        string GenerateFIO(int x, int y, int z){
            return surnames[x] + " " + names[y] + " " + patronymics[z];
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
        random_device rd;
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

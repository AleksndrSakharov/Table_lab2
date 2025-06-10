#include"ScanTable.h"

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
    int k = 0;
    while (true){
        Key key = GenerateRandomSurname() + " " + GenerateRandomName() + " " + GenerateRandomPatronymic();
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
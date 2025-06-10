cmake_minimum_required(VERSION 3.14)
project(Table)

add_executable(main 
    main.cpp
    ArrayTable.cpp
    HashArray.cpp
    HashTable.cpp
    ScanTable.cpp
    TabRecord.cpp
    SortTable.cpp
    TreeTable.cpp
)

target_include_directories(main PRIVATE include)

cmake_minimum_required(VERSION 3.16)

project(PasswordManager)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

add_executable(PasswordManager
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    databasemanager.cpp
    databasemanager.h
    vaultrepository.cpp
    vaultrepository.h
    vaultrecord.h
)

target_link_libraries(PasswordManager Qt6::Widgets Qt6::Sql)

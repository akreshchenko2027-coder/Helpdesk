cmake_minimum_required(VERSION 3.16)

project(PasswordManager19 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql Network)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    PasswordRecord.h
    PasswordRepository.cpp
    PasswordRepository.h
    PasswordTableModel.cpp
    PasswordTableModel.h
    PasswordFilterProxyModel.cpp
    PasswordFilterProxyModel.h
    PasswordLeakChecker.cpp
    PasswordLeakChecker.h
)

add_executable(PasswordManager19 ${PROJECT_SOURCES})

target_link_libraries(PasswordManager19 PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

cmake_minimum_required(VERSION 3.16)
project(PasswordManager20 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql Network Concurrent)

add_executable(PasswordManager20
    main.cpp mainwindow.cpp mainwindow.h
    PasswordRecord.h PasswordRepository.cpp PasswordRepository.h
    PasswordTableModel.cpp PasswordTableModel.h
    PasswordFilterProxyModel.cpp PasswordFilterProxyModel.h
    PasswordLeakChecker.cpp PasswordLeakChecker.h
)

target_link_libraries(PasswordManager20 PRIVATE
    Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql Qt6::Network Qt6::Concurrent
)

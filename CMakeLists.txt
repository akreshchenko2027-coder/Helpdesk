cmake_minimum_required(VERSION 3.16)

project(PasswordManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Підключаємо потрібні модулі Qt, включаючи Sql для бази даних
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql)

# Твій список файлів (відповідно до того, що відкрито в тебе зліва)
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
)

# Кажемо CMake створити програму PasswordManager із цих файлів
add_executable(PasswordManager ${PROJECT_SOURCES})

# Підключаємо бібліотеки до нашої програми
target_link_libraries(PasswordManager PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

cmake_minimum_required(VERSION 3.16)

project(Helpdesk VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Helpdesk
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ticketdialog.cpp
    ticketdialog.h
    ticketdialog.ui
)

target_link_libraries(Helpdesk PRIVATE Qt6::Widgets)

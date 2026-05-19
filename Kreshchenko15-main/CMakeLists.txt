cmake_minimum_required(VERSION 3.16)

project(Helpdesk)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Helpdesk
    main.cpp

    mainwindow.cpp
    mainwindow.h

    ticket.h

    tickettablemodel.cpp
    tickettablemodel.h

    ticketfilterproxymodel.cpp
    ticketfilterproxymodel.h
)

target_link_libraries(Helpdesk Qt6::Widgets)

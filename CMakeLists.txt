cmake_minimum_required(VERSION 3.16)

project(StudyBuddyCS2LabProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Test)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    chatselectionwindow.cpp
    chatselectionwindow.h
    chatselectionwindow.ui
    chatwindow.cpp
    chatwindow.h
    chatwindow.ui
    courseselectionwindow.cpp
    courseselectionwindow.h
    courseselectionwindow.ui
)

add_executable(StudyBuddyCS2LabProject
    ${PROJECT_SOURCES}
)

target_link_libraries(StudyBuddyCS2LabProject PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

add_executable(ChatControllerTests
    test_chatcontroller.cpp
    chatcontroller.cpp
    chatcontroller.h
    ichatclient.h
)

target_include_directories(ChatControllerTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ChatControllerTests PRIVATE
    Qt6::Core
    Qt6::Test
)

target_compile_options(ChatControllerTests PRIVATE -O0)
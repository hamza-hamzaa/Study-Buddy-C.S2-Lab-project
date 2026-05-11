cmake_minimum_required(VERSION 3.16)

project(StudyBuddyProject LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Test)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

set(CLIENT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    inputvalidation.cpp
    inputvalidation.h
    chatselectionwindow.cpp
    chatselectionwindow.h
    chatselectionwindow.ui
    chatwindow.cpp
    chatwindow.h
    chatwindow.ui
    courseselectionwindow.cpp
    courseselectionwindow.h
    courseselectionwindow.ui
    chatcontroller.cpp
    chatcontroller.h
    ichatclient.h
    realchatclient.cpp
    realchatclient.h
)

add_executable(StudyBuddy ${CLIENT_SOURCES})

target_include_directories(StudyBuddy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(StudyBuddy PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

if(APPLE)
    target_compile_options(StudyBuddy PRIVATE -include arm_acle.h)
endif()


add_executable(StudyBuddyServer
    Server.cpp
    json.hpp
)

target_link_libraries(StudyBuddyServer PRIVATE
    Boost::headers
    Threads::Threads
)

if(WIN32)
    target_link_libraries(StudyBuddyServer PRIVATE ws2_32 mswsock)
    target_link_options(StudyBuddyServer PRIVATE "-Wl,-subsystem,console")
endif()

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

add_test(NAME ChatControllerTests COMMAND ChatControllerTests)

add_executable(ChatWindowTests
    test_chatwindow.cpp
    chatwindow.cpp
    chatwindow.h
    chatwindow.ui
)

target_include_directories(ChatWindowTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ChatWindowTests PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Test
)

add_test(NAME ChatWindowTests COMMAND ChatWindowTests)

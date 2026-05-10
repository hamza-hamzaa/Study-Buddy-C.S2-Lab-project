cmake_minimum_required(VERSION 3.16)

# Name of the overall project
project(StudyBuddyProject LANGUAGES CXX)

# Kept from the repo: Enables the unit tests
enable_testing()

# Kept from you: CRITICAL FIX: Upgraded to C++20 so Youssef's Server Coroutines will compile!
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt UI Generators
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find Required Libraries
# Manually tell CMake where Qt6 is installed
set(CMAKE_PREFIX_PATH "E:/Applications/Qt/6.11.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Test)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

# ==========================================
# 1. THE QT CLIENT APPLICATION (Hamza & Ali)
# ==========================================
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
)

add_executable(StudyBuddyClient ${CLIENT_SOURCES})

# FIX 1: Corrected target name and linked the required Qt6 UI libraries
target_link_libraries(StudyBuddyClient PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

# ==========================================
# 2. THE BOOST C++20 SERVER (Youssef & Ahmed)
# ==========================================
set(SERVER_SOURCES
    Server.cpp
)

add_executable(StudyBuddyServer ${SERVER_SOURCES}
    json.hpp)

# FIX 2: Added ws2_32 here to fix the _imp_WSAStartup networking errors
target_link_libraries(StudyBuddyServer PRIVATE
    Boost::headers
    Threads::Threads
    ws2_32
    mswsock
)
# FIX 3: Forces MinGW to treat the Server as a Console app (fixes WinMain error)
target_link_options(StudyBuddyServer PRIVATE "-Wl,-subsystem,console")

# ==========================================
# 3. THE UNIT TESTS (Ali)
# ==========================================
set(TEST_SOURCES
    test_chatcontroller.cpp
    chatcontroller.cpp
    chatcontroller.h
    ichatclient.h
)

add_executable(ChatControllerTests ${TEST_SOURCES})
target_include_directories(ChatControllerTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ChatControllerTests PRIVATE
    Qt6::Core
    Qt6::Test
)

# Kept from the repo: Ali's new test configurations
target_compile_options(ChatControllerTests PRIVATE -O0)

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

target_compile_options(ChatWindowTests PRIVATE -O0)

add_test(NAME ChatWindowTests COMMAND ChatWindowTests)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ScreenSnip)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ScreenSnip # WIN32 # todo
    mainwindow.h
    mainwindow.cpp
    uimainwindow.h
    uimainwindow.cpp
    main.cpp
	snipwidget.h
    snipwidget.cpp	
	utility.h
    utility.cpp
	settings.h
    settings.cpp
	hotkeymanager.h
    hotkeymanager.cpp
)

target_link_libraries(ScreenSnip Qt5::Widgets)
target_link_libraries(ScreenSnip gh)
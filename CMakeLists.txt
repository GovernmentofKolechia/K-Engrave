cmake_minimum_required(VERSION 3.16)
project(kengrave)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Widgets DBus)
find_package(KF6 REQUIRED COMPONENTS Kirigami CoreAddons I18n)

add_executable(kengrave 
    src/main.cpp 
    src/systemdmanager.h
    src/resources.qrc
)

target_link_libraries(kengrave 
    Qt6::Quick 
    Qt6::QuickControls2 
    Qt6::Widgets 
    Qt6::DBus
    KF6::Kirigami 
    KF6::CoreAddons 
    KF6::I18n
)

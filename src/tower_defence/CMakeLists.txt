cmake_minimum_required(VERSION 3.5)

project(tower_defence VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia)

set(PROJECT_SOURCES

        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tower_defence
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        game_engine.cpp
        defense.hpp
        balloon.hpp
        balloon.cpp
        defense.cpp
        red.hpp
        game_engine.hpp
        resources.qrc
        basic_shooter.hpp
        fast_shooter.hpp
        map.hpp
        map.cpp
        map_tile.hpp
        maptile_ui.hpp
        maptile_ui.cpp
        projectile.hpp
        projectile.cpp
        basic_shooter.cpp
        main.cpp
        blue.hpp
        silver.hpp
        black.hpp

        final_boss.hpp
        fast_shooter.cpp
        sniper_shooter.hpp sniper_shooter.cpp
        freezer_shooter.hpp freezer_shooter.cpp
        armor_balloon.hpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET tower_defence APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tower_defence SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tower_defence
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(tower_defence PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(tower_defence PRIVATE Qt6::Multimedia)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tower_defence)
endif()
set_target_properties(tower_defence PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tower_defence
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tower_defence)
endif()

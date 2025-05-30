cmake_minimum_required(VERSION 3.10)
project(RATP_PROJET)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Afficher des informations de débogage
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
set(Qt6_DIR "C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia Svg SvgWidgets)
include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/Projet.cpp
    src/mainwindow.cpp
    include/Projet.hpp
    include/Generic_connection_parser.hpp
    include/Generic_mapper.hpp
    include/Generic_station_parser_derivative.hpp
    include/Generic_station_parser.hpp
    include/Grade.hpp
    include/mainwindow.h
    include/zoomablegraphicsview.h
)

# Créer l'exécutable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Svg Qt6::SvgWidgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
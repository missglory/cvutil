cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)


project(opencv)
message("RPOJECT " ${PROJECT_NAME} ":")
message("SRC DIR " ${CMAKE_CURRENT_SOURCE_DIR})
message("BIN DIR " ${CMAKE_CURRENT_BINARY_DIR})


set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set (CMAKE_PREFIX_PATH "C:\\Qtvc\\5.11.1\\msvc2017_64\\")
#set (CMAKE_INSTALL_PREFIX C:/Qtvc/5.11.1/msvc2017_64/bin)
if (EXISTS ${CMAKE_PREFIX_PATH})
	message("CMAKE PREFIX PATH EXISTS")
endif()

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

find_package(Qt5Core)


if ( NOT Qt5_FOUND )    
 message(FATAL_ERROR "Package QT not found!")    
endif( )

set (SRC 
	src/Source1.cpp
	src/mainwindow.cpp
	#src/mocs_compilation.cpp
	)

set (HEADERS src/mainwindow.h)

set (UI src/mainwindow.ui)

message ("SRC " ${SRC})

set (INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(EXISTS ${INCLUDEDIR})
	message("INCLUDEDIR EXISTS")
endif()
include_directories(${INCLUDEDIR})

include_directories(${Qt5_DIR}/../../../include)

qt5_wrap_ui(WRAPPED_UI ${UI})
qt5_wrap_cpp(WRAPPED_SRC ${HEADERS})
add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SRC} ${WRAPPED_SRC} ${WRAPPED_UI})
#add_executable(${PROJECT_NAME} ${HEADERS} ${SRC})
#target_include_directories(${PROJECT_NAME} ${INCLUDEDIR})

find_library(OPENCVLIB opencv_world341d PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib NO_DEFAULT_PATH)
message("OPENCV LIB " ${OPENCVLIB})
message("Qt5::Core" Qt5::Core)
message("qt5core dir " ${Qt5Core_DIR}/..)
find_library(QT5CORE Qt5Cored.lib PATH "${Qt5_DIR}/../..")
find_library(QT5WIDGETS Qt5Widgetsd.lib PATH "${Qt5_DIR}/../..")
message("Qt5 Core " ${QT5CORE})
message("Qt5 Widgets " ${QT5WIDGETS})
target_link_libraries(${PROJECT_NAME} ${QT5CORE} ${QT5WIDGETS} Qt5::Gui ${OPENCVLIB} )

#get_target_property(QtCore_location Qt5::Core LOCATION)


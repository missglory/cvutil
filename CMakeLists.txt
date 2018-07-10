cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)


project(opencv)
message("RPOJECT " ${PROJECT_NAME} ":")
message("SRC DIR " ${CMAKE_CURRENT_SOURCE_DIR})
message("BIN DIR " ${CMAKE_CURRENT_BINARY_DIR})


set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

set (CMAKE_PREFIX_PATH "C:\\Qtvc\\5.11.1\\msvc2017_64\\")
#set (CMAKE_INSTALL_PREFIX C:/Qtvc/5.11.1/msvc2017_64/bin)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

set (SRC 
	src/Source1.cpp
	src/mainwindow.cpp
	src/Worker.cpp
	src/masterwindow.cpp
	#src/NewMainWindow.cpp
	#src/mainwidget.cpp
	)

set (HEADERS src/mainwindow.h
	src/utils.h
	src/Worker.h
	src/masterwindow.h
	#src/NewMainWindow.h
	)#src/mainwidget.h)
set (UI src/mainwindow.ui
		src/masterwindow.ui
	)#src/mainwidget.ui)

message ("SRC " ${SRC})

set (INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDEDIR})
include_directories(${Qt5_DIR}/../../../include)

qt5_wrap_ui(WRAPPED_UI ${UI})
qt5_wrap_cpp(WRAPPED_SRC ${HEADERS})
add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SRC} ${WRAPPED_SRC} ${WRAPPED_UI})

#find_library(OPENCVLIB opencv_world341d PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib NO_DEFAULT_PATH)
find_library(OPENCVLIB opencv_world341d)
message("OPENCV LIB " ${OPENCVLIB})
message("Qt5::Core" Qt5::Core)
message("qt5core dir " ${Qt5Core_DIR}/..)
find_library(QT5CORE Qt5Cored.lib PATHS "${Qt5_DIR}/../..")
find_library(QT5WIDGETS Qt5Widgetsd.lib PATHS "${Qt5_DIR}/../..")
message("Qt5 Core " ${QT5CORE})
message("Qt5 Widgets " ${QT5WIDGETS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui ${OPENCVLIB} )

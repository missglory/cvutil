cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)


project(opencv)
message("RPOJECT " ${PROJECT_NAME} ":")
message("SRC DIR " ${CMAKE_CURRENT_SOURCE_DIR})
message("BIN DIR " ${CMAKE_CURRENT_BINARY_DIR})

set(BUILD_SHARED_LIBS OFF)
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
set (LIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
include_directories(${INCLUDEDIR})
include_directories(${Qt5_DIR}/../../../include)

qt5_wrap_ui(WRAPPED_UI ${UI})
qt5_wrap_cpp(WRAPPED_SRC ${HEADERS})
add_executable(${PROJECT_NAME} WIN32 ${HEADERS} ${SRC} ${WRAPPED_SRC} ${WRAPPED_UI})

#find_library(OPENCVLIB opencv_world341d
#	HINTS ${CMAKE_CURRENT_SOURCE_DIR}/lib 
#	PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib
#	NO_DEFAULT_PATH)
find_library(OPENCVLIB 		 opencv_world341.lib PATHS ${LIBDIR})
set(OPENCV_CORE342D		 	 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_core342.lib") 		# PATHS ${LIBDIR})
set(OPENCV_IMGPROC342D		 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_imgproc342.lib") 		# PATHS ${LIBDIR})
set(OPENCV_HIGHGUI342D		 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_highgui342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_ML342D		 	 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_ml342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_VIDEO342D		 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_video342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_FEATURES2D342D	 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_features2d342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_CALIB3D342D		 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_calib3d342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_OBJDETECT342D	 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_objdetect342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_CONTRIB342D		 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_contrib342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_LEGACY342D		 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_legacy342.lib") 		# PATHS ${LIBDIR})
# set(OPENCV_FLANN342D		 "${CMAKE_CURRENT_SOURCE_DIR}/lib/opencv_flann342.lib") 		# PATHS ${LIBDIR})

message("OPENCV LIB " ${OPENCVLIB})
message("Qt5::Core" Qt5::Core)
message("qt5core dir " ${Qt5Core_DIR}/..)
#find_library(QT5CORE Qt5Cored )#PATHS "${Qt5_DIR}/../..")
#find_library(QT5WIDGETS Qt5Widgetsd )#PATHS "${Qt5_DIR}/../..")
#message("Qt5 Core " ${QT5CORE})
#message("Qt5 Widgets " ${QT5WIDGETS})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)
target_link_libraries(${PROJECT_NAME}
	${OPENCVLIB} 
	${OPENCV_CORE342D}
	${OPENCV_IMGPROC342D}
	${OPENCV_HIGHGUI342D}
	# ${OPENCV_ML342D}
	# ${OPENCV_VIDEO342D}
	# ${OPENCV_FEATURES2D342D}
	# ${OPENCV_CALIB3D342D}
	# ${OPENCV_OBJDETECT342D}
	# ${OPENCV_CONTRIB342D}
	# ${OPENCV_LEGACY342D}
	# ${OPENCV_FLANN342D}
)
message("</>RPOJECT " ${PROJECT_NAME})

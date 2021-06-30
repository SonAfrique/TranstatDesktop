cmake_minimum_required(VERSION 3.17)

project(transtatDesktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql Charts PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql Charts PrintSupport REQUIRED)
find_package(OpenCV)
find_package(OpenMP)
if (OPENMP_FOUND)
  list(APPEND CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
#set(CMAKE_CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors -std=c++14" CACHE STRING COMPILE_FLAGS FORCE)
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -march=native -mtune=native -funroll-loops -Wall -DNDEBUG -DBOOST_DISABLE_ASSERTS" CACHE STRING COMPILE_FLAGS FORCE)
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -march=native -mtune=native -Wall -DDEBUG" CACHE STRING COMPILE_FLAGS FORCE)
elseif (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /W4 -DGTL_STATIC" CACHE STRING COMPILE_FLAGS FORCE)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /Ox /Ob2 /Oi /Ot /arch:AVX2 /fp:fast /DNDEBUG" CACHE STRING COMPILE_FLAGS FORCE)
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /Od /Ob0 /DDEBUG" CACHE STRING COMPILE_FLAGS FORCE)
endif()

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

option(SILENT_WORK "Remove all imshow and waitKey functions?" OFF)
if (SILENT_WORK)
  add_definitions(-DSILENT_WORK)
endif(SILENT_WORK)
option(BUILD_YOLO_LIB "Should compiled standalone yolo_lib with original darknet?" ON)
if (BUILD_YOLO_LIB)
  add_subdirectory(src/Detector/darknet)
  add_definitions(-DBUILD_YOLO_LIB)
  if (MSVC)
    if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
      set(BIT_SYSTEM x32)
    else()
      set(BIT_SYSTEM x64)
    endif()

    set(LIB_PTHREAD pthreadVC2)
  else()
    set(LIB_PTHREAD pthread)
  endif()

  if (MSVC)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/Detector/darknet/3rdparty/dll/${BIT_SYSTEM}/pthreadVC2.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/Detector/darknet/3rdparty/dll/${BIT_SYSTEM}/pthreadVC2.dll DESTINATION ${CMAKE_BINARY_DIR}/Release)

    file(GLOB CUDNN_DLL ${CUDNN_DIR}/bin/*.dll)
    file(COPY ${CUDNN_DLL} DESTINATION ${CMAKE_BINARY_DIR}/Release)
    file(COPY ${CUDNN_DLL} DESTINATION ${CMAKE_BINARY_DIR}/Debug)
  endif()
endif(BUILD_YOLO_LIB)

option(BUILD_YOLO_TENSORRT "Should compiled TensorRT binding for YOLO?" ON)
if (BUILD_YOLO_TENSORRT)
  add_subdirectory(src/Detector/tensorrt_yolo)
  add_definitions(-DBUILD_YOLO_TENSORRT)
endif(BUILD_YOLO_TENSORRT)
#add_subdirectory(src/Detector/tensorrt_yolo)
add_definitions(-DBUILD_YOLO_TENSORRT)

add_subdirectory(src)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        addcounter.cpp
        addcounter.h
        addcounter.ui


        analysisid.cpp
        analysisid.h
        analysisid.ui

        drawcounter.cpp
        drawcounter.h
        drawcounter.ui

        magnifyvisuals.cpp
        magnifyvisuals.h
        magnifyvisuals.ui

        player.cpp
        player.h

        opencvviewer.cpp
        opencvviewer.h

        cvutilities.cpp
        cvutilities.h

        detector.cpp
        detector.h

        dbconnection.cpp
        dbconnection.h

        debugger.h

        icons.qrc
        support_images.qrc


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(transtatDesktop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(transtatDesktop SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(transtatDesktop
            ${PROJECT_SOURCES}
        )
    endif()
endif()
INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/../src
        ${PROJECT_SOURCE_DIR}/../src/common
        ${PROJECT_SOURCE_DIR}/../src/Detector
        ${PROJECT_SOURCE_DIR}/../src/Detector/vibe_src
        ${PROJECT_SOURCE_DIR}/../src/Detector/Subsense
        ${PROJECT_SOURCE_DIR}/../src/Tracker
        ${PROJECT_SOURCE_DIR}/../src/Tracker/HungarianAlg

        )
    set(LIBS
            ${OpenCV_LIBS}
            mtracking
            mdetection
            )

    if (BUILD_YOLO_LIB)
      if (MSVC)
        if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
          set(BIT_SYSTEM x32)
        else()
          set(BIT_SYSTEM x64)
        endif()

        link_directories(${PROJECT_SOURCE_DIR}/../src/Detector/darknet/3rdparty/lib/${BIT_SYSTEM})
      endif(MSVC)

      add_definitions(-DBUILD_YOLO_LIB)
    endif(BUILD_YOLO_LIB)
target_link_libraries(transtatDesktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::Sql Qt5::PrintSupport
        Qt5::Charts ${HIREDIS_LIB}  ${REDIS_PLUS_PLUS_LIB} ${LIBS} ${OpenCV_LIBS}
         -lpthread)

set_target_properties(transtatDesktop PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(transtatDesktop)
endif()

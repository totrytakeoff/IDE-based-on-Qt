cmake_minimum_required(VERSION 3.16)

project(MyIDE VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)





#  手动指定需要 MOC 处理的头文件
set(MOC_HEADERS

    ${CMAKE_CURRENT_LIST_DIR}/qscintilla/Qsci/qsciscintilla.h
    # 其他需要 MOC 处理的头文件
)

qt_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})





set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MyIDE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resourcemanager.h resourcemanager.cpp
        editarea.h editarea.cpp
        newfile.h newfile.cpp
        terminal.cpp terminal.h
        coderunner.h coderunner.cpp
        searchwidget.h searchwidget.cpp
        res.qrc
        res.rc

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MyIDE APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MyIDE SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MyIDE
            ${PROJECT_SOURCES}
            res.rc
        )
    endif()
endif()


set(QSCILIB ${CMAKE_CURRENT_LIST_DIR}/qscintilla/libqscintilla2_qt6d.a)

target_link_libraries(MyIDE PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_link_libraries(MyIDE PRIVATE ${CMAKE_SOURCE_DIR}/qscintilla/libqscintilla2_qt6d.a)
target_link_directories(MyIDE PRIVATE ${CMAKE_SOURCE_DIR}/qscintilla/Qsci)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MyIDE)
endif()
set_target_properties(MyIDE PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


# 将 MOC 文件添加到可执行文件
target_sources(MyIDE PRIVATE ${MOC_SOURCES})


include(GNUInstallDirs)
install(TARGETS MyIDE
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)




# 设置图标（仅适用于Windows）
if(WIN32)
    set(RESOURCE_SCRIPT "${CMAKE_SOURCE_DIR}/res.rc")
    set_source_files_properties(${RESOURCE_SCRIPT} PROPERTIES LANGUAGE RC)
    target_sources(${PROJECT_NAME} PRIVATE ${RESOURCE_SCRIPT})
endif()



if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyIDE)
endif()

cmake_minimum_required(VERSION 3.16)

project(ScriptEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(PROJECT_SOURCES
    main.cpp
    mainWindow.cpp
    mainWindow.h
    mainWindow.ui
    highlighter.cpp
    highlighter.h
    lineNumber.cpp
    lineNumber.h
    lineNumber.ui
    scriptEditor.cpp
    scriptEditor.h
    scriptEditor.ui
    scriptEditorPanel.cpp
    scriptEditorPanel.h
    scriptEditorPanel.ui

)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ScriptEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ScriptEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ScriptEditor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ScriptEditor
            ${PROJECT_SOURCES}

            scripteditorpanel.h scripteditorpanel.cpp scripteditorpanel.ui
            highlighter.h highlighter.cpp
            linenumber.h linenumber.cpp linenumber.ui
            scripteditor.h scripteditor.cpp scripteditor.ui
            commandlist.h commandlist.cpp commandlist.ui
            newcommand.h newcommand.cpp newcommand.ui
            editCommand.h editCommand.cpp
            editCommand.ui
            config.h
            style.h

            resources.qrc
            buttonBar.h buttonBar.cpp buttonBar.ui
        )
    endif()
endif()

target_link_libraries(ScriptEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ScriptEditor)
endif()
set_target_properties(ScriptEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ScriptEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ScriptEditor)
endif()

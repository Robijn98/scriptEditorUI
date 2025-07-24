cmake_minimum_required(VERSION 3.16)

project(ScriptEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(UI_FILES
    ui/buttonBar.ui
    ui/commandList.ui
    # Add all other .ui files
)

set(PROJECT_SOURCES

    src/main.cpp
    src/mainWindow.cpp
    include/mainWindow.h
    ui/mainWindow.ui
    src/highlighter.cpp
    include/highlighter.h
    src/lineNumber.cpp
    include/lineNumber.h
    ui/lineNumber.ui
    src/scriptEditor.cpp
    include/scriptEditor.h
    ui/scriptEditor.ui
    src/scriptEditorPanel.cpp
    include/scriptEditorPanel.h
    ui/scriptEditorPanel.ui
    src/buttonBar.cpp
    include/buttonBar.h
    ui/buttonBar.ui
    src/commandList.cpp
    include/commandList.h
    ui/commandList.ui
    src/editCommand.cpp
    include/editCommand.h
    ui/editCommand.ui
    src/newCommand.cpp
    include/newCommand.h
    ui/newCommand.ui
    src/searchAndReplace.cpp
    include/searchAndReplace.h
    ui/searchAndReplace.ui
    src/openTemplate.cpp
    include/openTemplate.h
    ui/openTemplate.ui
    src/newTemplate.cpp
    include/newTemplate.h
    ui/newTemplate.ui
    include/editTemplate.h
    src/editTemplate.cpp
    ui/editTemplate.ui

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
            include/buttonBar.h include/commandList.h include/config.h include/editCommand.h include/editFile.h include/highlighter.h include/linenumber.h include/mainWindow.h include/newCommand.h include/scriptEditor.h include/scriptEditorPanel.h include/searchAndReplace.h include/style.h
            src/buttonBar.cpp src/commandList.cpp src/editCommand.cpp src/editFile.cpp src/highlighter.cpp src/lineNumber.cpp src/main.cpp src/mainWindow.cpp src/newCommand.cpp src/scriptEditor.cpp src/scriptEditorPanel.cpp src/searchAndReplace.cpp
            ui/buttonBar.ui ui/commandList.ui ui/editCommand.ui ui/form.ui ui/lineNumber.ui ui/mainWindow.ui ui/newCommand.ui ui/scriptEditor.ui ui/scriptEditorPanel.ui ui/searchAndReplace.ui
            resources.qrc
            include/openTemplate.h src/openTemplate.cpp ui/openTemplate.ui
            include/newTemplate.h src/newTemplate.cpp ui/newTemplate.ui
            include/editTemplate.h src/editTemplate.cpp ui/editTemplate.ui

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

cmake_minimum_required(VERSION 3.19)
project(DroneControl LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network MultimediaWidgets)

# Знаходження GStreamer через pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-video-1.0)

# Включення директорій заголовків
include_directories(
    ${GSTREAMER_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}
)



# Додавання шляхів до бібліотек
link_directories(${GSTREAMER_LIBRARY_DIRS})

qt_standard_project_setup()

qt_add_executable(DroneControl
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    DtUdpServer.h DtUdpServer.cpp
    appsetupdialog.h appsetupdialog.cpp appsetupdialog.ui
    DtFifo.h DtFifo.cpp
    DtCRC.h DtCRC.cpp
    DtProtocol.h DtProtocol.cpp
    DtCommand.h
    DtRxTxParser.h DtRxTxParser.cpp
    DtParser.h DtParser.cpp
    DtVideoWidget.h DtVideoWidget.cpp
)

target_link_libraries(DroneControl
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        Qt6::MultimediaWidgets
        ${GSTREAMER_LIBRARIES}
)

# Додавання флагів компіляції
target_compile_options(${PROJECT_NAME} PRIVATE ${GSTREAMER_CFLAGS_OTHER})

include(GNUInstallDirs)

install(TARGETS DroneControl
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET DroneControl
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

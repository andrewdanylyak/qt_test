cmake_minimum_required(VERSION 3.19)
project(DroneControl LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

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
)

target_link_libraries(DroneControl
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

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

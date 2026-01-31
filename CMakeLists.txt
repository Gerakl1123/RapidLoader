cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(DownloaderFromEthernetMultiThreading LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(DownloaderFromEthernetMultiThreading
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    downloaderworker.h downloaderworker.cpp
    RapidNetworkManager.h RapidNetworkManager.cpp
    RapidFileManager.h RapidFileManager.cpp
)

target_link_libraries(DownloaderFromEthernetMultiThreading
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)
target_link_libraries(DownloaderFromEthernetMultiThreading PRIVATE Qt6::Core)
target_link_libraries(DownloaderFromEthernetMultiThreading PRIVATE Qt6::Core)

target_link_libraries(DownloaderFromEthernetMultiThreading PRIVATE Qt6::Network)
target_link_libraries(DownloaderFromEthernetMultiThreading PRIVATE Qt6::Core)
target_link_libraries(DownloaderFromEthernetMultiThreading PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS DownloaderFromEthernetMultiThreading
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET DownloaderFromEthernetMultiThreading
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

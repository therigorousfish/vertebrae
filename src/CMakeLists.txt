include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})

# Find the QtWidgets library
find_package(Qt5Widgets)

set(SOURCES
	main.cpp
	mainwindow.cpp
	${CMAKE_SOURCE_DIR}/include/mainwindow.h
)

set(UI_SOURCES
    gui/mainwindow.ui
)

qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

# Tell CMake to create the helloworld executable
add_executable(helloworld WIN32 ${SOURCES} ${UI_GENERATED_HEADERS})


# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets)
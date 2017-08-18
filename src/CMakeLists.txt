add_definitions(${Qt5Gui_DEFINITIONS})

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
	main.cpp
	mainwindow.cpp
	scene/viewport.cpp
	logo.cpp
	scene/scene.cpp
	scene/actor.cpp
	${CMAKE_SOURCE_DIR}/include/mainwindow.h
	${CMAKE_SOURCE_DIR}/include/scene/viewport.h
	${CMAKE_SOURCE_DIR}/include/logo.h
	${CMAKE_SOURCE_DIR}/include/scene/scene.h
	${CMAKE_SOURCE_DIR}/include/scene/actor.h
	${PROJECT_BINARY_DIR}/config.h
)

set(UI_SOURCES
    gui/mainwindow.ui
)

qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

# Tell CMake to create the helloworld executable
add_executable(helloworld WIN32 ${SOURCES} ${UI_GENERATED_HEADERS})

if(WIN32)
   set_target_properties(helloworld PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
   set_target_properties(helloworld PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
endif(WIN32)

# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets)
# Use system module from Boost
target_link_libraries(helloworld Boost::system)

if(${MSVC})
    target_compile_options(helloworld PRIVATE /std:c++latest)
endif()
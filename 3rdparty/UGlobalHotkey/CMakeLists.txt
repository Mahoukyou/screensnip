set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(
	GLOB lib_srcs
	"*.h"
	"*.cpp"
)

add_compile_definitions(UGLOBALHOTKEY_LIBRARY)

set(CMAKE_DEBUG_POSTFIX d)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(gh SHARED ${lib_srcs})
set_target_properties(gh PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(gh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gh Qt5::Widgets)
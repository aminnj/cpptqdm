message(STATUS "reading ${CMAKE_CURRENT_LIST_FILE}")
project(tqdm_test)

if (NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "_d")
    include(GNUInstallDirs)
endif()

add_executable(${PROJECT_NAME} "")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_sources(${PROJECT_NAME}
    PRIVATE
    test.cpp
    )

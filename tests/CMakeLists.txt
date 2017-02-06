project(test)

set(CMAKE_CXX_FLAGS "-pthread")
find_package(Boost 1.58.0 COMPONENTS program_options system log date_time REQUIRED)

include(CTest)
enable_testing()

include(DownloadProject.cmake)
download_project(
        PROJ googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        UPDATE_DISCONNECTED 1
)

file(GLOB SOURCE_FILES "../src/*.cpp")
file(GLOB TEST_SOURCE_FILES "./dive_tests/*.cpp")


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions(-DBOOST_LOG_DYN_LINK)

    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
    add_executable(runUnitTests gtest.cpp  ${SOURCE_FILES} ${TEST_SOURCE_FILES})
    target_link_libraries(runUnitTests gtest gmock ${Boost_LIBRARIES})
endif ()
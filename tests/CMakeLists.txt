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

set(SOURCE_FILES ../src/dive.cpp ../src/rpc.cpp ../src/member_list.cpp)


if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions(-DBOOST_LOG_DYN_LINK)

    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

    add_executable(runUnitTests gtest.cpp dive_tests/dive_tests.cpp ${SOURCE_FILES} dive_tests/member_tests.cpp dive_tests/member_list_tests.cpp)
    target_link_libraries(runUnitTests gtest gmock ${Boost_LIBRARIES})
endif ()
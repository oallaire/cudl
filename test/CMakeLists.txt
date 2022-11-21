project(cudl-test LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME} cudl_test.cpp cudl_prefix_test.cpp cudl_no_prefix_test.cpp)
target_link_libraries(${PROJECT_NAME} cudl::lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

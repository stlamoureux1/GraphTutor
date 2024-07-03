# GTest build info
option(TEST "Enable Test" OFF)

if(TEST)

    include(FetchContent)
    FetchContent_Declare(
        googletest 
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(GraphTutorTest
        
    )

    include_directories("${PROJECT_SOURCE_DIR}/src/Model")

    target_include_directories(GraphViz PUBLIC "${PROJECT_SOURCE_DIR}/src/Model/")
    target_link_directories(GraphViz PUBLIC "${PROJECT_SOURCE_DIR}/src/Model/")
    
    target_link_libraries(
        GraphTutorTest
        GTest::gtest_main
        GTest::gmock_main
    )

    include(GoogleTest)
    gtest_discover_tests(GraphTutorTest)

    enable_testing()

    add_test(test_node GraphTutorTest --gtestfilter=NodeTest*)
endif(TEST)
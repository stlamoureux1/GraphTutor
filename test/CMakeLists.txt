# GTest build info
option(TEST "Enable Test" OFF)

if(TEST)

    include(FetchContent)
    FetchContent_Declare(
        googletest 
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    include_directories(${PROJECT_SOURCE_DIR}/src)

    add_executable(
        GraphTutorTest
        # GUI
        ${PROJECT_SOURCE_DIR}/test/GUI/GraphViewTest.cpp
        ${PROJECT_SOURCE_DIR}/src/GUI/SimpleGraphView.cpp
        ${PROJECT_SOURCE_DIR}/src/GUI/NodeView.cpp 
        ${PROJECT_SOURCE_DIR}/src/GUI/EdgeView.cpp
        # Model
        ${PROJECT_SOURCE_DIR}/test/Model/NodeTest.cpp 
        ${PROJECT_SOURCE_DIR}/test/Model/EdgeTest.cpp
        ${PROJECT_SOURCE_DIR}/test/Model/SimpleGraphTest.cpp
    )
    
    target_link_libraries(
        GraphTutorTest
        GTest::gtest_main
        GTest::gmock_main
        ${wxWidgets_LIBRARIES}
    )

    include(GoogleTest)
    gtest_discover_tests(GraphTutorTest)

    enable_testing()

    add_test(test_node GraphTutorTest --gtestfilter=NodeTest*)
endif(TEST)
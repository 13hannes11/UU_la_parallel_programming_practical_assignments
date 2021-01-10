include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(node_unit_test Node_test.cpp)
target_link_libraries(node_unit_test PUBLIC gtest gtest_main)
target_link_libraries(node_unit_test PUBLIC stack)
add_test(NodeTest node_unit_test)

add_executable(adt_unit_test ADT_Stack_test.cpp)
target_link_libraries(adt_unit_test PUBLIC gtest gtest_main)
target_link_libraries(adt_unit_test PUBLIC stack)
add_test(ADTTest adt_unit_test)

add_executable(treiber_unit_test Treiber_Stack_test.cpp)
target_link_libraries(treiber_unit_test PUBLIC gtest gtest_main)
target_link_libraries(treiber_unit_test PUBLIC stack)
add_test(TreiberTest treiber_unit_test)

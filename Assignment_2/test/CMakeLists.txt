include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(fine_unit_test FineSet_test.cpp)
target_link_libraries(fine_unit_test PUBLIC gtest gtest_main)
target_link_libraries(fine_unit_test PUBLIC sets)

add_test(FineSetTest fine_unit_test)


add_executable(lazy_unit_test LazySet_test.cpp)
target_link_libraries(lazy_unit_test PUBLIC gtest gtest_main)
target_link_libraries(lazy_unit_test PUBLIC sets)
add_test(LazySetTest lazy_unit_test)

add_executable(optimistic_unit_test OptimisticSet_test.cpp)
target_link_libraries(optimistic_unit_test PUBLIC gtest gtest_main)
target_link_libraries(optimistic_unit_test PUBLIC sets)
add_test(OptimisticSetTest optimistic_unit_test)

add_executable(multi_unit_test MultiSet_test.cpp)
target_link_libraries(multi_unit_test PUBLIC gtest gtest_main)
target_link_libraries(multi_unit_test PUBLIC sets)
add_test(MultiSetTest multi_unit_test)

add_executable(vshlog_test "vshlog_test327.cpp")
target_link_libraries(vshlog_test PRIVATE vshlog)
target_include_directories(vshlog_test PRIVATE ../vshlog/include)
set_property(TARGET vshlog_test PROPERTY CXX_STANDARD 20)

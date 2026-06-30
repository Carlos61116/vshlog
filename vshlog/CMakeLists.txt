add_library(vshlog
    src/Logger.cpp
    src/Sink.cpp
    src/Category.cpp
    src/LogLevel.cpp
 "include/vshlog/LogLevel.h" "include/vshlog/LogEntry.h" "include/vshlog/Category.h" "src/Category.cpp" "include/vshlog/Sink.h" "src/LogLevel.cpp" "include/vshlog/Config.h" "include/vshlog/Hash.h" "include/vshlog/vshlog.h")


target_include_directories(vshlog PUBLIC include)

set_property(TARGET vshlog PROPERTY CXX_STANDARD 20)

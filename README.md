# vshlog

A procedural, allocation-conscious logging library for C++20

`vshlog` is my first serious C++ project — a static library written from scratch to learn the language at a systems level: translation units, linkage, the ODR, CMake, and data-oriented design without classes or inheritance.

## Why procedural, not OOP?

Most C++ loggers (spdlog, log4cpp) use a class hierarchy with virtual `write()` methods for sinks. `vshlog` takes a different approach: **function pointers instead of vtables**.

```cpp
using WriterFn = void(*)(const LogEntry&, void* context);

struct Sink {
    WriterFn writer;
    void* context;
    SinkType type;
};
```

A `Sink` is just data — a pointer to a writer function and an opaque `void*` context. The Logger doesn't know or care what kind of sink it's calling; it just invokes `sink.writer(entry, sink.context)`. No inheritance, no `new`, no virtual dispatch. This mirrors patterns common in engine and systems code, where data-oriented design is the default.

## Features

- **Static library** (not header-only) — chosen deliberately to keep compile times low on larger projects.
- **Level filtering**, both globally (`vsh::init`) and per-sink (`ConsoleSinkConfig` / `FileSinkConfig`).
- **Console and file sinks**, both driven by the same writer/context mechanism.
- **Per-source-file log files**, created on demand. Logging from `Renderer.cpp` automatically writes to `Logs/<category>/Renderer.log` — no manual path configuration needed.
- **Category system** backed by a global `unordered_map`, encapsulated behind `register_category` / `category_name` so the map itself has no external linkage.
- **Compile-time string hashing** (`constexpr hash_str`) used to key source files into the file-sink map without runtime string comparisons.
- **Automatic `__FILE__` / `__LINE__` capture** via macros, so every log line knows exactly where it came from.

## Quick example

```cpp
#include "vshlog/vshlog.hpp"

int main() {
    vsh::init(vsh::LogLevel::DEBUG);
    vsh::add_console_sink(vsh::ConsoleSinkConfig{ .min_log_level = vsh::LogLevel::DEBUG });
    vsh::add_file_sink(vsh::FileSinkConfig{ .append = true, .min_log_level = vsh::LogLevel::WARN });

    VSH_LOG_INFO("vshlog up and running", "General");
    VSH_LOG_WARN("Texture not found", "Render");

    vsh::shutdown();
}
```

Output:
[INFO] main.cpp 8 vshlog up and running
[WARN] main.cpp 9 Texture not found

And on disk:
Logs/
Render/
main.log

## Architecture
include/vshlog/
LogLevel.h     — severity enum (TRACE..FATAL) + to_string
LogEntry.h     — POD struct: level, text, timestamp, category, file, line
Category.h     — runtime category registration backed by a hidden unordered_map
Sink.h         — Sink/WriterFn definitions, FileSinkContext/ConsoleSinkContext
Config.h        — LoggerConfig / FileSinkConfig / ConsoleSinkConfig
Hash.h         — constexpr string hashing
Logger.h       — public API: init, shutdown, add_sink, log
vshlog.hpp     — umbrella header + VSH_LOG macros
src/
LogLevel.cpp
Category.cpp
Sink.cpp
Logger.cpp

All global state (the sink list, the category map, the per-file contexts) lives in unnamed namespaces inside the relevant `.cpp` files — never exposed directly, only through the functions declared in the matching header. This was a deliberate exercise in respecting the One Definition Rule and internal linkage rather than reaching for `static` everywhere.

## Building

`vshlog` builds as a CMake static library target. A companion `vshlog_test` executable exercises the API end to end.

```cmake
add_subdirectory("vshlog")
add_subdirectory("vshlog_test")
```

Requires C++20 (designated initializers, `std::format`, `std::filesystem`).

## Known limitations

- **Not thread-safe.** Global sink/context state has no synchronization. Fine for single-threaded use; a hard blocker for concurrent logging without further work.
- **No log rotation yet.** `FileSinkConfig::max_size_bytes` exists in the config struct but rotation logic isn't implemented.
- **No bounded cache for open file handles.** Every distinct `__FILE__` that logs keeps its `ofstream` open for the program's lifetime. Fine for typical projects, but an LRU eviction policy is a planned improvement before this scales to very large codebases.

## Status

Functionally complete for single-threaded use: console/file sinks, level filtering, categories, automatic per-file log files, and convenience macros all work end to end. Built entirely by hand as a learning project — no code was copied, only reviewed.
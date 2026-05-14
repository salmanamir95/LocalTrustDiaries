cmake_minimum_required(VERSION 3.20)

project(LocalTrustDiaries LANGUAGES C CXX)

# -------------------------------------------------
# Core header-only interface library
# -------------------------------------------------
add_library(LocalTrustDiaries INTERFACE)

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(LocalTrustDiaries INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# -------------------------------------------------
# Dependencies (core shared utilities)
# -------------------------------------------------
target_link_libraries(LocalTrustDiaries INTERFACE
    shared
)

# -------------------------------------------------
# Language standard (C++23 required)
# -------------------------------------------------
target_compile_features(LocalTrustDiaries INTERFACE cxx_std_23)

# -------------------------------------------------
# Strict compilation settings (recommended for your runtime system)
# -------------------------------------------------
target_compile_options(LocalTrustDiaries INTERFACE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# -------------------------------------------------
# Optional: enable assertions in debug builds
# -------------------------------------------------
target_compile_definitions(LocalTrustDiaries INTERFACE
    $<$<CONFIG:Debug>:LOCAL_TRUST_DIARIES_DEBUG>
)

# -------------------------------------------------
# Optional: threading support (important for TaskSystem / TaskQueue)
# -------------------------------------------------
find_package(Threads REQUIRED)

target_link_libraries(LocalTrustDiaries INTERFACE
    Threads::Threads
)
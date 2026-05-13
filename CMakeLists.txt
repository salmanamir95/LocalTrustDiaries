cmake_minimum_required(VERSION 3.20)

project(LocalTrustDiaries LANGUAGES C CXX)

# -------------------------------------------------
# Header-only library (NO compilation)
# -------------------------------------------------
add_library(LocalTrustDiaries INTERFACE)

# -------------------------------------------------
# Include directories
# -------------------------------------------------
target_include_directories(LocalTrustDiaries INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# -------------------------------------------------
# Dependency: shared (crypto + core utilities)
# -------------------------------------------------
target_link_libraries(LocalTrustDiaries INTERFACE shared)

# -------------------------------------------------
# Language standard requirement (propagated)
# -------------------------------------------------
target_compile_features(LocalTrustDiaries INTERFACE cxx_std_23)
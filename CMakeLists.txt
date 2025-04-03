cmake_minimum_required(VERSION 3.10)

project(ChronoClientTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to ChronoClientSDK
set(CHRONO_SDK_PATH "/home/eneko/ChronoClientSDK")

# Add the executable
add_executable(chronoclient-test src/main.cpp)

# Specify include directories for the executable
target_include_directories(chronoclient-test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include   # Optional: for project-specific headers
    ${CHRONO_SDK_PATH}/include             # Headers from the ChronoClientSDK
)

# Specify the directory where the ChronoClientSDK libraries reside
target_link_directories(chronoclient-test PRIVATE ${CHRONO_SDK_PATH}/lib)

# Link against the ChronoClientSDK libraries
target_link_libraries(chronoclient-test PRIVATE
    chronolog_client
    ChronoCommon
)

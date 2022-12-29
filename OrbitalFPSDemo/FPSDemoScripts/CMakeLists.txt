file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME}Scripts SHARED ${SOURCES})

target_compile_definitions(${PROJECT_NAME}Scripts PRIVATE FPSDEMOSCRIPTS_EXPORT)

target_link_libraries(${PROJECT_NAME}Scripts PUBLIC ${PROJECT_NAME}Library)

target_include_directories(${PROJECT_NAME}Scripts
  PUBLIC
  include
  ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}Library/include
  ${CMAKE_SOURCE_DIR}/OrbitalEngine/include # TODO find a better way to get the include
  PRIVATE
  src)

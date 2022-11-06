add_executable(
    ecs_test
    ecs_test.cpp
)

target_link_libraries(
    ecs_test
    PRIVATE GTest::GTest OrbitalECS
)

add_test(NAME ecs_test COMMAND $<TARGET_FILE:ecs_test>)

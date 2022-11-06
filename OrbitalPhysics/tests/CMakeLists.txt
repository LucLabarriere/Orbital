add_executable(
    physics_test
    physics_test.cpp
)

target_link_libraries(
    physics_test
    PRIVATE GTest::GTest OrbitalPhysics
)

add_test(
    NAME physics_test
    COMMAND $<TARGET_FILE:physics_test>
)

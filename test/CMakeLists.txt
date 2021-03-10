
# Local header files here ONLY
set(TARGET_HPP)

# Local source files here
set(TARGET_CPP
    main.cpp
    test_890_to_ass.cpp)


# Define an executable
add_executable(cb_test_890_to_ass ${TARGET_HPP} ${TARGET_CPP})

# External Dependencies
#add_dependencies(cb_test_890_to_ass googletest)

# Add postfix onto executable debug filename
set_target_properties(cb_test_890_to_ass PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})


# Additional Include Directories
target_include_directories(cb_test_890_to_ass PUBLIC
    #TPSDKS
    #${GTEST_INCLUDE_DIRS}

    #CB Directories
    )

# Define the libraries this project depends upon
target_link_libraries(cb_test_890_to_ass

    # CB Libraries
    cb_890_to_ass_plugin

    # TPSDKS
    GTest::GTest
    )

# Lastly add support for GTest in CTest
GTEST_ADD_TESTS(cb_test_890_to_ass "" AUTO)

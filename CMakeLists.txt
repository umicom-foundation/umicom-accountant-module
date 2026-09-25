#-----------------------------------------------------------------------------
# Umicom Accountant Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build the thin Umicom Accountant composition against the canonical Umicom
#   Framework application target without defining local reusable services.
#
# AUTHOR AND ORGANISATION:
#   Sammy Hegab
#   Umicom Foundation
#
# LICENCE:
#   MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(
    UmicomAccountantModule
    VERSION 0.1.0
    DESCRIPTION "Thin Umicom Accountant composition over Umicom Framework"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_ACCOUNTANT_BUILD_CONSOLE
       "Build the native Umicom Accountant verification console"
       ON)

include(CTest)
include(GNUInstallDirs)

# Apply this branch only when its contract condition is satisfied.
if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()
# Apply this branch only when its contract condition is satisfied.
if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Accountant requires Framework target Umicom::application")
endif()

# Apply this branch only when its contract condition is satisfied.
if(NOT COMMAND umicom_apply_warnings)
    # Provide the apply warnings operation used by this module and its client applications.
    function(umicom_apply_warnings target)
        # Apply this branch only when its contract condition is satisfied.
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        # Use this fallback path when the earlier condition does not apply.
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()
# Apply this branch only when its contract condition is satisfied.
if(NOT COMMAND umicom_apply_sanitizers)
    # Provide the apply sanitizers operation used by this module and its client applications.
    function(umicom_apply_sanitizers target)
    endfunction()
endif()

add_library(umicom_accountant_module STATIC
    src/application.c
    src/workspace.c
)
add_library(Umicom::accountant_module ALIAS umicom_accountant_module)

target_include_directories(umicom_accountant_module PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(umicom_accountant_module PUBLIC
    Umicom::Framework
    Umicom::application
)

# Apply this branch only when its contract condition is satisfied.
if(COMMAND umicom_apply_warnings)
    umicom_apply_warnings(umicom_accountant_module)
endif()
# Apply this branch only when its contract condition is satisfied.
if(COMMAND umicom_apply_sanitizers)
    umicom_apply_sanitizers(umicom_accountant_module)
endif()

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomThinApplicationRuntime.cmake")
umicom_extend_thin_application_runtime(
    NAME "accountant"
    TARGET "umicom_accountant_module")

# Keep the operation inside its valid bounds before reading, writing or adding data.
if(UMICOM_ACCOUNTANT_BUILD_CONSOLE)
    add_executable(umicom-accountant-console
        src/console/main.c)
    target_link_libraries(umicom-accountant-console PRIVATE
        Umicom::accountant_module)
    # Apply this branch only when its contract condition is satisfied.
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom-accountant-console)
    endif()
    # Apply this branch only when its contract condition is satisfied.
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom-accountant-console)
    endif()
endif()

# Apply this branch only when its contract condition is satisfied.
if(BUILD_TESTING)
    add_executable(umicom_accountant_module-test
        tests/test_application.c)
    target_link_libraries(umicom_accountant_module-test PRIVATE
        Umicom::accountant_module)
    # Apply this branch only when its contract condition is satisfied.
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom_accountant_module-test)
    endif()
    # Apply this branch only when its contract condition is satisfied.
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom_accountant_module-test)
    endif()
    add_test(
        NAME accountant.module.application
        COMMAND umicom_accountant_module-test)

    add_executable(umicom_accountant_workspace-test
        tests/test_workspace.c)
    target_link_libraries(umicom_accountant_workspace-test PRIVATE
        Umicom::accountant_module)
    # Apply this branch only when its contract condition is satisfied.
    if(COMMAND umicom_apply_warnings)
        umicom_apply_warnings(umicom_accountant_workspace-test)
    endif()
    # Apply this branch only when its contract condition is satisfied.
    if(COMMAND umicom_apply_sanitizers)
        umicom_apply_sanitizers(umicom_accountant_workspace-test)
    endif()
    add_test(
        NAME accountant.module.workspace
        COMMAND umicom_accountant_workspace-test)
endif()

install(TARGETS umicom_accountant_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# Keep the operation inside its valid bounds before reading, writing or adding data.
if(TARGET umicom-accountant-console)
    install(TARGETS umicom-accountant-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/accountant)
# Apply this branch only when its contract condition is satisfied.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    install(FILES README.md
        DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/accountant)
endif()
# Apply this branch only when its contract condition is satisfied.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/accountant)
endif()

message(STATUS "Umicom Accountant Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom Accountant uses Framework-owned application experience")

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomApplicationProductisationContribution.cmake")
umicom_add_application_productisation_contribution(
    NAME "accountant"
    TARGET umicom_accountant_productisation
    SOURCE "src/productisation_contribution.c"
    TEST_SOURCE "tests/test_productisation_contribution.c")

# Select the shared operational service without replacing the existing module,
# console, productisation contribution, tests or catalogue layouts.
include("${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomFinanceOperations.cmake")
umicom_attach_finance_operations(NAME accountant TARGET umicom_accountant_module)

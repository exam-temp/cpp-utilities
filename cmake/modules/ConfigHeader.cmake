# before including this module, all relevant variables must be set
# just include this module as last one since nothing should depend on it

if(NOT TARGET_CONFIG_DONE)
    message(FATAL_ERROR "Before including the ConfigHeader module, the AppTarget/LibraryTarget module must be included.")
endif()

# find config.h template
include(TemplateFinder)
find_template_file("config.h" CPP_UTILITIES CONFIG_H_TEMPLATE_FILE)

# create list of dependency versions present at link time (one list for shared library and another for
# the static library since the lists might differ)
include(ListToString)
foreach(LINKAGE IN ITEMS "" "STATIC_")
    unset(DEPENCENCY_VERSIONS)
    unset(${LINKAGE}DEPENCENCY_VERSIONS_ARRAY)
    # iterate through public and private libraries of shared/static library
    foreach(DEPENDENCY IN LISTS PUBLIC_${LINKAGE}LIBRARIES PRIVATE_${LINKAGE}LIBRARIES)
        if(TARGET ${DEPENDENCY})
            # find version and display name for target
            string(SUBSTRING "${DEPENDENCY}" 0 5 DEPENDENCY_PREFIX)
            if("${DEPENDENCY_PREFIX}" STREQUAL "Qt5::" OR "${DEPENDENCY_PREFIX}" STREQUAL "StaticQt5::")
                # read meta-data of Qt module
                string(SUBSTRING "${DEPENDENCY}" 5 -1 DEPENDENCY_MODULE_NAME)
                set(DEPENDENCY_DISPLAY_NAME "Qt ${DEPENDENCY_MODULE_NAME}")
                set(DEPENDENCY_VER "${Qt5${DEPENDENCY_MODULE_NAME}_VERSION_STRING}")
            elseif(${DEPENDENCY}_varname)
                # read meta-data of one of my own libraries
                set(DEPENDENCY_VARNAME "${${DEPENDENCY}_varname}")
                set(DEPENDENCY_DISPLAY_NAME "${DEPENDENCY}")
                if(${DEPENDENCY_VARNAME}_DISPLAY_NAME)
                    set(DEPENDENCY_DISPLAY_NAME "${${DEPENDENCY_VARNAME}_DISPLAY_NAME}")
                endif()
                set(DEPENDENCY_VER "${${DEPENDENCY_VARNAME}_VERSION}")
            else()
                unset(DEPENDENCY_DISPLAY_NAME)
                unset(DEPENDENCY_VER)
                # FIXME: provide meta-data for other libs, too
            endif()
            if(DEPENDENCY_VER AND NOT "${DEPENDENCY_VER}" STREQUAL "DEPENDENCY_VER-NOTFOUND")
                list(APPEND DEPENCENCY_VERSIONS "${DEPENDENCY_DISPLAY_NAME}: ${DEPENDENCY_VER}")
            endif()
        endif()
    endforeach()
    if(DEPENCENCY_VERSIONS)
        list_to_string("," " \\\n    \"" "\"" "${DEPENCENCY_VERSIONS}" ${LINKAGE}DEPENCENCY_VERSIONS_ARRAY)
    endif()
endforeach()

# add configuration header
configure_file(
    "${CONFIG_H_TEMPLATE_FILE}"
    "${CMAKE_CURRENT_BINARY_DIR}/resources/config.h"
)

# ensure generated include files can be included via #include "resources/config.h"
foreach(TARGET_NAME ${TARGET_PREFIX}${META_PROJECT_NAME}${TARGET_SUFFIX} ${TARGET_PREFIX}${META_PROJECT_NAME}${TARGET_SUFFIX}_static ${TARGET_PREFIX}${META_PROJECT_NAME}${TARGET_SUFFIX}_tests ${TARGET_PREFIX}${META_PROJECT_NAME}${TARGET_SUFFIX}_testlib)
    if(TARGET ${TARGET_NAME})
        target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
endforeach()

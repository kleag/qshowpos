project(qshowpos)

cmake_minimum_required(VERSION 2.8)

include(SystemSpecificInformations.cmake)

add_definitions(-D QT_NO_KEYWORDS)
include(${CMAKE_SOURCE_DIR}/manageQt5.cmake)
addQt5Modules(Core Gui Widgets)
include_directories(${Qt5_INCLUDES})
get_target_property(QtCore_location Qt5::Core LOCATION)
get_target_property(QtGui_location Qt5::Gui LOCATION)
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)
set(QT_LIBRARIES "${Qt5_LIBRARIES}")

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  install(FILES ${QtCore_location}
    ${QtGui_location}
    ${QtWidgets_location}
  DESTINATION ${LIB_INSTALL_DIR})
endif ()


add_subdirectory(src)


########### documentation ###############

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

########### packaging ###############
INCLUDE(InstallRequiredSystemLibraries)

set(CPACK_MONOLITHIC_INSTALL 1)
SET(CPACK_PACKAGE_NAME "qshowpos")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Q Show Position tool")
SET(CPACK_PACKAGE_VENDOR "CEA LIST")
SET(CPACK_PACKAGE_CONTACT "Gaël de Chalendar <Gael.de-Chalendar@cea.fr>")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
SET(CPACK_STRIP_FILES "bin/qshowpos")
SET(CPACK_SOURCE_STRIP_FILES "")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_GENERATOR ${SPECIFIC_SYSTEM_PREFERED_CPACK_GENERATOR})
IF (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  set(CPACK_RPM_PACKAGE_REQUIRES "")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
ELSE (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  set(CPACK_RPM_PACKAGE_REQUIRES "")
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "")
endif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")

INCLUDE(CPack)

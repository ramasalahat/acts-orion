#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ActsCore" for configuration "RelWithDebInfo"
set_property(TARGET ActsCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(ActsCore PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libActsCore.dylib"
  IMPORTED_SONAME_RELWITHDEBINFO "@rpath/libActsCore.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS ActsCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_ActsCore "${_IMPORT_PREFIX}/lib/libActsCore.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

# Generated by funapi_initiator
# You can edit this file to meet your taste.

###############################################################################
# Put your build rules here.
###############################################################################

# NOTE: IF YOU HAVE MORE SOURCE FILES, ADD HERE.
set(
  ADDITIONAL_CPP_SOURCES
  client.cc
  client.h
  server.cc
  server.h
  ${PROJECT_NAME}_server.cc
)

set(
  ADDITIONAL_PROTO_SOURCES
  ${PROJECT_NAME}_rpc_messages.proto
  ${PROJECT_NAME}_messages.proto
)

set(
  ADDITIONAL_LIBRARIES
)


###############################################################################
# Compile flags
###############################################################################
# Please append your compile flag like this:
# set_property(TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS " -DMY_FLAG")



###############################################################################
# Inclusion after setting variables.
###############################################################################

set(CMAKE_MODULE_PATH "/usr/share/funapi/cmake")
include(Funapi-src)



###############################################################################
# Now, ${PROJECT_NAME} rule is available after the inclusion above.
# If you need to handle ${PROJECT_NAME} target, specify here.
#
# E.g., set_target_properties(${PROJECT_NAME} ...)
###############################################################################

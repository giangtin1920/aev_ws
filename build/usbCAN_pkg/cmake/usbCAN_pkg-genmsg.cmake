# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "usbCAN_pkg: 1 messages, 0 services")

set(MSG_I_FLAGS "-IusbCAN_pkg:/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(usbCAN_pkg_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg" NAME_WE)
add_custom_target(_usbCAN_pkg_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "usbCAN_pkg" "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(usbCAN_pkg
  "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/usbCAN_pkg
)

### Generating Services

### Generating Module File
_generate_module_cpp(usbCAN_pkg
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/usbCAN_pkg
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(usbCAN_pkg_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(usbCAN_pkg_generate_messages usbCAN_pkg_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg" NAME_WE)
add_dependencies(usbCAN_pkg_generate_messages_cpp _usbCAN_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(usbCAN_pkg_gencpp)
add_dependencies(usbCAN_pkg_gencpp usbCAN_pkg_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS usbCAN_pkg_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(usbCAN_pkg
  "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/usbCAN_pkg
)

### Generating Services

### Generating Module File
_generate_module_eus(usbCAN_pkg
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/usbCAN_pkg
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(usbCAN_pkg_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(usbCAN_pkg_generate_messages usbCAN_pkg_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg" NAME_WE)
add_dependencies(usbCAN_pkg_generate_messages_eus _usbCAN_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(usbCAN_pkg_geneus)
add_dependencies(usbCAN_pkg_geneus usbCAN_pkg_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS usbCAN_pkg_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(usbCAN_pkg
  "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/usbCAN_pkg
)

### Generating Services

### Generating Module File
_generate_module_lisp(usbCAN_pkg
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/usbCAN_pkg
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(usbCAN_pkg_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(usbCAN_pkg_generate_messages usbCAN_pkg_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg" NAME_WE)
add_dependencies(usbCAN_pkg_generate_messages_lisp _usbCAN_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(usbCAN_pkg_genlisp)
add_dependencies(usbCAN_pkg_genlisp usbCAN_pkg_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS usbCAN_pkg_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(usbCAN_pkg
  "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/usbCAN_pkg
)

### Generating Services

### Generating Module File
_generate_module_nodejs(usbCAN_pkg
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/usbCAN_pkg
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(usbCAN_pkg_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(usbCAN_pkg_generate_messages usbCAN_pkg_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg" NAME_WE)
add_dependencies(usbCAN_pkg_generate_messages_nodejs _usbCAN_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(usbCAN_pkg_gennodejs)
add_dependencies(usbCAN_pkg_gennodejs usbCAN_pkg_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS usbCAN_pkg_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(usbCAN_pkg
  "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/usbCAN_pkg
)

### Generating Services

### Generating Module File
_generate_module_py(usbCAN_pkg
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/usbCAN_pkg
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(usbCAN_pkg_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(usbCAN_pkg_generate_messages usbCAN_pkg_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/giangtin/aev/aev_ws/src/usbCAN_pkg/msg/CAN_msg.msg" NAME_WE)
add_dependencies(usbCAN_pkg_generate_messages_py _usbCAN_pkg_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(usbCAN_pkg_genpy)
add_dependencies(usbCAN_pkg_genpy usbCAN_pkg_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS usbCAN_pkg_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/usbCAN_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/usbCAN_pkg
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(usbCAN_pkg_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/usbCAN_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/usbCAN_pkg
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(usbCAN_pkg_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/usbCAN_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/usbCAN_pkg
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(usbCAN_pkg_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/usbCAN_pkg)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/usbCAN_pkg
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(usbCAN_pkg_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/usbCAN_pkg)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/usbCAN_pkg\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/usbCAN_pkg
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(usbCAN_pkg_generate_messages_py std_msgs_generate_messages_py)
endif()


# Copyright (c) 2012 Christopher Lux <christopherlux@gmail.com>
# Distributed under the Modified BSD License, see license.txt.

project(ex_volume_ray_cast_cuda)

include(schism_project)
include(schism_boost)
include(schism_macros)
include(schism_qt5)

IF (NOT ${SCM_ENABLE_CUDA_CL_SUPPORT})
  message("Warning: Ignoring target ex_volume_ray_cast_cuda: Please enable SCM_ENABLE_CUDA_CL_SUPPORT to build this example.")
  return()
ENDIF (NOT ${SCM_ENABLE_CUDA_CL_SUPPORT})

# source files
scm_project_files(SOURCE_FILES      ${SRC_DIR} *.cpp)
scm_project_files(HEADER_FILES      ${SRC_DIR} *.h *.inl)

scm_project_files(SOURCE_FILES_GUI  ${SRC_DIR}/application *.cpp)
scm_project_files(HEADER_FILES_GUI  ${SRC_DIR}/application *.h *.inl)
scm_project_files(SOURCE_FILES_GUI  ${SRC_DIR}/application/volume_gui *.cpp)
scm_project_files(HEADER_FILES_GUI  ${SRC_DIR}/application/volume_gui *.h *.inl)

scm_project_files(SOURCE_FILES_GUI  ${SRC_DIR}/gui_support *.cpp)
scm_project_files(HEADER_FILES_GUI  ${SRC_DIR}/gui_support *.h *.inl)

scm_project_files(SOURCE_FILES      ${SRC_DIR}/renderer *.cpp)
scm_project_files(HEADER_FILES      ${SRC_DIR}/renderer *.h *.inl)
scm_project_files(SHADER_FILES      ${SRC_DIR}/renderer/shader *.glsl *.glslh *.glslf *.glslv *glslg *.glsltc *.glslte)
scm_project_files(KERNEL_FILES      ${SRC_DIR}/renderer/kernel *.cl *.clh *.cu *.h)

scm_add_moc_command(SOURCE_FILES_GUI ${HEADER_FILES_GUI})
list(APPEND HEADER_FILES ${HEADER_FILES_GUI})
list(APPEND SOURCE_FILES ${SOURCE_FILES_GUI})

# include header and inline files in source files for visual studio projects
if (WIN32)
    if (MSVC)
        set (SOURCE_FILES ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES} ${KERNEL_FILES})
    endif (MSVC)
endif (WIN32)

# set include and lib directories
scm_project_include_directories(ALL   ${SRC_DIR}
                                      ${SCM_ROOT_DIR}/scm_core/src
                                      ${SCM_ROOT_DIR}/scm_cl_core/src
                                      ${SCM_ROOT_DIR}/scm_gl_core/src
                                      ${SCM_ROOT_DIR}/scm_gl_util/src
                                      ${SCM_ROOT_DIR}/scm_input/src
                                      ${SCM_BOOST_INC_DIR}
                                      ${SCM_QT5_INC_DIR})

scm_project_include_directories(WIN32 ${GLOBAL_EXT_DIR}/inc
                                      ${GLOBAL_EXT_DIR}/inc/cuda
                                      ${GLOBAL_EXT_DIR}/inc/freeimage)
scm_project_include_directories(UNIX  /opt/OpenCL/include
                                      /opt/cuda/current/cuda/include)

#scm_cuda_project_include_directories( ${GLOBAL_EXT_DIR}/inc
#                                      ${GLOBAL_EXT_DIR}/inc/cuda)
#message(${PROJECT_NAME} ${SCM_CUDA_NVCC_INCLUDE_DIRECTORIES})

# set library directories
scm_project_link_directories(ALL      ${SCM_LIB_DIR}/${SCHISM_PLATFORM}
                                      ${SCM_BOOST_LIB_DIR}
                                      ${SCM_QT5_LIB_DIR})
scm_project_link_directories(UNIX     /opt/cuda/current/cuda/lib64
                                      /usr/lib/nvidia-current)

#scm_project_link_directories(WIN32    ${GLOBAL_EXT_DIR}/lib)
#scm_project_link_directories(UNIX     )

# add/create library
#set(cu_output "")
#message(${KERNEL_FILES})
scm_cuda_add_nvcc_prepass(cu_output ${KERNEL_FILES})
#message(${cu_output})
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${cu_output})

# link libraries
scm_link_libraries(ALL
    general scm_core
    general scm_cl_core
    general scm_gl_core
    general scm_gl_util

	general cuda
	general cudart
)
scm_link_libraries(WIN32
    optimized libboost_filesystem-${SCM_BOOST_MT_REL}       debug libboost_filesystem-${SCM_BOOST_MT_DBG}
    optimized libboost_program_options-${SCM_BOOST_MT_REL}  debug libboost_program_options-${SCM_BOOST_MT_DBG}
    optimized Qt5Core       debug Qt5Cored
    optimized Qt5Gui        debug Qt5Guid
    optimized Qt5Widgets    debug Qt5Widgetsd
    optimized FreeImage     debug FreeImaged
    optimized FreeImagePlus debug FreeImagePlusd
)
scm_link_libraries(UNIX
    general boost_filesystem${SCM_BOOST_MT_REL}
    general boost_program_options${SCM_BOOST_MT_REL}
    general QtCore
    general QtGui
)
scm_copy_schism_libraries()

add_dependencies(${PROJECT_NAME}
    scm_core
    scm_cl_core
    scm_gl_core
    scm_gl_util
)

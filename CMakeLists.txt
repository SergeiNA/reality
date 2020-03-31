cmake_minimum_required(VERSION 3.7)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(reality VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(reality VERSION 7.7.7)
endif()


set (EXE_NAME_1 rclst)
set (EXE_NAME_2 rclss)

set (SRC_FILES_1
                rclst_main.cpp
                rclst_common.hpp
                rclst_utils.hpp   rclst_utils.cpp
                )

set (SRC_FILES_2
                rclss_main.cpp
                rclss_common.hpp
                rclss_utils.hpp   rclss_utils.cpp
                )

add_executable(${EXE_NAME_1} ${SRC_FILES_1})
add_executable(${EXE_NAME_2} ${SRC_FILES_2})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  set(CMP_OPTIONS "-Wall;-Wextra;-Wshadow;-Wnon-virtual-dtor;\
                    -Wold-style-cast;-Wcast-align;-Wunused;\
                    -Woverloaded-virtual;-Wconversion;\
                    -Wsign-conversion;-Wduplicated-cond")

  if(CMAKE_BUILD_TYPE MATCHES Debug)
      set(CMP_OPTIONS ${CMP_OPTIONS}";-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
      message("debug")
  endif()
else()
  set(CMP_OPTIONS "/W4")
endif()

set_target_properties(${EXE_NAME_1} ${EXE_NAME_2} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS ${CMP_OPTIONS}
)

target_link_libraries(${EXE_NAME_1}
        dlib openblas
)

target_link_libraries(${EXE_NAME_2}
        dlib openblas
)

install(TARGETS ${EXE_NAME_1} ${EXE_NAME_2} RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT nikseas@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)





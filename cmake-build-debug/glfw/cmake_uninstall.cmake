
if (NOT EXISTS "/media/yanshi/EE10BE3610BE059D/Linux/rzshao/MeshRenderDataMaker/cmake-build-debug/glfw/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/media/yanshi/EE10BE3610BE059D/Linux/rzshao/MeshRenderDataMaker/cmake-build-debug/glfw/install_manifest.txt\"")
endif()

file(READ "/media/yanshi/EE10BE3610BE059D/Linux/rzshao/MeshRenderDataMaker/cmake-build-debug/glfw/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("/home/yanshi/Downloads/clion-2019.1.4/bin/cmake/linux/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("/home/yanshi/Downloads/clion-2019.1.4/bin/cmake/linux/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

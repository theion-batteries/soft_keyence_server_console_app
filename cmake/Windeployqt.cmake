# Helper cmake to deploy qt application using windeployqt
# original work: https://github.com/nitroshare/nitroshare-desktop/blob/226dd32879981c0bf2ef4c78faee3af3b797bfdc/cmake/Windeployqt.cmake
# article: https://blog.nathanosman.com/2017/11/24/using-windeployqt-with-cpack.html
# useful link: https://github.com/miurahr/cmake-qt-packaging-example/blob/master/Packaging.cmake
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Widgets Concurrent )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Concurrent )

cmake_policy(SET CMP0087 NEW)
# Retrieve the absolute path to qmake and then use that path to find
# the windeployqt binary
get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

# Running this with MSVC 2015 requires CMake 3.6+
if((MSVC_VERSION VERSION_EQUAL 1900 OR MSVC_VERSION VERSION_GREATER 1900)
        AND CMAKE_VERSION VERSION_LESS "3.6")
    message(WARNING "Deploying with MSVC 2015+ requires CMake 3.6+")
endif()

# Add commands that copy the Qt runtime to the target's output build_dir after
# build and install the Qt runtime to the specified build_dir
function(windeployqt target build_dir install_dir)

    message("windeployqt arguments:
    target: ${target}.exe
    build_dir: ${build_dir}/
    full path: ${build_dir}/${target}.exe
    install_dir: ${install_dir}/
    ")
    # Run windeployqt immediately after build
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
                --no-compiler-runtime
                --no-opengl-sw
                \"${build_dir}/${target}.exe\"
    )
    set(wgm_path ${build_dir}/${target}.exe)
    # install(CODE ...) doesn't support generator expressions, but
    # file(GENERATE ...) does - store the path in a file
    set(${CMAKE_BUILD_TYPE} $<CONFIG>)
    file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${target}_path"
        CONTENT "${CMAKE_BUILD_TYPE}"
    )
    message("path: ${CMAKE_CURRENT_BINARY_DIR}/${target}_path")
    # Before installation, run a series of commands that copy each of the Qt
    # runtime files to the appropriate build_dir for installation
    install(CODE
        "
        file(READ \"${CMAKE_CURRENT_BINARY_DIR}/${target}_path\" _file)
        execute_process(
            COMMAND \"${CMAKE_COMMAND}\" -E
                env PATH=\"${_qt_bin_dir}\" \"${WINDEPLOYQT_EXECUTABLE}\"
                    --dry-run
                    --no-compiler-runtime
                    --no-opengl-sw
                    --list mapping
                    \${CMAKE_INSTALL_PREFIX}/bin/Debug/${target}.exe
            OUTPUT_VARIABLE _output
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        message(\" file: \${_file} \")
        separate_arguments(_files WINDOWS_COMMAND \${_output})
        while(_files)

            list(GET _files 0 _src)
            list(GET _files 1 _dest)
            message(\" copy \${_dest} to install folder \")

            execute_process(
                COMMAND \"${CMAKE_COMMAND}\" -E
                    copy \${_src} \"\${CMAKE_INSTALL_PREFIX}/bin/Debug/\${_dest}\"
            )
            list(REMOVE_AT _files 0 1)
        endwhile()

        # windeployqt doesn't work correctly with the system runtime libraries,
        # so we fall back to one of CMake's own modules for copying them over
        foreach(lib \${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
            get_filename_component(filename \${lib} NAME)
            message(\" copy \${lib} to install folder \")
            execute_process(
                COMMAND \"${CMAKE_COMMAND}\" -E
                    copy \${lib} \"\${CMAKE_INSTALL_PREFIX}/\${install_dir}/\"
            )
        endforeach()
        "
    )

set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)
install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION ${install_dir})




endfunction()

mark_as_advanced(WINDEPLOYQT_EXECUTABLE)
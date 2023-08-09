function(qserializer_get_semver_from_git varname)
        if(NOT PROJECT_IS_TOP_LEVEL)
                return ()
        endif()

        find_package (Git REQUIRED)
        # cmake-format: off
        execute_process (
                COMMAND
                        ${GIT_EXECUTABLE} describe --tags --long --dirty
                COMMAND
                        sed -e s/-\\\([[:digit:]]\\+\\\)-g/+\\1\\./
                COMMAND
                        sed -e s/-dirty\$/\\.dirty/
                COMMAND
                        sed -e s/+0\\.[^\\.]\\+\\.\\?/+/
                COMMAND
                        sed -e s/^v//
                COMMAND
                        sed -e s/+\$//
                OUTPUT_VARIABLE
                        ${varname}
                RESULTS_VARIABLE  rets
                OUTPUT_STRIP_TRAILING_WHITESPACE
                COMMAND_ECHO STDOUT
        )

        foreach(ret ${rets})
                if(NOT ret EQUAL 0)
                        return ()
                endif()
        endforeach()

        message (STATUS "Get semver from git repository: ${${varname}}")
        # cmake-format: on

        set (
                ${varname}
                ${${varname}}
                PARENT_SCOPE
        )
endfunction()

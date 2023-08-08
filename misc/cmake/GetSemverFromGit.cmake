function(qserializer_get_semver_from_git varname)
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
                RESULT_VARIABLE ret
                OUTPUT_STRIP_TRAILING_WHITESPACE
                COMMAND_ERROR_IS_FATAL ANY
                COMMAND_ECHO STDOUT
        )
        # cmake-format: on
        message (
                STATUS
                        "get semver from git: ${${varname}}"
        )
        set (
                ${varname}
                ${${varname}}
                PARENT_SCOPE
        )
endfunction()

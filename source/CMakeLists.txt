
# Local header files here ONLY
set(TARGET_HPP
    ../include/export.hpp
    ../include/890toass.hpp
    ../include/stltoass.hpp
)

# Local source files here
set(TARGET_CPP
    890toass.cpp
    stltoass.cpp
)
set(LIB890_FILE
        cavena_reader/Formats/Cavena890.cpp
        cavena_reader/Formats/Cavena890.h
        cavena_reader/Formats/Ebu.cpp
        cavena_reader/Formats/Ebu.h
        cavena_reader/Formats/Pac.cpp
        cavena_reader/Formats/Pac.h
        cavena_reader/Formats/PacUnicode.cpp
        cavena_reader/Formats/PacUnicode.h
        cavena_reader/Formats/SubtitleFormat.cpp
        cavena_reader/Formats/SubtitleFormat.h
        cavena_reader/libse/Configuration.cpp
        cavena_reader/libse/Configuration.h
        cavena_reader/libse/FileUtil.cpp
        cavena_reader/libse/FileUtil.h
        cavena_reader/libse/LanguageAutoDetect.cpp
        cavena_reader/libse/LanguageAutoDetect.h
        cavena_reader/libse/Paragraph.cpp
        cavena_reader/libse/Paragraph.h
        cavena_reader/libse/Settings.cpp
        cavena_reader/libse/Settings.h
        cavena_reader/libse/StringExtensions.cpp
        cavena_reader/libse/StringExtensions.h
        cavena_reader/libse/Subtitle.cpp
        cavena_reader/libse/Subtitle.h
        cavena_reader/libse/TimeCode.cpp
        cavena_reader/libse/TimeCode.h
        cavena_reader/libse/TimeSpan.cpp
        cavena_reader/libse/TimeSpan.h
        cavena_reader/libse/Utilities.cpp
        cavena_reader/libse/Utilities.h
        common/bankersrounding.h
        common/define.h
        common/exceptionhelper.h
        common/stringbuilder.h
        common/stringhelper.h
        common/vectorhelper.h
        linux_lib/findfirst.cpp
        linux_lib/findfirst.h
        linux_lib/spec.cpp
        linux_lib/spec.h
        my_api.cpp
        my_api.h
)
add_library(cb_890_to_ass_plugin SHARED ${TARGET_HPP} ${TARGET_CPP} ${LIB890_FILE})

target_include_directories(cb_890_to_ass_plugin PRIVATE
)

target_link_libraries(cb_890_to_ass_plugin

)

/*************************************************************************
 * Copyright (C) coralbay.tv Ltd. - All Rights Reserved.
 * Unauthorized copying of this file via any medium is strictly prohibited
 * Proprietary and Confidential
 ************************************************************************/

#ifndef PACTOASSPLUGIN_PACTOASS_H
#define PACTOASSPLUGIN_PACTOASS_H

#include "export.hpp"

#include <iosfwd>

namespace cb::subtitle::PAC
{

enum class result
{
    RESULT_OK = 0,

    RESULT_INCOMPLETE = 1,
    RESULT_INVALID = 2,
    RESULT_BAD_DATA = 3,
    RESULT_NOT_IMPLEMENTED = 4,

    RESULT_UNKNOWN_ERROR
};

enum codepageType
{
    CODEPAGE_LATIN = 0,
    CODEPAGE_GREEK = 1,
    CODEPAGE_LATIN_CZECH = 2,
    CODEPAGE_ARABIC = 3,
    CODEPAGE_HEBREW = 4,
    CODEPAGE_THAI = 5,
    CODEPAGE_CYRILLIC = 6,
    CODEPAGE_CHINESE_TRADITIONAL = 7,
    CODEPAGE_CHINESE_SIMPLIFIED = 8,
    CODEPAGE_KOREAN = 9,
    CODEPAGE_JAPANESE = 10,
    CODEPAGE_LATIN_TURKISH = 11
};

//////////////////////////////////////////////////////////////////////////
CB_890TOASS_PUBLIC result probe(std::istream &istrm);

//////////////////////////////////////////////////////////////////////////
CB_890TOASS_PUBLIC result set_code_page(codepageType codePage);
CB_890TOASS_PUBLIC result convert(std::istream &istrm, std::ostream &ostrm);
CB_890TOASS_PUBLIC result set_frame_rate(double frameRate);

//////////////////////////////////////////////////////////////////////////
CB_890TOASS_PUBLIC bool is_input_binary_format();

} // namespace cb::subtitle::EBU


#endif  // PACTOASSPLUGIN_PACTOASS_H
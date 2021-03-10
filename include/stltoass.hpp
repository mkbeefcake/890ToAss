/*************************************************************************
 * Copyright (C) coralbay.tv Ltd. - All Rights Reserved.
 * Unauthorized copying of this file via any medium is strictly prohibited
 * Proprietary and Confidential
 ************************************************************************/

#ifndef STLTOASSPLUGIN_STLTOASS_H
#define STLTOASSPLUGIN_STLTOASS_H

#include "export.hpp"

#include <iosfwd>

namespace cb::subtitle::EBU
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

//////////////////////////////////////////////////////////////////////////
CB_890TOASS_PUBLIC result probe(std::istream &istrm);

//////////////////////////////////////////////////////////////////////////
CB_890TOASS_PUBLIC result convert(std::istream &istrm, std::ostream &ostrm);
CB_890TOASS_PUBLIC result set_frame_rate(double frameRate);

//////////////////////////////////////////////////////////////////////////
CB_890TOASS_PUBLIC bool is_input_binary_format();

} // namespace cb::subtitle::EBU


#endif //STLTOASSPLUGIN_STLTOASS_H

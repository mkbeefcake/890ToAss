/*************************************************************************
 * Copyright (C) coralbay.tv Ltd. - All Rights Reserved.
 * Unauthorized copying of this file via any medium is strictly prohibited
 * Proprietary and Confidential
 ************************************************************************/

#include "890toass.hpp"
#include "my_api.h"
#include <istream>
#include <ostream>

namespace cb::subtitle::L890
{

//////////////////////////////////////////////////////////////////////////
// export
result probe(std::istream &istrm)
{
    bool bProbe = probe_format(istrm, STREAM_TYPE_890);
    if (bProbe == true)
        return result::RESULT_OK;
    else
        return result::RESULT_UNKNOWN_ERROR;
}

//////////////////////////////////////////////////////////////////////////
// export
result convert(std::istream &istrm, std::ostream &ostrm)
{
    Subtitle* subtitle = read_buffer(istrm, STREAM_TYPE_890);
    if(subtitle)
    {
        //printf("read success");
        write_buffer(subtitle, ostrm);
        delete subtitle;
        return result::RESULT_OK;
    }
    return result::RESULT_UNKNOWN_ERROR;
}
result set_frame_rate(double frameRate)
{
    set_frame_rate(frameRate);
    return result::RESULT_OK;
}


//////////////////////////////////////////////////////////////////////////
// export
bool is_input_binary_format()
{
    return false;
}

} // namespace cb::subtitle::L890
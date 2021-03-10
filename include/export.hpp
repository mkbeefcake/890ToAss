/*************************************************************************
 * Copyright (C) coralbay.tv Ltd. - All Rights Reserved.
 * Unauthorized copying of this file via any medium is strictly prohibited
 * Proprietary and Confidential
 ************************************************************************/

#ifndef L890TOASSPLUGIN_EXPORT_HPP
#define L890TOASSPLUGIN_EXPORT_HPP

#if (defined _WIN32 || defined __CYGWIN__) && !defined(__GNUC__)
#ifdef CB_890TOASS_EXPORTS
#define CB_890TOASS_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#else
#define CB_890TOASS_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#if __GNUC__ >= 4
#define CB_890TOASS_PUBLIC __attribute__ ((visibility ("default")))
#else
#define CB_890TOASS_PUBLIC
#endif
#endif


#endif //L890TOASSPLUGIN_EXPORT_HPP

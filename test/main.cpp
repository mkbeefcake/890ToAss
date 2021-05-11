/*************************************************************************
 * Copyright (C) coralbay.tv Ltd. - All Rights Reserved.
 * Unauthorized copying of this file via any medium is strictly prohibited
 * Proprietary and Confidential
 ************************************************************************/

#include <gtest/gtest.h>

///////////////////////////////////////////////////////////////////////////
int main(int ac, char *av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}


// #include <stdio.h>
// #include <iconv.h>
// #include <errno.h>
// #include <err.h>
// #include <string.h>

// int main() {
//   iconv_t cd;
//   size_t k, f, t;
//   int se;
//   char code[5];
//   code[0] = 0xa5; code[1] = 0x4c; code[2] = 0xc0; code[3] = 0xb3; code[4] = 0x00;
//   char* in = (char*) code;
//   char buf[100];
//   char* out = buf;

//   cd = iconv_open("UTF-8", "BIG-5");
//   if( cd == (iconv_t)(-1) )
//     err( 1, "iconv_open" );
//   f = 5;
//   t = sizeof buf;
//   memset( &buf, 0, sizeof buf );
//   errno = 0;
//   k = iconv(cd, &in, &f, &out, &t);
//   se = errno;
//   printf( "converted: 0x%x,error=%d\n", (unsigned) k, se );
  
//   printf("string: %s\n", buf);

//   iconv_close(cd);
//   return 0;
// }













// #include <stdio.h>
// #include <stdlib.h>
// #include <clocale>
// #include <memory.h>
// #include <cstdio>
// #include <clocale>
// #include <ctime>
// #include <cwchar>

// #pragma warning(disable: 4996)

// int main(void)
// {
//     std::setlocale(LC_ALL, "zh_HK.UTF-8");

//     // wchar_t str[100];
//     // memset(str, 0, 100 * sizeof(wchar_t));

//     // std::time_t t = std::time(NULL);
//     // std::wcsftime(str, 100, L"%A %c", std::localtime(&t));
//     // std::wprintf(L"%Ls\n", str);

//     // // 4 wide characters
//     const wchar_t src[] = L"\ua54c\uc0b3\ub8d3\ub77c\ua7c6\ub1e6\ua46a";
//     // // they occupy 10 bytes in UTF-8

//     char dst[100];
//     memset(dst, 0, 100);

//     // std::setlocale(LC_ALL, "zh_HK.UTF-8");
//     // printf("wide-character string: '%ls'\n", src);
//     // for (size_t ndx = 0; ndx < sizeof src / sizeof src[0]; ++ndx)
//     //     printf("   src[%2zu] = %#8x\n", ndx, src[ndx]);

//     int rtn_val = wcstombs(dst, src, sizeof dst);
//     wprintf(L"rtn_val = %d\n", rtn_val);
    
//     // if (rtn_val > 0)
//     //     printf("multibyte string:  '%s'\n", dst);
//     for (size_t ndx = 0; ndx < rtn_val + 1; ++ndx)
//         wprintf(L"   dst[%2zu] = %#2x\n", ndx, (unsigned char)dst[ndx]);
// }
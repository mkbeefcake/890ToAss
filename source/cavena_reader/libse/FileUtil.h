#pragma once

#include "../../common/define.h"
class FileUtil final
{
public:
	static u8Vector ReadAllBytesShared(std::string path);
    static u8Vector ReadAllStream(std::istream& istrm);
    static u8Vector ReadBytes(std::istream& istrm, uint offset, uint size);
};

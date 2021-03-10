#include "FileUtil.h"
#include "../../my_api.h"
#define _CRT_SECURE_NO_WARNINGS
u8Vector FileUtil::ReadAllBytesShared(std::string path)
{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
	{
		FILE* fs;
#ifdef WIN32
		fopen_s(&fs, path.data(), "rb");
#else
		fs = fopen(path.data(), "rb");
#endif
		if(fs != nullptr)
		{
			int index = 0;
			_finddata_t fi = getFileInfo(path);
			unsigned long long fileLength = fi.size;
			if (fileLength > (uint)-1)
			{
				throw IOException("File too long");
			}
			

			auto count = static_cast<int>(fileLength);
			auto bytes = u8Vector(count);
			while (count > 0)
			{
				auto n = fread(bytes.data() + index, 1, count, fs);
				if (n == 0)
				{
					throw IOException("End of file reached before expected");
				}

				index += n;
				count -= n;
			}
			fclose(fs);
			return bytes;
		}		
		return u8Vector();
	}
}
#include <string.h>

u8Vector FileUtil::ReadAllStream(std::istream& istrm)
{
    const int buffer_size = 1024;
    u8Vector final_vec;
    u8Vector tmp_vec(buffer_size);
    int read_size = 0;
    int cur_size;

	istrm.seekg(0, istrm.beg);
    while((read_size = istrm.readsome((char*)tmp_vec.data(), buffer_size) ) > 0)
    {
        cur_size = final_vec.size();
        final_vec.resize(cur_size + read_size);

        memcpy((void*)&final_vec[cur_size], (void*)&tmp_vec[0], read_size);
    }
    return final_vec;
}

u8Vector FileUtil::ReadBytes(std::istream& istrm, uint offset, uint size)
{
    const int buffer_size = size;
    u8Vector tmp_vec(buffer_size);
	istrm.seekg(offset, istrm.beg);
    istrm.readsome((char*)tmp_vec.data(), buffer_size);
    return tmp_vec;
}
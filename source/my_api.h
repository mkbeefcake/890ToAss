#pragma once
#include "common/define.h"
#include "cavena_reader/libse/Subtitle.h"

_finddata_t getFileInfo(std::string file_name);

bool setCodePage(int code_page);

std::string getEncodedString(u8Vector& buffer, int start, int textLength);
std::string getEncodedString(u8Vector& buffer);
std::string getEncodedString(u8Vector buffer);
std::string getEncodedString(int code_page, u8Vector& buffer, int start, int textLength);
std::string getW16EncodedString(int code_page, u8Vector& buffer, int start, int textLength);

std::string getASCIIString(u8Vector& buffer, int start, int textLength);

std::string getUTF8String(u8Vector& buffer, int start, int textLength);


#define     STREAM_TYPE_UNKNONW 0x00
#define     STREAM_TYPE_890     0x01
#define     STREAM_TYPE_PAC     0x02
#define     STREAM_TYPE_PAC_UNI 0x03
#define     STREAM_TYPE_EBU     0x04

bool probe_format(std::istream& istrm, int type);
Subtitle* read_buffer(std::istream& istrm, int type);
Subtitle* read_file(std::string file_name);
void set_frame_rate(double frame_rate);
void write_buffer(Subtitle* subtitle, std::ostream& ostrm);
void write_to_ass(Subtitle* subtitle, char* file_name);

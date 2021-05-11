/*************************************************************************
 * Copyright (C) coralbay.tv Ltd. - All Rights Reserved.
 * Unauthorized copying of this file via any medium is strictly prohibited
 * Proprietary and Confidential
 ************************************************************************/

#include <gtest/gtest.h>

#include <890toass.hpp>
#include <stltoass.hpp>

#include <fstream>

#include "../source/common/stringhelper.h"
#include "../source/common/vectorhelper.h"
#include "../source/common/stringbuilder.h"
#include "../source/common/exceptionhelper.h"
#include "../source/common/bankersrounding.h"
#include "../source/cavena_reader/libse/Utilities.h"
#include "../source/cavena_reader/libse/TimeCode.h"
#include "../source/cavena_reader/libse/StringExtensions.h"
#include "../source/cavena_reader/libse/Settings.h"
#include "../source/cavena_reader/libse/Configuration.h"
#include "../source/cavena_reader/libse/FileUtil.h"


////////////////////////////////////////////////////////////////////////////////
class test_utilities : public testing::Test
{
public:

    test_utilities() = default;

    ~test_utilities() override = default;
};

////////////////////////////////////////////////////////////////////////////////
TEST_F(test_utilities, stringhelper)
{
    std::string empty = std::string();

    // ------------------------------------------------------
    std::string HelloWorld = "Hello World";

    // CHECK : toLower()
    std::string helloworld = StringHelper::toLower(HelloWorld);
    EXPECT_TRUE(helloworld == "hello world");

    std::string emptyLowercase = StringHelper::toLower(empty);
    EXPECT_TRUE(emptyLowercase == "");

    // CHECK : toUpper()
    std::string HELLOWORLD = StringHelper::toUpper(HelloWorld);
    EXPECT_TRUE(HELLOWORLD == "HELLO WORLD");

    std::string emptyUppercase = StringHelper::toUpper(empty);
    EXPECT_TRUE(emptyUppercase == "");

    // ------------------------------------------------------
    std::string stringWithSpaces = "   Fox brown ";

    // CHECK : trimStart()
    std::string stringWithTrimStart = StringHelper::trimStart(stringWithSpaces);
    EXPECT_TRUE(stringWithTrimStart == "Fox brown ");

    std::string emptyTrimStart = StringHelper::trimStart(empty);
    EXPECT_TRUE(emptyTrimStart == "");

    // CHECK : trimEnd()
    std::string stringWithTrimEnd = StringHelper::trimEnd(stringWithSpaces);
    EXPECT_TRUE(stringWithTrimEnd == "   Fox brown");

    std::string emptyTrimEnd = StringHelper::trimEnd(empty);
    EXPECT_TRUE(emptyTrimEnd == "");

    // CHECK : trim()
    std::string stringWithTrim = StringHelper::trim(stringWithSpaces);
    EXPECT_TRUE(stringWithTrim == "Fox brown");

    std::string emptyTrim = StringHelper::trim(empty);
    EXPECT_TRUE(emptyTrim == "");

    // ------------------------------------------------------
    std::string greetings = "Hello Anatoliy! ";

    std::string greetingsToOther = StringHelper::replace(greetings, "Anatoliy", "Denis");
    EXPECT_TRUE(greetingsToOther == "Hello Denis! ");

    std::string emptyReplace = StringHelper::replace(empty, "Hi", "Hello");
    EXPECT_TRUE(emptyReplace == "");

    // ------------------------------------------------------
    std::string happyNewYear = "Happy new year!";

    bool bHappy = StringHelper::startsWith(happyNewYear, "Happy");
    EXPECT_TRUE(bHappy == true);

    bool bStartEmpty = StringHelper::startsWith(happyNewYear, std::string());
    EXPECT_TRUE(bStartEmpty == true);

    bool bStartHello = StringHelper::startsWith(empty, "Hello");
    EXPECT_TRUE(bStartHello == false);

    bool bYear = StringHelper::endsWith(happyNewYear, "year!");
    EXPECT_TRUE(bYear == true);

    bool bEndEmpty = StringHelper::endsWith(happyNewYear, std::string());
    EXPECT_TRUE(bEndEmpty == true);

    bool bEndHello = StringHelper::endsWith(empty, "Hello");
    EXPECT_TRUE(bEndHello == false);

    // ------------------------------------------------------
    std::string sentence = "Hello there! How are you?";
    std::vector<std::string> words = StringHelper::split(sentence, ' ');
    EXPECT_TRUE(words.size() == 5);

    double number = 123.45;
    std::string printed = StringHelper::toString(number);
    EXPECT_TRUE(printed == "123.45");

    std::string printed1 = StringHelper::toString(-1.231);
    EXPECT_TRUE(printed1 == "-1.231");

    std::string numberString = "1234";
    int value = StringHelper::fromString<int>(numberString);
    EXPECT_TRUE(value == 1234);

    EXPECT_THROW(StringHelper::fromString<int>(empty), std::runtime_error);

    std::string whitespaceString = "              ";
    bool bEmpty = StringHelper::isEmptyOrWhiteSpace(whitespaceString);
    EXPECT_TRUE(bEmpty == true);

    bool bEmptyString = StringHelper::isEmptyOrWhiteSpace(empty);
    EXPECT_TRUE(bEmptyString == true);

    std::string formula = "Formula: {0} + {1} = {2}";
    std::string result = StringHelper::formatSimple(formula, 123, 321, "444");
    EXPECT_TRUE(result == "Formula: 123 + 321 = 444");

    std::string result1 = StringHelper::formatSimple(empty, 123, 321, empty);
    EXPECT_TRUE(result1 == "");
}

TEST_F(test_utilities, vectorhelper)
{
    std::vector<int> numberList = {2, 4, 6, 8, 10, 12, 6};

    int indexofSix = VectorHelper::indexOf(numberList, 6);
    EXPECT_TRUE(indexofSix == 2);

    int indexOfSix2 = VectorHelper::indexOf(numberList, 6, 4);
    EXPECT_TRUE(indexOfSix2 == 6);

    int indexOfSix3 = VectorHelper::lastIndexOf(numberList, 6);
    EXPECT_TRUE(indexOfSix3 == 6);

    int indexOfSix4 = VectorHelper::lastIndexOf(numberList, 6, 3);
    EXPECT_TRUE(indexOfSix4 == 2);
}

TEST_F(test_utilities, stringbuilder)
{
    StringBuilder* greetings = new StringBuilder("Hi ");
    greetings->append("There");
    EXPECT_TRUE(greetings->toString() == "Hi There");

    StringBuilder* emptyBuilder = new StringBuilder(std::string());
    emptyBuilder->append("Wow!");
    EXPECT_TRUE(emptyBuilder->toString() == "Wow!");

    greetings->appendLine();
    EXPECT_TRUE(greetings->toString() == "Hi There\r\n");

    greetings->appendLine("How are you?");
    EXPECT_TRUE(greetings->toString() == "Hi There\r\nHow are you?\r\n");

    delete greetings;
    delete emptyBuilder;

    StringBuilder *sb = new StringBuilder("Hi , How are you?");
    sb->insert(3, "Anatoliy");
    EXPECT_TRUE(sb->toString() == "Hi Anatoliy, How are you?");    

    EXPECT_TRUE(sb->length() == 25);

    sb->setLength(50);
    EXPECT_TRUE(sb->length() == 50);

    sb->replace(", How are you?", "");
    EXPECT_TRUE(sb->toString() == "Hi Anatoliy");

    sb->remove(0, 3);
    EXPECT_TRUE(sb->toString() == "Anatoliy");

    emptyBuilder = new StringBuilder(std::string());
    emptyBuilder->insert(3, 123.32);
    EXPECT_TRUE(emptyBuilder->toString() == "123.32");

    EXPECT_TRUE((*emptyBuilder)[0] == '1');
    EXPECT_TRUE((*emptyBuilder)[10] == 0);

    EXPECT_TRUE(emptyBuilder->toString(10, 10) == "");

    emptyBuilder->setLength(4);
    EXPECT_TRUE(emptyBuilder->length() == 4);

    emptyBuilder->ensureCapacity(50);
    EXPECT_TRUE(emptyBuilder->capacity() == 50);

    emptyBuilder->remove(10, 10);
    EXPECT_TRUE(emptyBuilder->toString() == "123.");

    emptyBuilder->replace(std::string(), "test");
    EXPECT_TRUE(emptyBuilder->toString() == "123.");
}

TEST_F(test_utilities, exceptionhelper)
{
    EXPECT_THROW(throw InvalidOperationException("test exception"), InvalidOperationException);
    EXPECT_THROW(throw IOException("test exception"), IOException);
}

TEST_F(test_utilities, bankersrounding)
{
    double original = 3.562;
    double round = BankersRounding::round(original);
    EXPECT_TRUE(round == 4.0);

}

TEST_F(test_utilities, utilities)
{
    std::string original = "Hello World!";
    std::string reverse = Utilities::ReverseString(original);
    EXPECT_TRUE(reverse == "!dlroW olleH");

    std::string empty = std::string();
    std::string reverseEmpty = Utilities::ReverseString(empty);
    EXPECT_TRUE(reverseEmpty == "");

    std::string hebrew = "הכי אוהבים בעולם?";
    std::vector<bool> b_heb_vec = {true, true, true, false, true, true, true, true, true, true, false, true, true, true, true, true, false};
    std::string reverseHebrew = Utilities::ReverseStartAndEndingForRightToLeft(hebrew, b_heb_vec);
    EXPECT_TRUE(reverseHebrew == "?הכי אוהבים בעולם");

    std::string reverseEmpty1 = Utilities::ReverseStartAndEndingForRightToLeft(empty, std::vector<bool>());
    EXPECT_TRUE(reverseEmpty1 == "");

    std::string hebrew1 = "?נועה- .מה";
    std::vector<bool> b_heb_vec1 = {true, true, true, true, false, false, false, true, true, false};
    std::string reverseHebrew1 = Utilities::FixPunctuationMarks1(hebrew1, b_heb_vec1);
    EXPECT_TRUE(reverseHebrew1 == "?נועה. -מה");

    std::string reverseEmpty2 = Utilities::FixPunctuationMarks1(empty, std::vector<bool>());
    EXPECT_TRUE(reverseEmpty2 == "");
}

TEST_F(test_utilities, timecode)
{
    TimeCode* timeCode = new TimeCode(1, 10, 30, 0);
    double milliseconds = timeCode->getTotalMilliseconds();
    EXPECT_TRUE(milliseconds == 4230000);

    std::string assString = timeCode->ToASSString();
    EXPECT_TRUE(assString == "1:10:30.00");  
}

TEST_F(test_utilities, StringExtensions)
{
    std::string empty = std::string();

    std::string s = "STL23123";
    bool bSTL = StringExtensions::StartsWith(s, "STL");
    EXPECT_TRUE(bSTL == true);

    bool bEmpty = StringExtensions::StartsWith(s, empty);
    EXPECT_TRUE(bEmpty == true);

    bool bEmpty1 = StringExtensions::StartsWith(empty, "STL");
    EXPECT_TRUE(bEmpty1 == false);

    std::string s1 = "1231.pac";
    bool bPac = StringExtensions::EndsWith(s1, "pac");
    EXPECT_TRUE(bPac == true);

    bool bEmpty2 = StringExtensions::EndsWith(s1, empty);
    EXPECT_TRUE(bEmpty2 == true);

    bool bEmpty3 = StringExtensions::EndsWith(empty, "pac");
    EXPECT_TRUE(bEmpty3 == false);

    std::string s2 = "\x06\x10\x11\r\n   ";
    bool isEmpty = StringExtensions::IsOnlyControlCharactersOrWhiteSpace(s2);
    EXPECT_TRUE(isEmpty == true);

    bool bEmpty4 = StringExtensions::IsOnlyControlCharactersOrWhiteSpace(empty);
    EXPECT_TRUE(bEmpty4 == true);

    std::string s3 = StringExtensions::RemoveControlCharactersButWhiteSpace(s2);
    EXPECT_TRUE(s3 == "\r\n   ");

    std::string r1 = StringExtensions::RemoveControlCharactersButWhiteSpace(empty);
    EXPECT_TRUE(r1 == "");

    std::string s4 = "hahaha";
    std::string s5 = StringExtensions::PadLeft(s4, 10, '+');
    EXPECT_TRUE(s5 == "++++hahaha");

    std::string r2 = StringExtensions::PadLeft(empty, 10, '=');
    EXPECT_TRUE(r2 == "==========");

    std::string s6 = StringExtensions::PadRight(s4, 10, '+');
    EXPECT_TRUE(s6 == "hahaha++++");

    std::string r3 = StringExtensions::PadRight(empty, 10, '=');
    EXPECT_TRUE(r3 == "==========");
}

TEST_F(test_utilities, GeneralSettings)
{
    Configuration::getSettings()->General->setCurrentFrameRate(30);
    double rate = Configuration::getSettings()->General->getCurrentFrameRate();
    EXPECT_TRUE(rate == 30);
}

TEST_F(test_utilities, FileUtil)
{
    std::ifstream ifs("/home/anatoliym/Desktop/890ToASS/sub_samples/TTY9001051HB.890", std::ifstream::binary);
    ASSERT_TRUE(!!ifs);

    u8Vector content = FileUtil::ReadAllStream(ifs);
    EXPECT_TRUE(content.size() == 77824);

    u8Vector content1 = FileUtil::ReadBytes(ifs, 100, 100);
    EXPECT_TRUE(content1.size() == 100);
}
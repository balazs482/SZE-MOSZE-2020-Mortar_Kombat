#include "../JSON.h"

#include <gtest/gtest.h>
#include <map>
#include <string>
#include <fstream>
#include <any>

//_______________________________JSON::parse basic tests_______________________________
TEST(parse_test, string_test)
{
	std::string dataString = " {\"name\" : \"Kakarott\"} ";
	ASSERT_NO_THROW(JSON::parse(dataString));
}

TEST(parse_test, stream_test)
{
	std::ifstream fileStream;
	fileStream.open("./good.json");
	ASSERT_NO_THROW(JSON::parse(fileStream));
	fileStream.close();
}

TEST(parse_test, file_test)
{
	std::string fileName = "./good.json";
	ASSERT_NO_THROW(JSON::parse(fileName, true));
}

TEST(parse_test, missing_file)
{
	std::string fileName = "./tobe_or_nottobe_unit_test.json";
	ASSERT_ANY_THROW(JSON::parse(fileName, true));
}

TEST(parse_test, any_types)
{
	std::map<std::string, std::any> data = JSON::parse(" {\"string\" : \"Stringtype\", \"bool\" : true, \"float\" : 1.6, \"null pointer\" : null} ");
	ASSERT_EQ(std::any_cast<std::string>(data["string"]), "Stringtype");
    	ASSERT_EQ(std::any_cast<bool>(data["bool"]), true);
   	ASSERT_EQ(std::any_cast<float>(data["float"]), 1.6f);
	ASSERT_EQ(std::any_cast<nullptr_t>(data["null pointer"]), nullptr);
}

TEST(parse_test, rearranged_keys)
{
	std::map<std::string, std::any> data = JSON::parse(" {\"name\" : \"Kakarott\", \"hp\" : 380} ");
	ASSERT_EQ(std::any_cast<float>(data["hp"]), 380);
	ASSERT_EQ(std::any_cast<std::string>(data["name"]), "Kakarott");
}

//_______________________________JSON::parse wrong input tests_______________________________
TEST(parse_test, empty_string)
{
	std::string dataString = " {\"name\" : \"\"} ";
	ASSERT_THROW(JSON::parse(dataString), std::runtime_error);
}

TEST(parse_test, unexpected_backslash)
{
	std::string dataString = " {\"name\" : \"Kaka\rott\"} ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}

TEST(parse_test, unexpected_mokusos_bracket)
{
	std::string dataString = " {\"name\" : \"Kaka}rott\"} ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}

TEST(parse_test, no_string_ending)
{
	std::string dataString = "{ \"name\" : \"Kakarott }";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}

TEST(parse_test, unrecognizedvalue)
{
	std::string dataString = " { \"name\" : almostString } ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}

TEST(parse_test, duplicate_keys)
{
	std::string dataString = " {\"name\" : \"Kakarott\", \"name\" : \"another Kakarott\"} ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}

TEST(parse_test, no_value)
{
	std::string dataString = " {\"name\" : } ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}
													   
TEST(parse_test, bad_start)
{
	std::string dataString = " this should not be here {\"name\" : \"Kakarott\"} ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}
													   
TEST(parse_test, bad_continuation)
{
	std::string dataString = " {\"name\" : \"Kakarott\"} this should not be here ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}
													   
TEST(parse_test, expected_char)
{
	std::string dataString = " {\"name\" \"Kakarott\"} ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}													   
													   
TEST(parse_test, unexpected_char)
{
	std::string dataString = " {\"name\" :: \"Kakarott\"} ";
	ASSERT_ANY_THROW(JSON::parse(dataString));
}

//_______________________________JSON::parseFromFile and relevant functions test_______________________________
TEST(parseFromFile_test, call_test)
{
	std::string fileName = "./good.json";
	ASSERT_NO_THROW(JSON::parseFromFile(fileName));
}

TEST(parseFromFile_test, count)
{
	std::string fileName = "./good.json";
	JSON testMap = JSON::parseFromFile(fileName);
	ASSERT_EQ(testMap.count("name"), 1);
}

TEST(parseFromFile_test, get_string)
{
	std::string fileName = "./good.json";
	JSON testMap = JSON::parseFromFile(fileName);
	ASSERT_EQ(testMap.get<std::string>("name"), "Test Elek");
}

TEST(parseFromFile_test, get_numeric)
{
	std::string fileName = "./good.json";
	JSON testMap = JSON::parseFromFile(fileName);
	ASSERT_EQ(testMap.get<float>("hp"), 666f);
}

//_______________________________running all tests_______________________________
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

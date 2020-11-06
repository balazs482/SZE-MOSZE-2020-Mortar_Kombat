#include "../JSON.h"

#include <gtest/gtest.h>
#include <map>
#include <string>
#include <fstream>
#include <any>

//_______________________________JSON::map membervariable and relevant functions test_______________________________
TEST(JSON_members_test, construction)
{
	std::map<std::string, std::any> sourceMap;
	sourceMap["key"] = "value";
	ASSERT_THROW(JSON(sourceMap), std::runtime_error);
}

TEST(JSON_members_test, count)
{
	std::map<std::string, std::any> sourceMap;
	sourceMap["sameKey"] = "firstValue";
	sourceMap["sameKey"] = "secondValue";
	JSON testMap = JSON(sourceMap);
	ASSERT_EQ(testMap.count("sameKey"), 2);
}

TEST(JSON_members_test, get_string)
{
	std::map<std::string, std::any> sourceMap;
	sourceMap["key"] = "value";
	JSON testMap = JSON(sourceMap);
	ASSERT_EQ(testMap.get<std::string>("key"), "value");
}

TEST(JSON_members_test, get_numeric)
{
	std::map<std::string, std::any> sourceMap;
	sourceMap["key"] = 1;
	JSON testMap = JSON(sourceMap);
	ASSERT_EQ(testMap.get<float>("key"), 1);
}

//_______________________________JSON::parse basic tests_______________________________
TEST(parse_test, string_test)
{
	std::string data = JSON::parse(" {\"name\" : \"Kakarott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

TEST(parse_test, stream_test)
{
	std::ifstream fileStream;
	fileStream.open("./good.json");
	ASSERT_THROW(JSON::parse(fileStream), std::runtime_error);
	fileStream.close();
}

TEST(parse_test, file_test)
{
	std::string fileName = "./good.json";
	ASSERT_THROW(JSON::parse(fileName, true), std::runtime_error);
}

TEST(parse_test, missing_file)
{
	std::string fileName = "./tobe_or_nottobe_unit_test.json";
	ASSERT_THROW(JSON::parse(fileName, true), std::runtime_error);
}

TEST(parse_test, any_types)
{
	std::string data = JSON::parse("{\"string\":\"Stringtype\",\"bool\":true,\"float\":1.6,\"null pointer\":null}");
	ASSERT_EQ(std::any_cast<std::string>(data["string"]), "Stringtype");
    	ASSERT_EQ(std::any_cast<bool>(data["bool"]), true);
   	ASSERT_EQ(std::any_cast<float>(data["float"]), 1.6f);
	ASSERT_EQ(std::any_cast<nullptr_t>(data["null pointer"]), nullptr);
}

TEST(parse_test, rearranged_keys)
{
	std::string data = JSON::parse("{\"name\":\"Kakarott\",\"hp\":380}");
	ASSERT_EQ(std::any_cast<std::string>(data["hp"]), 380);
	ASSERT_EQ(std::any_cast<std::string>(data["name"]), "Kakarott");
}

//_______________________________JSON::parse wrong input tests_______________________________
TEST(parse_test, empty_string)
{
	std::string data = JSON::parse(" {\"name\" : \"\"} ";
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

TEST(parse_test, unexpected_backslash)
{
	std::string data = JSON::parse(" {\"name\" : \"Kaka\rott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

TEST(parse_test, unexpected_mokusos_bracket)
{
	std::string data = JSON::parse(" {\"name\" : \"Kaka}rott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

TEST(parse_test, no_string_ending)
{
	std::string data = JSON::parse("{ \"name\" : \"Kakarott }");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

TEST(parse_test, unrecognizedvalue)
{
	std::string data = JSON::parse(" { \"name\" : almostString } ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

TEST(parse_test, duplicate_keys)
{
	std::string data = JSON::parse(" {\"name\" : \"Kakarott\", \"name\" : \"another Kakarott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

TEST(parse_test, no_value)
{
	std::string data = JSON::parse(" {\"name\" : } ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}
													   
TEST(parse_test, bad_start)
{
	std::string data = JSON::parse(" this should not be here {\"name\" : \"Kakarott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}
													   
TEST(parse_test, bad_continuation)
{
	std::string data = JSON::parse(" {\"name\" : \"Kakarott\"} this should not be here ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}
													   
TEST(parse_test, expected_char)
{
	std::string data = JSON::parse(" {\"name\" \"Kakarott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}													   

TEST(parse_test, unexpected_char)
{
	std::string data = JSON::parse(" {\"name\" :: \"Kakarott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}
													   
TEST(parse_test, unexpected_char)
{
	std::string data = JSON::parse(" {\"name\" :: \"Kakarott\"} ");
	ASSERT_THROW(JSON::parse(data), std::runtime_error);
}

//_______________________________JSON::parseFromFile test_______________________________
TEST(parseFromFile_test, call_test)
{
	std::string fileName = "./good.json";
	ASSERT_THROW(JSON::parseFromFile(fileName), std::runtime_error);
}

//_______________________________running all tests_______________________________
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

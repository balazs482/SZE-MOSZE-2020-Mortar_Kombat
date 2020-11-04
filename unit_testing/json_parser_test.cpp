#include "../JSON.h"
#include "../Character.h"
#include "../Hero.h"
#include "../Monster.h"

#include <gtest/gtest.h>
#include <map>
#include <string>
#include <fstream>
#include <any>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int generateRandom() {
	srand((unsigned)time(0));
	int randomNumber = rand() % 1000;
	return randomNumber;
}

std::string generateWhiteSapces()
{
	std::string whiteSpaces = "";
	for (int i = 0; i < generateRandom(); i++) { whiteSpaces += " "; }
	return whiteSpaces;
}

std::string generateCommas()
{
	std::string commas = "";
	for (int i = 0; i < generateRandom(); i++) { commas += ","; }
	return commas;
}

TEST(jsonParserTest, parsetest)
{
	ASSERT_THROW(JSON::parse("none.json", true), std::runtime_error);
   	ASSERT_NO_THROW(JSON::parse("../unit_testing/good.json", true));
}

TEST(jsonParserTest, valcheck)
{
	std::map<std::string, std::any> template_inp = JSON::parse("{\"string\":\"Stringtype\",\"bool\":true,\"float\":1.6,\"null pointer\":null}");
	ASSERT_EQ(std::any_cast<std::string>(template_inp["string"]), "Stringtype");
	ASSERT_EQ(std::any_cast<bool>(template_inp["bool"]), true);
	ASSERT_EQ(std::any_cast<float>(template_inp["float"]), 1.6f);
	ASSERT_EQ(std::any_cast<nullptr_t>(template_inp["null pointer"]), nullptr);
}

TEST(jsonParserTest, filetest)
{
	std::ifstream jsonFile;
	jsonFile.open("../unit_testing/missing_comma.json");
	jsonFile.close();
	ASSERT_THROW(JSON::parse(jsonFile), std::runtime_error);
}

TEST(jsonParserTest, stringtest)
{
	std::map<std::string, std::any> template_string = JSON::parse("{\"name\":\"Kakarott\",\"hp\":380,\"dmg\":20,\"as\":1.2}");
	ASSERT_EQ(std::any_cast<std::string>(template_string["name"]), "Kakarott");
	ASSERT_EQ(std::any_cast<float>(template_string["hp"]), 380);
	ASSERT_EQ(std::any_cast<float>(template_string["dmg"]), 20);
	ASSERT_EQ(std::any_cast<float>(template_string["as"]), 1.2f);
}

TEST(jsonParserTest, missingfile)
{
	std::string not_exists = "../../tobe_or_nottobe_unit_test.json";
	ASSERT_THROW(JSON::parse(not_exists, true), std::runtime_error);
}

TEST(jsonParserTest, hero_get_test)
{
	Hero* hero = new Hero::parse("../unit/unit1_Hero.json");
	ASSERT_EQ(hero->getName(), "Kakarott");
	ASSERT_EQ(hero->getMaxHealthPoints(), 380);
	ASSERT_EQ(hero->getDamage(), 20);
	ASSERT_EQ(hero->getAttackCoolDown(), 1.9);
}

TEST(jsonParseTest, monster_get_test)
{
	Monster* enemy = new Monster::parse("Zombie.json");
	ASSERT_EQ(enemy->getName(), "Zombie");
	ASSERT_EQ(enemy->getHealthPoints(), 10);
	ASSERT_EQ(enemy->getDamage(), 1);
	ASSERT_EQ(enemy->getAttackCoolDown(), 2.8);
}

TEST(jsonParseTest, type_test)
{
	Hero* unit = new Hero::parse("../units/unit1_Hero.json");
	ASSERT_EQ(typeid(std::string), typeid(unit->getName()));
	ASSERT_EQ(typeid(float), typeid(unit->getHealthPoints()));
	ASSERT_EQ(typeid(float), typeid(unit->getMaxHealthPoints()));
	ASSERT_EQ(typeid(float), typeid(unit->getDamage()));
	ASSERT_EQ(typeid(float), typeid(unit->getAttackCoolDown()));
	ASSERT_EQ(typeid(bool), typeid(unit->isAlive()));

}

TEST(jsonParseTest, figthTilDeath_test)
{
	Hero* hero = new Hero::parse("../units/unit1_Hero.json");
	Monster* enemy = new Monster::parse("../units/unit2_Monster.json");
	hero->fightTilDeath(enemy*);
	ASSERT_FALSE(hero->isAlive() || enemy->isAlive());
}

TEST(jsonParserTest, missing_comma_test)
{
	ASSERT_THROW(JSON::parse("missing_comma.json"), std::runtime_error);
}

TEST(jsonParserTest, messed_up_input_keys_test)
{
	Hero* bad_hero = new Hero::parse("messed_up_input_keys.json");
	ASSERT_EQ(bad_hero->getName(), "Kakarott");
	ASSERT_EQ(bad_hero->getMaxHealthPoints(), 380);
	ASSERT_EQ(bad_hero->getDamage(), 20);
	ASSERT_EQ(bad_hero->getAttackCoolDown(), 1.9);
}


int main(int argc, char** argv)
{
 n RUN_ALL_TESTS();
}

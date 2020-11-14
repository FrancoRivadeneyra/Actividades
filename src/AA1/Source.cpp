#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "enemy.h"
#include "weapon.h"

int main()
{
	std::vector<Enemy> enemies;
	//Creacion de un documento XML desde el fichero XML para poder leer su contenido
	rapidxml::xml_document<> doc;
	std::ifstream file("C:/Users/franc/source/repos/res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("enemy"); pNode;
		pNode = pNode->next_sibling())
	{
		//Enemigos
		std::string name = std::string(pNode->first_attribute("name")->value());
		float health = std::stoi(pNode->first_node("health")->value());
		float defense = std::stoi(pNode->first_node("defense")->value());
		float attack = std::stoi(pNode->first_node("attack")->value());
		float attackSpeed = std::stoi(pNode->first_node("attackSpeed")->value());
		float exp = std::stoi(pNode->first_node("exp")->value());

		std::vector<Weapon> weapons;

		for (rapidxml::xml_node<>* pNode1 = pNode->first_node("weapon"); pNode1; pNode1->next_sibling())
		{
			std::string type = std::string(pNode1->first_attribute("type")->value());
			std::string id = std::string(pNode1->first_node("id")->value());
			float range = std::stoi(pNode1->first_node("range")->value());
			Weapon auxWeapon = Weapon(type, id, range);
			weapons.push_back(auxWeapon);

		}

	}



	return 0;
}
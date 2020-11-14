#pragma once
#include <string>
#include <vector>
#include "weapon.h"

class Enemy
{
public:
	std::string name;
	float health;
	float defense;
	float attack;
	float attackSpeed;
	float exp;

	std::vector<Weapon> weapon;

	Enemy();
	Enemy(std::string _name, float _health, float _defense, float _attack, float _attackSpeed, float _exp, std::vector<Weapon> _weapon);


};
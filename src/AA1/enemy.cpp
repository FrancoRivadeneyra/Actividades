#include "enemy.h"

Enemy::Enemy() // Por defecto
{

}

Enemy::Enemy(std::string _name, float _health, float _defense, float _attack, float _attackSpeed, float _exp, std::vector<Weapon> _weapon)
{
	health = _health;
	defense = _defense;
	attack = _attack;
	attackSpeed = _attackSpeed;
	exp = _exp;
	weapon = _weapon;
}
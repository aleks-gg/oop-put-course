#include <iostream>
#include <vector>
#include <map>

std::map<std::string, int> creatureLevels;

class Creature {
private:
	std::string Type;
	int Health;
	int Damage;
public:
	void TypeCreature(std::string newType) {
		this->Type = std::move(newType);
		int level = creatureLevels[this->Type];
		this->Health = level * 3;
		this->Damage = level * 4;
	}
	int DamageValue() {
		return this->Damage;
	}
	int HealthValue() {
		return this->Health;
	}
	void TakeDamage(int DamageTaken) {
		this->Health -= DamageTaken;
	}
};

class Arena {
private:
	Creature Player, Opponent;
public:
	void Fighters(Creature newPlayer, Creature newOpponent) {
		this->Player = newPlayer;
		this->Opponent = newOpponent;
	}
	void Fight() {
		while (Player.HealthValue() > 0 && Opponent.HealthValue() > 0) {
			Opponent.TakeDamage(Player.DamageValue());
			Player.TakeDamage(Opponent.DamageValue());
		}
		if (Player.HealthValue() > 0) {
			std::cout << "The player has won";
		}
		else {
			std::cout << "The opponent has won";
		}
	}
};

int main() {

	creatureLevels["Human"] = 10;
	creatureLevels["Wolf"] = 6;
	creatureLevels["Ogre"] = 23;
	Creature Knight;
	Knight.TypeCreature("Human");

	Creature Burek;
	Burek.TypeCreature("Ogre");

	Arena Colosseum;
	Colosseum.Fighters(Knight, Burek);

	Colosseum.Fight();
}
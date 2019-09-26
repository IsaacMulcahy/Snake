#pragma once


class Character
{
public:
	Character() = default;
	virtual ~Character() = default;

	enum CharacterType 
	{
		HUMAN = 1
	};

	int getType() const;

protected:
	CharacterType type = HUMAN;
};
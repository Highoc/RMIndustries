#pragma once
#include <tinyxml2.h>
#include <SFML\Graphics.hpp>


using namespace sf;
namespace TXML = tinyxml2;
class Animation
{
public:
	std::vector<IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying;   // loop ��������� ��������� �� ��������. �������� �������� ������ ������ ����������� ���� ��� � ������������, loop=false
	Sprite sprite;

	Animation()
	{
		currentFrame = 0;
		isPlaying = true;
		flip = false;
		loop = true;
	}

	void tick(float time);
	
};

// ���������� �������� ����������/����� ��� ���������� �� ����� xml, 
// ������� ������ ��� ������ ��������� spritedecomposer (����� ������� ������� �������� ����������)


class AnimationManager
{

public:
	std::string currentAnim;
	std::map <std::string, Animation> animList;

	AnimationManager()
	{}

	~AnimationManager()
	{
		animList.clear();
	}

	//�������� �� ����� XML
	void loadFromXML(std::string fileName, Texture &t);
	

	void set(std::string name);

	void draw(RenderWindow &window, int x = 0, int y = 0);

	void flip(bool b = 1);

	void tick(float time);

	void pause();

	void play();

	void play(std::string name);

	bool isPlaying();

	float getH();

	float getW();

};


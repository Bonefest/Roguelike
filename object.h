//Файл,описывающий структуру живых объектов.
//Создание экземлпяров данных структур поручается EntityManager , который на основе XML файлов генерирует существа.

#define NAME_SIZE 128

struct ColorRGB {
	short red;
	short green;
	short blue;
};
	

//Структура для представления объекта на экране
struct View {
	int posX;
	int posY;
	char model;
	struct ColorRGB color;
};


//Структура,которая описывает все аттрибуты существа
struct Attributes {
	short strength;				//(str)Сила
	short constitution;			//(con)Телосложение
	short stabillity;			//(stb)Устойчивость

	short intellect;			//(int)Интеллект
	short willpower;			//(wlp)Сила воли
	short wisdom;				//(wdm)Мудрость
	short confidence;			//(cnf)Уверенность
	short charisma;				//(chr)Харизма

	short dexterity;			//(dex)Ловкость
	short speed;				//(spd)Скорость
	short flexibility;			//(flx)Гибкость
};

//Структура,которая представляет класс живого объекта.Как и раса,каждый класс имеет свои навыки(ск) и умения(аб).
//К примеру класс лучник имеет навык стрельбы двумя стрелами.
//На возможность выбора класса влияет интеллект (животные не могут брать класс)
struct Class {
	char className[NAME_SIZE];
	//Skill* skills;
	//Abillity* abillities;
};

struct Entity {
	
	char entityName[NAME_SIZE];

	struct View view;
	struct Attributes attributes;

	long long minHealth;
	long long maxHealth;

	short weight;
	short height;

	int level;
	long long experience;


};
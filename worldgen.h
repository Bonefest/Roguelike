//Color struct
typedef struct ColorRGB {
	short red;
	short green;
	short blue;
}ColorRGB;

//Структура для описания региона
typedef struct Region{
	char biom[2];
	int pos[2];
	ColorRGB color;
	//int height;
	//Location* locations;
} Region;

/*
Список возможных биомов:
Луга - meadow
Леса - woods
Степь - steppe
Пустыня - desert
Снега - snows
*/

//Функция для генерирования всех регионов-пустышек
void GenStart(int y_size, int x_size, Region[y_size][x_size]);

//Функция для генерирования одного региона исходя от расстояния до экватора midline и соседних регионов
void GenRegion(int y_size, int x_size, Region[y_size][x_size], int, int, int);

//Функция для запуска кучи других функций
void Generate(int y_size, int x_size, Region[y_size][x_size]);

//Вывод на экран
void PrintWorld(int y_size, int x_size, Region[y_size][x_size]);
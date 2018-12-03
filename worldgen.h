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
	int height;
	//Location* locations;
} Region;

/*
Список возможных биомов:
Луга - meadow
Леса - woods
Степь - steppe
Пустыня - desert
Снега - snows
Вода - water
*/

//Функция для генерирования всех регионов-пустышек
void GenStart(int y_size, int x_size, Region[y_size][x_size]);

//Функция для генерирования одного региона исходя от расстояния до экватора midline и соседних регионов
void GenRegion(int y_size, int x_size, Region[y_size][x_size], int, int, int);

//Функция для запуска кучи других функций
void Generate(int y_size, int x_size, Region[y_size][x_size]);

//Вывод на экран
void PrintWorld(int y_size, int x_size, Region[y_size][x_size]);

//Шаг square
void Square(const int y_size, const int x_size, Region continent[y_size][x_size], int y_pos[4], int x_pos[4], int mask[y_size][x_size]);

//Шаг diamond
void Diamond(const int y_size, const int x_size, Region continent[y_size][x_size], int, int, int, int mask[y_size][x_size]);

//Запуск diamond-square
void DS(const int y_size, const int x_size, Region continent[y_size][x_size]);

//Я затрудняюсь описать предназначение этой функции
void CheckForNegative(int a[4], int b[4], int, int);

//Генерация карты высот
void GenHeight(int y_size, int x_size, Region continent[y_size][x_size]);
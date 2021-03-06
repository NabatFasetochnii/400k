// astrometry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

/*struct tychostar
{
	double tra;
	double tdec;
	double vt;
	double bt;
};*/

struct star //создана структура
{
	int ra;
	int dec;
	short int v;
};




void show(star object) //создаем функцию, которая принимает структуру, как параметр
{
	cout << "ra " << object.ra << endl;
	cout << "dec" << object.dec << endl;
	cout << "v" << object.v << endl;
};

int main()
{
	setlocale(0, "ru");
	int rat;	//прямое восхождение тихо
	int dect;	//склонение тихо
	short int magt;	//звездная величина тихо
	int bminusv;	// разница B и V тихо
	string str;	//строка, в которую будут помещаться данные, чтоб потом можно было брать данные из этой строки и подставлять их в нужный файл для тихо
	string path = "C://Users/User/Desktop/astrometry/Catalogues/ucac2/z/z";	//путь до файла
	int k = 0;	//счетчик для всех звезд
	int starnumb[289];	// массив для номеров последней звезды в каждом файле
	starnumb[0] = 0;	//начинаем с нуля
	//ofstream number("C://Users/User/Desktop/astrometry/Catalogues/ucac2/number.txt");	//считал номера последних звезд
	ifstream ucac("C://Users/User/Desktop/astrometry/Catalogues/ucac2/ucac.txt", ios::binary); //создаем поток для чтения или записи в файл ucac
	double tra;		//для тихо 
	double tdec;	//для тихо 
	double bt;		//для тихо 
	double vt;		//для тихо
	double tmag;	//для тихо
	double tbminusv; // для тихо
	//star buffer;	//буфер обмена для работы с ветором и нужным диапазоном
	int arrNumb[289];

	cout.setf(ios::fixed);  // вывод в фиксированном формате 
	cout.precision(10);      // вывод до 6 знака после точки, включительно

	

	// дорогой дневник могу считать укак в вектор

	vector<star> s;
	star star1;

	try
	{
		while (ucac.read((char*)&star1, sizeof(star1)))
		{
			s.push_back(star1);
		}

		cout << s.size() << endl; // для считывания файла ucac в вектор
	}
	catch (const std::bad_alloc&)
	{
		cout << "oops bad alloc" << endl;
	}

	

	for (int i = 1; i < 289; i++) // перебираем все файлы из укака
	{
		string part = to_string(1000 + i).substr(1, 3);	// идем по файлам
		string result = path + part;	// идем по файлам

		ifstream fs;     // поток для чтения-записи
		fs.open(result, ios::binary);	//открыли файл в бинарном режиме
		if (!(fs.is_open())) 
		{
			cout << "File ucac not find\n";
			cout << "exit";
			cin.get();  //Это если окошко сразу закрывается, задерживаем
			return -1;
		}
		else {
			cout << "ucac. Process began\n";
		}


		while (fs.peek() != EOF)
		{

			fs.read((char*)&star1.ra, 4);
			fs.read((char*)&star1.dec, 4);
			fs.read((char*)&star1.v, 2);

			fs.seekg(34, ios::cur);

			//ucac.write((char*)&star1,sizeof(star1));	// больше не надо, так как записали в файл ucac

			k++;
		}
		//starnumb[i] = k;
		//cout << k;
		//number << k << endl;	//считал номера последних звезд
		fs.close();

	}	//для создания массива номеров послежних звезд в файлах и для считывания звезд в файл, чтоб потом считать его в вектор

	//чтение укак сверху

	//Чтение тихо внизу
	string pathtycho = "C://Users/User/Desktop/astrometry/Catalogues/tyco2/DATA/catalog.dat"; //указали путь к изначальному файлу тихо
	string pathmytycho = "C://Users/User/Desktop/astrometry/Catalogues/tyco2/moytycho.txt"; //указали путь к моему файлу тихо, в который будет запись, но в процессе теперь это стало файл с общими звездами
	ifstream tycho;     // создали поток для чтения-записи изначального тихо
	tycho.open(pathtycho, ios::in); // открыли файл в нужном режиме
	if (!(tycho.is_open()))
	{
		cout << "File not find\n";
		cout << "exit";
		cin.get();  
		return -1;
	}//проверяем открывается файл или нет

	ofstream mytycho;     // создали поток для чтения-записи моего тихо
	mytycho.open(pathmytycho, ios::in); // открыли файл в нужном режиме
	if (!(mytycho.is_open()))
	{
		cout << "File not find\n";
		cout << "exit";
		cin.get();
		return -1;
	}//проверяем открывается файл или нет
	
	
	for (int i = 0; i < 2539913; i++)
	{
		try
		{
		getline(tycho, str);
		if (str.substr(13, 1)=="X") // пропускаем проблемные места в тихо
		{
			continue;
		}
		tra = (stod((str.substr(15, 3) + str.substr(19, 8))) / pow(10, 8)) * 3600000;	//значение для прям восхожд в милисек для укака
		tdec = (stod(str.substr(28, 3) + str.substr(32, 8)) / pow(10, 8)) * 3600000;	//значение для склонен в милисек для укака
		bt = (stod(str.substr(110, 2) + str.substr(113, 3)) / pow(10, 3));
		vt = (stod(str.substr(123, 2) + str.substr(126, 3)) / pow(10, 3));
		rat = tra;	//нужное значение прям восхождения для тихо, чтоб сравнить его с укаком
		dect = tdec;	//нужное значение склонения для тихо, чтоб сравнить его с укаком
		cout << tra << endl;
		cout << tdec << endl;
		cout << rat << endl;
		cout << dect << endl;// проверка рабочести для цикла фор
		if (dect > 194400000) continue;	//если больше 54 градусов то нам не нужна эта звезда. Продолжаем

		//теперь найдем верное значение v для тихо, чтоб можно было сравнивать его с укаком
		tmag = (vt - 0.09*(bt - vt)) * 100;	//перевели в сотые значения для сравнения с укаком
		//cout << tmag << endl;
		magt = tmag;
		//cout << magt << endl;

		//теперь найдем верную разницу B-V
		tbminusv = (0.85*(bt - vt)) * 100;
		//cout << tbminusv << endl;
		bminusv = tbminusv;
		//cout << bminusv << endl;

		int x = ((dect / 3600000) + 90) / (0.5) + 1;
		//cout << x << endl; // получили номер зоны из тихо

		
		// Ниже мы возьмем нужный диапазон значений из текстового файла и обратимся к вектору
		ifstream file("C://Users/User/Desktop/astrometry/Catalogues/ucac2/number.txt"); // считываем текстовый файл с номерами последних звезд в каждой зоне в массив
		arrNumb[0] = 0;
		for (int iNumb = 1; iNumb < 289; iNumb++)
		{
			file >> arrNumb[iNumb];
			//cout << arrNumb[iNumb] << endl;
		}
		
		int a;
		int b;

		a = arrNumb[x - 1];
		b = arrNumb[x];

		// теперь мы выбираем нужный диапазон вектора
		
			for (int vectorindex = a; vectorindex <= b; vectorindex++)	// цикл для прохождения по нужному диапазону в укаке и сравнение одной звезды из тихо с этим диапазоном
			{
				
				//s[vectorindex];
				if (abs(s[vectorindex].ra - rat) < 1000 && abs(s[vectorindex].dec - dect) < 1000 && abs(s[vectorindex].v - magt) < 100)
				{
					mytycho <<i<< " "
						<< rat << " "
						<<dect << " "
						<<magt << " "
						<< vectorindex << " "
						<< s[vectorindex].ra << " "
						<< s[vectorindex].dec << " "
						<< s[vectorindex].v << " "
						<< bminusv << endl;
					s[vectorindex].ra = -10000; // а нам больше одинаковые звезды не нужны!
					break;
				}
				
			}
		
		}
		catch (std::invalid_argument&)
		{
			cout << "oops invalid" << endl;
			continue;
		}
	
	}
	
	tycho.close();
	mytycho.close();

// Сверху подсчитаны общие звезды

// снизу расчет ошибки



cout.setf(ios::fixed);  // вывод в фиксированном формате 
cout.precision(8);      // вывод до 6 знака после точки, включительно

string str;	//строка, в которую будут помещаться данные, чтоб потом можно было брать данные из этой строки и подставлять их в нужный файл
string pathcommons = "C://Users/User/Desktop/astrometry/Commonstars.txt"; //указали путь к файлу общих звезд
ifstream commons;     // создали поток для чтения-записи общих звезд
int numtycho;
int numucac;
int rat;
int dect;
short int vt;
int rau;
int decu;
short int vu;
int BmV;

double suma1 = 0;
double sumd1 = 0;

int arrnumber[24];	//массив для номеров зон по альфа, чтоб они плюсовались в цикле
double arrsuma[24];	//массив для суммирования ошибок альфа
double arrsumd[24];	//массив для суммирования ошибок дельта
for (int i = 0; i < 24; i++)
{
	arrnumber[i] = 0;
	arrsuma[i] = 0;
	arrsumd[i] = 0;
}
int zonenumber;
int zonenumberd;
int zonenumberddop;
int zonenumberm;

int arrnumberd[18];	//массив для номеров зон по дельта, чтоб они плюсовались в цикле
double arrsumad[18];	//массив для суммирования ошибок альфа
double arrsumdd[18];	//массив для суммирования ошибок дельта
//дополнительные массивы
//int arrnumberddop[18];	//массив для номеров зон по дельта, чтоб они плюсовались в цикле
//double arrsumaddop[18];	//массив для суммирования ошибок альфа
//double arrsumdddop[18];	//массив для суммирования ошибок дельта


for (int i = 0; i < 18; i++)
{
	arrnumberd[i] = 0;
	arrsumad[i] = 0;
	arrsumdd[i] = 0;
	//arrnumberddop[i] = 0;
	//arrsumaddop[i] = 0;
	//arrsumdddop[i] = 0;
}

//массивы для блеска
int arrnumberm[17];
double arrsumam[17];
double arrsumdm[17];

for (int i = 0; i < 17; i++)
{
	arrnumberm[i] = 0;
	arrsumam[i] = 0;
	arrsumdm[i] = 0;
}



// основные ошибки
double alpha1;
double delta1;
double alpha2;
double delta2;
double alpha3;
double delta3;
double alpha4;
double delta4;
double alpha5;
double delta5;
double alpha6;
double delta6;

double deltaA;	//ошибка весен равноденст
double deltaD;	//ошибка плоск небес экватора

double alphaALPHA;
double alphaDELTA;

commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

vector<double> csa;	//вектор изначальной ошибки альфа
vector<double> csd;	//вектор изначальной ошибки дельта

//1. Определяем ошибки определения координат, неопределенностей весен равноденствия и плоскости небесного экватора
for (int ci1 = 0; ci1 < 395990; ci1++) // считаем суммы всех дельта алфа и дельта дельта и одновременно заполняем два вектора
{
	//getline(commons, str);
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	alpha1 = rau - rat;
	//arra1[ci1] = alpha1;
	suma1 = suma1 + alpha1;
	csa.push_back(alpha1);
	delta1 = decu - dect;
	csd.push_back(delta1);
	//arrd1[ci1] = delta1;
	sumd1 = sumd1 + delta1;
	//cout << alpha1 << endl;

}
commons.close();
//cout << sum;
deltaA = suma1 / 395991.;	//неопределенность весен равноден
deltaD = sumd1 / 395991.;	// неопрежделенность влоскости небесного экватора

for (int i = 0; i < csa.size(); i++) // вторые дельты (неопределенность поведения началотсчета)
{
	csa[i] = csa[i] - deltaA;
	csd[i] = csd[i] - deltaD;
}

//2 ошибки связанные с кривизной сетки
//2.1 разбиваем по альфа
commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // разбиваем на зоны по часу каждая (15 градусов, переведем в милисек)
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	zonenumber = rat / 54000000;
	arrnumber[zonenumber] = arrnumber[zonenumber] + 1;
	arrsuma[zonenumber] = arrsuma[zonenumber] + csa[i];
	arrsumd[zonenumber] = arrsumd[zonenumber] + csd[i];
}

commons.close();

for (int i = 0; i < 24; i++)	//считаем значения ошибок для всех 24х зон
{
	arrsuma[i] = arrsuma[i] / arrnumber[i];
	arrsumd[i] = arrsumd[i] / arrnumber[i];
}

commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // третьи дельты
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	zonenumber = rat / 54000000;
	csa[i] = csa[i] - arrsuma[zonenumber];
	csd[i] = csd[i] - arrsumd[zonenumber];
}

commons.close();


//2.2 разбиваем по склонению
commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // разбиваем на зоны по 10 градусов каждая
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	zonenumberd = (dect + 324000000) / 36000000;
	arrnumberd[zonenumberd] = arrnumberd[zonenumberd] + 1;
	arrsumad[zonenumberd] = arrsumad[zonenumberd] + csa[i];
	arrsumdd[zonenumberd] = arrsumdd[zonenumberd] + csd[i];
}
commons.close();

for (int i = 0; i < 18; i++) //считаем значения ошибок для всех 18 зон
{
	arrsumad[i] = arrsumad[i] / arrnumberd[i];
	arrsumdd[i] = arrsumdd[i] / arrnumberd[i];
}

commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // четвертые дельты
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	zonenumberd = (dect + 324000000) / 36000000;
	csa[i] = csa[i] - arrsumad[zonenumberd];
	csd[i] = csd[i] - arrsumdd[zonenumberd];
}
commons.close();
/*for (int i = 0; i < 1; i++)
{
	cout << csa[i] << endl;
	cout << csd[i] << endl;
}// Проверяем рабту*/

//3. ошибки блеска
commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // разбиваем на зоны по 1 звездной величине
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	zonenumberm = vu / 100;
	arrnumberm[zonenumberm] = arrnumberm[zonenumberm] + 1;
	arrsumam[zonenumberm] = arrsumam[zonenumberm] + csa[i];
	arrsumdm[zonenumberm] = arrsumdm[zonenumberm] + csd[i];
}
commons.close();

for (int i = 0; i < 17; i++)	//считаем значения ошибок для всех зон от 5 до 16й
{
	//cout << arrsumam[i]<<endl;
	arrsumam[i] = arrsumam[i] / arrnumberm[i];
	arrsumdm[i] = arrsumdm[i] / arrnumberm[i];
}

commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // пятые дельты
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	zonenumberm = vu / 100;
	csa[i] = csa[i] - arrsumam[zonenumberm];
	csd[i] = csd[i] - arrsumdm[zonenumberm];
}
commons.close();


/*for (int i = 0; i < 1; i++)
{
	cout << csa[i] << endl;
	cout << csd[i] << endl;
}  // проверяем работает или нет*/
// 4. ошибка спектрального класса
int zonenumbersp;

int arrnumbersp[7];
double arrsumasp[7];
double arrsumdsp[7];
for (int i = 0; i < 7; i++)
{
	arrnumbersp[i] = 0;
	arrsumasp[i] = 0;
	arrsumdsp[i] = 0;
}


commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // разбиваем на зоны по спектральным классам
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	if (BmV / 100. < -0.31) //O
	{
		zonenumbersp = 0;
	}
	if (-0.31 < BmV / 100. && BmV / 100. <= 0.00) //B
	{
		zonenumbersp = 1;
	}
	if (0.00 < BmV / 100. && BmV / 100. < 0.27) //A
	{
		zonenumbersp = 2;
	}
	if (0.27 < BmV / 100. && BmV / 100. < 0.58) //F
	{
		zonenumbersp = 3;
	}
	if (0.58 < BmV / 100. && BmV / 100. < 0.89) //G
	{
		zonenumbersp = 4;
	}
	if (0.89 < BmV / 100. && BmV / 100. < 1.45) //K
	{
		zonenumbersp = 5;
	}
	if (BmV / 100. > 1.45) //M
	{
		zonenumbersp = 6;
	}
	arrnumbersp[zonenumbersp] = arrnumbersp[zonenumbersp] + 1;
	arrsumasp[zonenumbersp] = arrsumasp[zonenumbersp] + csa[i];
	arrsumdsp[zonenumbersp] = arrsumdsp[zonenumbersp] + csd[i];
}
commons.close();

for (int i = 0; i < 7; i++)	//считаем значения ошибок для всех 7 зон
{
	arrsumasp[i] = arrsumasp[i] / arrnumbersp[i];
	arrsumdsp[i] = arrsumdsp[i] / arrnumbersp[i];
}

commons.open(pathcommons, ios::in); // открыли файл в нужном режиме
if (!(commons.is_open()))
{
	cout << "File not find\n";
	cout << "exit";
	cin.get();
	return -1;
}//проверяем открывается файл или нет

for (int i = 0; i < csa.size(); i++) // последние дельты
{
	commons >> numtycho >> rat >> dect >> vt >> numucac >> rau >> decu >> vu >> BmV;
	if (BmV / 100. < -0.31) //O
	{
		zonenumbersp = 0;
	}
	if (-0.31 < BmV / 100. && BmV / 100. < 0.00) //B
	{
		zonenumbersp = 1;
	}
	if (0.00 < BmV / 100. && BmV / 100. < 0.27) //A
	{
		zonenumbersp = 2;
	}
	if (0.27 < BmV / 100. && BmV / 100. < 0.58) //F
	{
		zonenumbersp = 3;
	}
	if (0.58 < BmV / 100. && BmV / 100. < 0.89) //G
	{
		zonenumbersp = 4;
	}
	if (0.89 < BmV / 100. && BmV / 100. < 1.45) //K
	{
		zonenumbersp = 5;
	}
	if (BmV / 100. > 1.45) //M
	{
		zonenumbersp = 6;
	}
	csa[i] = csa[i] - arrsumasp[zonenumbersp];
	csd[i] = csd[i] - arrsumdsp[zonenumbersp];
}

// окончательные погреншности

double ALPHA = 0;
double DELTA = 0;

for (int i = 0; i < csa.size(); i++)
{
	ALPHA = ALPHA + csa[i] * csa[i];
	DELTA = DELTA + csd[i] * csd[i];
}

cout << sqrt(ALPHA / 395991.) << endl;
cout << sqrt(DELTA / 395991.) << endl;

return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

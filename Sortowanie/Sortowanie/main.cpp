#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const int wielkosctab = 10;

int *tablica = new int[wielkosctab];


void wyswietlanie()
{
	for (int i = 0; i < wielkosctab; i++)
	{
		cout << "Tablica[" << i << "] = " << tablica[i] << endl;
	}
}

void wstawianie()
{
	for (int i = 1; i < wielkosctab; i++)
	{
		int j;
		int schowek = tablica[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (schowek < tablica[j])
				tablica[j + 1] = tablica[j];
			else
				break;
		}
		tablica[j + 1] = schowek;
	}

	wyswietlanie();
}

void przezwybor()
{
	for (int i = 0; i < wielkosctab; i++)
	{
		int min = i;
		for (int j = i + 1; j < wielkosctab; j++)
		{
			if (tablica[j] < tablica[min])
				min = j;
		}

		int schowek = tablica[min];
		tablica[min] = tablica[i];
		tablica[i] = schowek;
	}

	wyswietlanie();
}

void babelki()
{
	for (int i = 0; i < wielkosctab; i++)
	{
		for (int j = 1; j < wielkosctab - i; j++)
		{
			if (tablica[j - 1] > tablica[j])
			{
				swap(tablica[j - 1], tablica[j]);
			}
		}
	}

	wyswietlanie();
}

void shell()
{
	for (int przerwa = wielkosctab / 2; przerwa > 0; przerwa /= 2)
	{
		for (int i = przerwa; i < wielkosctab; i += 1)
		{
			int temp = tablica[i];
			int j;
			for (j = i; j >= przerwa && tablica[j - przerwa] > temp; j -= przerwa)
				tablica[j] = tablica[j - przerwa];

			tablica[j] = temp;
		}
	}

	wyswietlanie();
}

void Quicksort(int lewa, int prawa)
{
	int i, j, srodek;
	
	i = (lewa + prawa) / 2;
	srodek = tablica[i]; 
	tablica[i] = tablica[prawa];
	
	for (j = i = lewa; i < prawa; i++)
		if (tablica[i] < srodek)
		{
			swap(tablica[i], tablica[j]);
			j++;
		}
	
	tablica[prawa] = tablica[j]; 
	tablica[j] = srodek;
	if (lewa < j - 1)  Quicksort(lewa, j - 1);
	if (j + 1 < prawa) Quicksort(j + 1, prawa);
}

void NaprawKopiec(int tablica[], int i, int wielkosctab)
{
	int l = 2 * i, p = 2 * i + 1;
	int wiekszy;
	if (l<wielkosctab&&tablica[l]>tablica[i])
		wiekszy = l;
	else
		wiekszy = i;
	if (p<wielkosctab&&tablica[p]>tablica[wiekszy])
		wiekszy = p;
	if (wiekszy != i)
	{
		int temp = tablica[i];
		tablica[i] = tablica[wiekszy];
		tablica[wiekszy] = temp;
		NaprawKopiec(tablica, wiekszy, wielkosctab);
	}
}
void StworzKopiec(int tablica[], int wielkosctab)
{
	for (int i = (wielkosctab - 1) / 2; i >= 1; i--)
		NaprawKopiec(tablica, i, wielkosctab);
}
void Heapsort(int tablica[], int wielkosctab)
{
	StworzKopiec(tablica, wielkosctab);
	for (int i = wielkosctab - 1; i >= 1; i--)
	{
		int temp = tablica[1];
		tablica[1] = tablica[i];
		tablica[i] = temp;
		NaprawKopiec(tablica, 1, i);
	}
	wyswietlanie();
}

int main()
{

	int wybor;
	do
	{
		cout << endl;
		cout << "Czego pragniesz?" << endl;
		cout << "1. Wyswietl" << endl;
		cout << "2. Posortowac przez wstawianie" << endl;
		cout << "3. Posortowac przez wybor" << endl;
		cout << "4. Posortowac babelkowo" << endl;
		cout << "5. Posortowac algorytmem Shella" << endl;
		cout << "6. Posortowac przez Quicksort" << endl;
		cout << "7. Posortowac przez Heapsort" << endl;
		cout << "8. Koniec" << endl;

		ifstream plik("data.txt");
		int liczba;
		
		for (int i = 0; i < wielkosctab; i++)
			{
				plik >> tablica[i];
			}
	
		cin >> wybor;
		switch (wybor)
		{
		case 1: //wyswietlanie
		{
			cout << endl << "Wyswietlanie:" << endl;
			wyswietlanie();
		break;
		}
			
		case 2: //sortowanie przez wstawianie
		{
			cout << endl << "Sortowanie przez wstawianie:" << endl;
			wstawianie();
		break;
		}

		case 3: //sortowanie przez wybor
		{
			cout << endl << "Sortowanie przez wybor:" << endl;
			przezwybor();
		break;
		}

		case 4: //sortowanie babelkowe
		{
			cout << endl << "Sortowanie babelkowe:" << endl;
			babelki();
		break;
		}
		
		case 5: //sortowanie Shella
		{
			cout << endl << "Sortowanie Shella:" << endl;
			shell();
		break;
		}

		case 6: //sortowanie Quicksort
		{
			cout << endl << "Sortowanie Quicksort:" << endl;
			Quicksort(0, wielkosctab - 1);
			wyswietlanie();
		break;
		}

		case 7: //sortowanie Heapsort
		{
			cout << endl << "Sortowanie Heapsort:" << endl;
			Heapsort(tablica, wielkosctab);
		break;
		}

		case 8: //wyjscie
		{
			return 0;
		break;
		}
		default:
			cout << "Wybierz wlasciwy numer:" << endl;
			cin.clear();
			cin.get();
			}
		}
		while (1);

		delete [] tablica;
		return 0;
}
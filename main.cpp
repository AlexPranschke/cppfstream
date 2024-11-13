#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream> // do obs³ugi plików
using namespace std;

int main(int argc, char** argv) {
	ifstream plik("dane.txt");	// plik Ÿród³owy - input
	ofstream wynik("wynik.txt"); // plik wynikowy - output
	int ilosc_pomiarow = 1;
	if (!plik.is_open()) {
		cout << "Blad dostêpu do pliku dane.txt\n";
		return 1;
	}
	if (!wynik.is_open()) {
		cout << "Blad dostêpu do pliku wynik.txt\n";
		return 2;
	}
	string dane;
	while (getline(plik, dane) && plik.eof() == false) { // funkcja eof() sprawdza czy osi¹gniêto koniec pliku
		// przetwarzanie
		if (dane.find("$GPGGA") != string::npos) { // zwrócone 'npos' oznacza ¿e nie znaleziono ci¹gu
			wynik << "Pomiar " << ilosc_pomiarow++ << endl; // zapis do pliku numeru pomiaru
			wynik << "Czas wykonania pomiaru: ";
			// zapis godziny
			if (dane[7] != 0) {
				wynik << dane[7] << dane[8] << ":";
			}
			wynik << dane[9] << dane[10] << ":"; // minuty
			wynik << dane[11] << dane[12] << "s\n"; // sekundy

			// szerokosc_geo
			wynik << "Szerokosc geograficzna : ";
			int geopos = dane.find(',', 12);

			wynik << dane[geopos + 1] << dane[geopos + 2] << "d "; // stopnie
			wynik << dane[geopos + 3] << dane[geopos + 4] << "' "; // minuty
			string sek = dane.substr(geopos + 6, dane.find(',', geopos + 1) - geopos - 6);
			// substr - zwraca wycinek stringu

			sek = "0." + sek;
			float s = atof(sek.c_str()); // atoi() zamienia const char * na int
			wynik << ((s * 60) - (int)(s * 60) > 0.5 ? (int)(s * 60) + 1 : (int)(s * 60)); // sekundy
			// operator trojargumentowy : (warunek) ? : jesli_prawda : jesli_falsz
			geopos = dane.find(',', geopos + 1) + 1;
			wynik << " " << dane[geopos] << endl; // wyœwietlenie pó³kuli

			wynik << "D³ugosc geograficzna : ";
			geopos = dane.find(',', geopos + 1);
			wynik << dane[geopos + 2] << dane[geopos + 3] << "d "; // stopnie
			wynik << dane[geopos + 4] << dane[geopos + 5] << "' "; // minuty
			sek = dane.substr(geopos + 7, dane.find(',', geopos + 1) - geopos - 7);
			sek = "0." + sek;
			s = atof(sek.c_str()); // atoi() zamienia const char * na int
			wynik << ((s * 60) - (int)(s * 60) > 0.5 ? (int)(s * 60) + 1 : (int)(s * 60)); // sekundy
			geopos = dane.find(',', geopos + 1) + 1;
			wynik << " " << dane[geopos] << endl; // wyœwietlenie pó³kuli

			wynik << "\n";
		}
	}


	return 0;
}


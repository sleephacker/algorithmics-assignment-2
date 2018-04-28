// Hoofdprogramma voor oplossing voor tweede programmeeropdracht Algoritmiek,
// voorjaar 2018: Lettersom
//
// Biedt de gebruiker een menustructuur om
// * een drietal woorden op te geven waarvan het aantal oplossingen
//   moet worden bepaald
// * twee woorden van gelijke lengte op te geven, waarbij complete puzzels
//   met een unieke oplossing worden geconstrueerd
//
// .... (auteurs), .... (datum)

#include <iostream>
#include <cstring>
#include <ctime>  // voor clock() en clock_t
#include "lettersom.h"
using namespace std;

//*************************************************************************

// Vraag de gebruiker om de drie woorden van een lettersom-puzzel, en bepaal
// daarbij het aantal oplossingen.
void doepuzzel() {
	Lettersom *ls1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
					// en weer weg te gooien
	char woord0[maxwoordlengte + 1], woord1[maxwoordlengte + 1], woord2[maxwoordlengte + 1];
	memset(woord0, 0, (maxwoordlengte + 1) * sizeof(char));
	memset(woord1, 0, (maxwoordlengte + 1) * sizeof(char));
	memset(woord2, 0, (maxwoordlengte + 1) * sizeof(char));
	clock_t t1, t2;
	int nroplossingen;

	ls1 = new Lettersom();

	cout << endl;
	cout << "Voer de drie woorden van de puzzel in." << endl;
	cout << "Woord 0: ";
	cin >> woord0;
	cout << "Woord 1: ";
	cin >> woord2;
	cout << "Woord 2: ";
	cin >> woord2;

	cout << "De puzzel is: " << woord0 << " + " << woord1 << " = " << woord2 << endl;

	t1 = clock();

	nroplossingen = ls1->zoekoplossingen(woord0, woord1, woord2);

	t2 = clock();

	cout << endl;
	cout << "De puzzel kent " << nroplossingen << " verschillende oplossing(en)."
		<< endl;
	cout << "Het zoeken van de oplossingen kostte " << (t2 - t1)
		<< " clock ticks, ofwel "
		<< (((double)(t2 - t1)) / CLOCKS_PER_SEC) << " seconden." << endl;

	delete ls1;

}  // doepuzzel

//*************************************************************************

// Vraag de gebruiker om de eerste twee woorden van een lettersom-puzzel,
// en bepaal daarbij het aantal complete puzzels met een unieke oplossing.
// De twee opgegeven woorden moeten even lang zijn.
void construeerpuzzels() {
	Lettersom *ls1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
					// en weer weg te gooien
	char woord0[maxwoordlengte + 1], woord1[maxwoordlengte + 1], woord2[maxwoordlengte + 1];
	clock_t t1, t2;
	int len0, len1,
		nrpuzzels;

	cout << endl;
	cout << "Voer de eerste twee woorden van de puzzel in (even lang)." << endl;
	cout << "Woord 0: ";
	cin >> woord0;
	cout << "Woord 1: ";
	cin >> woord1;

	len0 = strlen(woord0);
	len1 = strlen(woord1);
	if(len0 == len1) {
		ls1 = new Lettersom();

		t1 = clock();

		nrpuzzels = ls1->construeerpuzzels(woord0, woord1);

		t2 = clock();

		cout << endl;
		cout << "We vonden " << nrpuzzels << " puzzels met een unieke oplossing." << endl;
		cout << "Het construeren van de puzzels kostte " << (t2 - t1)
			<< " clock ticks, ofwel "
			<< (((double)(t2 - t1)) / CLOCKS_PER_SEC) << " seconden." << endl;

		delete ls1;
	}
	else  // verkeerde lengtes
	{
		cout << endl;
		cout << "De woorden moeten even lang zijn." << endl;
	}

}  // construeerpuzzels

//*************************************************************************

void hoofdmenu() {
	int keuze;

	do {
		cout << endl;
		cout << "1. Een lettersom-puzzel oplossen" << endl;
		cout << "2. Lettersom-puzzels construeren bij twee gegeven woorden" << endl;
		cout << "3. Stoppen" << endl;
		cout << endl;
		cout << "Maak een keuze: ";
		cin >> keuze;
		switch(keuze) {
			case 1: doepuzzel();
				break;
			case 2: construeerpuzzels();
				break;
			case 3: break;
			default: cout << endl;
				cout << "Voer een goede keuze in!" << endl;
		}

	}
	while(keuze != 3);

}  // hoofdmenu

//*************************************************************************

int main() {
	hoofdmenu();

	return 0;

}

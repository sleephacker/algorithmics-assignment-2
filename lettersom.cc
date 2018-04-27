// Implementatie van klasse Lettersom.

#include <iostream>
#include <cstring>
#include <vector>

#include "lettersom.h"
using namespace std;

// omdat <algorithm> niet toegestaan is
int max(int a, int b) { return a > b ? a : b; }

// decimale optelling
vector<int> operator + (const vector<int> a, const vector<int> b) {
	vector<int> c = vector<int>();
	int carry = 0;
	auto i_a = a.rbegin(), i_b = b.rbegin();
	while(i_a != a.rend() || i_b != b.rend() || carry != 0) {
		int av = (i_a != a.rend() ? *i_a : 0);
		int bv = (i_b != b.rend() ? *i_b : 0);

		int v = av + bv + carry;
		carry = v >= 10 ? 1 : 0;
		c.push_back(v % 10);

		if(i_a != a.rend()) ++i_a;
		if(i_b != b.rend()) ++i_b;
	}
	return c;
}

// stelt de toekenning van een cijfer aan een letter voor
struct letter {
	char letter;
	int cijfer;

	letter(char l, int c) {
		letter = l;
		cijfer = c;
	}
};

// checkt of een gedeeltelijke toekenning van letters klopt
bool SoFarSoGood(char *woord2, vector<int> cijfers0, vector<int> cijfers1, vector<letter> letters) {
	vector<int> cijfers2 = cijfers0 + cijfers1;
	if(cijfers2.size() > max(cijfers0.size(), cijfer1.size()))
		cijfers2.erase(cijfers2.begin());
	int len = strlen(woord2);
	if(len < cijfers0.size())
		return false;
	int i = len - 1;
	for(auto c = cijfers2.rbegin(); c != cijfers2.rend(); ++c, i--) {
		for(auto l = letters.begin(); l != letters.end(); l++)
			if((*l).letter == woord2[i])
				if((*l).cijfer == *c)
					goto next;
				else
					return false;
		// letter zat nog niet in letters, voeg hem toe
		letters.push_back(letter(woord2[i], *c))
	next:
	}
}

//*************************************************************************

Lettersom::Lettersom() {
	// TODO: zonodig implementeren

	cout << endl;
	cout << "De constructor van Lettersom is nog niet ge-implementeerd." << endl;

}  // Lettersom

//*************************************************************************

int Lettersom::zoekoplossingen(char *woord0, char *woord1, char *woord2) {

	int len0 = strlen(woord0);
	int len1 = strlen(woord1);
	int len2 = strlen(woord2);
	if(max(len0, len1) > len2 || max(len0, len1) < (len2 - 1))
		return 0;

	return 0;
}  // zoekoplossingen

//*************************************************************************

int Lettersom::construeerpuzzels(char *woord0, char *woord1) {
	// TODO: implementeren

	cout << endl;
	cout << "De methode construeerpuzzels is nog niet ge-implementeerd." << endl;

	return 0;

}  // construeerpuzzels

//*************************************************************************


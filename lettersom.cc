// Implementatie van klasse Lettersom.

#include <iostream>
#include <cstring>
#include <vector>

#include "lettersom.h"
using namespace std;

// omdat <algorithm> niet toegestaan is
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

Lettersom::Lettersom() {
	// TODO: zonodig implementeren

	cout << endl;
	cout << "De constructor van Lettersom is nog niet ge-implementeerd." << endl;

}  // Lettersom


bool lengtes_kloppen(char *woord0, char *woord1, char *woord2) {
    
    // TODO: hoogstens tien verschillende hoofdletters

    int len0 = strlen(woord0);
	int len1 = strlen(woord1);
	int len2 = strlen(woord2);

	if(max(len0, len1) > len2 || max(len0, len1) < (len2 - 1)) return false;

    // Volgens de opdracht: hoogstens 20 karakters
	if(len0 > 20 || len1 > 20 || len2 > 20) return false;
    
    return true;
}


void voeg_toe_aan_sleutel(string &sleutel, char const *woord, int index) {
    if(index >= 0)
		if(sleutel.find(woord[index]) == string::npos)
			sleutel.push_back(woord[index]);
}

string bepaal_sleutel(char const *woord0, char const *woord1, char const *woord2) {

    string sleutel;
    int i0 = strlen(woord0) - 1; // In 'lengtes_kloppen' rekenen we dit ook al uit
	int i1 = strlen(woord1) - 1; // maar de woorden zijn klein dus maakt dat niet uit.
	int i2 = strlen(woord2) - 1;
    
    while(i0 >= 0 || i1 >= 0 || i2 >= 0) {
        
        voeg_toe_aan_sleutel(sleutel, woord0, i0); 
        voeg_toe_aan_sleutel(sleutel, woord1, i1); 
        voeg_toe_aan_sleutel(sleutel, woord2, i2); 
        i0--;
        i1--;
        i2--;
    }

    return sleutel;
}

int volgend_getal(int toekenning[26], int hoger_dan) {

    // Alle negen getallen niet gebruikt.
    bool gebruikt[9] = {false};

    for(int i = 0; i < 26; i++)
    {
        if(toekenning[i] != -1) gebruikt[toekenning[i]] = true;
    }

    for(int i = hoger_dan + 1; i < 9; i++)
    {
        if(!gebruikt[i]) return i;
    }

    return -1; // Niet gevonden
}

// Update een al toegekend karakter. Zo mogelijk krijgt het
// laatste toegekende karakter een ander getal. Als het laatste karakter
// alle mogelijke getallen al heeft aangenomen, update dan het één na laatste
// karakter. Als het eerste karakter alle mogelijke waardes al heeft aangenomen,
// geef dan false terug.
bool vervang_toegekend(int toekenning[26], string sleutel) {

    int slen = sleutel.length();
    int laatste_idx = 0;

    for(int i = slen - 1; i >= 0; i--) {
         
        int huidige_toekenning = toekenning[sleutel[i] - 'A'];
        
        if(huidige_toekenning == -1) continue;
        
        int volgende_toekenning = volgend_getal(toekenning, huidige_toekenning);
        
        if(volgende_toekenning == -1 && i == 0) {
            return false;
        }
        else if(volgende_toekenning == -1) {
            toekenning[sleutel[i] - 'A'] = -1;
        }
        else {
            toekenning[sleutel[i] - 'A'] = volgende_toekenning;
            return true;
        }
    }
    
    // Bovenstaande loop wordt altijd met een return beëindigd, dus
    // deze regel is onbereikbaar.
	cout << "Kan toegekende karakters niet updaten" << endl;
    throw std::invalid_argument("Kan toegekende karakters niet updaten");
}

bool volgende_toekenning(int toekenning[26], string sleutel, bool geldig) {

    int slen = sleutel.length();

    if(geldig) {

        // Eerste niet toegekend karakter krijgt een getal

        for(int i = 0; i < slen; i++) {
            int toekenning_idx = sleutel[i] - 'A';

            if(toekenning[toekenning_idx] == -1) {
                toekenning[toekenning_idx] = volgend_getal(toekenning, -1);
                return true; // Volgende toekenning gelukt
            }
        }

        // Geen enkel niet toegekend karakter gevonden, probeer een toegekend
        // karakter te vervangen.
        return vervang_toegekend(toekenning, sleutel);
    }
    else return vervang_toegekend(toekenning, sleutel);
}

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
		c.insert(c.begin(), v % 10);

		if(i_a != a.rend()) ++i_a;
		if(i_b != b.rend()) ++i_b;
	}
	return c;
}

// telt hoeveel letters van achteren kloppen (d.w.z. hoeveel er niet definitief niet kloppen)
int letters_goed(char *woord2, vector<int> cijfers2, int toekenning[26]) {

	int tmp_toekenning[26];
	memcpy(tmp_toekenning, toekenning, 26 * sizeof(int));

	int len = strlen(woord2);
	int i = len - 1;
	int aantal = 0;
	for(auto c = cijfers2.rbegin(); c != cijfers2.rend(); ++c, i--, aantal++) {
		if(tmp_toekenning[woord2[i] - 'A'] == -1) {
			for(int j = 0; j < 26; j++)
				if(toekenning[j] == *c) // een andere letter heeft dit getal al
					return aantal;
			tmp_toekenning[woord2[i] - 'A'] = *c; // ken dit getal toe aan deze letter en kijk verder
		}
		else if(tmp_toekenning[woord2[i] - 'A'] != *c)
			return aantal;
	}
	return aantal;
}


// maakt vanaf achteren cijfers van een woord, en stopt bij de eerste letter waar nog geen toekenning voor is
vector<int> geef_cijfers(char *woord, int toekenning[26]) {
	vector<int> cijfers = vector<int>();
	for(int i = strlen(woord) - 1; i >= 0  && toekenning[woord[i] - 'A'] != -1; i--)
		cijfers.insert(cijfers.begin(), toekenning[woord[i] - 'A']);
	return cijfers;
}

bool toekenning_is_oplossing(char *woord0, char *woord1, char *woord2, int toekenning[26], bool &geldig) {
	vector<int> cijfers0 = geef_cijfers(woord0, toekenning);
	vector<int> cijfers1 = geef_cijfers(woord1, toekenning);
	int n = letters_goed(woord2, cijfers0 + cijfers1, toekenning);
	geldig = n >= min(cijfers0.size(), cijfers1.size());
	if(n != strlen(woord2) || cijfers0.size() != strlen(woord0) || cijfers1.size() != strlen(woord1))
		return false;
	else {
		for(int i = 0; i < strlen(woord2); i++)
			if(toekenning[woord2[i] - 'A'] == -1)
				return false;
		return true;
	}
}

int Lettersom::zoekoplossingen(char *woord0, char *woord1, char *woord2) {
	cout << "0" << endl;
    if(!lengtes_kloppen(woord0, woord1, woord2)) return 0;
	cout << "1" << endl;
    // Zie implementatie.md
    string sleutel = bepaal_sleutel(woord0, woord1, woord2);

    int oplossingen = 0;
    int toekenning[26];
    memset(toekenning, -1, 26 * sizeof(int));

    bool geldig = true;

    while(true) {
		cout << "2" << endl;
        bool gelukt = volgende_toekenning(toekenning, sleutel, geldig);

        if(!gelukt) return oplossingen;
		cout << "3" << endl;
        bool is_oplossing = toekenning_is_oplossing(woord0, woord1, woord2, toekenning, geldig);

        if(is_oplossing) oplossingen += 1;
    }
}


int Lettersom::construeerpuzzels(char *woord0, char *woord1) {
	// TODO: implementeren

	cout << endl;
	cout << "De methode construeerpuzzels is nog niet ge-implementeerd." << endl;

	return 0;

}  // construeerpuzzels



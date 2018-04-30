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

/*int woord_naar_getal(char const* woord, int toekenning[26]) {

    int getal = 0;
    int len = strlen(woord);

    for(int i = 0; i < len; i++) {

        int t = toekenning[woord[i] - 'A'];
        if(t == -1) return getal;

        getal *= 10;
        getal += t;
    }

    return getal;
}

int Lettersom::zoekoplossingen(char *woord0, char *woord1, char *woord2) {

    if(!lengtes_kloppen(woord0, woord1, woord2)) return 0;

    // Zie implementatie.md
    string sleutel = bepaal_sleutel(woord0, woord1, woord2);

    int oplossingen = 0;
    int toekenning[26];
    memset(toekenning, -1, 26 * sizeof(int));

    bool geldig = true;

    while(true) {
        bool gelukt = volgende_toekenning(toekenning, sleutel, geldig);

        if(!gelukt) return oplossingen;

        bool is_oplossing = toekenning_is_oplossing(woord0, woord1, woord2, toekenning, geldig);

        if(is_oplossing) oplossingen += 1;
    }
}*/

// de context waarin gezocht wordt naar een volledige toekenning
// bestaat uit o.a. een geldige gedeeltelijke toekenning en een lijst met al gebruikte cijfers
struct zoek_context {
	char *woord0, *woord1, *woord2;
	int toekenning[26];
	bool gebruikt[10];
	string sleutel;

	zoek_context(char *woord0, char *woord1, char *woord2, int toekenning[26], bool gebruikt[10], string sleutel) {
		this->woord0 = woord0;
		this->woord1 = woord1;
		this->woord2 = woord2;
		this->sleutel = sleutel;
		memcpy(this->toekenning, toekenning, 26 * sizeof(int));
		memcpy(this->gebruikt, gebruikt, 10 * sizeof(bool));
	}
};

void print_toekenning(int toekenning[26]) {
	cout << "toekenning:" << endl;
	for(int i = 'A'; i <= 'Z'; i++)
		if(toekenning[i - 'A'] != -1)
			cout << "\t" << (char)i << " = " << toekenning[i - 'A'] << endl;
}

// zoekt naar geldige toekenningen voor de letter in z->sleutel[i]
// indien een geldige toekenning gevonden is maar deze geen oplossing is wordt de functie opnieuw aangeroepen
// geeft het aantal gevonden oplossingen binnen de gegeven zoek_context terug
int zoek_oplossingen_recursief(zoek_context *z, int i) {
	int n = 0;
	bool beginletter = z->sleutel[i] == z->woord0[0] || z->sleutel[i] == z->woord1[0] || z->sleutel[i] == z->woord2[0];
	for(int j = beginletter ? 1 : 0; j < 10; j++) // 0 mag nooit het eerste cijfer ergens van zijn
		if(!z->gebruikt[j]) {
			z->toekenning[z->sleutel[i] - 'A'] = j; // ken dit ongebruikte cijfer toe aan de volgende letter
			bool geldig;
			bool oplossing = toekenning_is_oplossing(z->woord0, z->woord1, z->woord2, z->toekenning, geldig);
			if(oplossing) {
				n++; // deze toekenning leidde tot een oplossing van de puzzel
				print_toekenning(z->toekenning);
			}
			else if(geldig && i < z->sleutel.length() - 1) {
				// de toekenning was geldig maar nog geen oplossing, markeer het cijfer als gebruikt en zoek verder
				z->gebruikt[j] = true;
				n += zoek_oplossingen_recursief(z, i + 1);
				z->gebruikt[j] = false;
			}
			z->toekenning[z->sleutel[i] - 'A'] = -1; // maak de toekenning ongedaan om verder te kunnen zoeken
		}
	return n;
}

int Lettersom::zoekoplossingen(char *woord0, char *woord1, char *woord2) {
	if(!lengtes_kloppen(woord0, woord1, woord2)) return 0;

	string sleutel = bepaal_sleutel(woord0, woord1, woord2);
	int toekenning[26];
	for(int i = 0; i < 26; i++) toekenning[i] = -1;
	bool gebruikt[10];
	for(int i = 0; i < 10; i++) gebruikt[i] = false;

	// initialiseer een zoek_context waarin nog niets is toegekent
	zoek_context *z = new zoek_context(woord0, woord1, woord2, toekenning, gebruikt, sleutel);
	int n = zoek_oplossingen_recursief(z, 0); // begin in deze zoek_context te zoeken bij sleutel[0]
	delete z;
	return n;
}

void bepaal_beschikbare_karakters(
        bool karakter_beschikbaar[26],
        bool vrij_karakter[26],
        char const *woord0,
        char const *woord1,
        int min,
        int max) {

    // Unieke karakters
    string sleutel = bepaal_sleutel(woord0, woord1, "");
    
    // Er zijn maximaal 10 verschillende karakters nodig. Een deel
    // van deze karakters wordt al bepaald door de karakters in woord0, woord1.
    // De rest kunnen we vrij kiezen, deze kiezen we simpelweg als de eerste
    // karakters in het alfabet die nog vrij zijn.
    int vrije_karakters = 10 - sleutel.length();

    // Bepaal welke karakters gebruikt worden voor het derde woord.
    /*for(int i = 0; i < 26; i++) {

        if(sleutel.find(i + 'A') != string::npos) karakter_beschikbaar[i] = true;
        else if(vrij_karakter > 0) {
            karakter_beschikbaar[i] = true;
            vrij_karakter [i] = true;
            vrije_karakters -= 1;
        }
    }*/
	for(int i = 0; i < sleutel.length(); i++)
		karakter_beschikbaar[sleutel[i] - 'A'] = true;
	for(int i = 0, n = 0; n < vrije_karakters; i++)
		if(!karakter_beschikbaar[i]) {
			karakter_beschikbaar[i] = true;
			vrij_karakter[i] = true;
			n++;
		}
}

// Na afloop is volgende gevuld op zo'n manier dat, om te weten te komen
// welk beschikbare karakter na het beschikbare karakter 'C' komt, 'volgende'
// geindexeerd kan worden volgende['C' - 'A']. 
// Het beschikbare karakter na 'C' is dan dus volgende['C' - 'A'] + 'A'.
// karakter_beschikbaar geeft aan welke karakters in het alfabet beschikbaar zijn.
void construeer_volgende_tabel(bool karakter_beschikbaar[26], int volgende[26], int &eerste_kar) {

    for(eerste_kar = 0; !karakter_beschikbaar[eerste_kar]; eerste_kar++);
    
    int vorige = eerste_kar;

    for(int i = 25; i >= 0; i--) {

        if(karakter_beschikbaar[i]) {
            volgende[i] = vorige;
            vorige = i;
        }
    }
}

// Geef terug of er een volgend woord is gevonden, of dat dit niet
// is gelukt.
bool volgend_woord(char *derde_woord, int volgende[26], int max) {

	char kar = derde_woord[0];
    char volgend_kar = volgende[kar - 'A'] + 'A';
    derde_woord[0] = volgend_kar;

    if(volgend_kar > kar) return true;
    else if(volgend_kar < kar && max == 1) return false;
    else return volgend_woord(derde_woord + 1, volgende, max - 1);
}

// Bepaal of de vrije karakters in een oplopende volgorde staan.
bool vrije_karakters_goede_volgorde(char *derde_woord,  bool vrij_karakter[26]) {

    /*int vorige = -1;

    for(int i = 0; i < 26; i++) {
        if(vrij_karakter[i]) {

            if(vorige != -1 && vorige > i) return false;
            
            vorige = i;
        }
    }

    return true;*/

	int vorige = -1;
	for(int i = 0; i < strlen(derde_woord); i++)
		if(vrij_karakter[derde_woord[i] - 'A']) {
			if(derde_woord[i] < vorige)
				return false;
			vorige = derde_woord[i];
		}
	return true;
}

int zoek_die_shit_snel(zoek_context *z, int i) {
	int n = 0;
	bool beginletter = z->sleutel[i] == z->woord0[0] || z->sleutel[i] == z->woord1[0] || z->sleutel[i] == z->woord2[0];
	for(int j = beginletter ? 1 : 0; j < 10; j++)
		if(!z->gebruikt[j]) {
			z->toekenning[z->sleutel[i] - 'A'] = j;
			bool geldig;
			bool biem = toekenning_is_oplossing(z->woord0, z->woord1, z->woord2, z->toekenning, geldig);
			if(biem)
				n++;
			else if(geldig && i < z->sleutel.length() - 1) {
				z->gebruikt[j] = true;
				n += zoek_die_shit_snel(z, i + 1);
				z->gebruikt[j] = false;
			}
			if(n > 1) return n;
			z->toekenning[z->sleutel[i] - 'A'] = -1;
		}
	return n;
}

bool unieke_oplossing(char *woord0, char *woord1, char *woord2) {
	if(!lengtes_kloppen(woord0, woord1, woord2)) return 0;

	string sleutel = bepaal_sleutel(woord0, woord1, woord2);
	int toekenning[26];
	for(int i = 0; i < 26; i++) toekenning[i] = -1;
	bool gebruikt[10];
	for(int i = 0; i < 10; i++) gebruikt[i] = false;

	zoek_context *z = new zoek_context(woord0, woord1, woord2, toekenning, gebruikt, sleutel);
	int n = zoek_die_shit_snel(z, 0);
	delete z;
	return n == 1;
}


int Lettersom::construeerpuzzels(char *woord0, char *woord1) {
	cout << "1" << endl;
    // Minimale groote van het derde woord
    int min = max(strlen(woord0), strlen(woord1));
    // Maximale grootte
    int max = min + 1;

    bool karakter_beschikbaar[26] = { false };

    // De karakters die worden toegevoegd aan het spel.
    // Deze staan niet in woord0 en woord1.
    bool vrij_karakter[26] = { false };

    bepaal_beschikbare_karakters(karakter_beschikbaar,
            vrij_karakter, woord0, woord1, min, max);

    int volgende[26];
    int eerste_kar;
    construeer_volgende_tabel(karakter_beschikbaar, volgende, eerste_kar);
	eerste_kar += 'A';
	cout << "eerste_kar: " << (char)eerste_kar << "(" << eerste_kar << ")" << endl;
	for(int i = 0; i < 26; i++)
		cout << i << " -> " << volgende[i] << endl;

	char derde_woord[max + 1];// = { '\0' };
    memset(derde_woord, eerste_kar, min * sizeof(char));
	derde_woord[max + 1] = 0;
	cout << "derde_woord: " << derde_woord << endl;

    // We gaan nu alle mogelijke derde woorden genereren
    // met de beschikbare karakters.
    // Stel de beschikbare karakters zijn 'a', 'k', 'g' en dat
    // het woord tussen 3 en 4 karakters lang moet zijn, dan gaat dit als volgt:
    // aaa - kaa - gaa - aka - kka - gka - aga - .....
    // Er wordt als het ware geteld, waarbij er niet rechts maar juist links
    // telkens het volgende karakter wordt genomen.

    int oplossingen = 0;
	int woorden = 0;
	int goede_woorden = 0;
    do {
		if((woorden++ % 1000) == 0) {
			cout << woorden << " mogelijkheden bekeken." << endl;
			cout << goede_woorden << " keer naar een unieke oplossing gezocht." << endl;
			cout << oplossingen << " oplossingen gevonden." << endl;
		}
		//cout << derde_woord << endl;
        // Wordt alleen als een oplossing gezien als de vrije karakters
        // in een oplopende volgorde staan. Zie 'Het is de bedoeling dat...'
        // in de opdracht.
        if(!vrije_karakters_goede_volgorde(derde_woord, vrij_karakter)) continue;
		goede_woorden++;
        if(unieke_oplossing(woord0, woord1, derde_woord) == 1) oplossingen++;
    } while(volgend_woord(derde_woord, volgende, max));
    
    return oplossingen;
}



// Implementatie van klasse Lettersom.

#include <iostream>
#include <cstring>
#include <vector>

#include "lettersom.h"
using namespace std;

// omdat <algorithm> niet toegestaan is
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

Lettersom::Lettersom() {}

bool is_hoofdletter(char c) {

    return c >= 65 && c <= 90;
}

bool geldig_woord(char const *w) {

    int len = strlen(w);

    if(len == 0) return false;
    for(int i = 0; i < len; i++) if(!is_hoofdletter(w[i])) return false;

    return true;
}

bool lengtes_kloppen(char const *woord0, char const *woord1, char const *woord2) {
    
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

void print_getal(
        int toekenning[26],
        const char *woord0) {

    for(int i = 0; i < (int)strlen(woord0); i++) {

        int cijfer = toekenning[woord0[i] - 'A'];

        if(cijfer == -1) cout << '_';
        else cout << cijfer;
    }

}


void print_toekenning(
        int toekenning[26], 
        const char *woord0, 
        const char *woord1,
        const char *woord2) {
    
    cout << "=============================================================" << endl;

    string sleutel = bepaal_sleutel(woord0, woord1, woord2);

    for(int i = 0; i < (int)sleutel.length(); i++) {
        cout << sleutel[i] << ":";
        cout << toekenning[sleutel[i] - 'A'] << ", ";
    }

    cout << endl;

    print_getal(toekenning, woord0);
    cout << " + ";
    print_getal(toekenning, woord1);
    cout << " = ";
    print_getal(toekenning, woord2);
    cout << endl;
}


int volgend_getal(int toekenning[26], int hoger_dan) {

    // Alle tien getallen niet gebruikt.
    bool gebruikt[10] = {false};

    for(int i = 0; i < 26; i++)
    {
        if(toekenning[i] != -1) gebruikt[toekenning[i]] = true;
    }

    for(int i = hoger_dan + 1; i <= 9; i++)
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
int letters_goed(char const *woord2, vector<int> cijfers2, int toekenning[26]) {

	int tmp_toekenning[26];
	memcpy(tmp_toekenning, toekenning, 26 * sizeof(int));

	int len = strlen(woord2);
	int i = len - 1;
	int aantal = 0;
	for(auto c = cijfers2.rbegin(); c != cijfers2.rend(), i >= 0; ++c, i--, aantal++) {
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


// maakt vanaf achteren cijfers van een woord, en stopt
// bij de eerste letter waar nog geen toekenning voor is
vector<int> geef_cijfers(char const *woord, int toekenning[26]) {
	vector<int> cijfers = vector<int>();
	for(int i = strlen(woord) - 1; i >= 0  && toekenning[woord[i] - 'A'] != -1; i--)
		cijfers.insert(cijfers.begin(), toekenning[woord[i] - 'A']);
	return cijfers;
}

bool toekenning_is_oplossing(
        char const *woord0,
        char const *woord1,
        char const *woord2, 
        int len0,
        int len1,
        int len2,
        int toekenning[26],
        bool &geldig) {

    bool oplossing = true;
    int temp_toekenning[26];
    memcpy(temp_toekenning, toekenning, 26 * sizeof(int));

    int i0 = len0 - 1,  i1 = len1 - 1, i2 = len2 - 1;
    int carry = 0;

    for(;i2 >= 0; i0--, i1--, i2--) {

        int getal0 = i0 < 0 ? 0 : temp_toekenning[woord0[i0] - 'A'];
        int getal1 = i1 < 0 ? 0 : temp_toekenning[woord1[i1] - 'A'];

        if(getal0 == -1 || getal1 == -1) {
            
            geldig = true;
            return false;
        }

        int sum = getal0 + getal1 + carry;
        int kar2 = woord2[i2] - 'A';
        int getal2 = sum % 10;

        //cout << getal0 << "+" << getal1 << "+" << carry << "=" << sum << endl;

        carry = sum >= 10;

        if(temp_toekenning[kar2] == -1) {
            
            temp_toekenning[kar2] = getal2;
            oplossing = false; // Incompleet, dus geen oplossing
        }
        else if(temp_toekenning[kar2] != getal2) return geldig = false;
    }

    // Een 'carry' over de rand maakt de oplossing niet
    // definitief ongeldig?
    geldig = true;

    // Maar zorgt er wel voor dat de oplossing incompleet is.
    oplossing = oplossing && carry == 0;

    // Bekijk verder de voorloopnullen..
    bool voorloop0 = temp_toekenning[woord0[0] - 'A'] == 0;
    bool voorloop1 = temp_toekenning[woord1[0] - 'A'] == 0;
    bool voorloop2 = temp_toekenning[woord2[0] - 'A'] == 0;

    return oplossing && !voorloop0 && !voorloop1 && !voorloop2;
}

int woord_naar_getal(char const* woord, int toekenning[26]) {

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

// 'stop' dan wordt er gestopt als er meer dan één oplossing wordt gevonden.
// De mogelijke resultaten zijn in dat geval dus 0, 1, 2
int Lettersom::zoekoplossingen(char const *woord0,
        char const *woord1,
        char const *woord2,
        bool stop) {

    if(!lengtes_kloppen(woord0, woord1, woord2)) return 0;

    if(!geldig_woord(woord0)
            || !geldig_woord(woord1)
            || !geldig_woord(woord2)) {

        cout << "De ingevoerde woorden zijn ongeldig.. heeft u enkel hoofdletters gebruikt?" << endl;
        return 0;
    }

    // Zie implementatie.md
    string sleutel = bepaal_sleutel(woord0, woord1, woord2);
    int len0 = strlen(woord0), len1 = strlen(woord1), len2 = strlen(woord2);

    int oplossingen = 0;
    int toekenning[26];
    memset(toekenning, -1, 26 * sizeof(int));

    bool geldig = true;

    while(true) {
        bool gelukt = volgende_toekenning(toekenning, sleutel, geldig);


        if(!gelukt) return oplossingen;

        bool is_oplossing = toekenning_is_oplossing(woord0, woord1, woord2, len0, len1, len2, toekenning, geldig);

        if(is_oplossing) {
            print_toekenning(toekenning, woord0, woord1, woord2);
            oplossingen += 1;

            if(stop && oplossingen > 1) return oplossingen;
        }
    }
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
    
    cout << "Sleutel is " << sleutel << endl;

    // Wat is het maximaal aantal vrije karakters? Stel dat de resulterende som
    // geen enkel cijfer bevat dat al is toegekend is aan sleutel, dan hebben we
    // even veel vrije karakters nodig als dat er cijfers in het resultaat staan.
    // Aangezien het resultaat maximaal lengte 'max' heeft, is dit het mogelijk
    // aantal vrije karakters.
    int vrije_karakters = max;

    cout << "Aantal vrije karakters is " << vrije_karakters << endl;

    // Bepaal welke karakters al gebruikt worden voor het derde woord.
	for(int i = 0; i < (int)sleutel.length(); i++)
		karakter_beschikbaar[sleutel[i] - 'A'] = true;

    int i = 0;
    while(vrije_karakters > 0) {

        if(!karakter_beschikbaar[i]) {
            karakter_beschikbaar[i] = true;
            vrij_karakter[i] = true;
            vrije_karakters -= 1;
        }

        i += 1;
    }
}

// Na afloop is volgende gevuld op zo'n manier dat, om te weten te komen
// welk beschikbare karakter na het beschikbare karakter 'C' komt, 'volgende'
// geindexeerd kan worden volgende['C' - 'A']. 
// Het beschikbare karakter na 'C' is dan dus volgende['C' - 'A'] + 'A'.
// karakter_beschikbaar geeft aan welke karakters in het alfabet beschikbaar zijn.
void construeer_volgende_tabel(bool karakter_beschikbaar[26], int volgende[26], int &eerste_kar) {
    memset(volgende, -1, sizeof(int)*26);

    for(eerste_kar = 0; !karakter_beschikbaar[eerste_kar]; eerste_kar++);
    
    cout << eerste_kar << endl;
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
bool volgend_woord(char *derde_woord, int eerste_kar, int volgende[26], int max) {

    int len = strlen(derde_woord);

    for(int i = 0; i < len; i++) {

        char kar = derde_woord[i];

        // Het laatste karakter 'wijst' naar het eerste karakter
        derde_woord[i] = volgende[kar - 'A'] + 'A';

        if(derde_woord[i] > kar) {
            return true;
        }
    }

    // Door de loop heen, alles gereset naar het eerste karakter.
    // Heeft het woord al de maximale lengte?
    // Zo niet, betrek een extra karakter erbij
    if(len == max) return false;
    
    derde_woord[len] = eerste_kar;
    return true;
}

// Bepaal of de vrije karakters in een oplopende volgorde staan.
// Stel dat A,B,C vrije karakters zijn
// Dan moeten ABC en ACB niet dubbel geteld worden.
// Verder moeten ABB en ACC ook niet dubbel geteld worden.
// Hiervoor zorgen we door te checken dat:
// * De vrije karakters in een vaste volgorde staan
// * Er tussen de vrije karakters geen vrije karakters worden overgeslagen
bool vrije_karakters_goede_volgorde(char const *derde_woord, bool vrij_karakter[26]) {

	int huidig_vrij_karakter = -1;

	for(int i = 0; i < (int)strlen(derde_woord); i++) {

        int kar = derde_woord[i] - 'A';

		if(vrij_karakter[kar]) {

		    if(kar == huidig_vrij_karakter) continue;
            else if(kar < huidig_vrij_karakter) return false;
            else {

                // Zoek volgend vrij karakter
                for(huidig_vrij_karakter++;
                        !vrij_karakter[huidig_vrij_karakter];
                        huidig_vrij_karakter++);

                if(kar == huidig_vrij_karakter) continue;
                else return false;
            }
		}
	}

	return true;
}

int Lettersom::construeerpuzzels(char const *woord0, char const *woord1) {

    if(!geldig_woord(woord0) || !geldig_woord(woord1)) {
        cout << "De ingevoerde woorden zijn ongeldig.. heeft u alleen hoofdletters gebruikt?" << endl;
        return 0;
    }

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

	for(int i = 0; i < 26; i++) 
	    if(karakter_beschikbaar[i]) cout << (char)(i + 'A') << " is beschikbaar" << endl;

	int volgende[26];
	int eerste_kar;
	construeer_volgende_tabel(karakter_beschikbaar, volgende, eerste_kar);
	eerste_kar += 'A';

	cout << "eerste_kar: " << (char)eerste_kar << "(" << eerste_kar << ")" << endl;
	for(int i = 0; i < 26; i++)
		cout << (char)(i + 'A') << " -> " << (char)(volgende[i] + 'A') << endl;

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
	do {
		if(++woorden > 200) return 0;
			//cout << woorden << " woorden bekeken, " << oplossingen << " oplossingen gevonden." << endl;

		// Wordt alleen als een oplossing gezien als de vrije karakters
		// in een oplopende volgorde staan. Zie 'Het is de bedoeling dat...'
		// in de opdracht.
		if(!vrije_karakters_goede_volgorde(derde_woord, vrij_karakter)) continue;

		if(zoekoplossingen(woord0, woord1, derde_woord, true) == 1) {
		    
		    cout << derde_woord << " is een oplossing" << endl;
		    oplossingen++;
		}

    } while(volgend_woord(derde_woord, eerste_kar, volgende, max));
    
    return oplossingen;
}



class Lettersom {
public:
	Lettersom();

	int zoekoplossingen(char const *nwwoord0, char const *nwwoord1, char const *nwwoord2, bool stop = false);
	int construeerpuzzels(char const *nwwoord0, char const *nwwoord1);
};

#define LettersomHVar
#include "./lettersom.cc"

#ifndef __CYGWIN__
#include <assert.h>
#else
void assert(bool condition) {
	if(condition)
		cout << "Assert succeded." << endl;
	else
		cout << "Assert failed." << endl;
}
#endif

void bepaal_sleutel_test() {

    string sleutel = bepaal_sleutel("SINT", "PIET", "FEEST");
    assert(sleutel == "TNESIP");
	cout << sleutel << endl;

    sleutel = bepaal_sleutel("AAP", "BEER", "BUREAU");
    assert(sleutel == "PRUAEB");
}

void volgend_getal_test() {
    int toekenning[26];
    memset(toekenning, -1, 26 * sizeof(int));
    
    toekenning[5] = 0;
    toekenning[8] = 2;
    toekenning[9] = 3;

    int v = volgend_getal(toekenning, -1);
    assert(v == 1);
    v = volgend_getal(toekenning, 2);
    assert(v == 4);
}

void volgende_toekenning_test() {

    int toekenning[26];
    memset(toekenning, -1, 26 * sizeof(int));
   
    string sleutel = "SUPER";
    toekenning['S' - 'A'] = 5;
    toekenning['U' - 'A'] = 9;
    
    //print_toekenning(toekenning, sleutel);
    //volgende_toekenning(toekenning, sleutel, true);
    //print_toekenning(toekenning, sleutel);

    for(int i = 0; i < 6; i++) {
    //    volgende_toekenning(toekenning, sleutel, false);
        //print_toekenning(toekenning, sleutel);
    }

    sleutel = "DETAOSIHW";
    memset(toekenning, -1, 26 * sizeof(int));
    toekenning['D' - 'A'] = 8;
    toekenning['E' - 'A'] = 7;
    toekenning['T' - 'A'] = 5;
    toekenning['A' - 'A'] = 0;
    toekenning['O' - 'A'] = 3;
    toekenning['S' - 'A'] = 4;
    toekenning['I' - 'A'] = 2;
    toekenning['H' - 'A'] = 6;
    toekenning['W' - 'A'] = 1;
   
    volgende_toekenning(toekenning, sleutel, true);
   // print_toekenning(toekenning, sleutel);


}

void bepaal_beschikbare_karakters_test() {

    // Beschikbaar
    bool kb[26] = { false };
    bool vk[26] = { false };

    bepaal_beschikbare_karakters(kb, vk,"AKRF", "BCC", 4, 5);

    assert(kb['A' - 'A']);
    assert(kb['B' - 'A']);
    assert(kb['C' - 'A']);

    // Vier vrije karakters
    assert(kb['D' - 'A']);
    assert(kb['E' - 'A']);
    assert(kb['F' - 'A']);
    assert(kb['G' - 'A']);

    assert(kb['K' - 'A']);
    assert(kb['R' - 'A']);
    assert(kb['F' - 'A']);
}

void construeer_volgende_tabel_test() {

    bool karakter_beschikbaar[26] = { false };
    int volgende[26];

    karakter_beschikbaar['D' - 'A'] = true;
    karakter_beschikbaar['K' - 'A'] = true;

    int eerste_kar;

    construeer_volgende_tabel(karakter_beschikbaar, volgende, eerste_kar);
    
    assert(eerste_kar == 'D' - 'A');
    assert(volgende['K' - 'A'] == 'D' - 'A');
    assert(volgende['D' - 'A'] == 'K' - 'A');
}

void zoek_oplossingen_test() {

        Lettersom l;

        cout << "SINT + PIET = FEEST" << endl;
        cout << l.zoekoplossingen("SINT", "PIET", "FEEST")  << " oplossingen" << endl;

        cout << "SINT + PIET = RUZIE" << endl;
        cout << l.zoekoplossingen("SINT", "PIET", "RUZIE")  << " oplossingen" << endl;

        cout << "HEAD +  TOE = WAIST" << endl;
        cout << l.zoekoplossingen("HEAD", "TOE", "WAIST")  << " oplossingen" << endl;

        cout << "ELF +  ELF = FEE" << endl;
        cout << l.zoekoplossingen("ELF", "ELF", "FEE")  << " oplossingen" << endl;

        cout << "ELF + ELF = AFAB" << endl;
        cout << l.zoekoplossingen("ELF", "ELF", "AFAB")  << " oplossingen" << endl;
}

bool toekenning_is_oplossing_len(
        char const *woord0,
        char const *woord1,
        char const *woord2, 
        int toekenning[26],
        bool &geldig) {

    return toekenning_is_oplossing(woord0,
            woord1,
            woord2,
            strlen(woord0),
            strlen(woord1),
            strlen(woord2),
            toekenning,
            geldig);
}

void toekenning_is_oplossing_test() {
	int toekenning[26];
	bool geldig;

	char woord0[5] = "SINT";
	char woord1[5] = "PIET";
	char woord2[6] = "RUZIE";

	for(int i = 0; i < 26; i++)
		toekenning[i] = -1;

	toekenning['E' - 'A'] = 4;
	toekenning['I' - 'A'] = 9;
	toekenning['N' - 'A'] = 5;
	toekenning['P' - 'A'] = 6;
	toekenning['R' - 'A'] = 1;
	toekenning['S' - 'A'] = 3;
	toekenning['T' - 'A'] = 2;
	toekenning['U' - 'A'] = 0;
	toekenning['Z' - 'A'] = 8;
	assert(toekenning_is_oplossing_len(woord0, woord1, woord2, toekenning, geldig));
	assert(geldig);

	toekenning['E' - 'A'] = 4;
	toekenning['I' - 'A'] = 9;
	toekenning['N' - 'A'] = 5;
	toekenning['P' - 'A'] = 3;
	toekenning['R' - 'A'] = 1;
	toekenning['S' - 'A'] = 6;
	toekenning['T' - 'A'] = 2;
	toekenning['U' - 'A'] = 0;
	toekenning['Z' - 'A'] = 8;
	assert(toekenning_is_oplossing_len(woord0, woord1, woord2, toekenning, geldig));
	assert(geldig);

	toekenning['E' - 'A'] = 6;
	toekenning['I' - 'A'] = 4;
	toekenning['N' - 'A'] = 8;
	toekenning['P' - 'A'] = 7;
	toekenning['R' - 'A'] = 1;
	toekenning['S' - 'A'] = 5;
	toekenning['T' - 'A'] = 3;
	toekenning['U' - 'A'] = 2;
	toekenning['Z' - 'A'] = 9;
	assert(toekenning_is_oplossing_len(woord0, woord1, woord2, toekenning, geldig));
	assert(geldig);

	toekenning['E' - 'A'] = 6;
	toekenning['I' - 'A'] = 4;
	toekenning['N' - 'A'] = 8;
	toekenning['P' - 'A'] = 5;
	toekenning['R' - 'A'] = 1;
	toekenning['S' - 'A'] = 7;
	toekenning['T' - 'A'] = 3;
	toekenning['U' - 'A'] = 2;
	toekenning['Z' - 'A'] = 9;
	assert(toekenning_is_oplossing_len(woord0, woord1, woord2, toekenning, geldig));
	assert(geldig);

	for(int i = 0; i < 26; i++)
		toekenning[i] = -1;
	toekenning['E' - 'A'] = 5;
	toekenning['T' - 'A'] = 3;
	assert(!toekenning_is_oplossing_len(woord0, woord1, woord2, toekenning, geldig));
	assert(!geldig);

	for(int i = 0; i < 26; i++)
		toekenning[i] = -1;

	toekenning['E' - 'A'] = 2;
	toekenning['T' - 'A'] = 6;
	assert(!toekenning_is_oplossing_len(woord0, woord1, woord2, toekenning, geldig));
	assert(geldig);

    for(int i = 0; i < 26; i++)
		toekenning[i] = -1;
    
    toekenning['F' - 'A'] = 3;
    toekenning['E' - 'A'] = 6;
    toekenning['L' - 'A'] = 8;

    assert(!toekenning_is_oplossing_len("ELF", "ELF", "FEE", toekenning, geldig));
	assert(geldig);

    for(int i = 0; i < 26; i++)
		toekenning[i] = -1;
    
    toekenning['F' - 'A'] = 6;
    toekenning['B' - 'A'] = 2;
    toekenning['L' - 'A'] = 0;
    toekenning['A' - 'A'] = 1;
    toekenning['E' - 'A'] = 8;

    assert(toekenning_is_oplossing_len("ELF", "ELF", "AFAB", toekenning, geldig));

    for(int i = 0; i < 26; i++)
		toekenning[i] = -1;
    
    toekenning['F' - 'A'] = 8;
    toekenning['B' - 'A'] = 6;
    toekenning['L' - 'A'] = 0;
    toekenning['A' - 'A'] = 1;
    toekenning['E' - 'A'] = 9;

    assert(toekenning_is_oplossing_len("ELF", "ELF", "AFAB", toekenning, geldig));

    for(int i = 0; i < 26; i++)
		toekenning[i] = -1;
    
    toekenning['F' - 'A'] = 6;
    toekenning['B' - 'A'] = 2;
    toekenning['L' - 'A'] = 0;
    toekenning['A' - 'A'] = -1;
    toekenning['E' - 'A'] = -1;

    assert(!toekenning_is_oplossing_len("ELF", "ELF", "AFAB", toekenning, geldig));
    assert(geldig);
}


void vrije_karakters_goede_volgorde_test() {

    bool vrije_karakters[26] = { false };
    
    char const *derde_woord = "KRADCC";
    
    vrije_karakters['A' - 'A'] = true;
    vrije_karakters['B' - 'A'] = true;
    vrije_karakters['C' - 'A'] = true;

    bool goed = vrije_karakters_goede_volgorde(derde_woord, vrije_karakters);

    assert(!goed);

    vrije_karakters['B' - 'A'] = false;

    goed = vrije_karakters_goede_volgorde(derde_woord, vrije_karakters);

    assert(goed);
    
    vrije_karakters['A' - 'A'] = false;
    vrije_karakters['C' - 'A'] = false;

    goed = vrije_karakters_goede_volgorde(derde_woord, vrije_karakters);

    assert(goed);
}

int main() {
    bepaal_sleutel_test();
    volgend_getal_test();
    volgende_toekenning_test();
    bepaal_beschikbare_karakters_test();
    zoek_oplossingen_test();
    construeer_volgende_tabel_test();
    vrije_karakters_goede_volgorde_test();
    toekenning_is_oplossing_test();

    return 0;
}

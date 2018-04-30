class Lettersom {
public:
	Lettersom();

	int zoekoplossingen(char const *nwwoord0, char const *nwwoord1, char const *nwwoord2);
	int construeerpuzzels(char *nwwoord0, char *nwwoord1);
};

#define LettersomHVar
#include "./lettersom.cc"
#include <assert.h>

void bepaal_sleutel_test() {

    string sleutel = bepaal_sleutel("SINT", "PIET", "FEEST");
    assert(sleutel == "TNESIPF");

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

}

int main() {
    //bepaal_sleutel_test();
    //volgend_getal_test();
    //volgende_toekenning_test();
    //bepaal_beschikbare_karakters_test();
    zoek_oplossingen_test();
    //construeer_volgende_tabel_test();

    return 0;
}

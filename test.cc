class Lettersom {
public:
	Lettersom();

	int zoekoplossingen(char *nwwoord0, char *nwwoord1, char *nwwoord2);
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

void print_toekenning(int toekenning[26], string sleutel) {
    
    for(int i = 0; i < sleutel.length(); i++) {
        cout << toekenning[sleutel[i] - 'A'] << ",";
    }

    cout << endl;
}

void volgende_toekenning_test() {

    int toekenning[26];
    memset(toekenning, -1, 26 * sizeof(int));
   
    string sleutel = "SUPER";
    toekenning['S' - 'A'] = 5;
    toekenning['U' - 'A'] = 9;
    
    print_toekenning(toekenning, sleutel);
    volgende_toekenning(toekenning, sleutel, true);
    print_toekenning(toekenning, sleutel);

    for(int i = 0; i < 6; i++) {
        volgende_toekenning(toekenning, sleutel, false);
        print_toekenning(toekenning, sleutel);
    }
}

int main() {
    bepaal_sleutel_test();
    volgend_getal_test();
    volgende_toekenning_test();

    return 0;
}

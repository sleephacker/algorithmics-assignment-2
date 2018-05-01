// Definitie van klasse Lettersom.

#ifndef LettersomHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define LettersomHVar  // wordt ge-include 

const int aantalwoorden = 3;
const int maxwoordlengte = 20;

class Lettersom {
public:
	// Default constructor
	Lettersom();

	// Controleer of nwwoord0, nwwoord1, nwwoord2 alleen letters uit
	// het alfabet bevat (hoogstens 10 verschillende hoofdletters).
	// Zo ja, bepaal dan alle oplossingen voor de lettersom
	//   nwwoord0 + nwwoord1 = nwwoord2. Schrijf de eerste oplossing naar
	//   het scherm, en retourneer het aantal verschillende oplossingen.
	// Zo nee, retourneer -1.
	// Pre:
	// * nwoord0, nwoord1 en nwoord2 bevatten elk hoogstens maxwoordlengte
	//   karakters
	int zoekoplossingen(char const *nwwoord0, char const *nwwoord1, char const *nwwoord2, bool stop=false);

	// Controleer of nwwoord0 en nwwoord1 alleen letters uit
	// het alfabet bevatten (hoogstens 10 verschillende hoofdletters).
	// Zo ja, bepaal dan hoeveel puzzels met een unieke oplossing er te maken
	//   zijn bij nwwoord0 en nwwoord1, en retourneer dat aantal.
	// Zo nee, retourneer -1.
	// Pre:
	// * nwoord0 en nwoord1 zijn even lang en bevatten elk hoogstens
	//   maxwoordlengte karakters
	int construeerpuzzels(char *nwwoord0, char *nwwoord1);

private:
	// TODO: uw eigen private methoden en membervariabelen,

};

#endif


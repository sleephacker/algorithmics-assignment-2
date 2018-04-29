## Voorbeeld

Stel we zoeken de oplossingen voor SINT + PIET = FEEST. Allereerst bepalen we in welke volgorde we de karaketers een cijfer moeten toekennen. Hierbij geldt dat we achterin de eerste twee woorden beginnen. Dit doen we omdat we op deze manier het begin van de som kunnen berekenen, en hierdoor mogelijk een toekenning ongeldig kunnen verklaren. De volgorde moet alle verschillende karakters bevatten. In dit geval is de volgorde dus TNESIPF. De rij met getallen die aan deze voorwaardes voldoet noemen we een **sleutel**. Een oplossing van de puzzel is een complete toekenning van getallen aan de sleutel, waarbij de puzzel klopt. Hierbij lopen we van links naar rechts over de sleutel en kennen een getal toe aan elk karakter. Op het moment dat een toekenning de puzzel ongeldig maakt, geven we het huidige karaketer het volgende getal, zonder de rest van de karakters een getal toe te kennen.

## Functies

### zoekoplossingen
Input: woord0, woord1, woord2

Output: aantal oplossingen

```
zoekoplossingen(woord0, woord1, woord2) {

	if(lengtes kloppen niet) return 0;
	
	sleutel = toekenning_sleutel(woord0, woord1, woord2);
	
	oplossingen = 0
	toekenning = lege_toekenning(sleutel)
	geldig = true
	
	
	while(true) {
	
		toekenning, klaar = volgende_toekenning(toekenning, geldig)
		
		if(klaar) break
    	
		geldig, oplossing = bekijk_toekenning(toekenning)

		if(oplossing) oplossingen += 1;
	}
    
    return oplossingen
}
```

### toekenning_sleutel

Bepaal een sleutel voor de gegeven woorden. Zie het voorbeeld voor de definitie van een sleutel.

### volgende_toekenning

Een volgende toekenning van de sleutel als die bestaat. Hierbij moet gelden dat verschillende cijfers toegekend moeten worden aan verschillende letters.

### bekijk_toekenning
Bepaal of een gegeven toekenning van een sleutel geldig is. Deze functie moet ook bekijken of er geen onnodige voorloopnullen gebruikt worden. Als de toekenning zowel geldig is als compleet, dan geeft deze functie aan dat er een oplossing is gevonden. 

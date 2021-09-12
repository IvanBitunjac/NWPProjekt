# NWPProjekt - aplikacija za spremanje/ažuriranje/brisanje podataka iz MS Access baze
1. Kreirati bazu podataka unutar MSAccess (proizvoljno ime)
2. Kreirati novi ODBC Data Source pod imenom NWPProjekt i za njegovu bazu podataka odabrati novokreiranu MSAccess bazu
3. Aplikacija pri pokretanju sadrži gumb ''Create tables'' koji kreira 2 tablice, UserData i LastAccessed, potrebno ga je pritisnuti samo na prvom pokretanju aplikacije

 - UserData sprema korisničke podatke dok LastAccessed sprema informacije o zadnjem vremenu pristupanja određenom retku u UserData i koja operacija je napravljena nad njim (Updated,Written)

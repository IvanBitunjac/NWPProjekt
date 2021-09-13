# NWPProjekt - aplikacija za spremanje/ažuriranje/brisanje podataka iz MS Access baze
1. Kreirati novi ODBC Data Source pod imenom NWPProjekt i za njegovu bazu podataka odabrati preuzetu NWPProjektDB.accdb bazu
2. Pri pokretanju aplikacije otvara se dialog s buttonima Save Data, Update/Delete Data, Retrieve Data i Create Tables
3. Ako je aplikacija pokrenuta prvi put, potrebno je pritisnuti Create Tables button kako bi se u bazi kreirale potrebne tablice, UserData i LastAccessed
       - UserData struktura - DataID, FirstName, Surname, Username, Email, Password, Platform
       - LastAccessed struktura - DataID, LastAccessed, LatestOperation
4. Button Save Data otvara dialog koji odrađuje spremanje podataka u UserData tablicu i zapisuje u LastAccessed tablicu zadnje vrijeme pristupanja podacima i zadnju operaciju. Ako su podaci zapisani tek prvi put, zadnji pristup će biti trenutno vrijeme i operacija će biti ''Written''. Također nije potrebno ispuniti sva polja na dijalogu, osim Platform (koristi se za pretraživanje)
5. Button Update/Delete otvara dialog za ažuriranje i brisanje podataka iz baze. Podaci koji se žele ažurirati, proslijedi se DataID tog retka, ispune se polja koja se žele ažurirati i pritisne se Update button. Brisanje se također odrađuje preko DataID pritiskom na Delete button. Briše kompletan redak iz tablice
6. Button Retrieve Data otvara dijalog za dohvaćanje podataka iz baze odnosno ispisuje ih u ListBox. Pretraživanje se odrađuje preko Platform retka u tablici. U Search edit kontrolu se upiše ime platforme i pritisne se Search button. Svi retci s odgovarajućom platformom se ispišu u ListBox zajedno s zadnjom operacijom nad podacima i zadnjim pristupanjem. Get All button dohvati sve retke iz tablice i ispiše ih.


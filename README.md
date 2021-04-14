# NHF - Receptkönyv

## A program
A feladat egy olyan program készítése, ami képes recepteket és összetevőket tárolni, és ezek alapján ételeket felajánlani a felhasználónak. Lehetőség van új recepteket/összetevőket hozzáadni, módosítani és törölni. A megvalósítás egy menü vezérelt program, melyben ki lehet választani az egyes szekciókat (összetevők, étel sorsolása...), és ezeken belül lehet elérni az egyes feladatokat.
A program indítás után ellenőrzi, hogy a saját könyvtárában találhatók-e mentett fájlok, és azokat betölti, így onnan folytathatjuk a program használatát, ahol abbahagytuk. Mivel a program minden egyes módosítás után való visszalépéssel menti a változtatásokat, ezért kilépés után az összes adat fájlba lesz mentve1.

## A program használata
###### Alapanyaglista
Ebben a menüpontban lehet megtekinteni a már hozzáadott alapanyagokat. 
A menüponton belül a program kilistázza a már hozzáadott alapanyagokat. Ezek közül lehetőség van egyet kiválasztani, azt szerkeszteni, vagy törölni. Ezen kívül van egy opció új összetevő hozzáadására. A visszalépés gomb megnyomásával visszakerülünk a főmenübe, és a változtatások mentődnek1.

###### Kamra
Ebben a menüpontban lehet megadni, hogy az egyes alapanyagokból mennyi van otthon. A program kilistázza azokat az összetevőket melyből 0, vagy több mint 0 van megadva. A menüponton belül lehetőség van új összetevőt hozzáadni. Ezen opció választásakor meg kell adni a mennyiségét az adott összetevőnek. Főmenübe való visszalépés esetén, a program menti1 a módosításokat.

###### Receptkönyv
Ebben a menüpontban lehet törölni, módosítani és hozzáadni recepteket. A menüponton belül választható opciók:
Receptek listázása: Kilistázza az eddig megadott recepteket. Kiválaszthatjuk, hogy megtekintjük, módosítjuk, vagy töröljük a receptet. Megtekintés esetén, a program a képernyőre írja a hozzávalókat és az instrukciókat. Módosítás esetén adhatunk hozzá, eltávolíthatunk összetevőt, módosíthatunk összetevő mennyiséget, vagy módosíthatunk/törölhetünk instrukciót.
Recept hozzáadása: Megadjuk a receptünk nevét, majd kiválasztjuk az összetevőlistából az összetevőket, megadjuk a szükséges mennyiséget, és ha végeztünk ezek hozzáadásával, megadjuk az instrukciókat.
Recept törlése: Kilistázza a recepteket, és kiválaszthatjuk melyiket akarjuk törölni.
Főmenübe való visszalépésnél a program menti a módosításokat1.

###### Keresés
A menüponton belül az alábbiak közül választhatunk:
Az étel neve alapján
Itt megadhatjuk a keresett étel nevét, vagy ha nem tudjuk azt, megadhatunk egy szót (minimum 3 karakter) és ez alapján kilistázza azokat az ételeket, melyeknek a nevében megtalálható ez a szó.
Nincs ötletem
A program véletlenszerűen kisorsol egy ételt, és a felhasználó eldöntheti, hogy tetszik-e neki, vagy sem. Ha nem, akkor sorsol egy újat, ha igen, megjeleníti a választott étel receptjét.
De ennék egy kis...
Ebben a menüpontban a felhasználó megad egy összetevőt (az előre megadott összetevőlistából választva) és ez alapján a program felsorolja azokat az ételeket, amelyek tartalmazzák azt. Ezek közül a felhasználó kiválaszthatja melyik tetszik neki a legjobban, és a program megjeleníti annak a receptjét.
El kell használni
A felhasználó megadhat egy, vagy több hozzávalót (az előre megadott összetevőlistából), és a program kilistázza azokat a recepteket, melyek tartalmazzák az összes megadott hozzávalót. A felhasználó kiválaszthat egyet, melynek a program megjeleníti a receptjét.

## A program menüje
A programot konzolon belül lehet vezérelni. Nyílbillentyűkkel választhatunk menüpontot, az enter megnyomására belép a menübe. A menüpontokon belül szimplán kilistázza a rekordokat, melyek bizonyos esetekben kiválaszthatók, megnyomásra módosíthatjuk őket.

## Mentés
A program különböző fájlokba menti az adatokat. TXT kiterjesztésű fájlokat készít, az alábbiak szerint ment:
Összetevőlista -> osszetevolista.txt
Kamra -> kamra.txt
Receptek -> recept.txt
A fájlok soronként tartalmaznak 1-1 rekordot, az adatokat ; karakter választja el, és sor vége jel után következik az új rekord.

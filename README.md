Lupsa Alexandra Cristina - 312CC

Tema 2 - Structuri de Date si Algoritmi

Mod de implementare:
	Pentru a crea arborele binar construit cu Min-Heap am creat trei structuri.
O structura pentru arborele binar (din curs), unde avem un camp pentru
frecventa, unul pentru nume (alocat dinamic), unul pentru fiul stang si drept,
si un ultim camp pentru legatura cu arborele multicai, legatura de care avem
nevoie in cadrul CERINTEI 5. O structura pentru Min-Heap (din curs), si doua
pentru coada, de care avem nevoie pentru afisare in cadrul functiei
parcurgeNivel. Am mai creat si o structura pentru arborele multicai, avand
campurile de frecventa, nume (alocat dinamic), numarul de copii, un vector de
copii pentru fiecare nod in parte si o legatura cu arborele binar realizata prin
parametrul parinte_binar.

	Am citit cele trei argumente in main, acestea fiind numarul cerintei,
fisierul de intrare, respectiv cel de iesire. Am citit numarul de sateliti iar
apoi am initializat heap-ul in functia PQInit (din curs) in care am inceput de
la size 0 si am atribuit maxHeapSize cu numarul de sateliti. Apoi am declarat
variabila contor pe care am initializat-o cu 0. Pentru fiecare satelit citit,
citim frecventa si numele, creem un nod cu aceste informatii in functia buildNod
(din curs) iar apoi bagam nodul in heap cu ajutorul functiei Insert (din curs).
In cadrul acestei functii, dupa adaugarea nodului in heap pe ultima pozitie
disponibila, se apeleaza functia SiftUp (din curs) pentru a restaura
proprietatea de Min-Heap, urcand nodul nou adaugat pana la pozitia corecta,
conform criteriilor de comparare (frecventa si ordine alfabetica). La finalul
while-ului, reinitializam variabila contor cu 0 intrucat o vom folosi si pentru
citirea urmatoarelor linii in cadrul cerintelor. In cadrul unui alt while, luam
cate 2 noduri, cele cu frecventa cea mai mica. Le extragem cu ajutorul functiei
ExtractMin (din curs). Functia apeleaza si functia SiftDown (din curs), care are
rolul de a reface proprietatea de Min-Heap dupa ce varful heap-ului a fost
inlocuit cu ultimul element. Mai exact, ExtractMin scoate nodul de pe pozitia 1
(radacina heap-ului), care este intotdeauna cel cu frecventa cea mai mica, si il
returneaza. Apoi, ultimul nod din heap este mutat in varf, iar SiftDown este
apelata pentru a-l cobori in pozitia corecta, pastrand ordinea bazata pe
frecventa si, in caz de egalitate, pe ordine alfabetica a numelui. Apoi le
concatenam numele in cadrul functiei concatenare_nume. Adunam frecventele si din
combinarea celor doua noduri creem un nou nod in buildNod, pe care il adaugam cu
Insert in heap. Dam free la memoria alocata dinamic de functia concatenare_nume.
Dupa ce am creat Min-Heap-ul, acesta va avea un singur nod, si anume radacina,
pe care o extragem in variabila radacina. Vom avea nevoie de ea pentru toate
cerintele ce vor urma.

CERINTA 1:
	In cadrul acestui task apelam functia parcurgeNivel (din curs), care
afiseaza pe nivele arborele cu structura de Min-Heap realizat anterior. In
cadrul acestei functii am initializat 3 variabile, elemente_nivel,
elemente_verif si noduri_next. Elemente_nivel verifica cate noduri se afla pe
nivel, initializam cu 1 intrucat pe primul nivel stim garantat ca se afla doar
radacina. Elemente_verif verifica treptat cate elemente extragem din coada,
initializam variabila cu 0, iar noduri_next aduna elementele care vor apartine
urmatorului nivel, se aduna cand adaugam elemente in coada.  Initializam coada
cu ajutorul functiei initQueue, iar apoi adaugam primul element in coada
(radacina). Cat timp coada nu este vida, extragem din coada un element, crescand
astfel variabila elemente_verif, iar apoi afisam frecventa si numele elementului
extras. Verificam daca are fii, in acest caz crestem variabila noduri_next,
intrucat acestea vor fi noduri ce vor apartine urmatorului nivel. Daca avem
acelasi numar de elemente verificate cu cel de pe nivel, inseamna ca trebuie
sa trecem pe alt rand. Elemente_nivel primeste acum toti fiii nivelului care
tocmai s-a afisat (adica noduri_next), iar la final reinitializam noduri_next si
elemente_verif cu 0 pentru o noua iteratie.

CERINTA 2:
	In cadrul cerintei 2, ni se ofera mai multe codificari pe care noi trebuie
sa le decodificam, pentru a determina ce sateliti au fost codificati. Cu
ajutorul variabilei contor reinitializata cu 0 inaintea if-urilor cu cerinte,
parcurgem fiecare codificare in cadrul functiei parcurgere_codificare_c2.
Functia primeste ca parametrii radacina, string-ul cu codificarea si fisierul de
iesire. Retinem radacina, intrucat codificarea contine mai multe noduri iar
acestea se pot afla pornind toate de la radacina. Creem astfel un for care
parcurge tot string-ul incepand de la radacina, si care o ia la stanga
(cand avem '0') sau dreapta (cand avem '1'). Cand ajungem la un nod care nu mai
are descendenti, inseamna ca am gasit unul din sateliti si il afisam.
Reintializam t cu radacina si continam string-ul de unde am ramas pentru a gasi
urmatorii sateliti codificati.

CERINTA 3:
	La cerinta 3, avem de codificat intr-un string de 0 si 1 niste noduri. Citim
cate nume avem de codificat, iar apoi intr-un while citim nume cu nume fisierul.
Pentru fiecare nume citit, consumam \n -ul de la sfarsitul string-ului pentru a
face string-ul sa se termine cu terminatorul de sir '\0'. Initializam pointer-ul
lungime_string, in care crestem treptat in functia cautaNod lungimea codificarii
pe care o afisam ulterior in main. Functia cautaNod, primeste ca parametrii
radacina, numele, un vector codificari in care adaugam elementele si variabila
lungime_string care creste la fiecare char adaugat. Daca gasim numele exact,
returnam t si iesim din functie, in caz contrar, daca gasim o parte din nume in
fiul stang, afisam 0 si ne mutam la acesta. Daca gasim o parte din nume in fiul
drept, afisam 1 si ne mutam la acesta. Aceasta verificare legata de partea din
arbore spre care ne indreptam se face in functia cauta_nume_substring, unde
cautam cu exactitate daca avem numele nodului in t->nume sau nu. Ce face aceasta
functie, pe scurt daca gasim numele si el este urmat de o cifra => alt nod
(FALS). Daca gasim  numele si el este urmat de o litera => ne aflam in string-ul
corect si putem continua cautarea. Intrucat exista situatia in care noi sa
cautam de exemplu nodul R1 iar string-ul sa fie de forma R10, strstr ne va duce
pe acea cale care poate fi gresita. Astfel, in cadrul acestei functii, daca
identificam variabila R10 cand noi cautam R1, mai cautam in restul string-ului
daca avem structura R1 urmata de o litera. Daca acest lucru se intampla,
returnam 1 (conditia este adevarata). Daca nu, inseamna ca nu cautam nodul unde
trebuie si functia cautaNod nu o va mai lua pe acea ramura.

CERINTA 4:
	La cerinta 4, avem de gasit parintele comun al mai multor noduri. Citim cate
nume avem de codificat, intrucat pentru a gasi parintele comun m-am gandit la
implementarea unei matrici de codificari, unde fiecare linie a matricii
reprezinta codificarea unui satelit. Cautand astfel prefixul comun in functia
prefix_comun, afisam nodul parinte al nodurilor primite ca input. Pentru
fiecare nume citit, consumam \n -ul de la sfarsitul string-ului pentru a face
string-ul sa se termine cu terminatorul de sir '\0'. Functia cautaNod, primeste
ca parametrii radacina, numele, un linia contor din matricea coduri in care
adaugam elementele si variabila lungime_string care creste la fiecare char
adaugat. In matricea coduri punem pe fiecare linie cate o codificare pentru a
cauta apoi lungimea string-ului comun al tuturor codificarilor. In acest fel
gasim calea pana la parintele comun al celor nr_nume de codificat. La finalul
unei linii, adaugam terminatorul de sir iar apoi incrementam variabila contor
pentru urmatorul satelit ce trebuie codificat. Apoi, dupa ce am obtinut matricea
de codificari, mergem in functia prefix_comun, ce primeste ca parametrii
matricea, numarul de codificari, vectorul prefix in care vom adauga codificarea
parintelui comun si pointer-ul increment care creste la fiecare element adaugat
in string-ul prefix. In cadrul acestei functii, pornim de la primul satelit
codificat si comparam fiecare caracter din satelit cu caracterul de pe aceeasi
pozitie din ceilalti sateliti. Daca gasim o diferenta, adaugam terminatorul de
sir vectorului si iesim din functie, daca este identic pentru toti satelitii
incrementam variabila i pentru a verifica urmatorul caracter din string iar
procesul se repeta. Astfel obtinem string-ul comun tuturor satelitilor. Dupa
executia functiei, daca vectorul prefix are pe pozitia 0 doar terminatorul de
sir, inseamna ca parintele comun este chiar radacina, in caz contrar intram in
functia parcurgere_codificare_c4. In cadrul acestei functii, similar cu functie
parcurgere_codifcare_c2, parcurgem vectorul codificarii comune a numelor de la
radacina. La finalul string-ului afisam numele la care am ajuns.

CERINTA 5:
	La cerinta 5, am avut de calculat distanta dintre doua nume, numele putand
face parte atat din arborele binar, cat si dintr-un subarbore multicai. Astfel,
cu ajutorul functiilor folosite si la task-urile anterioare si cu altele pe care
le-am creat special pentru implementarea acestei cerinte, am abordat problema
astfel: am citit numarul de arbori multicai ce urmau a fi conectati de noduri
din arborele binar, iar apoi am creat un vector de noduri, acest vector retine
nodurile radacina ale arborilor multicai. Pentru fiecare arbore multicai, am
citit numele parintelui din binar de care se leaga, l-am cautat cu ajutorul
functiei cautaNod pentru a returna pointer la elementul gasit. Am citit apoi
frecventa si numele nodului din multicai de care se leaga nodul din arborele
binar, iar apoi cu acestea am intrat in functia creareconexiuneNod. Aceasta
functie primeste ca parametrii nodul din binar, radacina celui multicai,
frecventa si numele. Am creat astfel primul nod al arborelui multicai, pe care
l-am conectat de cel binar. Apoi in main am adaugat nodul la vectorul de noduri
radacina. Pentru fiecare arbore multicai, am citit dupa numarul de noduri
parinte, iar pentru fiecare am citit numele si l-am cautat in subarbore cu
ajutorul functiei cautanod_mtree. Totodata am mai citit si numarul de copii
aferent nodului parinte respectiv. Functia cautanod_mtree cauta recursiv prin
arbore si returneaza elementul gasit sau NULL, iar in cadrul ei totodata
calculam si distanta de la radacina pana la nod, aceasta ne va ajuta pentru
determinarea distantei finale a celor doua noduri ce urmeaza a fi citite. Creem
un for pentru a adauga iterativ fiecare copil de nodul sau parinte. In cadrul
for-ului, citim frecventa si numele fiecarui copil, adaugam aceste date campului
copil, facem legatura intre fiecare nod din subarbore si parintele din binar,
iar mai apoi intram in functia adaugare_copil, unde realocam dinamic memoria
intrucat am mai adaugat un copil, adaugam copilul la finalul vectorului,
actualizand la final numarul de fii din arbore.
	Dupa ce am creat toti arborii multicai si i-am conectat de noduri din binar,
am citit cele doua nume pentru care trebuie sa aflam distanta. Mai intai, am
verificat daca ele apartin arborelui binar sau unuia multicai. Pentru fiecare
nod, am creat variabila distanta1, respectiv distanta2, pe care le-am
initializat cu 0. Cu ajutorul functiei cautaNod, am determinat daca nodul se
afla in binar, in caz contrar functia a returnat NULL. In cazul in care nodul se
afla in binar, variabila distanta1/distanta2 salveaza distanta, matricea
codificari retine drumul parcurs, iar variabila apartine_binar1/apartine_binar2
se face 1. In caz contrar, reinitializam variabila distanta1/ distanta2 cu 0,
intrucat nodul nostru se afla intr-unul din arborii multicai. In acest caz, am
creat un for care trece prin toti arborii multicai, si verifica pentru fiecare
subarbore daca nodul se afla in el cu ajutorul functiei cautanod_mtree. Daca nu
gasim nodul intr-un arbore, reinitializam distanta cu 0 pentru a cauta in
urmatorul. Daca rezultatul functiei cautanod_mtree este diferit de NULL,
inseamna ca am gasit arborele multicai in care se afla nodul nostru, retinand
indicele acestuia in variabila indice_arbore1/ indice_arbore2.
	Dupa ce am determinat unde se afla cele doua nume pe care le-am primit ca
input, ramificam codul pe mai multe situatii: situatia in care ambele noduri
apartin arborelui binar, situatia in care unul apartine arborelui binar iar
celalalt apartine de un arbore multicai, situatia in care nodurile sunt in
acelasi arbore multicai si situatia in care nodurile apartin unor arbori
multicai diferiti.
	1. Cele doua nume se afla in arborele binar:
		Cum retinem codificarile si distante inca din cautarea nodurilor, tot ce
trebuie sa facem este sa apelam functia prefix_comun pentru a determina care
este lungimea comuna a celor doua drumuri. Daca prima pozitie a vectorului este
terminatorul de sir, inseamna ca drumurile se intersecteaza doar in radacina =>
rezultatul este suma celor doua drumuri distanta1 + distanta2. In caz contrar,
retinem in variabila len lungimea vectorului prefix, aceasta lungime se adauga
atat in distanta1 cat si in distanta2 si trebuie scazuta din ambele parti =>
rezultatul este distanta1 + distanta2 - 2 * len.
	2. Unul apartine arborelui binar, celalat face parte dintr-unul multicai:
		Am doua if-uri separate (binar + multicai si multicai + binar), dar ele
fac acelasi lucru numai ca pentru celalalat nume. Astfel, cum unul din nume se
afla in binar => distanta1/distanta2 detine lungimea caii. Pentru celalalt nume,
calculam distanta de la radacina la nodul binar de care este arborele multicai
respectiv legat cu ajutorul functiei cautaNod, salvand in matricea codificari
drumul si in variabila d1/d2 distanta. Prefix_comun calculeaza prefixul comun al
celor doua noduri, la care procedam exact ca in prima situatie: daca calea
comuna e radacina adunam distanta1/distanta2 + d2/d1, daca avem si o parte
comuna o scadem din ambele parti. La final, dupa ce am determinat distanta
comuna intre cele doua noduri apartinand ambele arborelui binar, adunam si
distanta1/distanta2 care a fost salvata inca de cand cautam unde se afla nodul,
la care mai adaugam 1, acesta reprezentand legatura dintre arborele binar si
radacina celui multicai.
	3. Ambele sunt in acelasi arbore multicai:
		Cu ajutorul functiei cautanod_mtree determinam distanta de la nod1 ce a
fost returnat ca pointer atunci cand am cautat unde se afla nodurile pana la
nume2, deoarece stim ca si acesta se afla in acelasi subarbore. Variabila d2
retine distanta pe care trebuie sa o afisam.
	4. Daca sunt in arbori multicai diferiti:
		Creem doua variabile TTree, nod1_bin si nod2_bin, ce reprezinta nodurile
din binar de care se leaga arborii multicai de care apartin. Calculam
codificarile cu ajutorul functiei cautaNod, salvand in variabilele d1 si d2
distantele din arborele binar. Gasim drumul comun cu ajutorul functiei
prefix_comun, si la fel ca la cazul 1, determinam distanta din binar. Adaugam
distanta1 si distanta2 intrucat la cautarea nodurilor la apelul functiei
cautarenod_mtree am calculat si distantele de la radacinile arborilor multicai
la nodurile cautate. La final, adunam distanta din binar cu cele doua distante
distanta 1 si distanta2 la care adaugam inca 2 pentru cele doua legaturi intre
binar si multicai.
	La final, am creat un for de la 0 la numarul de arbori binari-1 pentru a da
free la memoria din multicai. In functia free_arbore_multicai, creem un while
care trece prin toti copiii radacinii arborelui si recursiv sterge tot
continutul arborelui. Eliberam memoria vectorului copii, a numelui si nu in cele
din urma a radacinii. In mod similar, eliminam recursiv si memoria din arborele
binar cu ajutorul functiei free_arbore_binar, iar la finalul executiei acesteia,
eliberam si heap-ul, terminand programul cu inchiderea celor doua fisiere.

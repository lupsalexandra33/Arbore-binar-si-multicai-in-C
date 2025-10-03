/*Lupsa Alexandra-Cristina - 312CC*/
#include "biblioteca.h"

int main(int argc, char *argv[])
{
	char input[256], nume[16], nume_parinte[16], nume1[16], nume2[16];
	char coduri[100][1000], codificare[1000];
	int lungime_string, i;
	int d1 = 0, d2 = 0, d = 0;
	int distanta1 = 0, distanta2 = 0, apartine_binar1 = 0, apartine_binar2 = 0;
	int indice_arbore1 = -1, indice_arbore2 = -2;
	char *nume_concatenat;
	int contor = 0, frecventa, nr_sateliti, nr_codificari, nr_nume, nr_arbori,
	nr_noduri_parinte, nr_noduri_copil;
	// deschidem ambele fisiere, atat cel de intrare cat si cel de iesire
	FILE *f_in = fopen(argv[2], "r");
	FILE *f_out = fopen(argv[3], "w");
	// citim prima linie pentru a extrage numarul de sateliti
	fscanf(f_in, "%d ", &nr_sateliti);
	// initializam heap-ul
	PrQueue q;
	PQInit(&q, nr_sateliti, f_out);
	// pentru fiecare satelit citit, citim frecventa si numele
	// creem un nod de arbore pentru fiecare satelit
	// bagam in heap nodul rezultat
	while (contor < nr_sateliti && fgets(input, 256, f_in) != NULL) {
		sscanf(input, "%d %s", &frecventa, nume);
		TTree t = buildNod(frecventa, nume, NULL, NULL, f_out);
		Insert(&q, t);
		contor++;
	}
	contor = 0;
	TTree a, b;
	// creem arborele, extragem nodurile cu frecventa minima, le adunam
	// frecventele si le concatenam numele
	while (q.size > 1) {
		a = ExtractMin(&q);
		b = ExtractMin(&q);
		nume_concatenat = concatenare_nume(a, b);
		frecventa = a->frecventa + b->frecventa;
		TTree parinte = buildNod(frecventa, nume_concatenat, a, b, f_out);
		// dam free la memoria alocata in nume
		free(nume_concatenat);
		Insert(&q, parinte);
	}
	// rădăcina arborelui
	TTree radacina = ExtractMin(&q);
	if (strcmp(argv[1], "-c1") == 0) {
		Queue p;
		parcurgeNivel(radacina, f_out, &p);
	}
	if (strcmp(argv[1], "-c2") == 0) {
		// citim numarul de codificari
		fscanf(f_in, "%d ", &nr_codificari);
		while (contor < nr_codificari && fgets(input, 256, f_in) != NULL) {
			// decodificam string-ul
			parcurgere_codificare_c2(radacina, input, f_out);
			contor++;
			fprintf(f_out, "\n");
		}
	}
	if (strcmp(argv[1], "-c3") == 0) {
		// citim cate nume avem de codificat
		fscanf(f_in, "%d ", &nr_nume);
		while (contor < nr_nume && fgets(input, 256, f_in) != NULL) {
			// consumam \n -ul de la sfarsitul string-ului
			for (int i = 0; input[i] != '\0'; i++) {
				if (input[i] == '\n') {
					input[i] = '\0';
					break;
				}
			}
			lungime_string = 0;
			// cautam in cautaNod calea pe care se afla nodul
			cautaNod(radacina, input, codificare, &lungime_string);
			// afisam calea
			for (int i = 0; codificare[i] != '\0'; i++) {
				fprintf(f_out, "%c", codificare[i]);
			}
			contor++;
		}
	}
	if (strcmp(argv[1], "-c4") == 0) {
		// citim cate nume avem de codificat
		fscanf(f_in, "%d ", &nr_nume);
		while (contor < nr_nume && fgets(input, 256, f_in) != NULL) {
			// consumam \n -ul de la sfarsitul string-ului
			for (int i = 0; input[i] != '\0'; i++) {
				if (input[i] == '\n') {
					input[i] = '\0';
					break;
				}
			}
			// retinem cat de lung e string-ul in variabila lungime_string
			lungime_string = 0;
			cautaNod(radacina, input, coduri[contor], &lungime_string);
			coduri[contor][lungime_string] = '\0';
			contor++;
		}
		// in vectorul prefix retinem lungimea comuna a tuturor string-urilor
		char prefix[1000];
		int increment = 0;
		prefix_comun(coduri, contor, prefix, &increment);
		// daca primul caracter din vector e '\0' => parintele este radacina
		if (prefix[0] == '\0') {
			fprintf(f_out, "%s\n", radacina->nume);
		} else {
			parcurgere_codificare_c4(radacina, prefix, f_out);
		}
	}
	if (strcmp(argv[1], "-c5") == 0) {
		// citim numarul de arbori multicai pe care ii vom conecta de
		// arborele binar
		fscanf(f_in, "%d ", &nr_arbori);
		// creem un vector in care retinem toate radacinile arborilor multicai
		TMTree *vector_noduri_radacina = malloc(nr_arbori * sizeof(TMTree));
		if (vector_noduri_radacina == NULL) {
			fprintf(f_out, "Eroare la alocarea memoriei!");
			exit(1);
		}
		for (i = 0; i < nr_arbori; i++) {
			// citim numele nodului din arborele binar de care se leaga arborele
			fscanf(f_in, "%s", nume_parinte);
			lungime_string = 0;
			TTree nod_radacina = cautaNod(radacina, nume_parinte, coduri[0],
				&lungime_string);
			// citim frecventa si numele nodului radacina al arborelui multicai
			fscanf(f_in, "%d %s", &frecventa, nume);

			TMTree t = (TMTree)malloc(sizeof(TreeMultiNode));
			if (t == NULL) {
				fprintf(f_out, "Eroare la alocarea memoriei!");
				exit(1);
			}
			t = creareconexiuneNod(nod_radacina, t, frecventa, nume, f_out);
			// punem toate nodurile radacina ale arborilor multicai in vector
			vector_noduri_radacina[i] = t;

			// citim numarul de noduri parinte ale arborelui multicai
			fscanf(f_in, "%d ", &nr_noduri_parinte);
			for (int j = 0; j < nr_noduri_parinte; j++) {
				// citim un nod parinte si numarul de copii
				fscanf(f_in, "%s", nume_parinte);
				fscanf(f_in, "%d ", &nr_noduri_copil);
				// gasim nodul parinte in arborele multicai
				TMTree nod_parinte = cautanod_mtree(t, nume_parinte, &d);
				for (int k = 0; k < nr_noduri_copil; k++) {
					// citim fiecare copil si il atasam la nodul parinte
					fscanf(f_in, "%d %s", &frecventa, nume);
					TMTree copil = (TMTree)malloc(sizeof(TreeMultiNode));
					if (copil == NULL) {
						fprintf(f_out, "Eroare la alocarea memoriei!");
						exit(1);
					}
					copil->frecventa = frecventa;
					copil->nume = malloc((strlen(nume) + 1) * sizeof(char));
					if (copil->nume == NULL) {
						fprintf(f_out, "Eroare la alocarea memoriei!");
						exit(1);
					}
					strcpy(copil->nume, nume);
					copil->numar_copii = 0;
					copil->copii = NULL;
					// facem legatura intre fiecare nod din subarbore si
					// parintele din binar
					copil->parinte_binar = nod_parinte->parinte_binar;
					// adaugam copilul in arborele multicai
					adaugare_copil(nod_parinte, copil);
				}
			}
		}
		// citim cele doua nume pentru care avem de aflat distanta
		fscanf(f_in, "%s %s", nume1, nume2);
		TMTree nod1 = NULL, nod2 = NULL;
		// cautam daca primul nume se afla in arborele binar
		TTree nod_binar1 = cautaNod(radacina, nume1, coduri[0], &distanta1);
		coduri[0][distanta1] = '\0';
		// in caz contrar, cautam in arborii multicai
		if (nod_binar1 == NULL) {
			distanta1 = 0;
			for (int i = 0; i < nr_arbori; i++) {
				// cautam de la radacina fiecarui subarbore primul nume
				nod1 = cautanod_mtree(vector_noduri_radacina[i], nume1,
					&distanta1);
				if (nod1 == NULL) {
					distanta1 = 0;
				} else {
					// retinem indicele arborelui multicai in care avem numele
					indice_arbore1 = i;
					break;
				}
			}
		} else {
			apartine_binar1 = 1;
		}
		// cautam daca al doilea nume se afla in arborele binar
		TTree nod_binar2 = cautaNod(radacina, nume2, coduri[1], &distanta2);
		coduri[1][distanta2] = '\0';
		// in caz contrar, cautam in arborii multicai
		if (nod_binar2 == NULL) {
			distanta2 = 0;
			for (int i = 0; i < nr_arbori; i++) {
				// cautam de la radacina fiecarui subarbore al doilea nume
				nod2 = cautanod_mtree(vector_noduri_radacina[i], nume2,
					&distanta2);
				if (nod2 == NULL) {
					distanta2 = 0;
				} else {
					// retinem indicele arborelui multicai in care avem numele
					indice_arbore2 = i;
					break;
				}
			}
		} else {
			apartine_binar2 = 1;
		}
		// cele doua nume se afla in arborele binar
		if (apartine_binar1 == 1 && apartine_binar2 == 1) {
			char prefix[1000];
			int increment = 0;
			prefix_comun(coduri, 2, prefix, &increment);
			if (prefix[0] == '\0') {
				fprintf(f_out, "%d", distanta1 + distanta2);
			} else {
				// calculam care este calea comuna, aceasta se acumuleaza in
				// distanta1 si in distanta2 drept urmare trebuie sa o eliminam
				int len = strlen(prefix);
				fprintf(f_out, "%d", distanta1 + distanta2 - 2 * len);
			}

		} else if (apartine_binar1 == 1 && apartine_binar2 == 0) {
			// primul e in binar, al doilea in multicai

			// cum primul nume se afla in binar => distanta1 detine lungimea
			TTree nod = nod2->parinte_binar;
			// calculam distanta de la radacina la parinte_binar
			cautaNod(radacina, nod->nume, coduri[1], &d2);
			coduri[1][d2] = '\0';
			char prefix[1000];
			int increment = 0;
			// gasim calea comuna a celor doua drumuri
			prefix_comun(coduri, 2, prefix, &increment);
			if (prefix[0] == '\0') {
				d = distanta1 + d2;
			} else {
				int len = strlen(prefix);
				d = distanta1 + d2 - 2 * len;
			}
			// adunam distanta2 (adica cea de la radacina multicai la nodul
			// nostru) + 1 de legatura
			fprintf(f_out, "%d", d + distanta2 + 1);

		} else if (apartine_binar1 == 0 && apartine_binar2 == 1) {
			// primul e in multicai, al doilea in binar

			// cum primul nume se afla in binar => distanta2 detine lungimea
			TTree nod = nod1->parinte_binar;
			// calculam distanta de la radacina la parinte_binar
			cautaNod(radacina, nod->nume, coduri[0], &d1);
			coduri[0][d1] = '\0';
			char prefix[1000];
			int increment = 0;
			// gasim calea comuna a celor doua drumuri
			prefix_comun(coduri, 2, prefix, &increment);
			if (prefix[0] == '\0') {
				d = d1 + distanta2;
			} else {
				int len = strlen(prefix);
				d = d1 + distanta2 - 2 * len;
			}
			// adunam distanta1 (adica cea de la radacina multicai la nodul
			// nostru) + 1 de legatura
			fprintf(f_out, "%d", d + distanta1 + 1);

		} else if (indice_arbore1 == indice_arbore2) {
			// ambele sunt in acelasi arbore multicai

			cautanod_mtree(nod1, nume2, &d2);
			// afisam distanta intre nodurile din arborele multicai
			fprintf(f_out, "%d", d2);

		} else if (indice_arbore1 != indice_arbore2) {
			// daca sunt in arbori multicai diferiti

			TTree nod1_bin = nod1->parinte_binar;
			TTree nod2_bin = nod2->parinte_binar;
			// calculam codificarile si obtinem prefixul comun
			cautaNod(radacina, nod1_bin->nume, coduri[0], &d1);
			cautaNod(radacina, nod2_bin->nume, coduri[1], &d2);
			coduri[0][d1] = '\0';
			coduri[1][d2] = '\0';
			char prefix[1000];
			int increment = 0;
			prefix_comun(coduri, 2, prefix, &increment);
			int len = strlen(prefix);
			// adunam distantele din arborii multicai si cele de legatura la
			// binar (+2)
			if (prefix[0] == '\0') {
				d = d1 + d2;
			} else {
				d = d1 + d2 - 2 * len;
			}
			fprintf(f_out, "%d", d + distanta1 + distanta2 + 2);
		}
		// eliberam memoria din multicai
		for (int i = 0; i < nr_arbori; i++) {
			free_arbore_multicai(vector_noduri_radacina[i]);
		}
		free(vector_noduri_radacina);
	}
	// eliberam memoria din binar
	free_arbore_binar(radacina);
	// eliberam memoria din heap
	free(q.satelit);
	fclose(f_in);
	fclose(f_out);
	return 0;
}
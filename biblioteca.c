/*Lupsa Alexandra-Cristina - 312CC*/
#include "biblioteca.h"

// initializam coada
void initQueue(Queue *p)
{
	p->front = p->rear = NULL;
}

// verificam daca coada este goala
int isEmptyQueue(Queue *p)
{
	return p->front == NULL;
}

// adaugam un nod in coada pentru parcurgerea pe nivel - BFS
void enqueue(TTree a, FILE *f_out, Queue *p)
{
	PQueue q = (PQueue)malloc(sizeof(QueueCell));
	if (q == NULL) {
		fprintf(f_out, "memorie insuficienta\n");
		return;
	}
	// adaugam nodul arborelui in coada
	q->satelit = a;
	q->next = NULL;
	// daca coada este goala, si front si rear = q
	if (p->front == NULL && p->rear == NULL) {
		p->front = p->rear = q;
		return;
	}
	// finalul cozii se muta in q
	p->rear->next = q;
	p->rear = q;
}

// scoatem un element din coada
TTree dequeue(FILE *f_out, Queue *p)
{
	PQueue q = p->front;
	TTree t;
	if (p->front == NULL) {
		fprintf(f_out, "coada vida\n");
		return NULL;
	}
	// luam primul element din coada
	t = p->front->satelit;
	if (p->front == p->rear) {
		p->front = p->rear = NULL;
	} else {
		p->front = p->front->next;
	}
	free(q);
	return t;
}

void parcurgeNivel(TTree tree, FILE *f_out, Queue *p)
{
	TTree t;
	// elemente_nivel = cate noduri se afla pe nivel, initializam cu 1 intrucat
	// 					pe primul nivel stim garantat ca se afla doar radacina
	int elemente_nivel = 1;
	// elemente_verif = cate elemente am extras din coada
	int elemente_verif = 0;
	// elementele care vor apartine urmatorului nivel, se aduna cand adaugam
	// elemente in coada
	int noduri_next = 0;
	if (tree == NULL) {
		fprintf(f_out, "arbore vid\n");
		return;
	}
	// initializam coada
	initQueue(p);
	// adaugam radacina in coada
	enqueue(tree, f_out, p);
	while (!isEmptyQueue(p)) {
		// extragem un nod
		t = dequeue(f_out, p);
		elemente_verif++;
		fprintf(f_out, "%d-%s ", t->frecventa, t->nume);
		// daca exista copii, ii adaugam in coada
		if (t->lt != NULL) {
			enqueue(t->lt, f_out, p);
			noduri_next++;
		}
		if (t->rt != NULL) {
			enqueue(t->rt, f_out, p);
			noduri_next++;
		}
		// cand avem acelasi numar de elemente verificate cu cel de pe nivel,
		// inseamna ca trebuie sa trecem pe alt rand
		if (elemente_verif == elemente_nivel) {
			fprintf(f_out, "\n");
			// elemente_nivel primeste acum toti fiii nivelului care tocmai
			// s-a afisat
			elemente_nivel = noduri_next;
			// reinitializam cu 0 cele doua contoare
			noduri_next = 0;
			elemente_verif = 0;
		}
	}
}

void PQInit(APrQueue q, int maxSize, FILE *f_out)
{
	// initializam heap-ul gol
	q->size = 0;
	q->maxHeapSize = maxSize + 1;
	q->satelit = (TTree *)malloc(q->maxHeapSize * sizeof(TTree));
	if (q->satelit == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
}

// in functia buildNod creem un nou nod in arborele binar de sateliti
TTree buildNod(int frecventa, char *nume, TTree ltree, TTree rtree, FILE *f_out)
{
	TTree t = (TTree)malloc(sizeof(TreeNode));
	if (t == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	// copiem numele
	t->frecventa = frecventa;
	t->nume = malloc((strlen(nume) + 1) * sizeof(char));
	if (t->nume == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	strcpy(t->nume, nume);
	t->lt = ltree;
	t->rt = rtree;
	return t;
}

void SiftDown(APrQueue q, int k, int N)
{
	int j;
	TTree t;
	while (2 * k <= N) {
		// j = copilul stang
		// j + 1 = copilul drept
		j = 2 * k;
		// alegem copilul cu frecventa mai mica, respectiv numele mai mic in
		// cazul in care cele doua frecvente sunt egale
		if ((j < N) &&
			(q->satelit[j + 1]->frecventa < q->satelit[j]->frecventa ||
			 (q->satelit[j + 1]->frecventa == q->satelit[j]->frecventa &&
			  strcmp(q->satelit[j + 1]->nume, q->satelit[j]->nume) < 0))) {
			// daca copilul drept e mai mic => trecem la el
			j++;
		}
		if (q->satelit[k]->frecventa < q->satelit[j]->frecventa ||
			(q->satelit[k]->frecventa == q->satelit[j]->frecventa &&
			 strcmp(q->satelit[k]->nume, q->satelit[j]->nume) <= 0)) {
			// daca copilul stang e mai mic => ne aflam in pozitia corecta
			break;
		}
		// interschimbam nodul cu copilul sau
		t = q->satelit[k];
		q->satelit[k] = q->satelit[j];
		q->satelit[j] = t;
		// trecem la urmatorul nivel
		k = j;
	}
}

void SiftUp(APrQueue q, int i)
{
	TTree t = q->satelit[i];
	while (i > 1) {
		// parintele
		int p = i / 2;
		if (t->frecventa > q->satelit[p]->frecventa ||
			(t->frecventa == q->satelit[p]->frecventa &&
			 strcmp(t->nume, q->satelit[p]->nume) >= 0)) {
			// daca parintele este mai mic => ne aflam in pozitia corecta
			break;
		}
		// in caz contrar, mutam parintele in jos
		q->satelit[i] = q->satelit[p];
		i = p;
	}
	q->satelit[i] = t;
}

// in functia ExtractMin extragem nodul cu frecventa cea mai mica din heap
TTree ExtractMin(APrQueue q)
{
	TTree rezultat = q->satelit[1];
	q->satelit[1] = q->satelit[q->size];
	q->size = q->size - 1;
	SiftDown(q, 1, q->size);
	return rezultat;
}

// in functia Insert, inseram un nou nod in heap
void Insert(APrQueue q, TTree x)
{
	if (q->size == q->maxHeapSize) {
		return;
	}
	q->size = q->size + 1;
	q->satelit[q->size] = x;
	SiftUp(q, q->size);
}

// concatenam cele doua nume in aceasta functie
char *concatenare_nume(TTree a, TTree b)
{
	int lena = strlen(a->nume);
	int lenb = strlen(b->nume);
	char *nume_concatenat = (char *)malloc((lena + lenb + 1) * sizeof(char));
	if (nume_concatenat == NULL) {
		printf("Eroare la alocarea memoriei!");
		exit(1);
	}
	strcpy(nume_concatenat, a->nume);
	strcat(nume_concatenat, b->nume);
	return nume_concatenat;
}

void parcurgere_codificare_c2(TTree t, char *codificare, FILE *f_out)
{
	// retinem radacina, intrucat codificarea contine mai multe noduri iar
	// acestea se pot afla pornind toate de la radacina
	TTree radacina = t;
	// incepem de la radacina
	for (int i = 0; codificare[i] != '\n'; i++) {
		// daca avem 0 => trebuie sa o luam la stanga
		if (codificare[i] == '0') {
			t = t->lt;
		}
		// daca avem 1 => trebuie sa o luam la dreapta
		if (codificare[i] == '1') {
			t = t->rt;
		}
		// daca am ajuns un nod frunza, inseamna ca trebuie sa decodificam alt
		// nod din string => afisam numele nodului si reinitializam t = radacina
		if (t->lt == NULL && t->rt == NULL) {
			fprintf(f_out, "%s ", t->nume);
			t = radacina;
		}
	}
}

// in cadrul acestei functii cautam daca avem numele nodului in t->nume
int cauta_nume_substring(TTree t, char *nume)
{
	char *p = strstr(t->nume, nume);
	int len_nume = strlen(nume);
	int j = 0;
	// daca am gasit numele si el este urmat de o cifra => alt nod (FALS)

	// daca am gasit numele si el este urmat de o litera => ne aflam in
	// string-ul corect si putem continua cautarea
	if (p != NULL && !isdigit(*(p + len_nume))) {
		return 1;
	} else if (p != NULL) {
		// verificam daca mai gasim numele prin alta parte in string
		for (int i = 0; p[i] != '\0'; i++) {
			if (p[i] == nume[j]) {
				j++;
				if (j == len_nume) {
					// verificam daca urmatorul caracter nu e cifra
					if (!isdigit(p[i + 1])) {
						return 1;
					} else {
						j = 0;
					}
				}
			} else {
				j = 0;
			}
		}
	}
	// daca am ajuns aici, inseamna ca nu cautam in fiul care trebuie
	return 0;
}

void prefix_comun(char coduri[][1000], int nr_coduri, char *prefix, int *i)
{
	while (coduri[0][*i] != '\0') {
		char c = coduri[0][*i];
		for (int j = 1; j < nr_coduri; j++) {
			if (coduri[j][*i] != c) {
				prefix[*i] = '\0';
				return;
			}
		}
		prefix[*i] = c;
		(*i)++;
	}
}

TTree cautaNod(TTree t, char *nume, char *codificare, int *i)
{
	// daca am gasit nodul, iesim din functie
	if (strcmp(t->nume, nume) == 0) {
		codificare[*i] = '\0';
		return t;
	} else if (t->nume != NULL) {
		// daca gasim o parte din nume in fiul stang => 0 si ne mutam la acesta
		if (t->lt != NULL && cauta_nume_substring(t->lt, nume) == 1) {
			codificare[*i] = '0';
			(*i)++;
			return cautaNod(t->lt, nume, codificare, i);
		}
		// daca gasim o parte din nume in fiul drept => 1 si ne mutam la acesta
		if (t->rt != NULL && cauta_nume_substring(t->rt, nume) == 1) {
			codificare[*i] = '1';
			(*i)++;
			return cautaNod(t->rt, nume, codificare, i);
		}
	}
	return NULL;
}

// in aceasta functie parcurgem vectorul codificarii comune a numelor de la
// radacina iar la finalul string-ului afisam numele la care am ajuns
void parcurgere_codificare_c4(TTree t, char *codificare, FILE *f_out)
{
	for (int i = 0; codificare[i] != '\0'; i++) {
		if (codificare[i] == '0' && t->lt != NULL) {
			t = t->lt;
		} else if (codificare[i] == '1' && t->rt != NULL) {
			t = t->rt;
		}
		if (t->lt == NULL && t->rt == NULL) {
			return;
		}
	}
	fprintf(f_out, "%s", t->nume);
}

// legam radacina arborelui multicai de nodul din arborele binar
TMTree creareconexiuneNod(TTree tree, TMTree mtree, int frecventa, char *nume,
	FILE *f_out)
{
	mtree->frecventa = frecventa;
	mtree->nume = malloc((strlen(nume) + 1) * sizeof(char));
	if (mtree->nume == NULL) {
		fprintf(f_out, "Eroare la alocarea memoriei!");
		exit(1);
	}
	strcpy(mtree->nume, nume);
	mtree->numar_copii = 0;
	mtree->copii = NULL;
	tree->arbore_multicai = mtree;
	mtree->parinte_binar = tree;
	return mtree;
}

// in acesta functie cautam un nume si totodata calculam distanta
TMTree cautanod_mtree(TMTree mtree, char *nume, int *distanta)
{
	if (mtree == NULL) {
		return NULL;
	} else if (strcmp(mtree->nume, nume) == 0) {
		return mtree;
	}
	for (int i = 0; i < mtree->numar_copii; i++) {
		// incrementam distanta daca nodul se afla in subarborele curent
		(*distanta)++;
		TMTree gasit = cautanod_mtree(mtree->copii[i], nume, distanta);
		if (gasit != NULL) {
			return gasit;
		}
		// in caz contrar, decrementam distanta intrucat nu cautam unde trebuie
		(*distanta)--;
	}
	return NULL;
}

// adaugam un copil in arborele multicai
void adaugare_copil(TMTree mtree, TMTree copil)
{
	int i = mtree->numar_copii;
	mtree->copii = realloc(mtree->copii, (i + 1) * sizeof(TMTree));
	if (mtree->copii == NULL) {
		printf("Eroare la alocarea memoriei!");
		return;
	}
	mtree->copii[i] = copil;
	mtree->numar_copii++;
}

// in aceasta functie eliberam memoria din multicai
void free_arbore_multicai(TMTree mtree)
{
	int i = 0;
	while (i < mtree->numar_copii) {
		free_arbore_multicai(mtree->copii[i]);
		i++;
	}
	free(mtree->copii);
	free(mtree->nume);
	free(mtree);
}

// in aceasta functie eliberam memoria din binar
void free_arbore_binar(TTree t)
{
	if (t == NULL) {
		return;
	}
	if (t->lt != NULL) {
		free_arbore_binar(t->lt);
	}
	if (t->rt != NULL) {
		free_arbore_binar(t->rt);
	}
	free(t->nume);
	free(t);
}
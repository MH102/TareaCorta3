#include <iostream>
#include <string>
#include "Graph.h"
using namespace std;
using namespace Graph_lib;

enum color { rojo, negro };
typedef struct node *link;
struct node { // Red-Black Tree
public:
	int v;
	link izq, der;
	color nColor;
	Point p;
	node(int v, Point r) : v{ v }, izq{ nullptr },
		der{ nullptr }, nColor{ rojo }, p{ r } {}
	node(int v, color nColor, link izq, link der)
		: v{ v }, izq{ izq }, der{ der },
		nColor{ nColor } {}
	string scolor() {
		if (this->nColor == rojo)
			return "rojo";
		else
			return "negro";
	}
};

void rotateR(link &h) {
	link p = h->izq;    // (1)
	h->izq = p->der;    // (2)
	p->der = h;        // (3)
	h = p;              // (4)
}

void rotateL(link &h) {
	link p = h->der;    // (1)
	h->der = p->izq;    // (2)
	p->izq = h;        // (3)
	h = p;              // (4)
}

bool esRojo(link x) {
	if (x == nullptr) return false;
	return x->nColor == rojo;
}

void RBinsertR(link& h, int x, int sw, Point s) {
	if (h == nullptr) { h = new node(x, s); return; }
	if (esRojo(h->izq) && esRojo(h->der)) {
		h->nColor = rojo;
		h->izq->nColor = negro;
		h->der->nColor = negro;
	}
	if (x < h->v) {
		RBinsertR(h->izq, x, 0, s);
		if (esRojo(h) && esRojo(h->izq) && sw)
			rotateR(h);
		if (esRojo(h->izq) && esRojo(h->izq->izq)) {
			rotateR(h);
			h->nColor = negro;
			h->der->nColor = rojo;
		}
	}
	else {
		RBinsertR(h->der, x, 1, s);
		if (esRojo(h) && esRojo(h->der) && !sw)
			rotateL(h);
		if (esRojo(h->der) && esRojo(h->der->der)) {
			rotateL(h);
			h->nColor = negro;
			h->izq->nColor = rojo;
		}
	}
}

void RBinsert(link& h, int x, Point s) {
	RBinsertR(h, x, 0, s);
	h->nColor = negro;
}
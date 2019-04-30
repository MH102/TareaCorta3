#define _USE_MATH_DEFINES
#include "Simple_window.h"
#include "RojoNegro.h"
#include <cmath>
#include <stack>
using namespace Graph_lib;

class Binary_tree : public Shape
{
public:
	link r2;
	Binary_tree(int n)
		:l(7) , permu(n)
	{
		initialize_nodes(n);
	}
	~Binary_tree() {}

	void initialize_nodes(int n);
	void draw_lines() const;
	void initNiveles();

private:
	Point r;
	int l;
	int permu;
	vector<Point> node_points;
};
void Binary_tree::initNiveles() {
	stack<node *> s;
	node *curr = r2;
	r2->niv = 0;
	r2->p = Point(350, 20);
	while (curr != NULL || s.empty() == false)
	{
		while (curr != NULL)
		{
			s.push(curr);
			if (curr->izq) {
				curr->izq->niv = curr->niv + 1;
				if (permu >= 40) {
					curr->izq->p = Point(curr->p.x - (permu+20 * (5 / curr->izq->niv)), curr->p.y + 30);
					permu /= 2 + (permu/40);
				}
				else {
					curr->izq->p = Point(curr->p.x - (permu * (5 / curr->izq->niv)), curr->p.y + 30);
				}
			}
			curr = curr->izq;
		}
		curr = s.top();
		s.pop();
		if (curr->der) {
			curr->der->niv = curr->niv + 1;
			curr->der->p = Point(curr->p.x + (permu * (5 / curr->der->niv)), curr->p.y + 30);
		}
		curr = curr->der;
	}
}
void Binary_tree::initialize_nodes(int n)
{
	int * pt = new int[n];
	int j;
	int randint;
	for (int i = 0; i < n; i++) {
		pt[i] = i;
	}
	for (int i = 0; i < n; i++) {
		j = pt[i];
		randint = rand() % n;
		pt[i] = pt[randint];
		pt[randint] = j;
	}
	for (int i = 0; i < n; i++) {
		if (!r2) {
			r2 = new node(pt[i]);
		}
		else {
			if (pt[i] < r2->p.x) {
				RBinsert(r2, pt[i]);
			}
			else {
				RBinsert(r2, pt[i]);
				
			}
		}
	}
	initNiveles();
	draw_lines();
}

void Binary_tree::draw_lines() const
{
	stack<link> st;
	link curr = r2;
	while (curr != NULL || st.empty() == false)
	{
		while (curr != NULL)
		{
			st.push(curr);
			curr = curr->izq;
		}
		curr = st.top();
		st.pop();
		Point nod = curr->p;
		Circle c(nod, 5);
		c.set_style(Line_style(Line_style::solid, 2));
		if (curr->nColor == rojo) {
			c.set_color(Color::red);
			c.set_fill_color(Color::red);
		}
		if (curr->nColor == negro) {
			c.set_color(Color::black);
			c.set_fill_color(Color::black);
		}
		Point from(curr->p.x, curr->p.y + 5);
		if (curr->der && curr->izq) {
			Point to(curr->der->p.x + 1, curr->der->p.y - 5);
			Line l(from, to);
			l.set_color(Color::black);
			l.draw();
			Point to2(curr->izq->p.x - 1, curr->izq->p.y - 5);
			Line l2(from, to2);
			l2.set_color(Color::black);
			l2.draw();
		}
		else {
			if (curr->der) {
				Point to(curr->der->p.x + 1, curr->der->p.y - 5);
				Line l(from, to);
				l.set_color(Color::black);
				l.draw();
			}
			if (curr->izq) {
				Point to(curr->izq->p.x - 1, curr->izq->p.y - 5);
				Line l(from, to);
				l.set_color(Color::black);
				l.draw();
			}
		}
		c.draw();
		curr = curr->der;
	}
}

int main() {
	Point tl(100, 100);
	Simple_window win(tl, 720, 400, "Simple Window");
	Point center(win.x_max() / 2, win.y_max() / 2);
	Binary_tree tree(39);
	tree.r2->show(0);
	tree.draw_lines();
	win.attach(tree);

	win.wait_for_button();
}

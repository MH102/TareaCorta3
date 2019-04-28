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
	Binary_tree(Point punto,link root)
		:r(punto), r2(root), l(7)
	{
		initialize_nodes();
	}
	~Binary_tree() {}

	void initialize_nodes();
	void draw_lines() const;


private:
	Point r;
	int l;
	vector<Point> node_points;
};
string verificarColor(link r2,Point s)
{
	stack<link> st;
	link curr = r2;

	while (curr != NULL || st.empty() == false)
	{
		/* Reach the left most Node of the
		   curr Node */
		while (curr != NULL)
		{
			st.push(curr);
			curr = curr->izq;
		}

		curr = st.top();
		st.pop();
		if (curr->p.x == s.x && curr->p.y == s.y) {
			if (curr->nColor == rojo) {
				return "rojo";
			}
			if (curr->nColor == negro) {
				return "negro";
			}
		}
		curr = curr->der;
	}
	return "non";
}
void Binary_tree::initialize_nodes()
{
	double nodes = 1.0;

	double tree_w = l * 100;
	for (int i = 0; i < l; i++) {
		for (double j = -(nodes / 2); j < (nodes / 2); j++) {
			if (i == 0) {
				RBinsert(r2,i+5,Point(r.x + j, r.y + i * 30));
				node_points.push_back(Point(r.x + j, r.y + i * 30));
			}
			else {
				RBinsert(r2, i+5, Point(r.x + (double(tree_w / nodes) / 2) + (j * double(tree_w / nodes)), r.y + i * 30));
				node_points.push_back(Point(r.x + (double(tree_w / nodes) / 2) + (j * double(tree_w / nodes)), r.y + i * 30));
			}
		}
		nodes *= 2;
	}
}

void Binary_tree::draw_lines() const
{
	// draw nodes
	for (int i = 0; i < node_points.size(); i++) {
		Circle c(node_points[i], 5);
		c.set_style(Line_style(Line_style::solid, 2));
		string test = verificarColor(r2, node_points[i]);
		if (test == "rojo") {
			c.set_color(Color::red);
			c.set_fill_color(Color::red);
		}
		else {
			if (test == "negro") {
				c.set_color(Color::black);
				c.set_fill_color(Color::black);
			}
		}
		c.draw();
	}

	// draw connecting lines
	int node = 2;

	for (int i = 0; i < node_points.size() - ((node_points.size() + 1) / 2); i++) {
		for (int j = 1; j < 3; j++) {

			Point from(node_points[i].x, node_points[i].y + 5);
			Point to(node_points[i * node + j].x, node_points[i * node + j].y - 5);

			Line l(from, to);
			l.set_color(Color::black);
			l.draw();
		}
	}
}

int main() {
	Point tl(100, 100);
	Simple_window win(tl, 720, 400, "Simple Window");
	Point center(win.x_max() / 2, win.y_max() / 2);
	link h = new node(0,Point(center.x, 20));
	Binary_tree tree(Point(center.x,20),h);
	//tree.set_color(Color::red);

	win.attach(tree);

	win.wait_for_button();
}
#include <string.h>
#include "BTSlibrary.h"

int _index;

void init_tree(node **p)
{
	*p = (node *)malloc(sizeof(node));
	(*p)->left = NULL;
	(*p)->right = NULL;
}

void *btv_search(void *key, node *base, int *num, int width, FCMP fcmp)
{
	node *s;
	s = base->left;
	while (s != NULL && fcmp(key, s + 1) != 0) {
		if (fcmp(key, s + 1) < 0)
			s = s->left;
		else
			s = s->right;
	}
	if (s == NULL) return NULL;
	else return s + 1;
}

void *btv_insert(void *key, node *base, int *num, int width, FCMP fcmp)
{
	node *p, *s;
	p = base;
	s = base->left;
	while (s != NULL) {
		p = s;
		if (fcmp(key, s + 1) < 0)
			s = s->left;
		else
			s = s->right;
	}
	if ((s = (node*)malloc(sizeof(node) + width)) == NULL)
		return NULL;
	memcpy(s + 1, key, width);
	s->left = NULL;
	s->right = NULL;
	if (fcmp(key, p + 1) < 0 || p == base)
		p->left = s;
	else
		p->right = s;
	(*num)++;
	return s;
}

void _deleteall(node *t)
{
	if (t != NULL)
	{
		// post order traverse
		_deleteall(t->left);
		_deleteall(t->right);
		free(t);
	}
}

void *btv_deleteall(node *base, int *num)
{
	node *t;
	t = base->left;
	_deleteall(t);
	base->left = NULL;
	base->right = NULL;
	*num = 0;
	return base;
}

void btv_sort_list(node *p, void(*fpr)(void *))
{
	if (p != NULL) {
		btv_sort_list(p->left, fpr);
		fpr(p + 1);
		btv_sort_list(p->right, fpr);
	}
}

void btv_list(node *p, void(*fptr)(void *))
{
	int i;
	static int x = 0;

	if (p != NULL)
	{
		x += 2; // position for displaying a node

		// a kind of inorder traverse
		btv_list(p->right, fptr);
		for (i = 2; i < x; i++) printf("  ");
		fptr(p + 1); // print it in the monitor
		btv_list(p->left, fptr);
		x -= 2;
	}
}
/*
void _draw_node(node *p, void(*fptr)(void *, char *), int x1, int x2, int y, int mode)
{
	char content[20];
	if (p != NULL)
	{
		_draw_node(p->left, fptr, x1, (x1 + x2) / 2, y + DY, mode);
		fptr(p + 1, content);
		fillellipse((x1 + x2) / 2, y, textwidth(content) / 2 + 5, textheight(content) / 2 + 5);
		outtextxy((x1 + x2) / 2, y, content);
		_draw_node(p->right, fptr, (x1 + x2) / 2, x2, y + DY, mode);
	}
	else if (mode & TAIL)
		fillellipse((x1 + x2) / 2, y, 3, 3);
}

void _draw_link(node *p, int x1, int x2, int y, int mode)
{
	if (p != NULL)
	{
		lineto((x1 + x2) / 2, y);
		_draw_link(p->left, x1, (x1 + x2) / 2, y + DY, mode);
		moveto((x1 + x2) / 2, y);
		_draw_link(p->right, (x1+x2)/2, x2, y + DY, mode);
		lineto((x1 + x2) / 2, y);
	}
	else if (mode & TAIL)
	{
		lineto((x1 + x2) / 2, y);
		moveto((x1 + x2) / 2, y);
	}
}

void btv_draw(node *p, void(*fptr)(void *, char *), int mode)
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfillstyle(0, BLACK);
	moveto(getmaxx() / 2, 10);

	if (mode & LINK)
		_draw_link(p, 5, getmaxx() - 5, 10, mode);
	if (mode & NODE)
		_draw_node(p, fptr, 5, getmaxx() - 5, 10, mode);
//	closegraph();
}
*/
void _sort(node *p, void *a, int width)
{
	if (p != NULL)
	{
		_sort(p->left, a, width);
		memcpy((char *)a + (_index++)*width, p + 1, width);
		_sort(p->right, a, width);
	}
}

node *_balance(int n, void *a, int width)
{
	int nl, nr;
	node *p;
	if (n > 0)
	{
		nl = (n - 1) / 2;
		nr = n - nl - 1;
		p = (node *)malloc(sizeof(node) + width);
		p->left = _balance(nl, a, width);
		memcpy(p + 1, (char *)a + (_index++)*width, width);
		p->right = _balance(nr, a, width);
		return p;
	}
	else
		return NULL;
}

void btv_balance(node *base, int *num, int width)
{
	void *tmp;
	int ntmp = *num;
	tmp = malloc(width*ntmp);
	_index = 0;
	_sort(base->left, tmp, width);
	ntmp = *num;
	btv_deleteall(base, num);
	_index = 0;
	base->left = _balance(ntmp, tmp, width);
	*num = ntmp;
	free(tmp);
}
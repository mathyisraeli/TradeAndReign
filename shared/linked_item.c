#include "linked_item.h"

int count(char *name)
{
	if (strcmp(name, "fruit") == 0 || strcmp(name, "legume") == 0)
		return 10;
	if (strcmp(name, "fleche") == 0)
		return 20;
	if (strcmp(name, "herbe") == 0 || strcmp(name, "sable") == 0)
		return 10;
	return 1;
}

int n_item(struct linked_item *l)
{
	int ret = 0;
	for (struct linked_item *p = l; p != NULL; p = p->next)
		ret += 1;
	return ret;
}

char can_add(char *name, int cnt, struct linked_item *l)
{
	int max = count(name);
	int cnt_slot = 0;
	while (l != NULL)
	{
		if (strcmp(name, l->nom) == 0)
			cnt -= max - l->count;
		cnt_slot += 1;
		if (0 >= cnt)
			return 1;
		l = l->next;
	}
	while (10 > cnt_slot)
	{
		cnt -= max;
		cnt_slot += 1;
		if (0 >= cnt)
			return 1;
	}
	return 0;
}

struct linked_item *append_in_inventory(char *name, struct linked_item *p, int n)
{
	if (p == NULL)
	{
		p = malloc(sizeof(struct linked_item));
		p->nom[0] = 0;
		p->count = n;
		strcat(p->nom, name);
		p->next = NULL;
		return p;
	}
	else
	{
		struct linked_item *parcour = p;
		while (parcour->next != NULL)
		{
			parcour = parcour->next;
			if (strcmp(parcour->nom, name) == 0)
			{
				int max = count(name);
				if (max > parcour->count)
				{
					int b = max - parcour->count;
					if (b >= n)
					{
						parcour->count += n;
						return p;
					}
					else
					{
						parcour->count = max;
						n -= b;
					}
				}
			}
		}
		struct linked_item *new = malloc(sizeof(struct linked_item));
		new->nom[0] = 0;
		new->count = n;
		strcat(new->nom, name);
		new->next = NULL;
		parcour->next = new;
		return p;
	}
}

void moove_item(int a, int b, struct linked_item *l)
{
	struct linked_item *sa = NULL;
	struct linked_item *sb = NULL;
	char tmp[50];
	tmp[0] = 0;
	int i = 0;
	while (i <= a || i <= b)
	{
		if (l == NULL)
			return;
		if (i == a)
			sa = l;
		if (i == b)
			sb = l;
		i++;
		l = l->next;
	}
	strcat(tmp, sa->nom);
	int tmpi = sa->count;
	sa->nom[0] = 0;
	sa->count = sb->count;
	strcat(sa->nom, sb->nom);
	sb->nom[0] = 0;
	sb->count = tmpi;
	strcat(sb->nom, tmp);
}

int count_item(struct linked_item *l, char *name)
{
	int i = 0;
	while (l != NULL)
	{
		if (strcmp(l->nom, name) == 0)
			i+= l->count;
		l = l->next;
	}
	return i;
}

struct linked_item *get_item_n(int n, struct linked_item *l)
{
	while (l != NULL)
	{
		if (n == 1)
			return l;
		l = l->next;
		n -= 1;
	}
	return NULL;
}

struct linked_item *exist_in_linked_item(struct linked_item *e, char *cmp)
{
	while (e != NULL)
	{
		if (strcmp(e->nom, cmp) == 0)
			return e;
		e = e->next;
	}
	return NULL;
}

void free_linked_item(struct linked_item *e)
{
	if (e != NULL)
	{
		free_linked_item(e->next);
		free(e);
	}
}

void print(struct linked_item *e)
{
	if (e != NULL)
	{
		printf ("%s ", e->nom);
		print(e->next);
	}
	else
		putchar('\n');
}

struct linked_item *del(struct linked_item *root, struct linked_item *to_del)
{
	struct linked_item *p;
	if (root == to_del)
	{
		p = root->next;
		free(root);
		return p;
	}
	p = root;
	while (p->next != NULL)
	{
		if (p->next == to_del)
		{
			p->next = to_del->next;
			free(to_del);
			return root;
		}
		p = p->next;
	}
	return root;
}

struct linked_item *remove_from_inventory(char *name, struct linked_item *p, int n)
{
       while (n > 0 && p != NULL)
       {
               struct linked_item *a = exist_in_linked_item(p, name);
               if (a == NULL)
                       return p;
               if (a->count > n)
               {
                       a->count -= n;
                       n = 0;
               }
               else
               {
                       n -= a->count;
                       p = del(p, a);
               }
       }
       return p;
}

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

int n_item(char items[18][50])
{
	int ret = 0;
	for (int i = 0; i < 10; i++)
		if (items[i][0] == '.' && items[i][1] == 0)
			ret += 1;
	return ret;
}

char can_add(char *name, int cnt, char items[18][50], int items_cnt[12])
{
	int max = count(name);
	int available = 0;
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(name, items[i]) == 0)
			available += max - items_cnt[i];
		else if (items[i][0] == '.' && items[i][1] == 0)
			available += max;
	}
	return available >= cnt;
}

void append_in_inventory(char *name, int n, char items[18][50], int items_cnt[12])
{
	int max = count(name);
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(items[i], name) == 0)
		{
			if (max > items_cnt[i])
			{
				int b = max - items_cnt[i];
				if (b >= n)
				{
					items_cnt[i] += n;
					return;
				}
				else
				{
					items_cnt[i] = max;
					n -= b;
				}
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(items[i], ".") == 0)
		{
			sprintf(items[i], "%s", name);
			items_cnt[i] = n;
			return;
		}
	}
}

int count_item(char *name, char items[18][50], int items_cnt[12])
{
	int ret = 0;
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(items[i], name) == 0)
			ret += items_cnt[i];
	}
	return ret;
}

int find_index_in_inventory(char *name, char items[18][50])
{
	for (int i = 0; i < 10; i++)
		if (strcmp(items[i], name) == 0)
			return i;
	return -1;
}

void print(char items[18][50],  int items_cnt[12])
{
    for (int i = 0; i < 10; i++)
		printf ("%s %d ", items[i], items_cnt[i]);
	putchar('\n');
}

void remove_from_inventory(char *name, int n, char items[18][50], int items_cnt[12])
{
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(items[i], name) == 0)
		{
			if (items_cnt[i] >= n)
			{
				items_cnt[i] -= n;
				return;
			}
			else
			{
				n -= items_cnt[i];
				items_cnt[i] = 0;
			}
		}
	}
}

int echange_item(char p1_items[18][50], int p1_items_cnt[12], char p2_items[18][50], int p2_items_cnt[12])
{
	if (strcmp(p1_items[10], ".") == 0)
	{
		for (int i = 0; 10 > i; i++)
		{
			if (strcmp(p2_items[i], p1_items[11]) == 0 && p2_items_cnt[i] >= p1_items_cnt[11])
			{
				append_in_inventory(p1_items[11], p1_items_cnt[11], p1_items, p1_items_cnt);
				remove_from_inventory(p1_items[11], p1_items_cnt[11], p2_items, p2_items_cnt);
				break;
			}
		}
	}
	if (strcmp(p1_items[11], ".") == 0)
	{
		for (int i = 0; 10 > i; i++)
		{
			if (strcmp(p1_items[i], p1_items[10]) == 0 && p1_items_cnt[i] >= p1_items_cnt[10])
			{
				remove_from_inventory(p1_items[10], p1_items_cnt[10], p1_items, p1_items_cnt);
				append_in_inventory(p1_items[10], p1_items_cnt[10], p2_items, p2_items_cnt);
				break;
			}
		}
	}
	else
	{
		char p1get=0; char p2get = 0;
        for (int i = 0; 10 > i; i++)
        {
			if (strcmp(p2_items[i], p1_items[11]) == 0 && p2_items_cnt[i] >= p1_items_cnt[11])
                p1get = 1;
            if (strcmp(p1_items[i], p1_items[10]) == 0 && p1_items_cnt[i] >= p1_items_cnt[10])
                p2get = 1;
        }
		if (p1get == 1 && p2get == 1)
		{
			append_in_inventory(p1_items[11], p1_items_cnt[11], p1_items, p1_items_cnt);
			remove_from_inventory(p1_items[11], p1_items_cnt[11], p2_items, p2_items_cnt);
			remove_from_inventory(p1_items[10], p1_items_cnt[10], p1_items, p1_items_cnt);
			append_in_inventory(p1_items[10], p1_items_cnt[10], p2_items, p2_items_cnt);
	    }
    }
	p1_items[10][0] =  '.'; p1_items[10][1] = 0;
	p1_items[11][0] =  '.'; p1_items[11][1] = 0;	
	p1_items_cnt[10] = 0;	
	p1_items_cnt[11] = 0;
	return -1;
}
#include "pathfinding.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static const int dir[8][2] =
{
    {1,0},{-1,0},{0,1},{0,-1},
    {1,1},{-1,-1},{1,-1},{-1,1}
};

static inline float heuristic(int x1,int y1,int x2,int y2)
{
    int dx = abs(x1-x2);
    int dy = abs(y1-y2);

    int min = dx < dy ? dx : dy;
    int max = dx > dy ? dx : dy;

    return max + 0.41421356f * min;
}

static void heap_push(struct heap *h,int node,struct path *grid)
{
    int i = h->size++;
    h->data[i] = node;

    while (i > 0)
    {
        int p = (i - 1) >> 1;

        if (grid[h->data[p]].f <= grid[h->data[i]].f)
            break;

        int tmp = h->data[p];
        h->data[p] = h->data[i];
        h->data[i] = tmp;

        i = p;
    }
}

static int heap_pop(struct heap *h,struct path *grid)
{
    if (h->size == 0)
        return -1;

    int result = h->data[0];

    h->data[0] = h->data[--h->size];

    int i = 0;

    while (1)
    {
        int l = (i<<1)+1;
        int r = l+1;
        int smallest = i;

        if (l < h->size && grid[h->data[l]].f < grid[h->data[smallest]].f)
            smallest = l;

        if (r < h->size && grid[h->data[r]].f < grid[h->data[smallest]].f)
            smallest = r;

        if (smallest == i)
            break;

        int tmp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = tmp;

        i = smallest;
    }

    return result;
}

void init_grid(struct personnages *p)
{
    struct path *grid = p->chemin;

    for (int i=0;i<max_x*max_y;i++)
    {
        grid[i].g = 1e9f;
        grid[i].f = 1e9f;
        grid[i].prev = -1;

        grid[i].walkable =
            ground[i]->texture != ea2 &&
            ground[i]->texture != ea3 &&
            ground[i]->texture != ea1;

        if (building_id[i] != -1)
            grid[i].walkable = 0;
    }

    for (int i=0;i<list.maxid;i++)
    {
        if (!list.data[i].is_active)
            continue;

        int pos = (int)list.data[i].x + max_x*(int)list.data[i].y;
        if (grid[pos].walkable != 0)
        {
            if (list.data[i].skin[1] == '1')
                grid[pos].walkable += 2;

            else if (&list.data[i] != p && list.data[i].skin[1] == 0)
                grid[pos].walkable += 2;
        }
    }
}

int findpath(struct personnages *p)
{
    // === START = unité, GOAL = destination ===
    int start = (int)p->y * max_x + (int)p->x;
    int goal  = (int)p->ordrey * max_x + (int)p->ordrex;

    if (start < 0 || start >= max_x*max_y)
        return -1;

    if (goal < 0 || goal >= max_x*max_y)
        return -1;

    heap_pathfinding.size = 0;
    
    struct path *grid = p->chemin;
    init_grid(p);

    if (!grid[goal].walkable)
    {
        return -1;
    }

    int sx = start % max_x;
    int sy = start / max_x;
    int gx = goal % max_x;
    int gy = goal / max_x;

    grid[start].g = 0;
    grid[start].f = heuristic(sx,sy,gx,gy);

    heap_push(&heap_pathfinding,start,grid);

    while (heap_pathfinding.size)
    {
        int current = heap_pop(&heap_pathfinding,grid);



        if (current == goal)
        {
            p->chemin_is_set = 1;
            return 1;
        }

        int cx = current % max_x;
        int cy = current / max_x;

        for (int d=0; d<8; d++)
        {
            int nx = cx + dir[d][0];
            int ny = cy + dir[d][1];

            if (nx<0 || ny<0 || nx>=max_x || ny>=max_y)
                continue;

            int n = ny*max_x + nx;

            if (grid[n].walkable == 0)
                continue;

            if (abs(altitude(current) - altitude(n)) >= 30)
                continue;

            // bloquer diagonales si coin impossible
            if (d >= 4)
            {
                int ax = cx + dir[d][0];
                int ay = cy;
                int bx = cx;
                int by = cy + dir[d][1];

                int a = ay*max_x + ax;
                int b = by*max_x + bx;

                if (!grid[a].walkable || !grid[b].walkable)
                    continue;
            }

            float base = (d < 4) ? 1.0f : 1.41421356f;
            float g = grid[current].g + base * grid[n].walkable;

            if (g < grid[n].g)
            {
                grid[n].g = g;
                float h = heuristic(nx,ny,gx,gy);
                grid[n].f = g + h;
                grid[n].prev = current;
                heap_push(&heap_pathfinding,n,grid);
            }
        }
    }

    return -1;
}
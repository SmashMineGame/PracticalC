#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
	double x;
	double y;
} point;

typedef struct
{
	size_t verteciesLen;
	point vertecies[];
} polygon;

double point_distance(point a, point b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

void point_print(point p, char *name)
{
	printf("%s: x=%lf; y=%lf;\n", name, p.x, p.y);
}

void point_input(point *p)
{
	double x = 0;
	double y = 0;
	scanf("%lf %lf", &x, &y);

	p->x = x;
	p->y = y;
}

void polygon_input(polygon *poly)
{
	printf("Enter points in format \"x y\":\n");

	for (size_t i = 0; i < poly->verteciesLen; i++)
	{
		point_input(&poly->vertecies[i]);
	}
}

double polygon_perim(const polygon *poly)
{
	double out = 0;

	for (size_t i = 0; i < poly->verteciesLen - 1; i++)
	{
		out += point_distance(poly->vertecies[i], poly->vertecies[i + 1]);
	}

	out += point_distance(poly->vertecies[poly->verteciesLen - 1], poly->vertecies[0]);

	return out;
}

double polygon_area(const polygon *poly)
{
	double out = 0;

	for (size_t i = 1; i < poly->verteciesLen - 1; i++)
	{
		size_t j = i + 1 == poly->verteciesLen ? 0 : i + 1;
		double dx = poly->vertecies[i].x + poly->vertecies[j].x;
		double dy = poly->vertecies[i].y - poly->vertecies[j].y;
		out += dx * dy / 2;
	}

	return fabs(out);
}

int main()
{
	int n = 0;
	printf("Number of Points: ");
	scanf("%d", &n);

	polygon *poly = malloc(sizeof(polygon) + n * sizeof(point));
	poly->verteciesLen = n;
	polygon_input(poly);

	double perimeter = polygon_perim(poly);
	printf("Perimeter: %lf\n", perimeter);

	double area = polygon_area(poly);
	printf("Area: %lf\n", area);

	free(poly);

	return 0;
}
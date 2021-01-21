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
	point start;
	point end;
} line;

double distance(point a, point b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

double length(line l)
{
	return distance(l.start, l.end);
}

void print_point(point p, char *name)
{
	printf("%s: x=%lf; y=%lf;\n", name, p.x, p.y);
}

void input_point(point *p)
{
	double x = 0;
	double y = 0;
	scanf("%lf %lf", &x, &y);

	p->x = x;
	p->y = y;
}

void input_polygon(int n, point *points)
{
	printf("Enter points in format \"x y\":\n");

	for (int i = 0; i < n; i++)
	{
		input_point(&points[i]);
	}
}

double find_perim(int n, const point *points)
{
	double out = 0;

	for (int i = 0; i < n - 1; i++)
	{
		out += distance(points[i], points[i + 1]);
	}

	out += distance(points[n - 1], points[0]);

	return out;
}

double find_area(int n, const point *points)
{
	double out = 0;

	for (int i = 1; i < n - 1; i++)
	{
		int j = i + 1 == n ? 0 : i + 1;
		double dx = points[i].x + points[j].x;
		double dy = points[i].y + points[j].y;
		out += dx * dy / 2;
	}

	return fabs(out);
}

int main()
{
	int n = 0;
	printf("Number of Points: ");
	scanf("%d", &n);

	point *points = calloc(n, sizeof(point));

	input_polygon(n, points);

	double perimeter = find_perim(n, points);
	printf("Perimeter: %lf\n", perimeter);

	double area = find_area(n, points);
	printf("Area: %lf\n", area);

	return 0;
}
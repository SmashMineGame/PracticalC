#include <stdio.h>
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

double slope(line l)
{
	return (l.end.y - l.start.y) / (l.end.x - l.start.x);
}

int point_on_line(line l, point p)
{
	int out = (p.y == slope(l) * (p.x - l.start.x) + l.start.y) ? 1 : 0;
	return out;
}

int main()
{
	point a = {0, 0};
	point b = {3, 4};

	line l = {a, b};

	point test_point_1 = {1.5, 2};
	point test_point_2 = {5, 1};

	printf("\ndistance: %f\n", distance(a, b));
	printf("length:   %f\n", length(l));

	printf("\npoint on line 1: %s\n", point_on_line(l, test_point_1) ? "true" : "false");
	printf("point on line 2: %s\n", point_on_line(l, test_point_2) ? "true" : "false");

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXPOINTS 104
#define MAXPOLYGONS 24
#define RCROSSPRODUCT(pp1,pp2,pp3) \
	(((pp2).x-(pp1).x)*((pp3).y-(pp2).y) \
	-((pp2).y-(pp1).y)*((pp3).x-(pp2).x))

typedef struct {
	int x;
	int y;
}Point;

typedef struct {
	int numPoints;
	Point points[MAXPOINTS];
	char destroyed;
	int bottom;
	int vertices[MAXPOINTS];
	int numVertices;
}Polygon;

double areas, a;
int i, j, x, y, minX, minY, N, temp;
Polygon polygons[MAXPOLYGONS];
int numPolygons;
Point tempPoint, p1, p2, p3;
int numerator1, numerator2;
double denominator1, denominator2, frac1, frac2;

int cmp(const void *e1, const void *e2){
	p1 = *(Point *)e1;
	p2 = *(Point *)e2;
	numerator1 = p1.x - tempPoint.x;
	numerator2 = p2.x - tempPoint.x;
	denominator1 = sqrt((p1.x-tempPoint.x) * (p1.x-tempPoint.x)
					   +(p1.y-tempPoint.y) * (p1.y-tempPoint.y));
	denominator2 = sqrt((p2.x-tempPoint.x) * (p2.x-tempPoint.x)
					   +(p2.y-tempPoint.y) * (p2.y-tempPoint.y));
	frac1 = numerator1 / denominator1;
	frac2 = numerator2 / denominator2;
	
	if (frac1 - frac2 > 0 && frac1 - frac2 < 1e-8){	/* frac1 equals to frac2 */
		if (denominator1 > denominator2) return 1;
		else return -1;
	}
	else{
		if (frac1 > frac2) return -1;
		else return 1;
	}
}

int main(){
	/* freopen("109_data", "r", stdin); */
	/* get polygons */
	while (scanf("%d", &N), N != -1){
		minY = 501;
		for (i = 0; i < N; ++i){
			scanf("%d %d", &x, &y);
			if (y < minY){
				minY = y;
				minX = x;
				j = i;
			}
			else if (y == minY && x < minX){
				minX = x;
				j = i;				
			}
			polygons[numPolygons].points[i].x = x;
			polygons[numPolygons].points[i].y = y; 
		}
		polygons[numPolygons].numPoints = N;
		polygons[numPolygons].bottom = j;
		++numPolygons;
	}
	
	/* calculate convex hull */
	for (i = 0; i < numPolygons; ++i){
		/* swap the first point with bottom point */
		tempPoint = polygons[i].points[polygons[i].bottom];
		polygons[i].points[polygons[i].bottom] = polygons[i].points[0];
		polygons[i].points[0] = tempPoint;
		/* sort points by angle with bottom */
		qsort(polygons[i].points + 1, 
			  polygons[i].numPoints - 1,
		 	  sizeof(Point), cmp);
		/* Graham's algorithm */
		polygons[i].vertices[0] = 0;
		polygons[i].vertices[1] = 1;
		polygons[i].vertices[2] = 2;	/* temp */
		polygons[i].numVertices = 3;
		j = 3;
		while (j < polygons[i].numPoints){
			p1 = polygons[i].points[
				 polygons[i].vertices[polygons[i].numVertices - 2]
				 ];
			p2 = polygons[i].points[
				 polygons[i].vertices[polygons[i].numVertices - 1]
				 ];
			p3 = polygons[i].points[j];
			if (RCROSSPRODUCT(p1, p2, p3) < 0)
				--polygons[i].numVertices;
			else{
				polygons[i].vertices[polygons[i].numVertices++] = j;
				++j;
			}
		}
	}
	/* get missiles and using point in polygon algorithm */
	while (scanf("%d %d", &tempPoint.x, &tempPoint.y) != EOF){
		for (x = 0; x < numPolygons; ++x){
			i = 1;
			j = polygons[x].vertices[polygons[x].numVertices - 1];
			if (RCROSSPRODUCT(polygons[x].points[i], 
							  polygons[x].points[0],
							  tempPoint) > 0
				|| RCROSSPRODUCT(tempPoint, 
							  polygons[x].points[0],
							  polygons[x].points[j]) > 0){
				continue;
			}
			j = polygons[x].numVertices - 1;
			while (j != i + 1){
				y = (i + j) >> 1;
				temp = RCROSSPRODUCT(polygons[x].points[
					   	   polygons[x].vertices[y]], 
						   polygons[x].points[0],
						   tempPoint);
				if (temp < 0)
						i = y;
				else if (temp > 0)
						j = y;
				else{
					i = y;
					j = (y + 1) % polygons[x].numVertices;
					break;
				}
			}
			if (RCROSSPRODUCT(tempPoint, polygons[x].points[
								polygons[x].vertices[i]],
								polygons[x].points[
								polygons[x].vertices[j]]) >= 0)
				polygons[x].destroyed = 1;
		}
	}
	/* calculate areas */
	for (i = 0; i < numPolygons; ++i){
		if (!polygons[i].destroyed) continue;
		a = 0.0;
		polygons[i].vertices[polygons[i].numVertices] = 0;
		for (j = 1; j <= polygons[i].numVertices; ++j)
			a += (polygons[i].points[polygons[i].vertices[j - 1]].x 
				* polygons[i].points[polygons[i].vertices[j]].y
				- polygons[i].points[polygons[i].vertices[j]].x
				* polygons[i].points[polygons[i].vertices[j - 1]].y);
		a /= 2;
		/* add area to sum of areas */
		areas += a;
	}
	printf("%.2lf\n", areas);
	return 0;
}


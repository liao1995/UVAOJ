#include <stdio.h>
#define SQRT3D2 0.8660254f /* sqrt(3)/2 */
#define OMSQRT3D2 0.1339746 /* 1-sqrt(3)/2 */

double da, db;
int il, ia, ib, iGrid, iSkew;
int temp;

int main(){
	/* freopen("121_data", "r", stdin); */
	while (scanf("%lf%lf", &da, &db) != EOF){
		if (da < 1.0f || db < 1.0f){
			printf("0 grid\n");
			continue;
		}
		ia = (int)da;
		ib = (int)db;
		iGrid = ia * ib;
		/* a * b */
		for (il = ib; ;++il)
			if (SQRT3D2 * il + OMSQRT3D2 > db)
				break;
		--il;
		iSkew = ia * il;
		if (da - ia < 0.5)
			iSkew -= (il >> 1);
		/* b * a */
		for (il = ia; ; ++il)
			if (SQRT3D2 * il + OMSQRT3D2 > da)
				break;
		--il;
		temp = ib * il;
		if (db - ib < 0.5)
			temp -= (il>>1);
		iSkew = iSkew > temp ? iSkew : temp;
		if (iSkew > iGrid)
			printf("%d skew\n", iSkew);
		else
			printf("%d grid\n", iGrid); 
	}
	return 0;
}

#include "refleksi.h"
#include <stdio.h>

titik reflectDot(titik p, char axis, titik pAxis){
	titik pResult;
	pResult.x = 0;
	pResult.y = 0;
	if(axis == 'x'){
		if(p.y > pAxis.y){
			int diff = p.y - pAxis.y;
			pResult.y = pAxis.y - diff;
			pResult.x = p.x;
		}
		else {
			int diff = pAxis.y - p.y;
			pResult.y = pAxis.y + diff;
			pResult.x = p.x;
		}
	}
	else if(axis == 'y'){
		if(p.x > pAxis.x){
			int diff = p.x - pAxis.x;
			pResult.x = pAxis.x - diff;
			pResult.y = p.y;
		}
		else {
			int diff = pAxis.x - p.x;
			pResult.x = pAxis.x + diff;
			pResult.y = p.y;
		}
	}
	return pResult;
}

//mengembalikan array titik yang sudah dicerminkan oleh pAxis pada sumbu axis
void reflectDotArray(titik* p, int size, char axis, titik pAxis){
	//titik* pResult;
	for(int i=0; i<size; i++){
		p[i] = reflectDot(p[i], axis, pAxis);
	}
}

int main(){
	titik p[3];
	p[0].x = 4;
	p[0].y = 6;
	p[1].x = 9;
	p[1].y = 1;
	p[2].x = 0;
	p[2].y = 10;
	titik pAxis;
	pAxis.x = 10;
	pAxis.y = 10;
	titik pResult = reflectDot(p[0], 'x', pAxis);
	printf("%d, %d\n", pResult.x, pResult.y);
	pResult = reflectDot(p[0], 'y', pAxis);
	printf("%d, %d\n", pResult.x, pResult.y);

	reflectDotArray(p, 3, 'x', pAxis);
	for(int i=0; i<3; i++){
		printf("pX array %d, %d\n", p[i].x, p[i].y);
	}

	reflectDotArray(p, 3, 'y', pAxis);
	for(int i=0; i<3; i++){
		printf("pY array %d, %d\n", p[i].x, p[i].y);
	}
	return 0;
}
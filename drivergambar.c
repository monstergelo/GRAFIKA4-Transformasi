
#include "gambar.h"

int main() {
	init_fb();

	warna cRed ={255,25,25,255};
	warna cGreen = {25,255,25,255};
	warna cBlue = {25,25,255,255};
	
	titik pFirst = {0,0};
	titik pLast = {1366,700};

	titik ekorPesawatAtas[] = {{30,45}, {30,70}, {55,65}, {45,45}};
	titik ekorPesawatBawah[] = {{30,70}, {45,90}, {120,90}, {120,65}, {55,65}};

	titik badanPesawat[] = {{120,65}, {220,65}, {220,90}, {120, 90}};
	titik sayapAtas[] = {{100,20}, {115,20}, {135, 65}, {110,65}};
	titik sayapBawah[] = {{100,90}, {125,90}, {110, 140}, {85, 140}};
	titik kepalaPesawat[] = {{220,65}, {250,70}, {255, 90}, {220, 90}};
	titik pMulutPesawat = {255, 82};
	
	titik badanTank[] = {{100,600}, {200,600}, {220,570}, {80,570}};
	
	titik pShutterCircle = {150,570};
	titik tankGun[] = {{143,550}, {157,550}, {157,510}, {144,510}};
	titik peluru[] = {{150,400},{155,405},{155,430},{145,430}, {145,405}};

	while (1) {
		refreshBuffer(pFirst, pLast);

		bufferDrawPlaneSolid(&ekorPesawatAtas, cRed, cRed, 4);
		bufferDrawPlaneSolid(&ekorPesawatBawah, cRed, cRed, 5);
		bufferDrawPlaneSolid(&badanPesawat, cRed, cRed, 4);
		bufferDrawPlaneSolid(&sayapAtas, cRed, cRed, 4);
		bufferDrawPlaneSolid(&kepalaPesawat, cRed, cRed, 4);
		bufferDrawCircle(pMulutPesawat, 9, cRed);
		//bufferDrawPlane(&sayapBawah, cRed, 4);
		bufferDrawPlaneSolid(&badanTank, cBlue, cBlue, 4);
		bufferDrawCircle(pShutterCircle, 20, cBlue);
		bufferDrawPlaneSolid(&tankGun, cBlue, cBlue, 4);

		bufferDrawPlaneSolid(&peluru, cGreen, cGreen, 5);
		loadBuffer();
		//p1.x+=10; p2.y+= 30;
		usleep(300000);
	}
}
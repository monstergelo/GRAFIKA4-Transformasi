#include "tabrakan.h"
#include "tembakan.h"
#include "rotasi.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

//cek apakah terdapat peluru yang berada sejauh offset dari pesawat
//jika iya kedua objek memiliki status true

#define PI 3.14159265

extern int pesawatterakhir;
extern int peluruterakhir;
extern int objekterakhir;
tembakan prime;

extern objekTabrak pesawat[10];
extern objekTabrak peluru[10];
extern objekTabrak objek[10];


void cekTabrakanObjek(int offset){
	int qq = pesawatterakhir;
	int ww = peluruterakhir;

	for (int i =0; i<qq ; i++){
		for (int j =0; j<ww ; j++){

			float jarak = sqrt((pesawat[i].posisi.x-peluru[j].posisi.x)*(pesawat[i].posisi.x-peluru[j].posisi.x)+(pesawat[i].posisi.y-peluru[j].posisi.y)*(pesawat[i].posisi.y-peluru[j].posisi.y));

			if (jarak<=offset){
				pesawat[i].status=1;
				peluru[j].status=1;

			}
		}
	}
}




//hilangkan objek pesawat dari memori
void hancurObjek(objekTabrak* o){
	o->status=-1;
}


//ganti posisi seluruh objek sesuai kecepatan dan arah
void jalanObjek(){
	int qq = pesawatterakhir;
	int ww = peluruterakhir;
	int tt = objekterakhir;
	titik putar = {600,1050};

	double val = PI / 180.0;

	//jalanpesawat==========================================================================================
	for (int i =0; i<10 ; i++){

		if(pesawat[i].status==0){
			titik temp = pesawat[i].posisi;
			titik* temp2 = pesawat[i].citra;
			pesawat[i].posisi = rotasi(putar, temp, 1);
			//pesawat[i].citra = rotasibanyak(putar, temp2, 1, 8);
		}
	}
	//jalanpeluru==========================================================================================
	for (int i =0; i<10 ; i++){
		if(peluru[i].status==0){
		peluru[i].posisi.x = peluru[i].posisi.x+(cos(peluru[i].arah*val)*peluru[i].kecepatan);
		peluru[i].posisi.y = peluru[i].posisi.y-(sin(peluru[i].arah*val)*peluru[i].kecepatan);
		}
	}

	//jalanobjek==========================================================================================
	for (int i =0; i<10 ; i++){
		if(objek[i].status==0){
		objek[i].posisi.x = objek[i].posisi.x+(cos(objek[i].arah*val)*objek[i].kecepatan);
		objek[i].posisi.y = objek[i].posisi.y-(sin(objek[i].arah*val)*objek[i].kecepatan);
		}
	}
}

void setupCitraPesawat(objekTabrak *pesawat) {
	pesawat->citra = (titik*) malloc(8 * sizeof(titik));
	titik* citra = pesawat->citra;
	int xp = pesawat->posisi.x; int yp = pesawat->posisi.y;
	citra[0].x = -100; citra[0].y = -90;
	citra[1].x = -75; citra[1].y = -90;
	citra[2].x = -50; citra[2].y = -75;
	citra[3].x = 50; citra[3].y = -75;
	citra[4].x = 75; citra[4].y = -50;
	citra[5].x = 50, citra[5].y = -25;
	citra[6].x = -50; citra[6].y = -25;
	citra[7].x = -100; citra[7].y = -75;
}

void setupCitraPeluru(objekTabrak *peluru) {
	peluru->citra = (titik*) malloc(5 * sizeof(titik));
	titik* citra = peluru->citra;
	int xp = peluru->posisi.x; int yp = peluru->posisi.y;
	citra[0].x = -10; citra[0].y = 25;
	citra[1].x = -10; citra[1].y = 0;
	citra[2].x = 0; citra[2].y = -25;
	citra[3].x = 10; citra[3].y = 0;
	citra[4].x = 10; citra[4].y = 25;
}

void setupCitraPecah(objekTabrak *pecah, int type) {
	pecah->citra = (titik*) malloc(5 * sizeof(titik));
	int xp = pecah->posisi.x; int yp = pecah->posisi.y;
	titik* citra = pecah->citra;
	int xof = xp-600;
	int yof = yp-200;

	if(type == 0)
	{
		titik puing[] = {{xof,yof+25}, {xof,yof+50}, {xof+25,yof+45}, {xof+15,yof+25}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 1)
	{
		titik puing[] = {{xof+90,yof+45}, {xof+190,yof+45}, {xof+190,yof+70}, {xof+90, yof+70}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 2)
	{
		titik puing[] = {{xof+70,yof}, {xof+85,yof}, {xof+105, yof+45}, {xof+80,yof+45}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 3)
	{
		titik puing[] = {{xof+70,yof+70}, {xof+95,yof+70}, {xof+80, yof+120}, {xof+55, yof+120}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
	else if(type == 4)
	{
		titik puing[] = {{xof+190,yof+45}, {xof+220,yof+50}, {xof+225, yof+70}, {xof+190, yof+70}};
		citra[0] = puing[0];
		citra[1] = puing[1];
		citra[2] = puing[2];
		citra[3] = puing[3];
	}
}

//membuat objek baru(a=pesawat; b=peluru) pada posisi p
void spawnObjek(char t, titik p){
	if (t=='a'){

		pesawat[pesawatterakhir].posisi = p;
		pesawat[pesawatterakhir].arah = 0;
		pesawat[pesawatterakhir].kecepatan = 5;
		pesawat[pesawatterakhir].status = 0;
		setupCitraPesawat(&pesawat[pesawatterakhir]);
		// Set
		pesawatterakhir++;

	} else if (t=='b') {
		peluru[peluruterakhir].posisi = p;
		peluru[peluruterakhir].kecepatan = 25;
		peluru[peluruterakhir].arah = 90 - prime.kemiringan;
		peluru[peluruterakhir].status = 0;
		setupCitraPeluru(&peluru[peluruterakhir]);
		peluruterakhir++;
	}

	else if (t=='z') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 25;
		objek[objekterakhir].arah = 270;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 0);
		objekterakhir++;
	}
	else if (t=='x') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 25;
		objek[objekterakhir].arah = 260;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 1);
		objekterakhir++;
	}
	else if (t=='y') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 25;
		objek[objekterakhir].arah = 300;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 2);
		objekterakhir++;
	}
	else if (t=='w') {
		objek[objekterakhir].posisi = p;
		objek[objekterakhir].kecepatan = 25;
		objek[objekterakhir].arah = 240;
		objek[objekterakhir].status = 0;
		setupCitraPecah(&objek[objekterakhir], 3);
		objekterakhir++;
	}
}

void gambarHancur(titik p) {

	//titik pe = {p.x,p.y};
	static int ii = 0;
	static int stage = 0;
	//titik pd = {p.x+10,p.y-10};
	if(ii==0 && stage == 0){
		titik pp = p;
		spawnObjek('z', p);
		p.x = pp.x+5; p.y =pp.y+9;

		spawnObjek('x', p);
		p.x = pp.x-20; p.y =pp.y-14;

		spawnObjek('y', p);
		p.x = pp.x-5; p.y =pp.y+20;

		spawnObjek('w', p);
	}

	if(ii<10 && stage == 0){
		warna c = {255, 10+20*ii, 0, 255};
		bufferDrawCircle(p, 10-1*ii, c);
		ii++;
	}
	else{
		stage = 1;
	}


	if(ii>0 && stage == 1){
		warna c = {255, 200-15*ii, 0, 255};
		bufferDrawCircle(p, 20-2*ii, c);
		ii--;
	}
}


//**************************************************************************************************
void gambarObjek() {
	warna green = {1, 255, 1, 255};
	warna red = {255, 1, 1, 255};
	warna black = {0, 0, 0, 255};

	// Draw airplane
	for (int i = 0; i < pesawatterakhir; i++) {
		if (pesawat[i].status == 0) {
			bufferDrawPlaneSolidCitra(pesawat[i].citra, pesawat[i].posisi, green, red, 8);
		}
	}

	// Draw bullet
	for (int i = 0; i < peluruterakhir; i++) {
		if (peluru[i].status == 0) {
			bufferDrawPlaneSolidCitra(peluru[i].citra, peluru[i].posisi, green, red, 5);
		}
	}

	//draw debris
	for (int i = 0; i < objekterakhir; i++) {
		if (objek[i].status == 0) {
			bufferDrawPlaneSolidCitra(objek[i].citra, objek[i].posisi, green, red, 4);
		}
	}
}

//**************************************************************************************************

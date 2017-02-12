#include "tabrakan.h"
#include "tembakan.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

//cek apakah terdapat peluru yang berada sejauh offset dari pesawat
//jika iya kedua objek memiliki status true

#define PI 3.14159265

extern int pesawatterakhir;
extern int peluruterakhir;
tembakan prime;
extern objekTabrak pesawat[10];
extern objekTabrak peluru[10];


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

	double val = PI / 180.0;

	for (int i =0; i<qq ; i++){

		if(pesawat[i].status==0){

			if(pesawat[i].arah<=180){
				pesawat[i].posisi.x = pesawat[i].posisi.x+(cos(pesawat[i].arah*val)*pesawat[i].kecepatan);
				pesawat[i].posisi.y = pesawat[i].posisi.y+(sin(pesawat[i].arah*val)*pesawat[i].kecepatan);
			}else{
				pesawat[i].posisi.x = pesawat[i].posisi.x+(cos(pesawat[i].arah*val)*pesawat[i].kecepatan);
				pesawat[i].posisi.y = pesawat[i].posisi.y-(sin(pesawat[i].arah*val)*pesawat[i].kecepatan);
			}
		}
	}


	for (int i =0; i<ww ; i++){
		if(peluru[i].status==0){
		peluru[i].posisi.x = peluru[i].posisi.x+(cos(peluru[i].arah*val)*peluru[i].kecepatan);
		peluru[i].posisi.y = peluru[i].posisi.y-(sin(peluru[i].arah*val)*peluru[i].kecepatan);
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
}

void gambarHancur(titik p) {

	//titik pe = {p.x,p.y};
	static int ii = 0;
	static int stage = 0;
	//titik pd = {p.x+10,p.y-10};
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
	/* Use this one for bigger explosion
	 *
	for (i=0;i<10;i++) {
		usleep(50000-(i*5000));
		warna c = {255, 10+20*i, 0, 255};
		bufferDrawCircle(p, 20-2*i, c);
	}
	for (;i>=0;i--) {
		usleep(100000-(i*10000));
		warna c = {255, 200-15*i, 0, 255};
		bufferDrawCircle(p, 40-4*i, c);
	}
	* */
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
}

//**************************************************************************************************

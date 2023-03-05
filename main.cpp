#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctype.h>
#include <Windows.h>

using namespace std;

void printer(double array[][25], int valv[25], int valh[25], string ver, int x, int max,
	int func, int vermax, double array2[][25], double& maxi, int& keyh, bool zway, string hor[25]) {
	int i, p = 2, leftspace, rightspace, j;
	char spacee = ' ', linee = '-';

	if(func==1 && x==0){ //output top
		p=8;
		cout << string(p, spacee);
		for (i = 0; i < max; i++) {
			cout << " " << valh[i] << string(p, spacee);
		}
		cout << "\n" << string(p + 1, spacee);
		for (i = 0; i < max; i++) {
			cout << hor[i] << string(p, spacee);
		}
		cout << "|  \n";
		p=2;
	}
	// output values
	if (func == 1) { if (0 == x) { cout << string(7 + 10 * (max + 1), linee); } cout << "\n" << valv[x] << " " << ver << "|  "; }

	for (i = 0; i <= max; i++) {
		leftspace = 0; rightspace = 4; p = 2;

		if (func == 2) {
			array[0][i] = 0;
			for (j = 0; j <= vermax; j++) {
				array[0][i] += valv[j] * array2[j][i];
			}
		}

		if (func == 3) {
			array[0][i] = valh[i] - array2[0][i];
		}

		if (i == max && func != 3) { cout << "  | "; }
		if (array[x][i] >= 0) { leftspace++; }
		if (array[x][i]<10 && array[x][i]>-10) { leftspace++; }
		if (ceilf(array[x][i]) == array[x][i]) {
			p = 0; rightspace += 3;cout;
		}
		cout << string(leftspace, spacee) << fixed << setprecision(p) << array[x][i] << string(rightspace, spacee);

		if (func == 3) {
			if (zway == true) {
				if (array[0][i] > maxi) {
					maxi = array[0][i];
					keyh = i;
				}
			}
			else {
				if (array[0][i] < maxi) {
					maxi = array[0][i];
					keyh = i;
				}
			}
		}
	}
	if (func == 1 && vermax == x) { cout << "\n" << string(7 + 10 * (max + 1), linee); }
}

void bottom(double dizi[10][25], int valv[25], int valh[25], string ver[25], string hor[25], bool& score, int& max, bool& zway,
	 double zj[1][25], double cz[1][25], int vermax, bool& oldZway, int& rcounter, bool& rmin, bool& rem, bool& integ, double& intempo,
	 double tempdizi[25], int& keyh, bool& passint, int tempanswer [10][25], int& nen) {
	int i, keyv = 0, j, lcount = 0, intemp=0;
	double maxi = 0, multiply, key = 0, temp = 0, tempo = 0, intempor=0;

	// output Zj
	cout << "\n  Zj|  ";
	printer(zj, valv, valh, ver[0], 0, max, 2, vermax, dizi, maxi, keyh, zway, hor);
	// output Cj-Zj
	cout << "\nC-Zj|  ";
	printer(cz, valv, valh, ver[0], 0, max - 1, 3, vermax, zj, maxi, keyh, zway, hor);

	if (maxi == 0) { 					//checks if loop has ended
		//turn to integer
		if(integ==true){
			intemp=dizi[0][max];
			if(dizi[0][max]==intemp&&passint==true){goto sc;}
			dizi[0][max]=intemp; intempor=tempdizi[keyh]*intemp;
			if(passint==true){passint=false; goto end;}
			
			if(intempo!=intempor){
				tempanswer[nen][0]=keyh;
				tempanswer[nen][1]=dizi[0][max];
				cout << "\n\n 	"<<hor[keyh]<<": "<<tempanswer[nen][1] << " New Sequence..\n";
				nen++;
				passint=true;
				for(i=0;i<max;i++){
					while(dizi[0][i]==0){i++;}
					dizi[0][i]=tempdizi[i];
				}
				dizi[0][max]=intempo-intempor;
				intempo=dizi[0][max];
				valh[keyh]=0;
				dizi[0][keyh]=0;
				valv[0]=0;
				ver[0]=hor[max-1];
			}goto end;}
		sc:score = true; if (rmin == true) { rmin = false; score = false; rem = true; if (oldZway == true) { zway = true; } }
		goto end;
	}
	maxi = 0;
	// finds keyv
	for (i = 0; i <= vermax; i++) {
		while (dizi[i][keyh] <= 0) { if (i == vermax + 1) { goto skip; }i++; }
		temp = dizi[i][max] / dizi[i][keyh];
		if (i == 0) { tempo = temp; }
		if (tempo > temp) { keyv = i; tempo = temp; }
	}

skip:								// calculates keyv line
	key = dizi[keyv][keyh];
	for (i = 0; i <= max; i++) {
		dizi[keyv][i] = dizi[keyv][i] / key;
	}
	// calculates other lines
	for (i = 0; i <= vermax; i++) {
		if (i == keyv) { i++; }
		multiply = dizi[i][keyh];
		for (j = 0; j <= max; j++) {
			dizi[i][j] = dizi[i][j] - multiply * dizi[keyv][j];
		}
	}
	// sets new ver according to keyv and keyh
	valv[keyv] = valh[keyh];
	ver[keyv] = hor[keyh];
end:cout << "\n\n\n";
}

void remover(double dizi[10][25], string hor[25], string ver[25], int valh[25], int valv[25],
	int& max, int vermax, int rcounter, bool& rem, double zj[1][25], double cz[1][25], int rmark[25], double tempvalh[25], int xmax) {
	int i, j, u, y = 0;
	bool start = false;
	rem = false;
	// copy old valh to current
	for (i = 0; i <= max; i++) {
		valh[i] = tempvalh[i];
	}
	//remove R columns from array
	u = xmax;
	for (i = 0; i <= max; i++) {
		if (rmark[i] == 1) { start = true; }
		if (rmark[i] == 0 && start == true) {
			valh[u] = valh[i]; hor[u] = hor[i];
			for (j = 0; j <= vermax + 1; j++) {
				dizi[j][u] = dizi[j][i];
			}
			u++;
		}
	}
	//copy valh to valv
	for (i = 0; i <= vermax + 1; i++) {
		for (j = 0; j <= max; j++) {
			if (ver[i] == hor[j]) { valv[i] = valh[j]; }
		}
	}
	max -= rcounter;
}

int main() {
	char input[250] = {};			//inputted characters
	string hor[25] = {};			//Horizontal line S1 R -V etc.
	string ver[25] = {};			//Vertical line of hor
	string temphor[25] = {};		//temporary hor till i find x length
	int valh[25] = {};			//horizontal values of hor
	int valv[25] = {};			//vertical values of ver
	double dizit[25] = {};			//temporary values of > < =
	int ci[10] = {};			//values after > < =
	double tempvalh[25] = {};			//store original values of valh for use later
	int rmarker[25] = {};			//mark r columns
	int rmark[25] = {};			//extend rmarker array to fit max
	double dizi[10][25] = {};		//midline array values
	double tempdizi[25]={};
	double zj[1][25] = {};			//Zj line
	double cz[1][25] = {};			//Cj-Zj line	
	int tempanswer[10][25]={};

	int i = 0, j = 0, y = 0, d = 0, xassigner = 0, xcounter = 0, max = 0, hori = 0, ct = 0, vermax = 0, keyh=0,
		z = 0, rcounter = 0, scount = 1, rcount = 1, xmax = 0, a = 0, b = 0, nen=0;
	double fre, intempo=0; int free;
	string convert = "", stemp, tempS;
	char spacee = ' '; char ent = 'a';

	bool zway = false, rmin = false, oldZway = false, rem = false, score = false, db = true, integ = false, passint=true;
	// zway= if zmax or zmin | rmin= if rmin or normal method | oldZway= if zway was max before turning min because of rmin |
	// rem= if should start remover function | score= if loop has ended | integ= for integer values

	cout << "\n Enter the equations. Example: \n\n 	Zmin=6x1+1x2 6x1+2x2=5 8x1+6x2>12 2x1+4x2<8 \n\n 	Zmax=6x1+8x2 30x1+20x2<300 5x1+10x2<110";
	cout << "\n\n 	Zmax=8x1+60x2+15x3+2x4+20x5+100x6+80x7+200x8+6x9 0.2x1+1.2x2+0.8x3+0.1x4+2x5+3.5x6+1.5x7+4x8+2x9<20 -t \n\n";
	cout << " Options:	-t	for integer values. Press enter for next step \n\n";
	// input the characters

	while (input[i - a] != '\n') {
		cin >> noskipws >> input[i];
		if(input[i-a]=='t'||input[i-a]=='T'){integ=true;}
		if ((input[i - a] == 'x' || input[i - a] == 'X') && isdigit(input[i])) {
			// find numbers after x
			stemp = "";
			stemp = stemp + input[i];
			xassigner = stod(stemp) - 1;
			// set array 0 if x skipped
			while (xcounter != xassigner) {
				if (d == 0 && db == true) { valh[xcounter] = 0; }
				else { dizi[d][xcounter] = 0; }
				xcounter++;
			}
			// find numbers before x
			j = 2;
			while (isdigit(input[i - j])||input[i-j]=='.') {
				convert = input[i - j] + convert;
				j++;
			}
			// create array with numbers before x
			if (d == 0 && db == true) {
				valh[xassigner] = stod(convert);
				if (input[i - j - 1] == '-') { valh[xassigner] = 0 - valh[xassigner]; }
			}
			else {
				dizi[d][xassigner] = stod(convert);
				if (input[i - j - 1] == '-') { dizi[d][xassigner] = 0 - dizi[d][xassigner]; }
			}
			convert = "";
			//find max x
			if (max < xassigner) { max = xassigner; }
			xcounter++;
		}
		//check chars > < =
		if (input[i - a] == '<' || input[i - a] == '>' || input[i - a] == '=' && isdigit(input[i - b])) {
			dizit[hori] = 1;
			switch (input[i - a]) {

			case '<':
				tempS = to_string(scount); scount++; temphor[hori] = "S" + tempS;
				break;

			case '>':
				tempS = to_string(rcount); rcount++; temphor[hori] = "R" + tempS; rmin = true; rmarker[hori] = 1; rcounter++;
				 hori++; temphor[hori] = "V" + tempS; dizit[hori] = -1;
				break;

			case '=':
				tempS = to_string(rcount); rcount++; temphor[hori] = "R" + tempS; rmin = true; rmarker[hori] = 1; rcounter++;
				break;
			}
			// record the place of val which comes after ><= to find it later
			ci[ct] = i; ct++;	hori++;
		}
		//space moves to next line
		if (isspace(input[i - a]) && isdigit(input[i - b]) && isdigit(input[i])) { xcounter = 0; d++; if (d == 1 && db == true) { d--; db = false; } }
		if (i == 2) { a++; b += 2; }
		i++;
	}

	vermax = d; max += 1; xmax = max; max += hori;
	
	//store dizi
	for(i=0;i<=max;i++){
		tempdizi[i]=dizi[0][i];
	}
	// find val which was recorded above
	j = 0;
	for (i = 0; i < ct; i++) {
		tempS = "";
		y = 0;
		while (isdigit(input[ci[i] + y])||input[ci[i]+y]=='.') {
			tempS = tempS + input[ci[i] + y];
			y++;
		}
		dizi[i][max] = stod(tempS);
	}
	intempo=dizi[0][max];
	// check if zmax or zmin
	if (strstr(input, "a") || strstr(input, "A")) {
		zway = true; oldZway = true; if (rmin == true) { zway = false; }
	}
	else if (strstr(input, "i") || strstr(input, "I")) {
		zway = false;
	}
	// set hor
	tempS = "";
	for (i = 0; i < xmax; i++) {
		tempS = to_string(i + 1);
		hor[i] = "X" + tempS;
	}
	for (i = xmax; i <= xmax + hori; i++) {
		hor[i] = temphor[i - xmax];
	}
	// set ver
	y = 0;
	for (i = 0; i <= vermax + 1; i++) {
		if (dizit[i + y] == -1) { y++; }
		ver[i] = hor[i + xmax + y];
		valv[i] = 0;
	}
	//store valh
	if (rmin == true) {
		for (i = 0; i <= xmax + hori; i++) {
			tempvalh[i] = valh[i];
		}
	}
	//set rest of valh 0
	y = 0;
	if (rmin == true) { y = xmax; }
	for (i = xmax - y; i <= xmax; i++) {
		valh[i] = 0;
	}
	//set valh and valv of rmin
	if (rmin == true) {
		y = 0;
		for (i = 0; i <= max; i++) {
			if (dizit[i] == -1) { y++; }
			if (rmarker[i] == 1) { valh[i + xmax] = 1; valv[i - y] = 1; }
		}
	}
	//extends rmarker with 0 values
	for (i = 0; i < vermax; i++) {
		rmark[i] = 0;
	}

	for (i = vermax; i < max; i++) {
		rmark[i] = rmarker[i - vermax];
	}
	// add values of > < = to midline
	y = 0;
	for (i = xmax; i < max; i++) {
		if (dizit[i - xmax] == -1) { y -= 1; }
		dizi[i - xmax + y][i] = dizit[i - xmax];
	}
	// start the loop
	do {
		if(integ==true){
			dizi[0][max]=round(dizi[0][max]*10000)/10000.0;
			for(i=0;i<max;i++){
				dizi[0][i]=round(dizi[0][i]*10000)/10000.0;
				if(dizi[0][i]>dizi[0][max]){valh[i]=0;dizi[0][i]=0;}
			}
		}
		for (i = 0; i <= vermax; i++) {
			printer(dizi, valv, valh, ver[i], i, max, 1, vermax, zj, fre, free, zway, hor);
		}
		bottom(dizi, valv, valh, ver, hor, score, max, zway, zj, cz, vermax, oldZway, rcounter, rmin, rem, integ, intempo,
		 tempdizi, keyh, passint, tempanswer, nen);
		if (rem == true) { remover(dizi, hor, ver, valh, valv, max, vermax, rcounter, rem, zj, cz, rmark, tempvalh, xmax); }
		while (ent != '\n') { cin >> ent; } ent = 'a';
	} while (score != true);

	// output the answers
	cout << "\nConcluded:\n";

	if(integ==true){
		tempanswer[nen][0]=keyh;
		tempanswer[nen][1]=dizi[0][max];
		for(i=0;i<=nen;i++){
			cout <<"\n" <<hor[tempanswer[i][0]]<<": "<< tempanswer[i][1];
		}
	}
	else{
		if (zway == true) { cout << "Zmax="; }
		else { cout << "Zmin="; }
		cout << zj[0][max] << "\n";
		for (i = 0; i <= vermax; i++) {
			cout << ver[i] << "=" << dizi[i][max] << "\n";
		}
	} cout << "\n";

	while (ent != '\n') { cin >> ent; }
	return 0;
}

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

	//func: 1 top & mid, 2 Zj, 3 Cj-Zj

	//output top
	if (func == 1 && x == 0) {
		p = 8;
		cout << string(p, spacee);
		for (i = 0; i < max; i++) {
			cout << " " << valh[i] << string(p, spacee);
		}
		cout << "\n" << string(p + 1, spacee);
		for (i = 0; i < max; i++) {
			cout << hor[i] << string(p, spacee);
		}
		cout << "|  \n";
		p = 2;
	}

	if (func == 1) { if (0 == x) { cout << string(7 + 10 * (max + 1), linee); } cout << "\n" << valv[x] << " " << ver << "|  "; }

	// output mid/bottom
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
		if (ceil(array[x][i]) == array[x][i]) {
			p = 0; rightspace += 3; cout;
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

void bottom(double mid[10][25], int valv[25], int valh[25], string ver[25], string hor[25], bool& score, int& max, bool& zway,
	double zj[1][25], double cz[1][25], int vermax, bool& oldZway, int& rcounter, bool& rmin, bool& rem, bool& integ, double& intempo,
	double tempdizi[25], int& keyh, bool& passint, int tempanswer[10][25], int& k) {
	int i, keyv = 0, j, lcount = 0, intemp = 0;
	double maxi = 0, multiply, key = 0, temp = 0, tempo = 0, intempor = 0;

	// output Zj
	cout << "\n  Zj|  ";
	printer(zj, valv, valh, ver[0], 0, max, 2, vermax, mid, maxi, keyh, zway, hor);
	// output Cj-Zj
	cout << "\nC-Zj|  ";
	printer(cz, valv, valh, ver[0], 0, max - 1, 3, vermax, zj, maxi, keyh, zway, hor);

	//checks if loop should stop or continue with new sequence
	if (maxi == 0) {
		//turn to integer
		if (integ == true) {
			intemp = mid[0][max];
			if (mid[0][max] == intemp && passint == true) { goto sc; }
			mid[0][max] = intemp; intempor = tempdizi[keyh] * intemp;
			if (passint == true) { passint = false; goto end; }

			if (intempo != intempor) {
				tempanswer[k][0] = keyh;
				tempanswer[k][1] = mid[0][max];
				cout << "\n\n 	" << hor[keyh] << ": " << tempanswer[k][1] << " New Sequence..\n";
				k++;
				passint = true;
				for (i = 0; i < max; i++) {
					while (mid[0][i] == 0) { i++; }
					mid[0][i] = tempdizi[i];
				}
				mid[0][max] = intempo - intempor;
				intempo = mid[0][max];
				valh[keyh] = 0;
				mid[0][keyh] = 0;
				valv[0] = 0;
				ver[0] = hor[max - 1];
			}goto end;
		}
	sc:score = true; if (rmin == true) { rmin = false; score = false; rem = true; if (oldZway == true) { zway = true; } }
		goto end;
	}
	maxi = 0;

	// finds keyv
	for (i = 0; i <= vermax; i++) {
		while (mid[i][keyh] <= 0) { if (i == vermax + 1) { goto skip; }i++; }
		temp = mid[i][max] / mid[i][keyh];
		if (i == 0) { tempo = temp; }
		if (tempo > temp) { keyv = i; tempo = temp; }
	}

skip:
	// calculates keyv line
	key = mid[keyv][keyh];
	for (i = 0; i <= max; i++) {
		mid[keyv][i] = mid[keyv][i] / key;
	}
	// calculates other lines
	for (i = 0; i <= vermax; i++) {
		if (i == keyv) { i++; }
		multiply = mid[i][keyh];
		for (j = 0; j <= max; j++) {
			mid[i][j] = mid[i][j] - multiply * mid[keyv][j];
		}
	}
	// set new ver
	valv[keyv] = valh[keyh];
	ver[keyv] = hor[keyh];
end:cout << "\n\n\n";
}

void remover(double mid[10][25], string hor[25], string ver[25], int valh[25], int valv[25],
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
				mid[j][u] = mid[j][i];
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
	string hor[25] = {};			//Horizontal line of Cj values (S R -V)
	string ver[25] = {};			//Vertical line of hor
	string temphor[25] = {};		//temporary hor till x length is found
	int valh[25] = {};			//horizontal values of hor
	int valv[25] = {};			//vertical values of ver
	double dizit[25] = {};			//temporary values of relational operators (< > =)
	int ci[10] = {};			//values coming after relational operators
	double tempvalh[25] = {};		//store original values of valh for later use
	int rmarker[25] = {};			//mark R columns
	int rmark[25] = {};			//extend rmarker array to fit max length
	double mid[10][25] = {};		//midline array values
	double tempdizi[25] = {};		//store mid
	double zj[1][25] = {};			//Zj line
	double cz[1][25] = {};			//Cj-Zj line	
	int tempanswer[10][25] = {};

	int i = 0, j = 0, y = 0, d = 0, xassigner = 0, xcounter = 0, max = 0, hori = 0, ct = 0, vermax = 0, keyh = 0,
		z = 0, rcounter = 0, scount = 1, rcount = 1, xmax = 0, a = 0, b = 0, k = 0, free = 0;
	double fre = 0, intempo = 0;
	string convert = "", stemp, tempS;
	char spacee = ' '; char ent = 'a';

	bool zway = false, rmin = false, oldZway = false, rem = false, score = false, db = true, integ = false, passint = true;
	// zway= if zmax or zmin | rmin= if rmin or normal method | oldZway= if zway was max before turning min because of rmin |
	// rem= if should start remover function | score= if loop has ended | integ= for integer values | passint= new loop with integer type

	cout << "\n Enter the equations. Examples: \n\n 	Zmin=6x1+1x2 6x1+2x2=5 8x1+6x2>12 2x1+4x2<8 \n\n 	Zmax=6x1+8x2 30x1+20x2<300 5x1+10x2<110";
	cout << "\n\n 	Zmax=8x1+60x2+15x3+2x4+20x5+100x6+80x7+200x8+6x9 0.2x1+1.2x2+0.8x3+0.1x4+2x5+3.5x6+1.5x7+4x8+2x9<20 -t \n\n";
	cout << " Options:	-t	for integer values. Press [Enter] for next step \n\n";

	// input the characters
	while (input[i - a] != '\n') {

		cin >> noskipws >> input[i];

		if (input[i - a] == 't' || input[i - a] == 'T') { integ = true; }
		if ((input[i - a] == 'x' || input[i - a] == 'X') && isdigit(input[i])) {

			// find numbers after x
			stemp = "";
			stemp = stemp + input[i];
			xassigner = stod(stemp) - 1;

			// set array 0 if x skipped
			while (xcounter != xassigner) {
				if (d == 0 && db == true) { valh[xcounter] = 0; }
				else { mid[d][xcounter] = 0; }
				xcounter++;
			}

			// find numbers before x
			j = 2;
			while (isdigit(input[i - j]) || input[i - j] == '.') {
				convert = input[i - j] + convert;
				j++;
			}

			// create array with numbers before x
			if (d == 0 && db == true) {
				valh[xassigner] = stod(convert);
				if (input[i - j - 1] == '-') { valh[xassigner] = 0 - valh[xassigner]; }
			}
			else {
				mid[d][xassigner] = stod(convert);
				if (input[i - j - 1] == '-') { mid[d][xassigner] = 0 - mid[d][xassigner]; }
			}
			convert = "";

			//find max x
			if (max < xassigner) { max = xassigner; }
			xcounter++;
		}

		//check relational operators
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

	//store mid
	for (i = 0; i <= max; i++) {
		tempdizi[i] = mid[0][i];
	}
	// find val which was recorded above
	j = 0;
	for (i = 0; i < ct; i++) {
		tempS = "";
		y = 0;
		while (isdigit(input[ci[i] + y]) || input[ci[i] + y] == '.') {
			tempS = tempS + input[ci[i] + y];
			y++;
		}
		mid[i][max] = stod(tempS);
	}

	intempo = mid[0][max];

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

	// add values of relational operators to midline
	y = 0;
	for (i = xmax; i < max; i++) {
		if (dizit[i - xmax] == -1) { y -= 1; }
		mid[i - xmax + y][i] = dizit[i - xmax];
	}

	// start the loop
	do {
		if (integ == true) {
			// add less precision
			mid[0][max] = round(mid[0][max] * 10000) / 10000.0;
			for (i = 0; i < max; i++) {
				mid[0][i] = round(mid[0][i] * 10000) / 10000.0;
				if (mid[0][i] > mid[0][max]) { valh[i] = 0; mid[0][i] = 0; }
			}
		}
		for (i = 0; i <= vermax; i++) {
			printer(mid, valv, valh, ver[i], i, max, 1, vermax, zj, fre, free, zway, hor);
		}
		bottom(mid, valv, valh, ver, hor, score, max, zway, zj, cz, vermax, oldZway, rcounter, rmin, rem, integ, intempo,
			tempdizi, keyh, passint, tempanswer, k);
		if (rem == true) { remover(mid, hor, ver, valh, valv, max, vermax, rcounter, rem, zj, cz, rmark, tempvalh, xmax); }
		while (ent != '\n') { cin >> ent; } ent = 'a';
	} while (score != true);

	// output the answers
	cout << "\nConcluded:\n";

	if (integ == true) {
		tempanswer[k][0] = keyh;
		tempanswer[k][1] = mid[0][max];
		for (i = 0; i <= k; i++) {
			cout << "\n" << hor[tempanswer[i][0]] << ": " << tempanswer[i][1];
		}
	}
	else {
		if (zway == true) { cout << "Zmax="; }
		else { cout << "Zmin="; }
		cout << zj[0][max] << "\n";
		for (i = 0; i <= vermax; i++) {
			cout << ver[i] << "=" << mid[i][max] << "\n";
		}
	} cout << "\n";

	while (ent != '\n') { cin >> ent; }
	return 0;
}

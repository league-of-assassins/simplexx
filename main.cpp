#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctype.h>
#include <Windows.h>

using namespace std;

void printer(double array[][25], int cj_ver_val[25], int cj_hor_val[25], string cj_ver_name, int x, int max_hor,
	int func, int max_ver, double array2[][25], double& maxi, int& keyh, bool zway, string cj_hor_name[25]) {
	int i, p = 2, leftspace, rightspace, j;
	char spacee = ' ', linee = '-';

	//func: 1 top/mid[i], 2 Zj, 3 Cj-Zj

	//output top
	if (func == 1 && x == 0) {
		p = 8;
		cout << string(p, spacee);
		for (i = 0; i < max_hor; i++) {
			cout << " " << cj_hor_val[i] << string(p, spacee);
		}
		cout << "\n" << string(p + 1, spacee);
		for (i = 0; i < max_hor; i++) {
			cout << cj_hor_name[i] << string(p, spacee);
		}
		cout << "|  \n";
		p = 2;
	}

	if (func == 1) { if (0 == x) { cout << string(7 + 10 * (max_hor + 1), linee); } cout << "\n" << cj_ver_val[x] << " " << cj_ver_name << "|  "; }

	// output mid/bottom
	for (i = 0; i <= max_hor; i++) {
		leftspace = 0; rightspace = 4; p = 2;

		if (func == 2) {
			array[0][i] = 0;
			for (j = 0; j <= max_ver; j++) {
				array[0][i] += cj_ver_val[j] * array2[j][i];
			}
		}

		if (func == 3) {
			array[0][i] = cj_hor_val[i] - array2[0][i];
		}

		if (i == max_hor && func != 3) { cout << "  | "; }
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
	if (func == 1 && max_ver == x) { cout << "\n" << string(7 + 10 * (max_hor + 1), linee); }
}

void bottom(double mid[10][25], int cj_ver_val[25], int cj_hor_val[25], string cj_ver_name[25], string cj_hor_name[25], bool& score, int& max_hor, bool& zway,
	double zj[1][25], double cz[1][25], int max_ver, bool& oldZway, int& rcounter, bool& rmin, bool& rem, bool& integ, double& intempo,
	double mid_original[25], int& keyh, bool& passint, int int_answers[10][25], int& k) {
	int i, keyv = 0, j, lcount = 0, temp_int_max = 0;
	double maxi = 0, multiply, key = 0, temp = 0, tempo = 0, intempor = 0;

	// output Zj
	cout << "\n  Zj|  ";
	printer(zj, cj_ver_val, cj_hor_val, cj_ver_name[0], 0, max_hor, 2, max_ver, mid, maxi, keyh, zway, cj_hor_name);
	// output Cj-Zj
	cout << "\nC-Zj|  ";
	printer(cz, cj_ver_val, cj_hor_val, cj_ver_name[0], 0, max_hor - 1, 3, max_ver, zj, maxi, keyh, zway, cj_hor_name);

	//checks if loop should stop or continue with new sequence
	if (maxi == 0) {
		//turn to integer
		if (integ == true) {
			temp_int_max = mid[0][max_hor];
			if (mid[0][max_hor] == temp_int_max && passint == true) { goto sc; }
			mid[0][max_hor] = temp_int_max; intempor = mid_original[keyh] * temp_int_max;
			if (passint == true) { passint = false; goto end; }

			if (intempo != intempor) {
				int_answers[k][0] = keyh;
				int_answers[k][1] = mid[0][max_hor];
				cout << "\n\n 	" << cj_hor_name[keyh] << ": " << int_answers[k][1] << " New Sequence..\n";
				k++;
				passint = true;
				for (i = 0; i < max_hor; i++) {
					while (mid[0][i] == 0) { i++; }
					mid[0][i] = mid_original[i];
				}
				mid[0][max_hor] = intempo - intempor;
				intempo = mid[0][max_hor];
				cj_hor_val[keyh] = 0;
				mid[0][keyh] = 0;
				cj_ver_val[0] = 0;
				cj_ver_name[0] = cj_hor_name[max_hor - 1];
			}goto end;
		}
	sc:score = true; if (rmin == true) { rmin = false; score = false; rem = true; if (oldZway == true) { zway = true; } }
		goto end;
	}
	maxi = 0;

	// finds keyv
	for (i = 0; i <= max_ver; i++) {
		while (mid[i][keyh] <= 0) { if (i == max_ver + 1) { goto skip; }i++; }
		temp = mid[i][max_hor] / mid[i][keyh];
		if (i == 0) { tempo = temp; }
		if (tempo > temp) { keyv = i; tempo = temp; }
	}

skip:
	// calculates keyv line
	key = mid[keyv][keyh];
	for (i = 0; i <= max_hor; i++) {
		mid[keyv][i] = mid[keyv][i] / key;
	}
	// calculates other lines
	for (i = 0; i <= max_ver; i++) {
		if (i == keyv) { i++; }
		multiply = mid[i][keyh];
		for (j = 0; j <= max_hor; j++) {
			mid[i][j] = mid[i][j] - multiply * mid[keyv][j];
		}
	}
	// set new cj_ver_name
	cj_ver_val[keyv] = cj_hor_val[keyh];
	cj_ver_name[keyv] = cj_hor_name[keyh];
end:cout << "\n\n\n";
}

void remover(double mid[10][25], string cj_hor_name[25], string cj_ver_name[25], int cj_hor_val[25], int cj_ver_val[25],
	int& max_hor, int max_ver, int rcounter, bool& rem, double zj[1][25], double cz[1][25], int rmarker[25], double cj_hor_val_original[25], int max_x) {
	int i, j, u, y = 0;
	bool start = false;
	rem = false;
	// copy old cj_hor_val to current
	for (i = 0; i <= max_hor; i++) {
		cj_hor_val[i] = cj_hor_val_original[i];
	}
	//remove R columns from array
	u = max_x;
	for (i = 0; i <= max_hor; i++) {
		if (rmarker[i] == 1) { start = true; }
		if (rmarker[i] == 0 && start == true) {
			cj_hor_val[u] = cj_hor_val[i]; cj_hor_name[u] = cj_hor_name[i];
			for (j = 0; j <= max_ver + 1; j++) {
				mid[j][u] = mid[j][i];
			}
			u++;
		}
	}
	//copy cj_hor_val to cj_ver_val
	for (i = 0; i <= max_ver + 1; i++) {
		for (j = 0; j <= max_hor; j++) {
			if (cj_ver_name[i] == cj_hor_name[j]) { cj_ver_val[i] = cj_hor_val[j]; }
		}
	}
	max_hor -= rcounter;
}

int main() {
	char input[250] = {};			//inputted characters
	string cj_hor_name[25] = {};			//Horizontal line of Cj variables (S R -V)
	string cj_ver_name[25] = {};			//Vertical variation of cj_hor_name
	string cj_hor_name_temp[25] = {};		//temporary cj_hor_name till x length is found
	int cj_hor_val[25] = {};			//horizontal values of cj_hor_name
	int cj_ver_val[25] = {};			//vertical values of cj_ver_name
	double cj_hor_val_original[25] = {};		//store original values of cj_hor_val for later use
	double mid[10][25] = {};		//midline array values
	double mid_original[25] = {};		//original values of mid
	double mid_operator_val[25] = {};			//temporary values of relational operators (< > =) to be added to main mid array later
	int mid_last_val_marker[10] = {};			//last values coming after relational operators to be added to main mid array later
	double zj[1][25] = {};			//Zj line
	double cz[1][25] = {};			//Cj-Zj line	
	int rmarker_temp[25] = {};			//mark R columns
	int rmarker[25] = {};			//extended version of rmarker with zeroes
	int int_answers[10][25] = {};	//for recording integer method answers

	int i = 0, j = 0, y = 0, d = 0, xassigner = 0, xcounter = 0, max_hor = 0, hori = 0, ct = 0, max_ver = 0, keyh = 0,
		z = 0, rcounter = 0, scount = 1, rcount = 1, max_x = 0, a = 0, b = 0, k = 0, free = 0;
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
				if (d == 0 && db == true) { cj_hor_val[xcounter] = 0; }
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
				cj_hor_val[xassigner] = stod(convert);
				if (input[i - j - 1] == '-') { cj_hor_val[xassigner] = 0 - cj_hor_val[xassigner]; }
			}
			else {
				mid[d][xassigner] = stod(convert);
				if (input[i - j - 1] == '-') { mid[d][xassigner] = 0 - mid[d][xassigner]; }
			}
			convert = "";

			//find max x
			if (max_x < xassigner) { max_x = xassigner; }
			xcounter++;
		}

		//check relational operators
		if (input[i - a] == '<' || input[i - a] == '>' || input[i - a] == '=' && isdigit(input[i - b])) {
			mid_operator_val[hori] = 1;
			switch (input[i - a]) {

			case '<':
				tempS = to_string(scount); scount++; cj_hor_name_temp[hori] = "S" + tempS;
				break;

			case '>':
				tempS = to_string(rcount); rcount++; cj_hor_name_temp[hori] = "R" + tempS; rmin = true; rmarker_temp[hori] = 1; rcounter++;
				hori++; cj_hor_name_temp[hori] = "V" + tempS; mid_operator_val[hori] = -1;
				break;

			case '=':
				tempS = to_string(rcount); rcount++; cj_hor_name_temp[hori] = "R" + tempS; rmin = true; rmarker_temp[hori] = 1; rcounter++;
				break;
			}
			// mark the places of mid_last_val
			mid_last_val_marker[ct] = i; ct++;	hori++;
		}
		//space moves to next line
		if (isspace(input[i - a]) && isdigit(input[i - b]) && isdigit(input[i])) { xcounter = 0; d++; if (d == 1 && db == true) { d--; db = false; } }
		if (i == 2) { a++; b += 2; }
		i++;
	}

	max_ver = d; max_x += 1; max_hor = max_x; max_hor += hori;

	//store mid
	for (i = 0; i <= max_hor; i++) {
		mid_original[i] = mid[0][i];
	}
	// find mid_last_val which was marked above
	j = 0;
	for (i = 0; i < ct; i++) {
		tempS = "";
		y = 0;
		while (isdigit(input[mid_last_val_marker[i] + y]) || input[mid_last_val_marker[i] + y] == '.') {
			tempS = tempS + input[mid_last_val_marker[i] + y];
			y++;
		}
		mid[i][max_hor] = stod(tempS);
	}

	intempo = mid[0][max_hor];

	// check if zmax or zmin
	if (strstr(input, "a") || strstr(input, "A")) {
		zway = true; oldZway = true; if (rmin == true) { zway = false; }
	}
	else if (strstr(input, "i") || strstr(input, "I")) {
		zway = false;
	}

	// set cj_hor_name
	tempS = "";
	for (i = 0; i < max_x; i++) {
		tempS = to_string(i + 1);
		cj_hor_name[i] = "X" + tempS;
	}
	for (i = max_x; i <= max_x + hori; i++) {
		cj_hor_name[i] = cj_hor_name_temp[i - max_x];
	}

	// set cj_ver_name
	y = 0;
	for (i = 0; i <= max_ver + 1; i++) {
		if (mid_operator_val[i + y] == -1) { y++; }
		cj_ver_name[i] = cj_hor_name[i + max_x + y];
		cj_ver_val[i] = 0;
	}

	//store cj_hor_val
	if (rmin == true) {
		for (i = 0; i <= max_x + hori; i++) {
			cj_hor_val_original[i] = cj_hor_val[i];
		}
	}

	//set rest of cj_hor_val 0
	y = 0;
	if (rmin == true) { y = max_x; }
	for (i = max_x - y; i <= max_x; i++) {
		cj_hor_val[i] = 0;
	}

	//set cj_hor_val and cj_ver_val of rmin
	if (rmin == true) {
		y = 0;
		for (i = 0; i <= max_hor; i++) {
			if (mid_operator_val[i] == -1) { y++; }
			if (rmarker_temp[i] == 1) { cj_hor_val[i + max_x] = 1; cj_ver_val[i - y] = 1; }
		}
	}

	//extends rmarker_temp with 0 values
	for (i = 0; i < max_ver; i++) {
		rmarker[i] = 0;
	}

	for (i = max_ver; i < max_hor; i++) {
		rmarker[i] = rmarker_temp[i - max_ver];
	}

	// add values of relational operators to midline
	y = 0;
	for (i = max_x; i < max_hor; i++) {
		if (mid_operator_val[i - max_x] == -1) { y -= 1; }
		mid[i - max_x + y][i] = mid_operator_val[i - max_x];
	}

	// start the loop
	do {
		if (integ == true) {
			// add less precision
			mid[0][max_hor] = round(mid[0][max_hor] * 10000) / 10000.0;
			for (i = 0; i < max_hor; i++) {
				mid[0][i] = round(mid[0][i] * 10000) / 10000.0;
				if (mid[0][i] > mid[0][max_hor]) { cj_hor_val[i] = 0; mid[0][i] = 0; }
			}
		}
		for (i = 0; i <= max_ver; i++) {
			printer(mid, cj_ver_val, cj_hor_val, cj_ver_name[i], i, max_hor, 1, max_ver, zj, fre, free, zway, cj_hor_name);
		}
		bottom(mid, cj_ver_val, cj_hor_val, cj_ver_name, cj_hor_name, score, max_hor, zway, zj, cz, max_ver, oldZway, rcounter, rmin, rem, integ, intempo,
			mid_original, keyh, passint, int_answers, k);
		if (rem == true) { remover(mid, cj_hor_name, cj_ver_name, cj_hor_val, cj_ver_val, max_hor, max_ver, rcounter, rem, zj, cz, rmarker, cj_hor_val_original, max_x); }
		while (ent != '\n') { cin >> ent; } ent = 'a';
	} while (score != true);

	// output the answers
	cout << "\nConcluded:\n";

	if (integ == true) {
		int_answers[k][0] = keyh;
		int_answers[k][1] = mid[0][max_hor];
		for (i = 0; i <= k; i++) {
			cout << "\n" << cj_hor_name[int_answers[i][0]] << ": " << int_answers[i][1];
		}
	}
	else {
		if (zway == true) { cout << "Zmax="; }
		else { cout << "Zmin="; }
		cout << zj[0][max_hor] << "\n";
		for (i = 0; i <= max_ver; i++) {
			cout << cj_ver_name[i] << "=" << mid[i][max_hor] << "\n";
		}
	} cout << "\n";

	while (ent != '\n') { cin >> ent; }
	return 0;
}

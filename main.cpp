#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctype.h>
#include <Windows.h>

using namespace std;

void size_finder(double temp, int& leftspace) {
	int size;

	if (temp < 0) { leftspace--; temp = 0 - temp; }
	if (temp >= 10) {
		size = trunc(log10(temp)) + 1;
		leftspace = leftspace - size + 1;
	}
}

void printer(double array[][25], int cj_ver_val[25], double cj_hor_val[1][25], string cj_ver_name, int x, int max_hor,
	int printer_order, int max_ver, double array2[][25], double& maxi, int& key_hor, bool zway, string cj_hor_name[25]) {
	int i, p = 2, leftspace = 5, rightspace, j, size;
	double temp = 0;
	char spacee = ' ', linee = '-';

	//printer_order: 0 top, 1 mid[x], 2 Zj, 3 Cj-Zj

	if (printer_order == 1) {

		size_finder(cj_ver_val[x], leftspace);

		cout << "\n" << string(leftspace, spacee) << cj_ver_val[x] << " " << cj_ver_name << "|";
	}

	//output
	for (i = 0; i <= max_hor; i++) {
		leftspace = 5; rightspace = 1; p = 2, size = 0;

		if (printer_order == 0) { if (i == 0) { leftspace += 10; } else if (i == max_hor) { break; } }

		if (printer_order == 2) {
			array[0][i] = 0;
			for (j = 0; j <= max_ver; j++) {
				array[0][i] += cj_ver_val[j] * array2[j][i];
			}
		}

		if (printer_order == 3) {
			array[0][i] = cj_hor_val[0][i] - array2[0][i];
		}

		if (i == max_hor && printer_order != 0 && printer_order != 3) { cout << "   |"; }

		size_finder(array[x][i], leftspace);

		if (ceil(array[x][i]) == array[x][i]) {
			p = 0; rightspace += 3;
		}
		cout << string(leftspace, spacee) << fixed << setprecision(p) << array[x][i] << string(rightspace, spacee);

		if (printer_order == 3) {
			if (zway == true) {
				if (array[0][i] > maxi) {
					maxi = array[0][i];
					key_hor = i;
				}
			}
			else {
				if (array[0][i] < maxi) {
					maxi = array[0][i];
					key_hor = i;
				}
			}
		}
	}

	if (printer_order == 0) {
		leftspace = 4; rightspace = 7;
		cout << "\n" << string(leftspace + 3, spacee) << "Cj|";
		for (i = 0; i < max_hor; i++) {
			if (i == 1) { leftspace -= 3; }
			cout << string(leftspace, spacee) << cj_hor_name[i] << string(rightspace, spacee);
		}
		cout << "|\n " << string(12 + 10 * (max_hor + 1), linee);
	}

	if (printer_order == 1 && max_ver == x) { cout << "\n " << string(12 + 10 * (max_hor + 1), linee); }
}

void bottom(double mid[10][25], string cj_hor_name[25], string cj_ver_name[25], double cj_hor_val[1][25], int cj_ver_val[25],
	double zj[1][25], double cz[1][25], int& max_hor, int max_ver, int& key_hor, bool& zway, bool& zway_original, bool& score, bool& rmin_method,
	bool& remover_enable, bool& integer_method, bool& integer_pass, double& integer_last_val_current_original,
	double mid_original[25], int integer_answer[10][25], int& k)
{
	int i, key_ver = 0, j, lcount = 0, integer_last_val_int = 0;
	double maxi = 0, multiply, key = 0, temp = 0, tempo = 0, integer_last_val_rest = 0;

	// output Zj
	cout << "\n       Zj|";
	printer(zj, cj_ver_val, cj_hor_val, cj_ver_name[0], 0, max_hor, 2, max_ver, mid, maxi, key_hor, zway, cj_hor_name);
	// output Cj-Zj
	cout << "\n    Cj-Zj|";
	printer(cz, cj_ver_val, cj_hor_val, cj_ver_name[0], 0, max_hor - 1, 3, max_ver, zj, maxi, key_hor, zway, cj_hor_name);

	//checks if loop should stop or continue with new sequence
	if (maxi == 0) {
		//turn to integer
		if (integer_method == true) {
			integer_last_val_int = mid[0][max_hor];
			if (mid[0][max_hor] == integer_last_val_int && integer_pass == false) { goto sc; }
			mid[0][max_hor] = integer_last_val_int; integer_last_val_rest = mid_original[key_hor] * integer_last_val_int;
			if (integer_pass == false) { integer_pass = true; goto end; }

			if (integer_last_val_current_original != integer_last_val_rest) {
				integer_answer[0][k] = key_hor;
				integer_answer[1][k] = mid[0][max_hor];
				cout << "\n\n 	" << cj_hor_name[key_hor] << ": " << integer_answer[1][k] << " New Sequence..\n";
				k++;
				integer_pass = false;
				for (i = 0; i < max_hor; i++) {
					while (mid[0][i] == 0) { i++; }
					mid[0][i] = mid_original[i];
				}
				mid[0][max_hor] = integer_last_val_current_original - integer_last_val_rest;
				integer_last_val_current_original = mid[0][max_hor];
				cj_hor_val[0][key_hor] = 0;
				mid[0][key_hor] = 0;
				cj_ver_val[0] = 0;
				cj_ver_name[0] = cj_hor_name[max_hor - 1];
			}goto end;
		}
	sc:score = true; if (rmin_method == true) { rmin_method = false; score = false; remover_enable = true; if (zway_original == true) { zway = true; } }
		goto end;
	}
	maxi = 0;

	// finds key_ver
	for (i = 0; i <= max_ver; i++) {
		while (mid[i][key_hor] <= 0) { if (i == max_ver + 1) { goto skip; }i++; }
		temp = mid[i][max_hor] / mid[i][key_hor];
		if (i == 0) { tempo = temp; }
		if (tempo > temp) { key_ver = i; tempo = temp; }
	}

skip:
	// calculates key_ver line
	key = mid[key_ver][key_hor];
	for (i = 0; i <= max_hor; i++) {
		mid[key_ver][i] = mid[key_ver][i] / key;
	}

	// calculates other lines
	for (i = 0; i <= max_ver; i++) {
		if (i == key_ver) { i++; }
		multiply = mid[i][key_hor];
		for (j = 0; j <= max_hor; j++) {
			mid[i][j] = mid[i][j] - multiply * mid[key_ver][j];
		}
	}

	// set new cj_ver
	cj_ver_val[key_ver] = cj_hor_val[0][key_hor];
	cj_ver_name[key_ver] = cj_hor_name[key_hor];
end:cout << "\n\n\n";
}

void remover(double mid[10][25], string cj_hor_name[25], string cj_ver_name[25], double cj_hor_val[1][25], int cj_ver_val[25],
	int& max_hor, int max_ver, int count_r, bool& remover_enable, double zj[1][25], double cz[1][25], int rmarker[25], double cj_hor_val_x_original[25], int max_x) {
	int i = 0, j = 0, u = 0;
	bool start = false;
	remover_enable = false;

	// copy old cj_hor_val to current
	for (i = 0; i <= max_hor; i++) {
		cj_hor_val[0][i] = cj_hor_val_x_original[i];
	}

	//remove R columns from array
	u = max_x;
	for (i = max_x; i <= max_hor; i++) {
		while (rmarker[i - max_x] == 0 && start == false) {
			u++; i++;
		}

		if (rmarker[i - max_x] == 1) { start = true; }
		if (rmarker[i - max_x] == 0 && start == true) {
			cj_hor_val[0][u] = cj_hor_val[0][i]; cj_hor_name[u] = cj_hor_name[i];
			for (j = 0; j <= max_ver; j++) {
				mid[j][u] = mid[j][i];
			}
			u++;
		}
	}

	//copy cj_hor_val to cj_ver_val
	for (i = 0; i <= max_ver + 1; i++) {
		for (j = 0; j <= max_hor; j++) {
			if (cj_ver_name[i] == cj_hor_name[j]) { cj_ver_val[i] = cj_hor_val[0][j]; }
		}
	}
	max_hor -= count_r;
}

int main() {
	char input[250] = {};			//inputted characters
	string cj_hor_name[25] = {};		//Horizontal line of Cj variables (S R -V)
	string cj_ver_name[25] = {};		//Vertical variation of cj_hor_name
	double cj_hor_val[1][25] = {};		//horizontal values of cj_hor_name
	int cj_ver_val[25] = {};		//vertical values of cj_ver_name
	double cj_hor_val_x_original[25] = {};	//store original values of cj_hor_val for later use
	double mid[10][25] = {};		//midline array values
	double mid_original[25] = {};		//original values of mid
	double mid_operator_val[25] = {};	//temporary values of relational operators (< > =) to be added to main mid array later
	int mid_last_val_marker[10] = {};	//last values coming after relational operators to be added to main mid array later
	double zj[1][25] = {};			//Zj line
	double cz[1][25] = {};			//Cj-Zj line	
	int rmarker[25] = {};			//mark R columns
	int integer_answer[10][25] = {};	//for recording integer method answers

	int i = 0, j = 0, y = 0, count_equation = 0, assign_x = 0, count_x = 0, max_hor = 0, count_cj = 0, mark_last = 0, max_ver = 0, key_hor = 0,
		count_r = 0, count_s = 1, max_x = 0, a = 0, b = 0, k = 0, occupier = 0;
	double occupier_2 = 0, integer_last_val_current_original = 0;
	string temp_string;
	char ent = 'a';

	bool zway = false, rmin_method = false, zway_original = false, remover_enable = false, score = false, first_equation = true, integer_method = false, integer_pass = false;
	// zway= Zmax/Zmin | rmin_method= Rmin_method/Normal method | zway_original= if zway was max before turning min because of Rmin_method |
	// remover_enable= enable remover function | score= loop ended | integer_method= Integer/Normal method | integer_pass= new loop with integer type

	cout << "\n Enter the equations. Examples: \n\n 	Zmin=6x1+1x2 6x1+2x2=5 8x1+6x2>12 2x1+4x2<8 \n\n 	Zmax=6x1+8x2 30x1+20x2<300 5x1+10x2<110";
	cout << "\n\n 	Zmax=8x1+60x2+15x3+2x4+20x5+100x6+80x7+200x8+6x9 0.2x1+1.2x2+0.8x3+0.1x4+2x5+3.5x6+1.5x7+4x8+2x9<20 -t \n\n";
	cout << " Options:	-t	for integer values. Press [Enter] for next step \n\n";

	// input the characters
	while (input[i - a] != '\n') {

		cin >> noskipws >> input[i];

		if (input[i - b] == '-' && (input[i - a] == 't' || input[i - a] == 'T')) { integer_method = true; count_equation--; }

		if ((input[i - a] == 'x' || input[i - a] == 'X') && isdigit(input[i])) {

			// find numbers after x
			temp_string = "";
			temp_string = temp_string + input[i];
			assign_x = stod(temp_string) - 1;

			// set array 0 if x skipped
			while (count_x != assign_x) {
				if (count_equation == 0 && first_equation == true) { cj_hor_val[0][count_x] = 0; }
				else { mid[count_equation][count_x] = 0; }
				count_x++;
			}

			// find numbers before x
			j = 2; temp_string = "";
			while (isdigit(input[i - j]) || input[i - j] == '.') {
				temp_string = input[i - j] + temp_string;
				j++;
			}

			// create array with numbers before x
			if (count_equation == 0 && first_equation == true) {
				cj_hor_val[0][assign_x] = stod(temp_string);
				if (input[i - j] == '-') { cj_hor_val[0][assign_x] = 0 - cj_hor_val[0][assign_x]; }
			}
			else {
				mid[count_equation][assign_x] = stod(temp_string);
				if (input[i - j] == '-') { mid[count_equation][assign_x] = 0 - mid[count_equation][assign_x]; }
			}

			//find max x
			if (max_x < assign_x) { max_x = assign_x; }
			count_x++;
		}

		//check relational operators
		if (input[i - a] == '<' || input[i - a] == '>' || input[i - a] == '=' && isdigit(input[i - b])) {
			mid_operator_val[count_cj] = 1;
			switch (input[i - a]) {

			case '<':
				temp_string = to_string(count_s); count_s++; cj_hor_name[count_cj] = "S" + temp_string;
				break;

			case '>':
				count_r++; temp_string = to_string(count_r); cj_hor_name[count_cj] = "R" + temp_string; rmin_method = true; rmarker[count_cj] = 1;
				count_cj++; cj_hor_name[count_cj] = "V" + temp_string; mid_operator_val[count_cj] = -1;
				break;

			case '=':
				count_r++; temp_string = to_string(count_r); cj_hor_name[count_cj] = "R" + temp_string; rmin_method = true; rmarker[count_cj] = 1;
				break;
			}
			// mark mid_last_val
			mid_last_val_marker[mark_last] = i; mark_last++; count_cj++;
		}

		//space moves to next line
		if (isspace(input[i - a]) && isdigit(input[i - b]) && (isdigit(input[i]) || input[i] == '-')) {
			count_x = 0; count_equation++; if (count_equation == 1 && first_equation == true) { count_equation--; first_equation = false; }
		}
		if (i == 2) { a++; b += 2; }
		i++;
	}

	max_ver = count_equation; max_x += 1; max_hor = max_x; max_hor += count_cj;

	// check if zmax or zmin
	if (strstr(input, "a") || strstr(input, "A")) {
		zway = true; zway_original = true; if (rmin_method == true) { zway = false; }
	}
	else if (strstr(input, "i") || strstr(input, "I")) {
		zway = false;
	}
	else {
		cout << "\n    Z was not entered. Aborting...";
		return 0;
	}

	// find marked mid_last_val
	for (i = 0; i < mark_last; i++) {
		temp_string = ""; y = 0;
		while (isdigit(input[mid_last_val_marker[i] + y]) || input[mid_last_val_marker[i] + y] == '.') {
			temp_string = temp_string + input[mid_last_val_marker[i] + y];
			y++;
		}
		mid[i][max_hor] = stod(temp_string);
	}
	integer_last_val_current_original = mid[0][max_hor];

	//store mid
	for (i = 0; i <= max_hor; i++) {
		mid_original[i] = mid[0][i];
	}

	// set cj_hor_name
	y = max_hor - max_x - 1;
	for (i = max_hor - max_x - 1; i >= 0; i--) {
		cj_hor_name[max_hor - 1 + i - y] = cj_hor_name[i];
	}

	temp_string = "";
	for (i = 0; i < max_x; i++) {
		temp_string = to_string(i + 1);
		cj_hor_name[i] = "X" + temp_string;
	}

	// set cj_ver_name
	y = 0;
	for (i = 0; i <= max_ver + 1; i++) {
		if (mid_operator_val[i + y] == -1) { y++; }
		cj_ver_name[i] = cj_hor_name[i + max_x + y];
	}

	if (rmin_method == true) {
		//store and clear cj_hor_val
		for (i = 0; i <= max_x; i++) {
			cj_hor_val_x_original[i] = cj_hor_val[0][i];
			cj_hor_val[0][i] = 0;
		}

		//set cj_val of rmin_method
		y = 0;
		for (i = max_x; i <= max_hor; i++) {
			if (mid_operator_val[i - max_x] == -1) { y++; }
			if (rmarker[i - max_x] == 1) { cj_hor_val[0][i] = 1; cj_ver_val[i - y - max_x] = 1; }
		}
	}

	//add values of relational operators to mid
	y = 0;
	for (i = max_x; i < max_hor; i++) {
		if (mid_operator_val[i - max_x] == -1) { y -= 1; }
		mid[i - max_x + y][i] = mid_operator_val[i - max_x];
	}

	cout << "\n\n";

	//start the loop
	do {
		//add less precision
		for (i = 0; i <= max_hor; i++) {
			mid[0][i] = round(mid[0][i] * 10000) / 10000.0;
		}

		if (integer_method == true) {
			//remove unfit values
			for (i = 0; i < max_hor; i++) {
				if (mid[0][i] > mid[0][max_hor]) { cj_hor_val[0][i] = 0; mid[0][i] = 0; }
			}
		}

		printer(cj_hor_val, cj_ver_val, mid, cj_ver_name[i], 0, max_hor, 0, max_ver, zj, occupier_2, occupier, zway, cj_hor_name);

		for (i = 0; i <= max_ver; i++) {
			printer(mid, cj_ver_val, cj_hor_val, cj_ver_name[i], i, max_hor, 1, max_ver, zj, occupier_2, occupier, zway, cj_hor_name);
		}

		bottom(mid, cj_hor_name, cj_ver_name, cj_hor_val, cj_ver_val, zj, cz, max_hor, max_ver, key_hor, zway, zway_original, score,
			rmin_method, remover_enable, integer_method, integer_pass, integer_last_val_current_original, mid_original, integer_answer, k);

		if (remover_enable == true) {
			remover(mid, cj_hor_name, cj_ver_name, cj_hor_val, cj_ver_val, max_hor, max_ver, count_r, remover_enable, zj, cz,
				rmarker, cj_hor_val_x_original, max_x);
		}

		while (ent != '\n') { cin >> ent; } ent = 'a';
	} while (score != true);

	// output the answers
	cout << "\n  Concluded..\n\n    ";

	if (integer_method == true) {
		integer_answer[0][k] = key_hor;
		integer_answer[1][k] = mid[0][max_hor];
		for (i = 0; i <= k; i++) {
			cout << "\n    " << cj_hor_name[integer_answer[0][i]] << ": " << integer_answer[1][i];
		}
	}
	else {
		if (zway == true) { cout << "Zmax="; }
		else { cout << "Zmin="; }
		cout << zj[0][max_hor] << "\n";
		for (i = 0; i <= max_ver; i++) {
			cout << "    " << cj_ver_name[i] << "=" << mid[i][max_hor] << "\n";
		}
	} cout << "\n";

	while (ent != '\n') { cin >> ent; }
	return 0;
}

/*
	Notes:
space formation supports up to -+99999.99
integer type supports only 1st row
input order is important. entering characters in an order other than shown in the example might break the program
Correct way: zmax/zmin=equation | other equations | options

	Visual Studio Warnings explained:
Double to int data loss	| intentional
buffer & invalid data		| Doesn't apply since max_x >= 0
*/
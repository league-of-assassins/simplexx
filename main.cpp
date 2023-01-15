#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctype.h>
#include <cstdlib>
#include <Windows.h>

using namespace std;



void midprint( float dizi[][25], int valv, string ver, int x, int max){

									// output mid line
	int i;
	cout << "\n" <<valv << " " << ver << "|  ";
	for (i=0;i<=max;i++){
		if (i==max){cout <<"  | ";}
		if (dizi[x][i]>=0){cout << " ";}
		if (dizi[x][i]<10 && dizi[x][i]>-10){cout << " ";}
		if (ceilf(dizi[x][i]) == dizi[x][i]){
			cout << fixed << setprecision(0)  << dizi[x][i] << "   " << "    ";
		}
		else {
		cout << fixed << setprecision(2) << dizi[x][i] << "    ";
		}
	}
}

void topfunc(char linee, string hor[], int valh[], int &max){

									// output top line
	int i;
	cout << "        ";
	for (i=0;i<max;i++){
		cout << " "<< valh[i] << "        ";
	}
	cout << "\n"<< "         ";
	for (i=0;i<max;i++){
		cout << hor[i] << "        ";
	}
	cout << "|  \n" << string (13*max,linee);
}


void bottom( float dizi[][25], int valv[], int valh[], string ver[], string hor[],
 bool &score, char linee, int &max, bool &zway, float zj[],float cz[],int vermax, bool &oldZway, int &rcounter, bool &rway, bool &rem){
	int i, keyh=0, keyv=0, a, b, antikeyv, j, temp=0, tempo, u, lcount=0;
	float maxi=0, multiply, key=0;
	cout << "\n" << string (13*max,linee);

									// output Zj

	cout <<"\n  Zj|  ";
	for (i=0;i<=max;i++){
		zj[i]=0;
		for(j=0;j<=vermax;j++){
			zj[i]+=valv[j]*dizi[j][i];
		}
		if (i==max){cout <<"  | ";}
		if (zj[i]>=0){cout << " ";}
		if (zj[i]<10 && zj[i]>-10){cout << " ";}
		if (ceilf(zj[i]) == zj[i]){
			cout << fixed << setprecision(0)  << zj[i] << "   " << "    ";
		}
		else {
		cout << fixed << setprecision(2) << zj[i] << "    ";
		}
	}
									// output Cj-Zj

	cout <<"\nC-Zj|  ";
	for (i=0;i<max;i++){
		cz[i]=valh[i]-zj[i];
		if (cz[i]>=0){cout << " ";}
		if (cz[i]<10 && cz[i]>-10){cout << " ";}
		if (ceilf(cz[i]) == cz[i]){
			cout << fixed << setprecision(0)  << cz[i] << "   " << "    ";
		}
		else {
		cout << fixed << setprecision(2) << cz[i] << "    ";
		}
									// finds min or max of Cj-Zj and sets it as keyh
		if (zway==true){
			if (cz[i]>maxi){
				maxi=cz[i];
				keyh=i;
			}
		}
		else {
			if (cz[i]<maxi){					
				maxi=cz[i];
				keyh=i;
			}
		}
	}

									//checks if loop has ended

	if (maxi==0){ 
		score=true; if(rway==true){rway=false; score=false; rem=true; if(oldZway==true){zway=true;}}
		goto end;
	}
	maxi=0;
									// finds keyv

	for(i=0;i<=vermax;i++){
		while(dizi[i][keyh]<=0){ if(i==vermax+1){goto skip;}i++;}
		temp=dizi[i][max]/dizi[i][keyh];
		if(i==0){tempo=temp;}
		if(tempo>temp){keyv=i;tempo=temp;}
	}

	skip:							// calculates keyv line

	key=dizi[keyv][keyh];
	for(i=0;i<=max;i++){
		dizi[keyv][i]=dizi[keyv][i]/key;
	}
									// calculates other lines

	for(i=0;i<=vermax+1;i++){
		if(i==keyv){i++;}
		multiply=dizi[i][keyh];
		for(j=0;j<=max;j++){
			dizi[i][j]=dizi[i][j]-multiply*dizi[keyv][j];
		}
	}

									// sets new ver according to keyv and keyh

	valv[keyv]=valh[keyh];
	ver[keyv]=hor[keyh];
	end:cout << "\n\n\n";
}


void remover(float dizi[][25], string hor[], string ver[], int valh[], int valv[],
 int &max, int vermax, int rcounter, bool &rem, float zj[], float cz[], int rmark[], int tempvalh[], int xmax){
	int i, j, u, y=0;
	bool start=false;
	rem=false;

									// copy old valh to current
	for(i=0;i<=max;i++){
		valh[i]=tempvalh[i];
	}

									//remove R columns from array
	u=xmax;
	for(i=0;i<=max;i++){
		if(rmark[i]==1){start=true;}
		if(rmark[i]==0&&start==true){
			valh[u]=valh[i]; hor[u]=hor[i];
			for(j=0;j<=vermax+1;j++){
				dizi[j][u]=dizi[j][i];		
			}
			u++;
		}
	}


									//copy valh to valv
	for(i=0;i<=vermax+1;i++){
		for(j=0;j<=max;j++){
			if(ver[i]==hor[j]){valv[i]=valh[j];}
		}
	}
	max-=rcounter;
}

int main (){
	char input[250]={};			//inputted characters
	string hor[25]={};			//Horizontal line S1 R -V etc.
	string ver[25]={};			//Vertical line of hor
	string temphor[25]={};		//temporary hor till i find x length
	int valh[25]={};			//horizontal values of hor
	int valv[25]={};			//vertical values of ver
	int dizit[25]={};			//temporary values of > < =
	int ci[10]={};				//values after > < =
	int tempvalh[25]={};		//store original values of valh for use later
	int rmarker[25]={};			//mark r columns
	int rmark[25]={};			//extend rmarker array to fit max
	float dizi[10][25]={};		//midline array values
	float zj[25]={};			//Zj line
	float cz[25]={};			//Cj-Zj line	

	int i=0, j=0, y=0, d=-1, xassigner=0, xcounter=0, max=0, hori=0, ct=0, vermax=0, 
	 z=0, rcounter=0, scount=1, rcount=1, xmax=0;
	string convert="", stemp, tempS;
	char linee = '-';

	bool zway=false, rway=false, oldZway=false, rem=false, score=false;
	// zway= if zmax or zmin | rway= if rway or normal way | oldZway= if zway was max before turning min because of rway |
	// rem= if should start remover function | score= if loop has ended

	cout << "\n Enter the equations. Example: \n Zmin=6x1+1x2 6x1+2x2=5 8x1+6x2>12 2x1+4x2<8 or Zmax=6x1+8x2 30x1+20x2<300 5x1+10x2<110 Press enter to stop \n\n";

											// input the characters

	while(input[i-1]!='\n'){
		cin >> noskipws>> input[i];
		if(input[i-1]=='x'&&isdigit(input[i])){
											// find numbers before x
			j=2;
			while(isdigit(input[i-j])) { 
				convert=input[i-j]+convert;
				j++;
			}
											// find numbers after x
			stemp="";
			stemp=stemp+input[i];
			xassigner=stoi(stemp)-1;

											// set array 0 if x skipped
			while(xcounter!=xassigner){
				if(d<0){valh[xcounter]=0;}
				else {dizi[d][xcounter]=0;}
				xcounter++;
			}
											// create array with numbers before x
			if(d<0){
				valh[xassigner]=stoi(convert);
				if(input[i-j-1]=='-'){valh[xassigner]=0-valh[xassigner];}
			}
			else{
				dizi[d][xassigner]=stoi(convert);
				if(input[i-j-1]=='-'){dizi[d][xassigner]=0-dizi[d][xassigner];}
			}
			convert="";
											//find array length
			if(max<xassigner){max=xassigner;}
			xcounter++;
		}

											//check chars > < =

		if (input[i-1]=='<'||input[i-1]=='>'||input[i-1]=='='&&isdigit(input[i-2])){
			dizit[hori]=1;
			switch (input[i-1]){

			case '<':
				tempS=to_string(scount); scount++; temphor[hori]="S"+tempS;
				break;

			case '>':
				tempS=to_string(rcount); rcount++; temphor[hori]="R"+tempS; rway=true; rmarker[hori]=1; rcounter++; hori++; temphor[hori]="V"+tempS; dizit[hori]=-1;
				break;

			case '=':
				tempS=to_string(rcount); rcount++; temphor[hori]="R"+tempS; rway=true; rmarker[hori]=1; rcounter++;
			break;
			}	
											// record the place of val which comes after ><= to find it later
			ci[ct]=i; ct++;	hori++;
		}
											//space moves to next line
		if(isspace(input[i-1])&&isdigit(input[i-2])&&isdigit(input[i])){xcounter=0; d++;}
		i++;
	}

	vermax=d;
	max+=1;
	xmax=max;
	max+=hori;

											// find val which was recorded above
	j=0;
	for(i=0;i<ct;i++){
		tempS="";
		y=0;
		while(isdigit(input[ci[i]+y])){
			tempS=tempS+input[ci[i]+y];
			y++;
		}
		dizi[i][max]=stoi(tempS);
	}
											// check if zmax or zmin
	if (strstr(input,"a")||strstr(input,"A")){
		zway=true; oldZway=true; if(rway==true){zway=false;}
	}
	else if (strstr(input,"i")||strstr(input,"I")||strstr(input,"İ")){
		zway=false;
	}


											// set hor
	tempS="";
	for(i=0;i<xmax;i++){
		tempS=to_string(i+1);
		hor[i]="X"+tempS;
	}
	for(i=xmax;i<=xmax+hori;i++){
		hor[i]=temphor[i-xmax];
	}			

											// set ver
	y=0;
	for(i=0;i<=vermax+1;i++){
		if(dizit[i+y]==-1){y++;}
		ver[i]=hor[i+xmax+y];
		valv[i]=0;
	}
											//set tempvalh in case rway
	if(rway==true){
		for(i=0;i<=xmax+hori;i++){
			tempvalh[i]=valh[i];
		}
	}
											//set rest of valh 0
	y=0;
	if(rway==true){y=vermax+1;}
	for(i=vermax+1-y;i<=xmax;i++){
		valh[i]=0;
	}
											//set valh and valv of rway
	if(rway==true){
		y=0;
		for(i=0;i<=max;i++){
			if(dizit[i]==-1){y++;}
			if(rmarker[i]==1){valh[i+xmax]=1; valv[i-y]=1;}
		}
	}
											//extends rmarker with 0 values
	for(i=0;i<=vermax;i++){
		rmark[i]=0;
	}

	for(i=vermax;i<=max;i++){
		rmark[i]=rmarker[i-vermax];
	}

											// add values of > < = to midline
	y=0;
	for (i=xmax;i<max;i++){
		if(dizit[i-xmax]==-1){y-=1;}
		dizi[i-xmax+y][i]=dizit[i-xmax];
	}

											// start the loop
	do{
		topfunc(linee, hor, valh, max);
		for(i=0;i<=vermax;i++){
			midprint( dizi, valv[i], ver[i], i, max);
		}
		bottom(dizi, valv, valh, ver, hor, score, linee, max, zway, zj, cz, vermax, oldZway, rcounter, rway, rem);
		if(rem==true){ remover(dizi, hor, ver, valh, valv, max, vermax, rcounter, rem, zj, cz, rmark, tempvalh, xmax);}
		Sleep(3000);
	}
	while (score!=true);

											// output the answers
	cout<<"\nConcluded: \n";
	if(zway==true){cout << "Zmax=";}
	else{cout << "Zmin=";}
	cout << zj[max] << "\n";
	for(i=0;i<=vermax;i++){
		cout << ver[i] << "=" << valv[i] << "\n";
	} cout << "\n";

	system("pause");
	return 0;
}
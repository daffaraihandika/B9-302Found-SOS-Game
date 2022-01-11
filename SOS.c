/*
Program				: Game SOS
Kelompok			: B9 - 302Found
Author				: - Aini Diah Rahmawati
					  - Danu Mahesa
					  - Muhammad Daffa Raihandika
Kelas				: 1B
Prodi				: D4 - Teknik Informatika
		
		Politeknik Negeri Bandung
============================================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

#define WHITE 15
#define LIGHT_BLUE 11
#define LIGHT_YELLOW 14
#define RED 4

void tampilanMenu();		//Modul ini bertujuan untuk menampilkan tampilan menu
void tampilModePermainan();	//Modul ini bertujuan untuk menampilkan mode permainan
void tampilanLevel();		//Modul ini bertujuan untuk menampilkan beberapa level dalam permainan SOS dan user diharuskan untuk memilih level untuk memulai permainan SOS ini
void tampilanSOS();			//Modul ini untuk menampilkan gambar SOS berfungsi sebagai variasi pada User Interface
void tampilanMenang();		//Modul ini bertujuan untuk menampilkan kondisi ketika menang
void tampilanDraw();		//Modul ini bertujuan untuk menampilkan kondisi ketika tidak ada pemenang (draw/seri)
void howToPlay();			//Modul ini bertujuan untuk menampilkan how to play yang diambil dari file How To Play.txt	
void papanSOS();			//Modul ini bertujuan untuk menampilkan papan permainan SOS
void scoreBoard();			//Modul ini bertujuan untuk menampilkan papan skor pada permainan SOS
void resetBoard();			//Modul ini bertujuan untuk menginsialisasi seluruh kotak yang ada pada papan sos dengan karakter spasi 
void prosesInGamePvP();		//Modul ini bertujuan untuk membuat proses alur permainan game SOS pada mode player vs player
void prosesInGamePvC();		//Modul ini bertujuan untuk membuat proses alur permainan game SOS pada mode player vs computer
void InputNameFromUser1();	//Modul ini digunakan untuk menginputkan nama pemain jika user memilih mode permainan player vs komputer
void InputNameFromUser2();	//Modul ini digunakan untuk menginputkan nama pemain jika user memilih mode permainan player vs player
int takeInput(); 			//Modul ini bertujuan untuk user menginputkan huruf S atau O ke dalam papan SOS
int controlSOS();			//Modul ini bertujuan untuk mengecek SOS sudah terbentuk atau belum
int controlBot();			//Modul ini bertujuan untuk computer menyimpan huruf S atau O pada kondisi tertentu
void compMove();			//Modul ini bertujuan untuk alur proses computer pada saat melawan user modul ini hanya akan dipanggil di mode player vs computer
int checkWin();				//Modul ini bertujuan untuk mengecek pemenang dalam permainan SOS
int checkFreeSpace();		//Modul ini bertujuan untuk mengecek apakah papan SOS masih ada yang kosong atau tidak
void hasilPertandingan();	//Modul ini digunakan untuk menampilkan hasil pertandingan setelah game berakhir
void gameOver();			//Modul ini bertujuan untuk menampilkan “game over” ketika permainan sudah berakhir (tidak ada papan kosong yang tersisa)
void gotoxy(int x, int y);	//Modul ini bertujuan untuk menempatkan kursor ditempat yang diinginkan.
void warnateks(int warna);	//Modul yang berfungsi untuk memberi warna ke karakter
void kecepatan(float seconds);
void loading();				//Modul untuk menapilkan tampilan loading
void loadingScreen();				

char sos[8][8];				//Variabel ini digunakan untuk menyimpan huruf S atau O pada papan SOS
int scores[2] = { 0,0 }; 	//Variabel ini digunakan untuk menyimpan skor para pemain
int currentPlayer = 0; 		//Variabel ini digunakan untuk menentukan giliran pemain.
char name[2][20]; 			//Variabel ini digunakan untuk menyimpan nama dari setiap pemain
char nameWinner[20];		//Variabel ini digunakan untuk menampung nama dari pemenang game SOS. Nama ini akan ditampilkan ketika permainan sudah selesai dan diketahui pemenangnya.
int n, 						//Variabel ini digunakan untuk mendefinisikan banyaknya baris dan kolom pada papan SOS.
	sCol, 					//Variabel ini digunakan untuk menyimpan pilihan kolom yang diinput oleh user. Selain digunakan untuk menyimpan pilihan kolom yang diinput oleh user, variabel ini juga digunakan untuk computer dalam merandom kolom
	sRow;					//Variabel ini digunakan untuk menyimpan pilihan baris yang diinput oleh user. Selain digunakan untuk menyimpan pilihan baris yang diinput oleh user, variabel ini juga digunakan untuk computer dalam merandom baris
char symbol;				//Variabel ini digunakan untuk computer menyimpan huruf (S/O) pada papan SOS

/*Seluruh alur proses permainan dari mulai awal hingga akhir berada pada modul utama (main program)*/
int main() {
	int OptionFromUser;		//Variabel ini digunakan untuk pada saat user ingin pindah dari satu tampilan ke tampilan lain
	
 	loadingScreen();
 	do {					
 		tampilanMenu();
 		gotoxy(76,20);
 		scanf("%d", &OptionFromUser);
  		if(OptionFromUser == 1) {
   			do{			
   				tampilModePermainan();
	 			gotoxy(81,15);
 				scanf("%d", &OptionFromUser);
				if(OptionFromUser == 1) {
	   				InputNameFromUser1();
	   				do{	
	   					tampilanLevel();
						scores[0] = 0;
						scores[1] = 0;
			   			gotoxy(86,19);
 						scanf("%d", &OptionFromUser);						
						if(OptionFromUser == 1){
							n = 3;
							scoreBoard();
							resetBoard();
							prosesInGamePvC();
							gameOver();
							hasilPertandingan();													
			   				system("pause");
						}else if(OptionFromUser == 2){
							n = 5;
							scoreBoard();
			  				resetBoard();
							prosesInGamePvC();
							gameOver();
							hasilPertandingan();
							system("pause");
						}else if(OptionFromUser == 3){
							n = 7;
							scoreBoard();
			  				resetBoard();
							prosesInGamePvC();
							gameOver();
							hasilPertandingan();
							system("pause");		
						}
			   				}while(OptionFromUser != 0);	
	  			}else if(OptionFromUser == 2){
	  				InputNameFromUser2();
	  				scores[0] = 0;
					scores[1] = 0;
		  			n = 7;
		  			scoreBoard();
		  			resetBoard();
					prosesInGamePvP();
					gameOver();
					hasilPertandingan();					
					system("pause");
	  			}
		   			}while(OptionFromUser != 0); 		
  		}else if(OptionFromUser == 2){
  			do{				
  				howToPlay();
  				scanf("%d", &OptionFromUser);			
			  }while(OptionFromUser != 0);
		}else if(OptionFromUser == 3){
   			exit(1);
  		}	
			}while(OptionFromUser != 3);
 	return 0;
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan tampilan menu
I.S : Tampilan menu pada game SOS belum tampil
F.S : Tampilan menu pada game SOS tampil
=========================================================================*/
void tampilanMenu() {
 system("cls");
 tampilanSOS();
 warnateks(WHITE);
 printf("\t\t\t\t==========================================================\n");
 printf("\t\t\t\t\t\t       MAIN MENU\n");
 printf("\n");
 printf("\t\t\t\t\t\t      1. PLAY\n");
 printf("\t\t\t\t\t\t      2. HOW TO PLAY\n");
 printf("\t\t\t\t\t\t      3. EXIT\n"); 
 printf("\n\n");
 printf("\t\t\t        CHOOSE THE MENU (INPUT NUMBER 1, 2, OR 3) : ");
 printf("\n\n");
 printf("\t\t\t\t==========================================================\n"); 
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan mode permainan
I.S : Tampilan mode permainan pada game SOS belum tampil
F.S : Tampilan mode permainan pada game SOS tampil
=========================================================================*/
void tampilModePermainan(){
 system("cls");
 warnateks(LIGHT_YELLOW);
 printf("\n\n");
 printf("\t\t      ЫЫЫЫЫЫЫЫЫ  ЫЫЫЫЫЫ  ЫЫЫЫЫ ЫЫЫЫЫ ЫЫЫЫЫЫЫ     ЫЫЫЫЫ ЫЫЫЫЫ  ЫЫЫЫЫ  ЫЫЫЫЫЫ  ЫЫЫЫЫЫЫ   \n");
 printf("\t\t      Ы         Ы      Ы Ы   ЫЫЫ   Ы Ы           Ы   ЫЫЫ   Ы Ы     Ы Ы     Ы Ы         \n");
 printf("\t\t      Ы   ЫЫЫЫЫ Ы      Ы Ы         Ы ЫЫЫЫЫЫЫ     Ы         Ы Ы     Ы Ы    Ы  ЫЫЫЫЫЫЫ   \n");
 printf("\t\t      Ы       Ы Ы ЫЫЫЫ Ы Ы ЫЫЫ ЫЫЫ Ы Ы           Ы ЫЫЫ ЫЫЫ Ы Ы     Ы Ы   Ы   Ы         \n");
 printf("\t\t      ЫЫЫЫЫЫЫЫЫ ЫЫЫ  ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫЫЫЫЫ     ЫЫЫ ЫЫЫ ЫЫЫ  ЫЫЫЫЫ  ЫЫЫЫ    ЫЫЫЫЫЫЫ   \n");
 printf("\n");
 warnateks(WHITE);
 printf("\t\t\t    НННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННН  \n");
 printf("\n\n");
 printf(" \t\t\t\t   -----------------------  \t  ---------------------\n");
 printf("\t\t\t\t  | 1. Player vs Computer | \t | 2. Player vs Player |\n");
 printf("\t\t\t\t   -----------------------  \t  ---------------------\n");
 printf("\n");
 printf("\t\t\t\t\tCHOOSE GAME MODE (INPUT NUMBER 1 OR 2) : ");
 printf("\n\n");
 printf("\n");
 printf("\t\t\t\t\tInput Number 0 For Back to Main Menu");
 printf("\n");
 printf("\t\t\t\t==========================================================\n");
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan how to play yang diambil dari file How To Play.txt
I.S : Tampilan how to play pada game SOS belum tampil
F.S : Tampilan how to play pada game SOS tampil
=========================================================================================*/
void howToPlay(){
	FILE *how_to_play = NULL;
	system("cls");
	printf("\t\t\t\t -------------\n");
	printf("\t\t\t\t| HOW TO PLAY |\n");
	printf("\t\t\t\t -------------\n");
	char isiHowToPlay[250];
	
	how_to_play = fopen("How To Play.txt", "r");
	if(how_to_play == NULL){
		printf("File Doesn't Exist");
	}else {
		while(fscanf(how_to_play,"%[^\n]%*c", isiHowToPlay) == 1){
			printf("\n%s\n", isiHowToPlay);
		}
	}
	fclose(how_to_play);
	printf("\n\n");
	printf("\n\nInput Number 0 For Back to Main Menu : ");
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan beberapa level dalam permainan SOS  dan user diharuskan 
untuk memilih level untuk memulai permainan SOS ini
I.S : Level permainan belum tampil
F.S : Level permainan tampil di layar
=============================================================================================*/
void tampilanLevel(){
 system("cls");
 warnateks(LIGHT_YELLOW);
 printf("\n\n");
 printf("\t\t\t\t Ы         ЫЫЫЫЫЫЫЫЫ  Ы        Ы  ЫЫЫЫЫЫЫЫЫ   Ы          \n");
 printf("\t\t\t\t Ы         Ы          Ы        Ы  Ы           Ы          \n");
 printf("\t\t\t\t Ы         Ы          Ы        Ы  Ы           Ы          \n");
 printf("\t\t\t\t Ы         ЫЫЫЫЫЫЫЫЫ  Ы        Ы  ЫЫЫЫЫЫЫЫЫ   Ы          \n");
 printf("\t\t\t\t Ы         Ы           Ы      Ы   Ы           Ы          \n");
 printf("\t\t\t\t Ы         Ы            Ы    Ы    Ы           Ы          \n");
 printf("\t\t\t\t ЫЫЫЫЫЫЫЫЫ ЫЫЫЫЫЫЫЫЫ     ЫЫЫЫ     ЫЫЫЫЫЫЫЫЫ   ЫЫЫЫЫЫЫЫЫ  \n");
 printf("\n\n");
 printf("\t\t\t    ННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННН  \n");
 warnateks(WHITE);
 printf("\n\n");
 printf("\n");
 printf(" \t\t\t\t\t   ННННН\t ННННН\t      ННННН\n");
 printf("\t\t\t\t\t   | 1 | \t | 2 |\t      | 3 |\n");
 printf(" \t\t\t\t\t   ННННН\t ННННН\t      ННННН\n");
 printf("\n");
 printf("\t\t\t\t\tCHOOSE LEVEL GAME (INPUT NUMBER 1, 2, OR 3) : ");
 printf("\n\n");
 printf("\n");
 printf("\t\t\t\t\tInput Number 0 For Back to Main Menu");
 printf("\n");
 printf("\t\t\t\t==========================================================\n");
 printf("\n\n");
 printf("\n\n");
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan papan skor pada permainan SOS
I.S : papan skor belum tampil pada permainan SOS
F.S : papan skor tampil tampil pada permainan SOS
=========================================================================*/
void scoreBoard(){
	system("cls");
	printf("\n\t%d %s\t\tVS\t\t%s %d", scores[0], name[0] , name[1], scores[1]);
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menginsialisasi seluruh kotak yang ada pada papan sos dengan karakter spasi 
I.S : seluruh kotak yang ada pada papan sos belum diinisialisasi dengan karakter spasi
F.S : seluruh kotak yang ada pada papan sos diinisialisasi sudah diinisialisasi dengan karakter spasi 
======================================================================================================*/
void resetBoard(){
	int i,j;
	for( i=0; i<n; i++){
		for( j=0; j<n; j++){
			sos[i][j] = ' ';
		}
	}
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan papan permainan SOS
I.S : papan permainan SOS belum tampil
F.S : papan permainan SOS tampil
=========================================================================*/
void papanSOS() {
	int i,j;
	printf("\n\n\n");
	// top line
	for (i = 1; i < (n + 2) * 6 + 2; i++) {
		printf("\xdb");
	}
	printf("\n\xdb\xdb ");
	for (i = 0; i <= n; i++) {
		if (!i) printf("\xda\xc4\xc4\xc4\xc4\xc4\xc2");
		else if (i == n) printf("\xc4\xc4\xc4\xc4\xc4\xbf");
		else printf("\xc4\xc4\xc4\xc4\xc4\xc2");
	}
	 // gameboard
	printf(" \xdb\xdb");
	for (i = 0; i <= n; i++) {
		printf("\n\xdb\xdb ");
		for (j = 0; j <= n; j++) {
		if (!i && !j) printf("\xb3     ");
		else if (!i && j == n) printf("\xb3 %2d  \xb3 ", j);
		else if (!i) printf("\xb3 %2d  ", j);
		else if (!j) printf("\xb3 %2d  \xb3 ", i);
		else if (sRow && sCol && sRow == i && sCol == j) printf("\xdb\xdb  \xb3 ");
		else if (sos[i - 1][j - 1] == 'S' || sos[i - 1][j - 1] == 'O') printf(" %c  \xb3 ", sos[i - 1][j - 1]);
		else printf("  %c \xb3 ", sos[i - 1][j - 1]);
		}
		printf("\xdb\xdb\n\xdb\xdb ");
		for (j = 0; j <= n; j++) {
		if (i == n && !j) printf("\xc0\xc4\xc4\xc4\xc4\xc4");
		else if (i == n) printf("\xc1\xc4\xc4\xc4\xc4\xc4");
		else if (!j) printf("\xc3\xc4\xc4\xc4\xc4\xc4");
		else printf("\xc5\xc4\xc4\xc4\xc4\xc4");
		if (i == n && j == n) printf("\xd9");
		else if (j == n) printf("\xb4");
		}
		printf(" \xdb\xdb");
	}
	 // bottom line
	printf("\n");
	for (i = 1; i < (n + 2) * 6 + 2; i++) {
		printf("\xdb");
	}
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk membuat proses alur permainan game SOS pada mode player vs player
I.S : alur proses permainan pada mode player vs player tidak berjalan
F.S : alur proses permainan pada mode player vs player berjalan sesuai harapan
===========================================================================================*/
void prosesInGamePvP(){
	int counter = 1;	//Variabel ini digunakan untuk counter pada perulangan yang ada pada modul prosesInGamePvP().
	scores[0] = 0;
	scores[1] = 0;
	while (counter <= n * n) {
		system("cls");
		sRow = 0; sCol = 0;
		scoreBoard();
		papanSOS();
		int input = takeInput();
		if (input) {
			int point = controlSOS();
			if (!point) {
				currentPlayer = (currentPlayer + 1) % 2;
			}
			else {
				scores[currentPlayer] = scores[currentPlayer] + 1;
				printf("\xaf\xaf\xaf Congratulations, you take point in [%d][%d]", sRow, sCol);
				getch();
			}
			counter++;
		}
	}
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk membuat proses alur permainan game SOS pada mode player vs computer
I.S : alur proses permainan pada mode player vs computer tidak berjalan
F.S : alur proses permainan pada mode player vs computer berjalan sesuai harapan
==============================================================================================*/
void prosesInGamePvC(){
	while (!checkFreeSpace()) {
		system("cls");
		sRow = 0; sCol = 0;
		scoreBoard();
		papanSOS();
		if(currentPlayer == 0){
			int input = takeInput();
			if (input){
				int point = controlSOS();
				if (!point) {
					currentPlayer = (currentPlayer + 1) % 2;
				}
				else {
					scores[currentPlayer] = scores[currentPlayer] + 1;
					printf("\xaf\xaf\xaf Congratulations, you take point in [%d][%d]", sRow, sCol);
					getch();
				}
			}			
		}else{
			compMove();
			int point = controlSOS();
			if(point){
				scores[currentPlayer] = scores[currentPlayer] + 1;
				printf("\n\xaf\xaf\xaf Computer choose %c in [%d][%d]\n", symbol, sRow, sCol);
				getch();
				printf("\n\xaf\xaf\xaf Computer take point");
				getch();
			}else{
				currentPlayer = (currentPlayer + 1) % 2;
				printf("\n\xaf\xaf\xaf Computer choose %c in [%d][%d]", symbol, sRow, sCol);
				getch();
			}
		}
	}
}


/*Deskripsi Modul
Function (int)
Modul ini bertujuan untuk user menginputkan huruf S atau O ke dalam papan SOS
return 1 berarti user berhasil menginputkan huruf S atau O ke dalam papan SOS
return 0 berarti user gagal menginputkan huruf S atau O ke dalam papan SOS
==============================================================================*/
int takeInput() {
	do{
		fflush(stdin);
		printf("\n\n\xaf Player turn: %s\n", name[currentPlayer]);
		printf("\xaf Row: ");
		scanf("%d", &sRow);
		printf("\xaf Column: ");
		scanf("%d", &sCol);
		if (!(sRow > 0 && sRow <= n && sCol > 0 && sCol <= n)) {
			printf("\n\n\xaf\xaf Invalid position!!\n\xaf\xaf Press any key to continue!!");
			getch();
		}
	}while(!(sRow > 0 && sRow <= n && sCol > 0 && sCol <= n));

	switch (sos[sRow - 1][sCol - 1]) {

	case 'S':
	case 'O':   
		printf("\xaf\xaf Invalid position!!\n\xaf\xaf Press any key to continue!!");
		getch();
		return 0;

	default:    
		system("cls");
		scoreBoard();
		papanSOS();
		printf("\n\n\xaf Player turn: %s\n\xaf Row: %d\n\xaf Column: %d\n\xaf\xaf S/O? ", name[currentPlayer], sRow, sCol);
		char ch;
		scanf(" %c", &ch);
		switch (ch) {
		case 's':
		case 'S': 
			sos[sRow - 1][sCol - 1] = 'S'; 
			return 1;
		case 'o':
		case 'O': sos[sRow - 1][sCol - 1] = 'O'; return 1;
		}

		printf("\xaf\xaf Invalid letter!!\n\xaf\xaf Press any key to continue!!");
		getch();
		return 0;
	}
}


/*Deskripsi Modul
Function (int)
Modul ini bertujuan untuk mengecek SOS sudah terbentuk atau belum
Jika sudah terbentuk akan mengembalikan nilai 1
Jika belum terbentuk akan mengembalikan nilai 0
=========================================================================*/  
int controlSOS() {
	if (sos[sRow - 1][sCol - 1] == 'S') {
		if (sos[sRow - 3][sCol - 3] == 'S' && sos[sRow - 2][sCol - 2] == 'O') return 1; //diagonal kiri atas
		if (sos[sRow - 3][sCol - 1] == 'S' && sos[sRow - 2][sCol - 1] == 'O') return 1; //vertikal atas
		if (sos[sRow - 3][sCol + 1] == 'S' && sos[sRow - 2][sCol] == 'O') return 1;		//diagonal kanan atas
		if (sos[sRow - 1][sCol - 3] == 'S' && sos[sRow - 1][sCol - 2] == 'O') return 1;	//horizontal kiri
		if (sos[sRow - 1][sCol + 1] == 'S' && sos[sRow - 1][sCol] == 'O') return 1;		//horizontal kanan
		if (sos[sRow + 1][sCol - 3] == 'S' && sos[sRow][sCol - 2] == 'O') return 1;		//diagonal kiri bawah
		if (sos[sRow + 1][sCol - 1] == 'S' && sos[sRow][sCol - 1] == 'O') return 1;		//vertikal bawah 
		if (sos[sRow + 1][sCol + 1] == 'S' && sos[sRow][sCol] == 'O') return 1;			//diagonal kanan bawah
	}
	else {
		if (sos[sRow - 2][sCol - 2] == 'S' && sos[sRow][sCol] == 'S') return 1;			//diagonal
		if (sos[sRow - 2][sCol - 1] == 'S' && sos[sRow][sCol - 1] == 'S') return 1;		//vertikal
		if (sos[sRow - 2][sCol] == 'S' && sos[sRow][sCol - 2] == 'S') return 1;			//diagonal
		if (sos[sRow - 1][sCol - 2] == 'S' && sos[sRow - 1][sCol] == 'S') return 1;		//horizontal
	}
	return 0;
}


/*Deskripsi Modul
Function (int)
Modul ini bertujuan untuk computer menyimpan huruf S atau O pada kondisi tertentu
return 1 jika kondisi yang ada pada modul ini terpenuhi
return 0 jika kondisi yang ada pada modul ini tidak terpenuhi
==================================================================================*/
int controlBot(){
	/*Untuk Computer menyimpan huruf O pada papan*/
	if(sos[sRow - 2][sCol - 2] == 'S' && sos[sRow][sCol] == 'S'){
		symbol = 'O';	//diagonal 
		return 1;
	}else if(sos[sRow - 2][sCol - 1] == 'S' && sos[sRow][sCol - 1] == 'S'){
		symbol = 'O';	//vertikal
		return 1;
	}else if(sos[sRow - 2][sCol] == 'S' && sos[sRow][sCol - 2] == 'S'){
		symbol = 'O';	//diagonal
		return 1;
	}else if(sos[sRow - 1][sCol - 2] == 'S' && sos[sRow - 1][sCol] == 'S'){
		symbol = 'O';	//horizontal
		return 1;
	}

	/*Untuk Computer menyimpan huruf S pada papan*/
	if (sos[sRow - 3][sCol - 3] == 'S' && sos[sRow - 2][sCol - 2] == 'O'){
		symbol = 'S';	//diagonal
		return 1;	
	} 
	if (sos[sRow - 3][sCol - 1] == 'S' && sos[sRow - 2][sCol - 1] == 'O'){
		symbol = 'S';	//vertikal
		return 1;
	} 
	if (sos[sRow - 3][sCol + 1] == 'S' && sos[sRow - 2][sCol] == 'O'){
		symbol = 'S';	//diagonal
		return 1;	
	} 
	if (sos[sRow - 1][sCol - 3] == 'S' && sos[sRow - 1][sCol - 2] == 'O'){
		symbol = 'S';	//horizontal
		return 1;
	} 
	if (sos[sRow - 1][sCol + 1] == 'S' && sos[sRow - 1][sCol] == 'O'){
		symbol = 'S';	//horizontal
		return 1;	
	}
	if (sos[sRow + 1][sCol - 3] == 'S' && sos[sRow][sCol - 2] == 'O'){
		symbol = 'S';	//diagonal
		return 1;
	} 
	if (sos[sRow + 1][sCol - 1] == 'S' && sos[sRow][sCol - 1] == 'O'){
		symbol = 'S';	//vertikal
		return 1;
	} 
	if (sos[sRow + 1][sCol + 1] == 'S' && sos[sRow][sCol] == 'O'){
		symbol = 'S';	//diagonal
		return 1;
	} 		
	return 0;
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk alur proses computer pada saat melawan user modul ini hanya akan dipanggil di mode 
player vs computer
I.S : computer belum dapat melakukan pergerakan (input huruf S atau O ke dalam papan) pada saat melawan user
F.S : - alur proses computer pada saat melawan user berjalan sesuai harapan
	  - computer dapat melakukan pergerakan pada saat melawan user
=============================================================================================================*/
void compMove(){
	int x;	//untuk huruf O atau s
	system("cls");
	scoreBoard();
	papanSOS();
	srand(time(NULL));
	
	do{
		//baris kolom
		sRow = (rand() % n) + 1;
		sCol = (rand() % n) + 1;		
	}while(sos[sRow - 1][sCol - 1] != ' ');		
	if(!controlBot()){
		x = rand() % 2;
		if(x == 0){
			symbol = 'O';
		}else{
			symbol = 'S';
		}			
	}else {
		controlBot();
	}
	sos[sRow-1][sCol-1] = symbol;
}


/*Deskripsi Modul
Function (int)
Modul ini bertujuan untuk mengecek apakah papan SOS masih ada yang kosong atau tidak
return 0 berarti masih terdapat papan SOS yang belum diisi
return 1 berarti papan SOS sudah terisi semua
=========================================================================*/
int checkFreeSpace(){
	int freeSpace = n*n;
	for(sRow = 0; sRow < n; sRow++){
		for(sCol = 0; sCol < n; sCol++){
			if(sos[sRow][sCol] == ' '){
				return 0;
			}
		}
	}
	return 1;
}


/*Deskripsi Modul
Function (int)
Modul ini bertujuan untuk mengecek pemenang dalam permainan SOS
return 1 berarti terdapat pemenang dalam permainan SOS
return 0 berarti tidak terdapat pemenang (seri/draw)
=========================================================================*/
int checkWin(){
	if(scores[0] > scores[1]){
		strcpy(nameWinner, name[0]);
		return 1;
	}else if(scores[0] < scores[1]){
		strcpy(nameWinner, name[1]);
		return 1;
	}else{
		return 0;
	}
}

void kecepatan(float seconds){
	clock_t endwait;
	endwait=clock()+seconds*CLOCKS_PER_SEC;
	while(clock()<endwait){};
}


/*Deskripsi Modul
Prosedur
Modul ini untuk menampilkan gambar SOS berfungsi sebagai variasi pada User Interface
I.S : gambar SOS sebagai variasi pada User Inteface belum tampil
F.S : gambar SOS sebagai variasi pada User Inteface tampil
=====================================================================================*/
void tampilanSOS(){
 system("cls");
 warnateks(LIGHT_BLUE);
 printf("\n\n\n");
 printf("\t\t\t\t\t ЫЫЫЫЫЫЫ         ЫЫЫЫЫ         ЫЫЫЫЫЫЫ\n");
 printf("\t\t\t\t\tЫЫ             ЫЫ     ЫЫ      ЫЫ     \n");
 printf("\t\t\t\t\tЫЫ             ЫЫ     ЫЫ      ЫЫ\n");
 printf("\t\t\t\t\t ЫЫЫЫЫЫЫ       ЫЫ     ЫЫ       ЫЫЫЫЫЫЫ\n");
 printf("\t\t\t\t\t       ЫЫ      ЫЫ     ЫЫ             ЫЫ\n");
 printf("\t\t\t\t\t       ЫЫ      ЫЫ     ЫЫ             ЫЫ\n");
 printf("\t\t\t\t\t ЫЫЫЫЫЫЫ         ЫЫЫЫЫ         ЫЫЫЫЫЫЫ\n");
 printf("\n\n");
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan “game over” ketika permainan sudah berakhir 
(tidak ada papan kosong yang tersisa)
I.S : tampilan “game over” belum tampil ketika permainan berakhir
F.S : tampilan “game over” tampil ketika permainan berakhir
==================================================================================*/
void gameOver(){
	system("cls");
	warnateks(RED);
	printf("\n\n\n\n\n");
	printf("\t\t      ЫЫЫЫЫЫЫЫЫ  ЫЫЫЫЫЫ  ЫЫЫЫЫ ЫЫЫЫЫ ЫЫЫЫЫЫЫ      ЫЫЫЫЫ   Ы       Ы ЫЫЫЫЫЫЫ ЫЫЫЫЫЫЫ  \n");
 	printf("\t\t      Ы         Ы      Ы Ы   ЫЫЫ   Ы Ы           Ы     Ы  Ы       Ы Ы       Ы        \n");
 	printf("\t\t      Ы   ЫЫЫЫЫ Ы      Ы Ы         Ы ЫЫЫЫЫЫЫ     Ы     Ы   Ы     Ы  ЫЫЫЫЫЫЫ Ы        \n");
 	printf("\t\t      Ы       Ы Ы ЫЫЫЫ Ы Ы ЫЫЫ ЫЫЫ Ы Ы           Ы     Ы    Ы   Ы   Ы       Ы        \n");
 	printf("\t\t      ЫЫЫЫЫЫЫЫЫ ЫЫЫ  ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫЫЫЫЫ      ЫЫЫЫЫ      ЫЫЫ    ЫЫЫЫЫЫЫ Ы        \n");
 	printf("\n");
 	warnateks(WHITE);
 	printf("\t\t\t    НННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННН  \n");
	getch();
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan kondisi ketika menang, modul ini akan dipanggil oleh 
modul hasilPertandingan()
I.S : Tampilan saat menang tidak tampil
F.S : Tampilan saat menang tampil
=============================================================================================*/
void tampilanMenang(){
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t     ЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫ \n");
		printf("\t\t\t\t\t    Ы                         Ы      \n");
		printf("\t\t\t\t\t    Ы     Ы             Ы     Ы\n");
		printf("\t\t\t\t\t    ЫЫЫЫЫЫЫ   ЫЫЫЫЫЫЫ   ЫЫЫЫЫЫЫ\n");
		printf("\t\t\t\t\t          Ы   Ы     Ы   Ы      \n");
		printf("\t\t\t\t\t          Ы   ЫЫЫЫЫЫЫ   Ы      \n");
		printf("\t\t\t\t\t          Ы             Ы      \n");
		printf("\t\t\t\t\t          Ы             Ы      \n");
		printf("\t\t\t\t\t          ЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫ       \n");
		printf("\t\t\t\t\t                Ы  Ы           \n");
		printf("\t\t\t\t\t                Ы  Ы           \n");
		printf("\t\t\t\t\t              ЫЫЫ  ЫЫЫ         \n");
		printf("\t\t\t\t\t             ЫЫЫЫЫЫЫЫЫЫ        \n");
		printf("\t\t\t\t\t          ________________     \n");
		printf("\t\t\t\t\t        ____________________   \n");
		warnateks(WHITE);
		printf("\n\t\t\t\t\t Congratulation %s YOU WIN!!\n", nameWinner);
}


/*Deskripsi Modul
Prosedur
Modul ini bertujuan untuk menampilkan kondisi ketika tidak ada pemenang (draw/seri), 
modul ini akan dipanggil oleh modul hasilPertandingan()
I.S : Tampilan saat draw tidak tampil
F.S : Tampilan saat draw tampil
====================================================================================*/
void tampilanDraw(){
	printf("\n\n\n\n\n");
	printf("\t\t      ЫЫЫЫЫЫЫЫЫ  ЫЫЫЫЫЫ  ЫЫЫЫЫ ЫЫЫЫЫ ЫЫЫЫЫЫЫ   ЫЫЫЫЫЫ  ЫЫЫЫЫЫЫ  ЫЫЫЫЫЫ  Ы              Ы \n");
 	printf("\t\t      Ы         Ы      Ы Ы   ЫЫЫ   Ы Ы         Ы     Ы Ы       Ы      Ы  Ы            Ы  \n");
 	printf("\t\t      Ы   ЫЫЫЫЫ Ы      Ы Ы         Ы ЫЫЫЫЫЫЫ   Ы     Ы Ы       Ы      Ы   Ы          Ы   \n");
 	printf("\t\t      Ы       Ы Ы ЫЫЫЫ Ы Ы ЫЫЫ ЫЫЫ Ы Ы         Ы    Ы  Ы       Ы ЫЫЫЫ Ы    Ы   ЫЫ   Ы    \n");
 	printf("\t\t      ЫЫЫЫЫЫЫЫЫ ЫЫЫ  ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫЫЫЫЫ   ЫЫЫЫЫ   Ы       ЫЫЫ  ЫЫЫ     ЫЫЫ  ЫЫЫ     \n");
 	printf("\n");
 	warnateks(WHITE);
 	printf("\t\t\t    НННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННН  \n");
}

void loadingScreen(){
	tampilanSOS();
	loading();
}


/*Deskripsi Modul
Prosedur
Modul ini digunakan untuk menginputkan nama pemain jika user memilih mode permainan player vs komputer. 
Pada modul ini user akan menginputkan nama sebanyak 1 kali. 
I.S : Tampilan untuk tempat user menginputkan nama belum tampil
F.S : Tampilan untuk tempat user menginputkan nama tampil
=======================================================================================================*/
void InputNameFromUser1() {
	system("cls");
	char user1[15];
	warnateks(LIGHT_YELLOW);
 	printf("\n\n");	
 	printf("\t\t       ЫЫЫЫЫЫЫ ЫЫЫЫЫЫЫ ЫЫЫЫЫЫЫ ЫЫЫЫЫЫЫ ЫЫЫЫЫЫЫ    ЫЫЫЫЫЫЫ  ЫЫЫЫЫЫ  ЫЫЫЫЫ ЫЫЫЫЫ ЫЫЫЫЫЫЫ  \n");
 	printf("\t\t       Ы       Ы     Ы    Ы    Ы       Ы          Ы     Ы Ы      Ы Ы   ЫЫЫ   Ы Ы        \n");
 	printf("\t\t       ЫЫЫЫЫЫЫ Ы     Ы    Ы    ЫЫЫЫЫЫЫ Ы          Ы     Ы Ы      Ы Ы         Ы ЫЫЫЫЫЫЫ  \n");
 	printf("\t\t       Ы       Ы     Ы    Ы    Ы       Ы          Ы     Ы Ы ЫЫЫЫ Ы Ы ЫЫЫ ЫЫЫ Ы Ы        \n");
 	printf("\t\t       ЫЫЫЫЫЫЫ Ы     Ы    Ы    ЫЫЫЫЫЫЫ Ы          Ы     Ы ЫЫЫ  ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫ ЫЫЫЫЫЫЫ  \n");
 	printf("\n");
 	warnateks(WHITE);
 	printf("\t\t\t    НННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННН  \n");
	printf("\n\n\n");
	printf("\t\t\t\t\t\t      ___________________\n");
 	printf("\n");
	gotoxy(60,11); scanf("%s", &name[0][0]);
	strcpy(name[1], "Computer");
}


/*Deskripsi Modul
Prosedur
Modul ini digunakan untuk menginputkan nama pemain jika user memilih mode permainan player vs player. 
Pada modul ini user akan menginputkan nama sebanyak 2 kali. 
I.S : Tampilan untuk tempat user menginputkan nama belum tampil
F.S : Tampilan untuk tempat user menginputkan nama tampil
=======================================================================================================*/
void InputNameFromUser2() {
	system("cls");
	int i = 0;
	
	for(i = 1; i <= 2; i++) {
		printf("\n\n\n\n\n");
		printf("\t\t\t\t\t\t       ---------------------\n");
		printf("\t\t\t\t\t\t      | ENTER PLAYER %d NAME |\n", i);
		printf("\t\t\t\t\t\t       ---------------------\n");
		printf("\n\n");
		printf("\t\t\t\t\t\t      _______________________\n");	
	}
	gotoxy(62,9); scanf("%s", &name[0][0]);
	gotoxy(62,20); scanf("%s", &name[1][0]);
}


/*Deskripsi Modul
Prosedur
Modul ini digunakan untuk menampilkan hasil pertandingan setelah game berakhir
I.S : Hasil pertandingan belum diketahui
F.S : Hasil pertandingan diketahui
===============================================================================*/
void hasilPertandingan(){
	//buat pvc
	int win = checkWin();
	system("cls");
	warnateks(LIGHT_YELLOW);
	if(win){
		tampilanMenang();
	}else{
		tampilanDraw();
	}
}

void warnateks(int warna) //modul yang berfungsi untuk memberi warna ke karakter
{ 
	HANDLE hConsole; 
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, warna);
}

void gotoxy(int x, int y) {
    COORD coord;
     
    coord.X = x;
    coord.Y = y;
     
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loading()//modul untuk menapilkan tampilan loading
{ 
	int x = 28, y = 13, n;
	warnateks(WHITE);
	gotoxy(x,14); printf("\t\t\t     Please Wait");
	gotoxy(x,15);  printf("\t\tЙНННННННННННННННННННННННННННННННННННН»");
	gotoxy(x,16);printf("\t\tє                                    є");
	gotoxy(x,17);printf("\t\tИННННННННННННННННННННННННННННННННННННј");
	for(n=42;n<=75;n++){
		gotoxy(n,16);
		printf("Ы");
		kecepatan(0.04);
	};
}
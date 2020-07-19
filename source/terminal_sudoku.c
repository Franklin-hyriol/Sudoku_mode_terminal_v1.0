#include <stdio.h>
#include <stdlib.h>
#include <creaco.c> //point C  //copier creaco.h et creaco.c dans le dossier include de mingw

typedef enum boollean{
	false,
	true
}bool; 
    
    bool resolution = false; //pour annuler la fonction affichage() dans la fonction nouvelle_partie();
    bool clear = false; //pour savoir si on doit ou pas effacer l'ecran
    int mos_x = 20; //coordonne du curseur en x  
	int mos_y=9;   //coordonne du curseur en y 
	bool game_over = false;
	int niveau_facile[9][9] =  {7, 0, 0,  3, 4, 1,  9, 8, 0,
					            0, 0, 6,  2, 0, 0,  7, 0, 0,
					 		    4, 0, 0,  0, 9, 6,  1, 0, 2,
							    1, 0, 0,  0, 0, 2,  0, 0, 7,
							    2, 4, 0,  0, 0, 0,  0, 1, 5,
							    6, 0, 0,  1, 0, 0,  0, 0, 9,
							    3, 0, 4,  8, 2, 0,  0, 0, 1,
					 		    0, 0, 9,  0, 0, 3,  6, 0, 0,
					 		    0, 2, 1,  9, 6, 5,  0, 0, 4}; //Sudoku niveau facile

	char message_1[27] = "Une chiffre a ete placer.";
	char message_2[27] = " Deplacement du curseur. ";
	char message_3[27] = "SUDOKU by Franklin Hyriol";
	char message_4[27] = "NOOB sudoku (PressAnyKey)";
	int message = 0;//pour animé le personnage
	bool error = false; //Pour animé le personnage
	bool not_loop = false; // Pour arreter une boucle infinie dans endgame


void menu();
void affichage();
bool resoudre(int x, int y);
void valeur_utilisateur(int val, int coor_curX, int coor_curY); //valeur entrer par l'utilisateur
void curseur_et_actuallisation(); //deplacement du curseur et actuallisation de l'affichage (boucle de tout les evenements)
bool test(int val, int i, int j); //pour tester si une valeur peut etre entré ou non
bool endgame();
void nouvelle_partie();
int quiter();
int resoudre_sudoku(int x, int y);

int main(void){
	int couleur_bievenue = 9;
	if(couleur_bievenue == 9){
	set_color(couleur_bievenue);
	system("cls");
	printf("\n\t___________________________\n");
	printf("\t|                         |\n");
	printf("\t|   BIENVENU DANS SUDOKU  |\n");
	printf("\t|_________________________|\n\n");
	}
 
	menu();
	clear = true;
}

/*--------------------------------------------------*/

void affichage(){
	int couleur_affichage = 15;
	int i=0,j=0,k=0;
	system("cls");

	if(couleur_affichage == 15){
	set_color(15);
	gotoxy(17, 2);
	printf("SUDOKU\n");
	printf("\t+-------+-------+-------+\n\t");
	}	
		
			for(i=0;i<9;i++){
		     	for (j=0;j<13;j++){

			    	if(j == 0 || j == 4 || j == 8 || j == 12 ){
						set_color(15);
						printf("| ");
					}else{

						if((niveau_facile[i][k]) == 0){
							set_color(15);
							printf("* ");
						}else{
								switch(niveau_facile[i][k]){
									case 1:
						   				set_color(1);
						  				break;
									case 2:
										set_color(10);
										break;
									case 3:
										set_color(11);
										break;
									case 4:
										set_color(12);
										break;
									case 5:
										set_color(13);
										break;
									case 6:
										set_color(14);
										break;
									case 7:
										set_color(7);
										break;
									case 8:
										set_color(8);
										break;
									case 9:
										set_color(9);
										break;
								} // switch

				    			printf("%d ", niveau_facile[i][k]);
				    			
							}
						k++;
					}
					
				} // fin boucle j
		    
				k=0;

				if(i == 2 || i == 5){
					set_color(15);
	     			printf("\n\t+-------+-------+-------+\n\t");
				}else{
					printf("\n\t");
				}
			} //fin boucle i


         set_color(15);
		 printf("+-------+-------+-------+");
		 set_color(15);

		 gotoxy(8, 16);
printf("_________________________\n");
gotoxy(7, 17);
printf("(                         )\n");
gotoxy(7, 18);
printf("(                         )\n");
gotoxy(7, 19);
printf("(______ __________________)\n");

  if(resolution == false){
		 set_color(12);
		 gotoxy(7, 16);
		 if(message != 0 && error == true){
		    printf("\n\n\t%s\n\n", message_1);
		    error = false;
		}else if(message != 0 && error == false){
			printf("\n\n\t%s\n\n", message_2);
		}else{
			printf("\n\n\t%s\n\n", message_3);
		}
	}
		message++;
/////////////////////////////////////////////////////gladiateur

set_color(15);
printf("\t      V");
set_color(14);
printf("\n\t     ___\n");
printf("\t    /___\\\n");
printf("\t   (|0 0|)\n");
printf("\t __/{\\U/}\\_ ___/vvv\n");
printf("\t/ \\  {~}   / _|_P|\n");
printf("\t| /\\  ~   /_/   ||\n");
printf("\t| /\\  ~   /_/   ||\n");
printf("\t|_| (____)      ||\n");
printf("\t\\_]/______\\  /\\_||_/\\\n");
printf("\t   _\\_||_/_ |] _||_ [|\n");
printf("\t  (_,_||_,_) \\/ [] \\/\n");

////////////////////////////////////////////////////AIDE
	
	set_color(11);
	gotoxy(37, 3);
	printf("d\n");
	gotoxy(36, 4);
	printf("x\n");
	gotoxy(38, 4);
	printf("v:");
	printf(" Deplacement curseur\n");
	gotoxy(37, 5);
	printf("c\n");
	gotoxy(34, 7);
	printf("1-9: Entrer une valeur\n");
	gotoxy(36, 8);
	printf("0: Effacer une valeur");
	gotoxy(36, 9);
	printf("r: Recommencer la partie\n");
	gotoxy(36, 10);
	printf("s: Resoudre\n");
	gotoxy(36, 11);
	printf("m: Menu\n");
	gotoxy(36, 12);
	printf("q: Quiter\n");

//////////////////////////////////////////////////////////	 
	if(game_over == false){ //si le jeux n'est pas encore terminer
		curseur_et_actuallisation();
	}else{
		not_loop = true;
	}

} //fin fonction affichage


/*-------------------------------------------------------*/


void menu(){
	int x_res=0,y_res=0; //seulement pour empeche d'avoir une erreur hahahah :) 
	int couleur_menu = 10;
	if(couleur_menu == 10){
	  set_color(couleur_menu);
	  if(clear == true){system("cls");}
	  int choix;
	  printf("  >1-Nouvelle partie\n");
      printf("  >2-Resoudre un sudoku\n");
	  printf("  >3-Quiter\n\n");
	  printf("Votre choix: ");
	  scanf("%d", &choix);
	  switch(choix){
		  case 1:
		    affichage();
		  case 2:
		  	resoudre_sudoku(x_res, y_res);
		  case 3:
			exit(1);
		  default:
			printf("Choix non valide\n");
	    }
    }

}

/*-------------------------------------------------------*/

void valeur_utilisateur(int val, int coor_curX, int coor_curY){
	
	coor_curX = mos_x;
	coor_curY = mos_y;
/////////////////////////////////////////////////// CASE VIDE DANS LA 1ere LIGNE
	if(coor_curX == 12 && coor_curY == 4 && test(val, 0, 1)){  //si la coordonnée du curseur et 12, 4 et la case est utilisable
		niveau_facile[0][1] = val;     
		error = false;		                                   //alors en entre la valeur de l'utilisateur dans le tableau
	}else{
		error = true; ///ON CHANGE LE MESSAGE DU PERSONNAGE
	}
	if(coor_curX == 14 && coor_curY == 4 && test(val, 0, 2)){
		niveau_facile[0][2] = val;     
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 30 && coor_curY == 4 && test(val, 0, 8)){
		niveau_facile[0][8] = val;     
		error = false;
	}else{
		error = true;
	}
 //////////////////////////////////////////////////CASE VIDE 2eme LIGNE
	if(coor_curX == 10 && coor_curY == 5 && test(val, 1, 0)){
		niveau_facile[1][0] = val;     
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 12 && coor_curY == 5 && test(val, 1, 1)){
		niveau_facile[1][1] = val;     
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 20 && coor_curY == 5 && test(val, 1, 4)){
		niveau_facile[1][4] = val;     
		error = false;
	}else{ 
		error = true;
	}
	if(coor_curX == 22 && coor_curY == 5 && test(val, 1, 5)){
		niveau_facile[1][5] = val;     
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 28 && coor_curY == 5 && test(val, 1, 7)){
		niveau_facile[1][7] = val;     
		error = false;
	}else{

		error = true;
	}
	if(coor_curX == 30 && coor_curY == 5 && test(val, 1, 8)){
		niveau_facile[1][8] = val;     
		error = false;
	}else{
		error = true;
	}
 ///////////////////////////////////////////////////////CASE VIDE 3eme LIGNE
	if(coor_curX == 12 && coor_curY == 6 && test(val, 2, 1)){
		niveau_facile[2][1] = val;     
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 14 && coor_curY == 6 && test(val, 2, 2)){
		niveau_facile[2][2] = val;      
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 18 && coor_curY == 6 && test(val, 2, 3)){
		niveau_facile[2][3] = val;      
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 28 && coor_curY == 6 && test(val, 2, 7)){
		niveau_facile[2][7] = val;      
		error = false;
	}else{
		error = true;
	}
 /////////////////////////////////////////////////////// 4
	if(coor_curX == 12 && coor_curY == 8 && test(val, 3, 1)){
		niveau_facile[3][1] = val;      
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 14 && coor_curY == 8 && test(val, 3, 2)){
		niveau_facile[3][2] = val;      
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 18 && coor_curY == 8 && test(val, 3, 3)){
		niveau_facile[3][3] = val;      
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 20 && coor_curY == 8 && test(val, 3, 4)){
		niveau_facile[3][4] = val;      
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 26 && coor_curY == 8 && test(val, 3, 6)){
		niveau_facile[3][6] = val;      
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 28 && coor_curY == 8 && test(val, 3, 7)){
		niveau_facile[3][7] = val;       
		error = false;
	}else{
		error = true;
	}
 //////////////////////////////////////////////////////////// 5
	if(coor_curX == 14 && coor_curY == 9 && test(val, 4, 2)){
		niveau_facile[4][2] = val;       
		error = false;
	}else{ 
		error = true;
	}
	if(coor_curX == 18 && coor_curY == 9 && test(val, 4, 3)){
		niveau_facile[4][3] = val;       
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 20 && coor_curY == 9 && test(val, 4, 4)){
		niveau_facile[4][4] = val;       
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 22 && coor_curY == 9 && test(val, 4, 5)){
		niveau_facile[4][5] = val;       
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 26 && coor_curY == 9 && test(val, 4, 6)){
		niveau_facile[4][6] = val;       
		error = false;
	}else{
		error = true;
	}
 //////////////////////////////////////////////////////////// 6
	if(coor_curX == 12 && coor_curY == 10 && test(val, 5, 1)){
		niveau_facile[5][1] = val;       
		error = false;
	}else{ 
		error = true;
	}
	if(coor_curX == 14 && coor_curY == 10 && test(val, 5, 2)){
		niveau_facile[5][2] = val;       
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 20 && coor_curY == 10 && test(val, 5, 4)){
		niveau_facile[5][4] = val;       
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 22 && coor_curY == 10 && test(val, 5, 5)){
		niveau_facile[5][5] = val;        
		error = false;
	}else{ 
		error = true;
	}
	if(coor_curX == 26 && coor_curY == 10 && test(val, 5, 6)){
		niveau_facile[5][6] = val;        
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 28 && coor_curY == 10 && test(val, 5, 7)){
		niveau_facile[5][7] = val;        
		error = false;
	}else{
		error = true;
	}
 //////////////////////////////////////////////////////////////// 7
	if(coor_curX == 12 && coor_curY == 12 && test(val, 6, 1)){
		niveau_facile[6][1] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 22 && coor_curY == 12 && test(val, 6, 5)){
		niveau_facile[6][5] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 26 && coor_curY == 12 && test(val, 6, 6)){
		niveau_facile[6][6] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 28 && coor_curY == 12 && test(val, 6, 7)){
		niveau_facile[6][7] = val;         
		error = false;
	}else{
		error = true;
	}
 ////////////////////////////////////////////////////////////// 8
	if(coor_curX == 10 && coor_curY == 13 && test(val, 7, 0)){
		niveau_facile[7][0] = val;          
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 12 && coor_curY == 13 && test(val, 7, 1)){
		niveau_facile[7][1] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 18 && coor_curY == 13 && test(val, 7, 3)){
		niveau_facile[7][3] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 20 && coor_curY == 13 && test(val, 7, 4)){
		niveau_facile[7][4] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 28 && coor_curY == 13 && test(val, 7, 7)){
		niveau_facile[7][7] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 30 && coor_curY == 13 && test(val, 7, 8)){
		niveau_facile[7][8] = val;       
		error = false;
	}else{
		error = true;
	}
 //////////////////////////////////////////////////////////// 9
	if(coor_curX == 10 && coor_curY == 14 && test(val, 8, 0)){
		niveau_facile[8][0] = val;         
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 26 && coor_curY == 14 && test(val, 8, 6)){
		niveau_facile[8][6] = val;        
		error = false;
	}else{
		error = true;
	}
	if(coor_curX == 28 && coor_curY == 14 && test(val, 8, 7)){
		niveau_facile[8][7] = val;         
		error = false;
	}else{
		error = true;
	}
}// fin fonction valeur_utilisateur


/*----------------------------------------------*/



bool resoudre(int x, int y){  // Attention, fonction recursive (resolution par BACKTRACKING)


	int num = 1;
	int tx = 0; // nombre temporaire
	int ty = 0;

	if(niveau_facile[x][y] != 0){ //si le nombre et != 0 alors en passe à la colone suivant sinon à la ligne
 
 	if(x == 8 && y == 8){  // si on arrive à la dernier case alors on a terminé
		return true;
	}

		if(x < 8){
			x++;
		}else{
			x = 0;
			y++;
		}

		if(resoudre(x ,y) == true){
			return true;
		}else{
			return false;
		}
	}// fin test nombre

    if(niveau_facile[x][y] == 0){ // BACKTRACKING
			while(num < 10){
				if(test(num, x, y) == true){
					niveau_facile[x][y] = num;

					if(x == 8 && y == 8){
						return true;
					}
				
					if(x < 8){
						tx = x + 1;
					}else{
						if(y < 8){
						tx = 0;
						ty = y + 1;
						}
					}

				if(resoudre(tx, ty)){
					return true;
				}
				
			}
			niveau_facile[x][y] = 0;
			num++;
		}
		return false;
	}
}
	



/*------------------------------------------*/

void curseur_et_actuallisation(){ // tout les evenements
	char mov;
	int x = 0; //variable fonction resoudre
	int y = 0; //variable fonction resoudre
	int valeur;
	gotoxy(mos_x, mos_y);
	do{
		while(kbhit()){ //Atendre l'appuie d'une touche
			mov = getch(); //mov recupère la valeur appuié
				switch(mov){
			 		case 'd':
						mos_y--;
			 			affichage();
			    		break;
					case 'c':
			    		mos_y++;
			    		affichage();
			    		break;
			 		case 'x':
			    		mos_x-=2;
			    		affichage();
			    		break;
			 		case 'v':
			 		    mos_x+=2;
			    		affichage();
			    		break;
			    	case 'm':
			    		system("cls");
			    		gotoxy(0, 0);
			    		menu();
			    		break;
			    	case 'q':
			    		quiter();
			    		break;
			 		case 'r':
			 			nouvelle_partie();
			 			break;
			 		case 's':
			 			resolution = true; // ne pas executer la fonction affichage dans nouvelle_partie
			 			nouvelle_partie(); //reinitialisation avant resolution 
			 			resoudre(x, y);  
			 			affichage();
			 			break;
			 		case '0':
			 			valeur = 0;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
			 			affichage();
			 			break;
			    	case '1':
			 			valeur = 1;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			 		case '2':
			 			valeur = 2;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			 		case '3':
			 			valeur = 3;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
				 	case '4':
			 			valeur = 4;
						valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			 		case '5':
			 			valeur = 5;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			 		case '6':
			 			valeur = 6;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			 		case '7':
			 			valeur = 7;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			 		case '8':
			 			valeur = 8;
			 			valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			 		case '9':
			 			valeur = 9;
						valeur_utilisateur(valeur, mos_x, mos_y);
						affichage();
						break;
			    } // switch
        }// fin while
    
    	
    	if(endgame() == true){ //fin de la partie
        	game_over = true;
        	while(!kbhit()){
        		if(game_over && resolution){
        			while(!kbhit()){
        					set_color(12);
							gotoxy(8, 18);
    						printf("%s", message_4);
    					if(!not_loop){
    						affichage();
    					}
    				}
    			}
    			if(game_over && !resolution){
    				while(!kbhit()){
    					printf("\n");
        				system("cls");
        				gotoxy(17, 9);
        				set_color(rand()%6);
        				printf("Vous avez gagne\n");
        				set_color(15);
        				gotoxy(17, 11);
        				printf("Press eny key\n");
        			}
        		}
			}
			quiter();
        } 
	}while(true);// boucle infinie
}

/*----------------------------------------------------------*/


bool test(int nbr, int i, int j){  //regle du jeu

	int k;
	bool absentSurLigne = true;
	bool absentSurColonne = true;
	bool absentSurBloc = true;

    for(k=0; k<9; k++){  //test d'absence sur ligne
    	if(niveau_facile[i][k] == nbr)
    		absentSurLigne = false;
    }

    for(k=0; k<9; k++){ // test d'absence sur colone
    	if(niveau_facile[k][j] == nbr)
    		absentSurColonne = false;
    }

    int l = i-(i%3), m = j-(j%3);  //variable pour test d'absence sur bloc

    for(i=l; i<l+3; i++){  // test d'absence sur bloc
    	for(j=m; j<m+3; j++){
    		if(niveau_facile[i][j] == nbr){
    			absentSurBloc = false;
    		}else{
    			absentSurBloc = true;
    		}
    	}
    }

    if(absentSurLigne && absentSurColonne && absentSurBloc){
    	return true;
    }else{
    	return false;
    }

}

/*-------------------------------------------------*/
bool endgame(){
	int i,j;
	bool fin = false;
	for(i=0; i<9; i++){  // Si il y a plus de case vide alors le jeux et terminer;
		for (j=0; j<9; j++){
			if(niveau_facile[i][j] == 0){
				fin = false;
				break;
			}else{
				fin = true;
			}
		}
	}
return fin;
}

/*------------------------------------------------*/


void nouvelle_partie(){
	niveau_facile[0][1] = 0;	
	niveau_facile[0][2] = 0;
	niveau_facile[0][8] = 0;
	niveau_facile[1][0] = 0;
	niveau_facile[1][1] = 0;
	niveau_facile[1][4] = 0;
	niveau_facile[1][5] = 0;
	niveau_facile[1][7] = 0;
	niveau_facile[1][8] = 0;
	niveau_facile[2][1] = 0;
	niveau_facile[2][2] = 0;
	niveau_facile[2][3] = 0;
	niveau_facile[2][7] = 0;
	niveau_facile[3][2] = 0;
	niveau_facile[3][3] = 0;
	niveau_facile[3][4] = 0;
	niveau_facile[3][6] = 0;
	niveau_facile[3][7] = 0;
	niveau_facile[4][2] = 0;
	niveau_facile[4][3] = 0;
	niveau_facile[4][4] = 0;
	niveau_facile[4][5] = 0;
	niveau_facile[4][6] = 0;
	niveau_facile[5][1] = 0;
	niveau_facile[5][2] = 0;
	niveau_facile[5][4] = 0;
	niveau_facile[5][5] = 0;
	niveau_facile[5][6] = 0;
	niveau_facile[5][7] = 0;
	niveau_facile[6][5] = 0;
	niveau_facile[6][6] = 0;
	niveau_facile[6][7] = 0;
	niveau_facile[7][0] = 0;
	niveau_facile[7][1] = 0;
	niveau_facile[7][3] = 0;
	niveau_facile[7][4] = 0;
	niveau_facile[7][7] = 0;
	niveau_facile[7][8] = 0;
	niveau_facile[8][0] = 0;
	niveau_facile[8][6] = 0;
	niveau_facile[8][7] = 0;

	message = 0;

if(resolution == false){ //utilisation de bool resolution = false;
	
	affichage();
}
	
}

/*-------------------------------------------------*/

int quiter(){
	gotoxy(0, 33);
	set_color(15);
exit(1);
}

int resoudre_sudoku(int x, int y){
	system("cls");
	gotoxy(2, 2);
	printf("En cours de devellopement :)\n");
	printf("près Dans une semaine\n");
}
// ldd: -lncurses
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

unsigned int board[4][4] ; 

void init_board () {
  for (int f = 0 ; f<4 ; f++) {
    for (int g  = 0 ; g<4 ; g++) {
      board[f][g]=0 ; 
    }
  }
}

unsigned int score = 0 ; 

void display_board () {
  move(0, 0);                                                                                                                                                                      
  printw("==2048===========================================================================\n") ; 
  printw("==================================================================== score :    %i\n", score) ; 
  
  move(LINES + 1, COLS + 1); 
  printw("+ ") ; 
  for (int i  =0 ; i<4 ; i++) {
    for (int b  =0 ; b<9 ; b++) {
      printw("- ") ; 
    }
    printw("+ "); 
  } 
  printw("\n") ; 
  
  for (int e = 0 ; e<4 ; e++) {
    //affichage de 4 lignes avec |                 | etc.... sur la ligne x4
    for (int d  = 0 ; d<3 ; d++) {
      printw("| ") ; 
      for (int a = 0 ; a<4 ; a++) {
        for (int c = 0 ; c<9; c++) {
          printw("  ") ; 
        }
        printw("| ") ; 
      }
      printw("\n") ; 
    }
    
    
    //affichage de la ligne intermediaire avec + - - - - - - - - + 
    printw("+ ") ; 
    for (int i  =0 ; i<4 ; i++) {
      for (int b  =0 ; b<9 ; b++) {
        printw("- ") ; 
      }
      printw("+ "); 
    }
    printw("\n") ;
  }
  printw("\n") ;
  printw("\n") ; 
}

void display_values() {
  int va= 4 ;
  for (int a = 0 ; a< 4; a++) {
    int vb  = 10 ; 
    for (int b = 0 ; b< 4 ; b++)  { 
      if (board[a][b]==2) {
        move(va , vb) ; 
      	printw("%i", board[a][b]) ; 
      	vb = vb + 20 ;
      }
    }
    va = va + 4 ;
  }
}

void INIT_2048 () {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho(); 
  srand(time(NULL));
}

void DONE_2048() {
  endwin();
  exit(0);
}

//2e partie de 2048 avec exo 30 

int count_empty () {
  int count  = 0 ; 
  for (int a = 0 ; a <4 ; a++) {
    for (int b  =0 ; b<4 ; b++) {
      if (board[a][b] == 0) {
        count ++ ; 
      }
    }
  }
  return count ; 
}

void add_two (int empty) {
  int nombre = rand()%(empty+1) ; 
  int cmp = 0 ; 
  //boucle qui parcourt les lignes
  for (int a = 0 ; a <4 ; a++) {
    
    //boucle qui parcourt les colonnes 
    for (int b = 0 ; b<4 ; b++) {
      
      //si la case est libre 
      if (board[a][b] == 0) {
        //on retire 1 au nombre 
        cmp ++ ; 
        //nombre = nombre-1 ; 
        //et si le nombre vaut 0, on a atteint la case souhaitée alors on ajoute 2 à celle ci 
        if (nombre==cmp) {
          board[a][b] = 2 ; 
        }
      }
    }
  }
}

int game_over (int add) {
  int count = count_empty() ; 
  
  if (count == 0) {
    printw("\n") ; 
    printw("========================================== Game Over ==========================================\n") ; 
    printw("========================================= Press a key =========================================\n") ; 
    getch() ; 
    return 1 ; 
  }
  
  else if (count >0 && add==TRUE) {
    add_two(count) ;
    display_board() ; 
    display_values() ; 
    refresh() ;
    return 0 ; 
  }
  else {
    return 0 ; 
  }
}



int main ()  {
  int add  = 1 ; 
  INIT_2048() ; 
  while(!game_over(add)) {
    getch() ; 
  }
  //display_board() ; 
  //refresh() ; 
  //init_board() ; 
  //refresh() ; 
  //display_values() ; 
  //refresh() ; 
  //getch() ; 
  DONE_2048() ; 
}

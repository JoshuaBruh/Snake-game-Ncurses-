/*#include <ncurses.h> 
using namespace std;





//TUTORIAL 1 e 2: ncurses setup and hello world

int main(int argc, char ** argv) {
    initscr(); // initializes the screen, sets up memory and clears the screen

    int x, y;
    x = y = 10;
    move (y, x); // moves the cursor to the specified location


    printw("Hello world"); //prints a string (const char *) to a window


    refresh(); // refreshes the screen to match whats in memory


    int c = getch(); // waits for user input, return int value of that key
    

    clear(); //clears the screen

    
    
    //move (0,0);
    //printw("%d", c);
    mvprintw(0, 0, "%d", c); //move and print as one, first the coordinates then the type of the argument(%d means decimal integer) and then the argument itself


    getch();


    //noecho(); 
    //curs_set(0);


    endwin(); // deallocates memory and ends ncurses
    return 0;

}
*/





//TUTORIAL 3 e 4: box e window
/*
int main(int argc, char ** argv) {

    initscr();


    //cbreak(); //with this you can use ctrl+c to exit your ncurses program (helps if you use the bash, in which that command usually breaks the execution, in ncurses you have to specify that)
    //raw(); //it takes every keyboard command as raw, so ctrl+c will be counted as two characters (doesn't accept special character combinations)
    noecho(); //whathever Input is given from the keybord it is not shown on the screen

    int height, width, start_y, start_x;
    height = 10;
    width = 20;
    start_y = start_x = 10;
    WINDOW * win = newwin(height, width, start_y, start_x); //Variable that provides a virtual window, passed with a pointer


    refresh(); //after creating a window we need to refresh so the screen knows that we created one and displays it (refreshes the whole screen)

    char c = '~';
    box(win, (int)c, 103); //creates a box based on the window coordinates (around the edges of the window), takes other two parameters, which if are 0 then we are creating a default box, otherwise the first is about the left and the right pattern, the second is for the top and bottom)
    //wborder(win, left, right, top, bottom, tlc, trc, blc, brc); // to customize the box completely (tlc=top left corner, blc=bottom left corner)


    wprintw(win, "Box"); //prints the text where the cursore is, in this case the top left corner of the box
    mvwprintw(win, 2, 5, "Box"); //prints the text in the given coordinates (based on the window coordinates)


    wrefresh(win); //refreshes a specific window so it represents the box


    //the window and the box are allocated in the memory at this point but without refreshing they are not shown in the terminal (what's on the screen is different from what's in the memory)


    getch();
    getch();


    endwin();
    
    return 0;
}
*/





//TUTORIAL 5: Attributi e Colori
/*
int main(int argc, char ** argv) {

    initscr();
    if(!has_colors()){
        printw("Terminal does not support colors");
        getch();
        return -1;
        
    }
    if(!can_change_color()){
        printw("Terminal does not support change of colors");
        getch();
        return -1;
        
    }
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_CYAN ); //pair of foreground and background color, the 1 is the "pair ID"
    init_color(COLOR_CYAN, 800, 800, 489); //Changes the color cyan, the values refer to r-g-b values and they go from 0 to 999


    //A_NORMAL
    //A STANDOUT
    //A_REVERSE
    //A_BLINK
    //A_DIM
    //A_BOLD
    //A_PROTECT
    //A_INVIS
    //A_ALTCHARSET
    //A_CHARTEXT


    //attron(A_STANDOUT); //the attributes are terminal dependent so they will not always work
    attron(COLOR_PAIR(1));


    printw("Hello World");


    //attroff(A_STANDOUT);
    attroff(COLOR_PAIR(1));


    //COLOR_PAIR(n)
    //Black 0
    //Red 1
    //Green 2
    //Yellow 3
    //Blue 4
    //Magenta 5
    //Cyan 6
    //White 7
    getch();
    getch();
    endwin();


    
    return 0;
}
*/





//TUTORIAL 6 e 7: User Input e Prototipo di Menù

/*
int main(int argc, char ** argv) {

    initscr();
    noecho();
    cbreak();

    int y, x, ybeg, xbeg, ymax, xmax;
    getyx(stdscr, y, x); //gets the current position of the cursore in the specified window and puts them in the y and x variables
    getbegyx(stdscr, ybeg, xbeg); //gets the top left of the window
    getmaxyx(stdscr, ymax, xmax); //gets the height and width of the window
    //printw("%d %d %d %d %d %d", y, x, ybeg, xbeg, ymax, xmax);

    //printw("\n");
    //mvprintw(ymax/2, xmax/2, ":) <- is in the middle of the terminal \n");


    WINDOW * win = newwin(ymax-10, xmax-10, 1, 1);
    refresh();
    
    //getyx(win, y, x); 
    //getbegyx(win, ybeg, xbeg); 
    //getmaxyx(win, ymax, xmax);
    //printw("%d %d %d %d %d %d", y, x, ybeg, xbeg, ymax, xmax);


    box(win, 0, 0);
    wrefresh(win);


    keypad(win, true); // makes us use keyword like KEY_UP or KEY_F(1...12) for F1 ... F12


    //int c = wgetch(win);
    //if(c == 'j' || c == KEY_UP){
        //mvwprintw(win, 1, 1, "You pressed j or Key-up");
        //wrefresh(win);
    //}


    string choices[3] = {"Walk", "Jog", "Run"};
    int choice;
    int highlight = 0;


    while(1){  //infinite loop until a choice is made
        for(int i=0; i<3; i++){
            if(i == highlight){
            wattron(win, A_REVERSE );                //Attribute on for a specific window
            }
            mvwprintw(win, i+1, 1, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);
        switch (choice){
            case KEY_UP:
             highlight--;
             if(highlight == -1){
                    highlight = 2;
             }
             break;
            case KEY_DOWN:
             highlight++;
             if(highlight == 3){
                    highlight = 0;
             }
             break;
            default:
             break;
        }
        if(choice == 10){
         break;
        }
    }

    printw("Your choice was: %s", choices[highlight].c_str());




    getch();
    getch();
    endwin();


    
    return 0;
}
*/





//TUTORIAL 8 e 9: Player movement e Refresh usando l'header file player.hpp

/*
#include "include/player.hpp"
int main(int argc, char ** argv) {

    initscr();
    noecho();
    cbreak();

    int ymax, xmax;
    
    getmaxyx(stdscr, ymax, xmax); //gets the height and width of the window
    

    WINDOW * win = newwin(ymax-10, xmax-10, 1, 1);
    refresh();
    
    
    box(win, 0, 0);
    wrefresh(win);


    Player * p = new Player(win, 1, 1, '@');
    do {
        p->display();
        wrefresh(win);
    } while(p->getmv() != 'x');




    //ncurses works with a virtual screen and the physical screen, the virtual screen in in memory and is a virtual representation,
    //when you add something you add it to the virtual screen, it gets written in the memory but non necessarily to the physical screen,ù
    //refresh() will take what is on the virtual window and display to the physical screen, but it will just refresh the standard screen,
    //a box will not be represented for example, because the box is within a window that we create, so we need to use wrefresh(win)
    //it is better not to use refresh and wrefresh too much because it is expensive, so refresh only the window that got changed only when it gets changed
    
    
    //wgetch(win) actually displays the window without using wrefresh

    

    getch();
    getch();
    endwin();


    
    return 0;
}
*/





//TUTORIAL 10 e 11: Tipi di Input e data attributes

/*
int main(int argc, char ** argv) {

    initscr();
    noecho();
    start_color();


    //cbreak(); //it affects inputs, when you use getch for example, the input goes in a buffer and when it is cleared the information
                //goes to the terminal, so there is a delay between the user typing a character and the terminal getting it
                //cbreak gets rid of the line buffering so the input is immediatly available to the program


    //halfdelay(50); //makes the input immediatly available without the buffer but it adds a delay in terms of an int which represents tenths of a seconds
                     //if nothing is passed during that time it returns -1


    //nodelay(stdscr, true); //makes the input immediatly available without the buffer, it doesn't wait for input so it print -1 everywhere


    //timeout(delay); //if the int is less than 0 it waits for our input,
                      //if it is 0 acts like nodelay and returns -1 everywhere
                      //if greater than 0 it waits that amount of time in milliseconds before returning -1 


    //int c;
    //while((c=getch()) != 'x'){
        //printw("%d\n", c);
    //}





    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    attr_t emphasis = A_REVERSE | COLOR_PAIR(2);  //used to store attribute data inside a variable equal to attron(A_REVERSE | COLOR PAIR(1))
    attron(emphasis);
    mvaddch(5, 5, 'a');
    mvaddch(5, 6, 'b');
    mvaddch(5, 7, 'c');
    mvaddch(5, 8, 'd');
    attroff(emphasis);


    chtype c = 'a' | A_REVERSE | COLOR_PAIR(1);
    mvaddch(9, 5, c); //mvaddch works with chtype, a char is considered a chtype without attributes

    getch();
    getch();
    endwin();


    
    return 0;
}
*/





//TUTORIAL 12 : riconoscere attributi e colori

/*
#include <time.h>
    void setupColorPairs(){
        srand (time(NULL));
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_CYAN, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }

    attr_t getRandomColor (int max_color_index){
        int color_pair_index = rand()% max_color_index+1;
        attr_t random_color = COLOR_PAIR(color_pair_index);
        return random_color;
    }


int main(int argc, char ** argv) {

    initscr();
    noecho();
    cbreak();
    start_color();
    setupColorPairs();



    WINDOW * output_win = newwin(1, 1, 5, 5);
    WINDOW * status_win = newwin(1, 58, 8, 8);
    refresh();
    wrefresh(output_win);
    wrefresh(status_win);


    bool reverse_on = false;
    char input = ' ';
    while(input != 'x'){

        mvwaddch(output_win, 0, 0, '@' | getRandomColor(7));

        string status = "";

        wnoutrefresh(output_win);

        chtype ch = mvwinch(output_win, 0, 0); //we extracted the charachter, chtype=64 bits, 48 for attributes, 8 for color, 8 for char


        attr_t color = ch & A_COLOR; //A_Color returns the chtype bits where every bit is 0 except fot the bits that defines the color

        if (color == COLOR_PAIR(4)){
            status = "Found color pair 4";
        }
        

        attr_t reversed = ch & (A_ATTRIBUTES ^ A_COLOR);
         if (reversed == A_REVERSE){
            status = " [REVERSED]";
        }
        







        werase(status_win);
        mvwprintw(status_win, 0, 1, status.c_str());
        wnoutrefresh(status_win);
        doupdate();
        input = tolower(getch());


        if (input == 'r'){
            if(reverse_on){
                wattrset(output_win, A_NORMAL);
                reverse_on = false;
            }
            else{
                wattrset(output_win, A_REVERSE);
                reverse_on = true;
            }
        }
    }



    getch();
    endwin();

    
    return 0;
}
*/





//TUTORIAL 13: Riconoscere combinazioni di caratteri
/*

#define ctrl(x) (x & 0x1F)
int main(int argc, char ** argv) {

    initscr();
    noecho();
    cbreak();
    start_color();


    char ch;
    while (ch = getch()){
        mvprintw(1, 0, "KEY NAME : %s - 0x%02x\n", keyname(ch), ch);//Get info about the character, the keyname (for a is a)
                                                                    //and the exadecimal value, works for combination likes ctrl-A
        //if (ch == ('a' & 0x1F)){
        if (ch == ctrl ('a')){
            mvprintw(0, 0, "Detected CTRL+a");
        }
        //if(ch == 'A') to detect if you pressed shift+a
    }

    endwin();

    
    return 0;
}
*/





//TUTORIAL 14(.1 .2 .3): Menu funzionante con header menu.cpp e sottomenu

/*#include "include/menu.hpp"


#define ctrl(x) (x & 0x1F)
int main(int argc, char ** argv) {

    initscr();
    noecho();
    curs_set(0); //Cursore doesn't show up
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    



    int ymax, xmax;
    getmaxyx(stdscr, ymax, xmax);
    WINDOW * win = newwin(ymax/2, xmax/2, ymax/4, xmax/4);
    box(win, 0, 0);
    refresh();
    




    //Soluzione non generalizzata, naive e poco riutilizzabile, difficile da cambiare e poco utile
    

    //Menubar/Menu:Inizialization
    mvwprintw(win, 0, 2, "File");//goes from column 2 to 6 since file has 4 letters
    mvwprintw(win, 0, 8, "Edit");
    mvwprintw(win, 0, 14, "Options");

    char ch;
    while(ch = wgetch(win)){
        //MenuBar: check user input to select menu 'x' and reset menus in default case
        switch(ch){
            case 'f':
              wattron(win, A_STANDOUT);
              mvwprintw(win, 0, 2, "File");
              wattroff(win, A_STANDOUT);
              mvwprintw(win, 0, 8, "Edit");
              mvwprintw(win, 0, 14, "Options");
              break;
            case 'e':
              wattron(win, A_STANDOUT);
              mvwprintw(win, 0, 8, "Edit");
              wattroff(win, A_STANDOUT);
              mvwprintw(win, 0, 2, "File");
              mvwprintw(win, 0, 14, "Options");
              break;
            case 'o':
              wattron(win, A_STANDOUT);
              mvwprintw(win, 0, 14, "Options");
              wattroff(win, A_STANDOUT);
              mvwprintw(win, 0, 2, "File");
              mvwprintw(win, 0, 8, "Edit");
              break;
            default:
              mvwprintw(win, 0, 2, "File");
              mvwprintw(win, 0, 8, "Edit");
              mvwprintw(win, 0, 14, "Options");
              break;
        }
    }
    

  


    //Soluzione Generalizzata, usando l'header menu.hpp

    string menu1[] = {"New", "Open", "Save", "Exit"};
    string menu2[] = {"Copy", "Cut", "Paste"};
    string menu3[] = {"Sidebar", "Terminal"};
    Menu menus[3] = {
        Menu("File", 'f', menu1, 4),
        Menu("Edit", 'e', menu2, 3),
        Menu("Options", 'o', menu3, 2)
    };

    MenuBar menubar = MenuBar(win, menus, 3);
    menubar.draw();


    char ch;
    while ((ch = wgetch(win))){
        menubar.HandleTrigger(ch);
        menubar.draw();
    }







    wgetch(win);


    endwin();

    
    return 0;
}
*/





//TUTORIAL 15  e 16: chgat (change attributes dynamically) and Clear Routines
/*
int main(int argc, char ** argv) {

    initscr();
    noecho();
    start_color();

    refresh();

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_RED);


    //int chgat(int n, attr_t attr, short color, const void *opts) the last one is always NULL
    //chgat, mvchgat, wchgat, mvwchgat  -> the first two are for the standard screen, the third and fourth are a generalization for any given window
    
    
    //chgat(-1, A_STANDOUT, 0, NULL);//n column in the first line are changed to standout with color pair 0, if n=-1 all the raw is converted
    move(3,5);
    chgat(-1, A_STANDOUT, 0, NULL);
    move(0,5);
    printw("Hello");//chgat doesn't update the cursore, so when you print something the attributes gets overwritten
                    //if chgat is after a printw it takes the starting point at the end of the word we printed
    //chgat(-1, A_STANDOUT, 0, NULL);
    mvchgat(0, 5, 5, A_NORMAL, 1, NULL);//we moved back to 0,5 so we could highlight Hello, and highlighted the first 5 characters





    move(0,1);

    getch();
    //all with their respective window variant, wclrtoeol(win) ecc
    clrtoeol(); //clear to the end of line, clears from where the cursore is to the end of the line
    getch();





    mvprintw(4, 0, "Everything below this should get cleared");

    mvprintw(6, 0, "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    mvprintw(8, 0, "this should get cleared");
    mvprintw(10, 0, "this should get cleared");
    move(4,5);

    getch();
    clrtobot(); // clear to the bottom from the cursore position
    getch();





    printw("Hello World");
    mvprintw(5, 5, "Hello World");
    mvprintw(10, 30, "Hello World");
    getch();
    erase();//erase doesn't call a function called clearedok, it's a soft clear
    getch();


    printw("Hello World");
    mvprintw(5, 5, "Hello World");
    mvprintw(10, 30, "Hello World");
    getch();
    clear();//erase calls a function called clearedok, it's a hard clear
    getch();


    getch();
    endwin();

    
    return 0;
}
    */




    //TUTORIAL 17, 18, 19, 20, 21, 22: Refresh, Deleting Windows, Custom Colors, Deleting Characters, Insert and Delete Lines

    /*#define COLOR_PINK 8
int main(int argc, char ** argv){
   initscr();
   noecho();
   refresh();

   start_color();//sets variables in the background

   //idLok(WINDOW*, bool);
   //idcok(WINDOW*, bool);
   //clearok(WINDOW*, bool);
   //immedok(WINDOW*, bool);
   //leaveok(WINDOW*, bool); 
   //scrollok(WINDOW*, bool);

   //WINDOW * win = newwin (5, 8, 10, 10);
   //box(win, 0, 0);


   //leaveok(win, true); //tells the terminal when you refresh a window it doesn't have to redraw the cursore
   //wmove(win, 1, 2);
   //wgetch(win);


   //immedok(win, true);//tells every addch or printw we need to refresh immediatly after, it degrades performance
   //waddch(win, 'a');


   //scrollok(win, true); //tells the window that is ok to scroll past the last line of the window, so an infinite loop will continue to give his output
   //int counter = 0;
   //while(true){
    //chtype ch = (counter % 10) + '0';
    //waddch(win, ch);
    //wrefresh(win);
    //counter++;
   //}


  //clearok(win, true); // tells the terminal that when we run refresh we refresh everything, if not ncurses just refreshes the cells that changed
  //clear calls clearok for example, so everything gets refreshed











  WINDOW * test_win = newwin(10, 25, 0, 0);
  box(test_win, 0, 0);
  refresh();
  wrefresh(test_win);


  //getch();


  wclear(test_win);
  wrefresh(test_win);//if you put this after the refresh mit might cause segmentation fault
  delwin(test_win);//deletes the memory of the window in the background
  refresh();
  //getch();




  printw("%-13s: %d\n%-13s: %d\n\n", "COLORS", COLORS, "COLOR_PAIRS", COLOR_PAIRS); //tells how many colors we can make
  printw("%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n\n",
     "COLOR_BLACK", COLOR_BLACK,
     "COLOR_RED", COLOR_RED,
     "COLOR_GREEN", COLOR_GREEN,
     "COLOR_YELLOW", COLOR_YELLOW,
     "COLOR_BLUE", COLOR_BLUE,
     "COLOR_MAGENTA", COLOR_MAGENTA,
     "COLOR_CYAN", COLOR_CYAN,
     "COLOR_WHITE", COLOR_WHITE);
  

  //with color pair we can make up to 256 combinations (from 0 to 255)
  init_color(COLOR_PINK, 967, 375, 554); //unlike other color tools that go from 1 to 256 init color goes from 0 to 1000 so you need to convert

  init_pair(1, COLOR_PINK, COLOR_BLACK);
  attron(COLOR_PAIR(1));
  printw("%-13s: %d\n%-13s: %d\n\n", "COLORS", COLORS, "COLOR_PAIRS", COLOR_PAIRS); //tells how many colors we can make
  printw("%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n%-13s: %d\n\n",
     "COLOR_BLACK", COLOR_BLACK,
     "COLOR_RED", COLOR_RED,
     "COLOR_GREEN", COLOR_GREEN,
     "COLOR_YELLOW", COLOR_YELLOW,
     "COLOR_BLUE", COLOR_BLUE,
     "COLOR_MAGENTA", COLOR_MAGENTA,
     "COLOR_CYAN", COLOR_CYAN,
     "COLOR_WHITE", COLOR_WHITE);
  attroff(COLOR_PAIR(1));
  









  
  WINDOW * win = newwin(10, 50, 0, 0);
  box (win, 0 ,0);
  mvwprintw(win, 1, 1, "Hello this is some text");
  refresh();
  wrefresh(win);
  //printw("Hello this is some text");
  getch();


  //int row, column;
  //row = column = 0;
  //move (0, 9);

  //delch();//Deletes the character wherever the cursore is, doesn't leave a hole, everything shifts
  //getch();
  wmove(win, 1, 8);
  wdelch(win);
  wgetch(win);
  //mvdelch(row, column);
  //getch();
  mvwdelch(win, 1, 10);
  wgetch(win);
  










  WINDOW * win = newwin(4, 25, 5, 5);
  refresh();
  wrefresh(win);


  mvwprintw(win, 0, 0, "1 Line of Text Here");
  mvwprintw(win, 1, 0, "2 Line of Text Here");
  mvwprintw(win, 2, 0, "3 Line of Text Here");
  mvwprintw(win, 3, 0, "4 Line of Text Here");
  wgetch(win);

  wmove(win, 1, 0);
  wgetch(win);
  //winsertln(win); //insert a line wherever the cursore is, everything is pushed down, if you push over the boundaries of the window it deletes the line
  //wdeleteln(win);   //deletes a line wherever the cursore is, everything is pushed up
  winsdelln(win, 2); //positive int: it adds that many lines, negative int: it deletes that many lines
  wgetch(win);








  getch();
  endwin();

    
  return 0;

}
*/
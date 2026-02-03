#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

#ifndef _MENU_H_
#define _MENU_H_

class Menu{
    public:
      int start_x;
      string text;
      char trigger;



      string * items;
      int num_items;
      int selected_item;

      Menu(string text, char trigger, string *items, int num_items){
        
        this->text= text;
        this->trigger= trigger;
        this->items= items;


        this->num_items= num_items;
        this->selected_item=0;
        
      }




      void selectNextItem(){
        selected_item++;
        if(selected_item >= num_items){
          selected_item = 0;
        }

      }
      void selectPrevItem(){
        selected_item--;
        if(selected_item < 0){
          selected_item = num_items-1;
        }
        
      }



};


class MenuBar{
    public:
      WINDOW * win;
      Menu *menus;
      int num_menus;
      int selected_menu;
      WINDOW * menuwin;



      MenuBar(WINDOW * win, Menu * menus, int num_menus){
        
        this->win= win;
        this->menus= menus;
        this->num_menus= num_menus;
        this->selected_menu= -1;





        int ymax, xmax, ybeg, xbeg;
        getmaxyx(win, ymax, xmax);
        getbegyx(win, ybeg, xbeg);
        menuwin = newwin(ymax-2, xmax-2, ybeg+1, xbeg+1);
        keypad(menuwin, true);
        wrefresh(menuwin);
        




        int current_pos = 2;
        for(int i = 0; i<num_menus; i++){
            this->menus[i].start_x = current_pos;
            current_pos += this->menus[i].text.length() + 2;
        }
        }





      void reset(){
        for(int i = 0; i<num_menus; i++){
            int start_x = this->menus[i].start_x;
            string text = this->menus[i].text;
            mvwprintw(win, 0, start_x, text.c_str());

        }
        wrefresh(win);
      }




      /*
      void draw(){
        for(int i = 0; i<num_menus; i++){
            int start_x = this->menus[i].start_x;
            string text = this->menus[i].text;
            if(selected_menu == i){
                wattron(win, A_STANDOUT);
            }
            mvwprintw(win, 0, start_x, text.c_str());
            wattroff(win, A_STANDOUT);

        }
        selected_menu = -1;
      }*/




      void draw(){
        for(int i = 0; i<num_menus; i++){
          drawMenu(menus[i], (selected_menu==i));
        }
        selected_menu=-1;
      }





      void drawMenu(Menu menu, bool is_selected){
        int start_x = menu.start_x;
        string text = menu.text;
        if(is_selected){
            wattron(win, A_STANDOUT);
        }
        mvwprintw(win, 0, start_x, text.c_str());
        wattroff(win, A_STANDOUT);
        wrefresh(win);


        int ch;
        drawMenuItems(menu);
        wrefresh(menuwin);


        while (is_selected && (ch = wgetch(menuwin))){
          switch (ch){
            case KEY_DOWN:
              menu.selectNextItem();
              break;
            case KEY_UP:
              menu.selectPrevItem();
              break;
            default:
              is_selected = false;
          }
          drawMenuItems(menu);
        }

        werase(menuwin);
        wrefresh(menuwin);
        reset();

      }


      void drawMenuItems(Menu menu){

        int ymax, xmax;
        getmaxyx(menuwin, ymax, xmax);
        for (int i = 0; i< menu.num_items; i++){
          mvwprintw(menuwin, i, 0, menu.items[i].c_str());

          if ((menu.selected_item == i)){ //if selected change to color pair 1
            mvwchgat(menuwin, i, 0, xmax, A_NORMAL, 1, NULL); // changes attributes from a specific window and start point until a given length, 
                                                              // it needs the attribute we want to change and the color pair we will use
          }
          else{ //else make the menuItem of a different color to make it different to the Menu
            mvwchgat(menuwin, i, 0, xmax, A_STANDOUT, 0, NULL);

          }
        }

      }




      void HandleTrigger(char trigger){
        for(int i = 0; i<num_menus; i++){
            if(trigger == this->menus[i].trigger){
                selected_menu = i;
            }
        }

      }


      


      
};

#endif
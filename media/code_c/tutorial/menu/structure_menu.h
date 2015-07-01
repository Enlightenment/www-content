#ifndef __STRUCTURE_MENU_
#define __STRUCTURE_MENU_

typedef struct _Mainview
{
    Evas_Object *box;         //The main container of the view
    Evas_Object *img;          //An image
    Evas_Object *lb_day;      //A label
} Mainview;

typedef struct _Dateview
{
    Evas_Object *box;      //The main container of the view
    Evas_Object *datetime; //A datetime widget
    Evas_Object *lb_date;  //A label
} Dateview;

typedef struct _Calview
{
    Evas_Object *box;      //The main container of the view
    Evas_Object *calendar; //A calendar widget
    Evas_Object *lb_cal;   //A label widget
} Calview;

typedef struct _Setview
{
    Evas_Object *box;      //The main container of the view
    Evas_Object *lb;   //A label widget
} Setview;

typedef struct _Tbarmenu
{
    Evas_Object *tb;           //The toolbar
    Elm_Object_Item *submenu; //The submenu item
} Tbarmenu;

typedef struct _Menu
{
    Evas_Object* layout;   // The "edje" layout
    Evas_Object *nf;       // The Naviframe to handle the views
    Tbarmenu *menu;       // The main menu
    Tbarmenu *sidemenu;   // The side menu
    Mainview *main_view; // The main view
    Calview *cal_view;   // The calendar view
    Dateview *date_view; // The date and time view
    Setview *settings_view; //The settin view

    Eina_Bool sdmenu_up;   // A bool variable to keep the side menu status
} Menu;

#endif

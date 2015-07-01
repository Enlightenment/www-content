#include <Elementary.h>
#include "structure_menu.h"

#define MAINVIEW "view/main"
#define MAINMENU "menu/main"
#define SIDEMENU "menu/side"
#define ICON_DIR "<path_to_your_icon_dir>"

//to handle the key down events
static Eina_Bool
keydown_cb(void *data , int type , void *event)
{
   Menu *me = data;
   Ecore_Event_Key *ev = event;
   if (!strcmp(ev->keyname, "XF86Send"))
     {
        if (me->sdmenu_up == EINA_TRUE)
          {
             // If the menu is visible send a "hide,sidemenu" signal
             elm_object_signal_emit(me->layout, "hide,sidemenu", "MenuButton");
             // Store the new menu status (hidden).
             me->sdmenu_up = EINA_FALSE;
          }
        else
          {
             // If the menu is visible send a "hide,sidemenu" signal
             elm_object_signal_emit(me->layout, "show,sidemenu", "MenuButton");
             // Store the new menu status (hidden).
             me->sdmenu_up = EINA_TRUE;
          }
     }
   return ECORE_CALLBACK_PASS_ON;
}

//create the views
static void
_build_main_view(Menu *me)
{
   Mainview *view = me->main_view;
   char buf[PATH_MAX];

   //Main box
   view->box = elm_box_add(me->nf);
   elm_box_horizontal_set(view->box, EINA_FALSE);
   elm_box_homogeneous_set(view->box, EINA_TRUE);

   view->img = elm_image_add(view->box);
   evas_object_size_hint_weight_set(view->img, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_align_set(view->img, 0.5, 0.5);
   evas_object_size_hint_min_set(view->img, 25, 25);
   snprintf(buf, sizeof(buf), "%s/%s", ICON_DIR, "icon.png");
   if (!elm_image_file_set(view->img, buf, NULL))
      elm_object_text_set(view->lb_day, "Problem loading image");
   elm_box_pack_start(view->box, view->img);
   evas_object_show(view->img);

   view->lb_day = elm_label_add(view->box);
   elm_object_text_set(view->lb_day, "Main view");
   evas_object_size_hint_weight_set(view->lb_day, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_box_pack_end(view->box, view->lb_day);
   evas_object_show(view->lb_day);
}

static void
_build_calendar_view(Menu *me)
{
   Calview *view = me->cal_view;

   view->box = elm_box_add(me->nf);
   elm_box_horizontal_set(view->box, EINA_FALSE);
   elm_box_homogeneous_set(view->box, EINA_TRUE);

   view->calendar = elm_calendar_add(me->nf);
   evas_object_size_hint_weight_set(view->calendar, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_align_set(view->calendar, 0.5, 0.5);
   elm_box_pack_end(view->box, view->calendar);
   evas_object_show(view->calendar);

   view->lb_cal = elm_label_add(view->box);
   elm_object_text_set(view->lb_cal, "The calendar view");
   evas_object_size_hint_weight_set(view->lb_cal, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_box_pack_end(view->box, view->lb_cal);
   evas_object_show(view->lb_cal);
} // End of_build_calendar_view

static void
_build_date_view(Menu *me)
{
   Dateview *view = me->date_view;

   view->box = elm_box_add(me->nf);
   elm_box_horizontal_set(view->box, EINA_FALSE);
   elm_box_homogeneous_set(view->box, EINA_TRUE);

   view->datetime = elm_datetime_add(me->nf);
   evas_object_size_hint_weight_set(view->datetime, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(view->datetime, EVAS_HINT_FILL, 0.5);
   elm_box_pack_end(view->box, view->datetime);
   evas_object_show(view->datetime);

   view->lb_date = elm_label_add(view->box);
   elm_object_text_set(view->lb_date, "The calendar view");
   evas_object_size_hint_weight_set(view->lb_date, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_box_pack_end(view->box, view->lb_date);
   evas_object_show(view->lb_date);
} // End of_build_calendar_view

static void
_build_settings_view(Menu *me)
{
   Setview *view = me->settings_view;

   view->box = elm_box_add(me->nf);
   elm_box_horizontal_set(view->box, EINA_FALSE);
   elm_box_homogeneous_set(view->box, EINA_TRUE);

   view->lb = elm_label_add(view->box);
   elm_object_text_set(view->lb, "The settings view");
   evas_object_size_hint_weight_set(view->lb, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_box_pack_end(view->box, view->lb);
   evas_object_show(view->lb);
} // End of_build_calendar_view

static void
_menu_item_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *it = (Elm_Object_Item*) event_info;
   Menu * me = (Menu *)data;
   Evas_Object *view;

   // Get the menu item text
   const char *str = elm_object_item_text_get(it);

   // Comparing with the possible view names
   if (!strcmp(str, "Calendar"))
     {
        // Build the "Calendar View"
        _build_calendar_view(me);
        // Set the view from the application data
        view = me->cal_view->box;
     }
   else if (!strcmp(str, "Date"))
     {
        // Build the "Date View"
        _build_date_view(data);
        // Set the view from the application data
        view = me->date_view->box;
     }
   else if (!strcmp(str, "Home"))
     {
        // Build the "Home or main View"
        _build_main_view(me);
        // Set the view from the application data
        view = me->main_view->box;
     }
   else if (!strcmp(str, "Settings"))
     {
        // Build the "Settings" view
        _build_settings_view(data);
        // Set the view from the application data
        view = me->settings_view->box;
     }
   else if (!strcmp(str, "Clock"))
     {
        // Build the "Date View"
        _build_date_view(me);
        // Set the view from the application data
        view = me->date_view->box;
     }
   else return;

   // Show the view in the naviframe
   elm_layout_content_set(me->layout, MAINVIEW, view);
}

//main menu
static void
_build_main_menu(Menu *me, Evas_Object *win)
{
   //Memory allocation for the main menu function.
   Tbarmenu *menu = calloc(1, sizeof(Tbarmenu));
   //Putting the "main" menu in the application data.
   me->menu = menu;

   // Creation of the "Menu" toolbar
   menu->tb = elm_toolbar_add(win);

   // Setting the "Menu" Toolbar properties
   elm_toolbar_shrink_mode_set(menu->tb, ELM_TOOLBAR_SHRINK_NONE);
   elm_toolbar_transverse_expanded_set(menu->tb, EINA_TRUE);
   elm_toolbar_homogeneous_set(menu->tb, EINA_FALSE);

   // Adding menu items to the "Menu" toolbar
   elm_toolbar_item_append(menu->tb, ICON_DIR"home.svg", "Home", _menu_item_selected_cb, me);
   elm_toolbar_item_append(menu->tb, ICON_DIR"calendar.svg", "Calendar", _menu_item_selected_cb, me);
   elm_toolbar_item_append(menu->tb, ICON_DIR"clock.svg", "Date", _menu_item_selected_cb, me);
   elm_toolbar_item_append(menu->tb, ICON_DIR"settings.svg", "Settings", _menu_item_selected_cb, me);

   // Showing the widget
   evas_object_show(menu->tb);

   // Adding the widget to the "menu/main" SWALLOW container defined in the .edc theme file.
   elm_layout_content_set(me->layout, "menu/main", menu->tb);

   // Set the default view
   elm_toolbar_item_selected_set(elm_toolbar_first_item_get(menu->tb), EINA_TRUE);
}

//side menu not visible at default
static void _build_side_menu(Menu *me, Evas_Object *win)
{
   Tbarmenu *sidemenu = calloc(1, sizeof(Tbarmenu));
   me->sidemenu = sidemenu;

   sidemenu->tb = elm_toolbar_add(win);

   elm_toolbar_shrink_mode_set(sidemenu->tb, ELM_TOOLBAR_SHRINK_EXPAND);
   elm_toolbar_transverse_expanded_set(sidemenu->tb, EINA_TRUE);

   elm_toolbar_item_append(sidemenu->tb, ICON_DIR"/home.svg", "Home", _menu_item_selected_cb, me);
   elm_toolbar_item_append(sidemenu->tb, ICON_DIR"/account.svg", "Account", NULL, NULL);
   elm_toolbar_item_append(sidemenu->tb, ICON_DIR"/contact.svg", "Friends", NULL, NULL);
   elm_toolbar_item_append(sidemenu->tb, ICON_DIR"/clock.svg", "Clock", _menu_item_selected_cb, me);
   elm_toolbar_homogeneous_set(sidemenu->tb, EINA_FALSE);
   evas_object_show(sidemenu->tb);
   elm_object_part_content_set(me->layout, "menu/side", sidemenu->tb);
   elm_toolbar_horizontal_set(sidemenu->tb, EINA_FALSE);
   elm_toolbar_item_selected_set(elm_toolbar_first_item_get(sidemenu->tb), EINA_TRUE);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
    Evas_Object *win;
    char buf[PATH_MAX];
    win = elm_win_util_standard_add("Menu", "Menu Tutorial");
    elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
    elm_win_autodel_set(win, EINA_TRUE);

    // Memory allocation
    Menu *me = calloc(1, sizeof(Menu));
    me->main_view = calloc(1, sizeof(Mainview)); // Allocating memory for the main view
    me->cal_view = calloc(1, sizeof(Calview));   // Allocating memory for the calendar view
    me->date_view = calloc(1, sizeof(Dateview)); // allocating memory for the date view
    me->settings_view = calloc(1, sizeof(Setview)); // allocating memory for the date view
    me->sdmenu_up = EINA_FALSE;

    me->layout = elm_layout_add(win);
    evas_object_resize(me->layout, 400, 400);

    elm_layout_file_set(me->layout, "menu.edj", "my_layout");

    me->nf = elm_naviframe_add(win);
    _build_main_menu(me, win);
    _build_side_menu(me, win);

    evas_object_show(me->layout);
    ecore_event_handler_add(ECORE_EVENT_KEY_DOWN, keydown_cb, me);
    evas_object_smart_callback_add(win, "delete,request", _free_menu_cb, me);
    //win 400x400 px
    evas_object_resize(win, 400, 400);
    evas_object_show(win);
    elm_run();
    free(me->menu);
    free(me->sidemenu);
    free(me->main_view);
    free(me->cal_view);
    free(me->settings_view);
    free(me);
    elm_shutdown();
    return 0;
}
ELM_MAIN()

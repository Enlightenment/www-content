#include <Elementary.h>

    static void
_prepend_itembutton_cb(void *data, Evas_Object *obj, void *event_info)
{
    Elm_Object_Item *list_it;
    Evas_Object *li = obj;

    Elm_Object_Item *selected=elm_list_selected_item_get(li);
    if(selected == (Elm_Object_Item*)data)
        {
            static int counter=0;
            char label[32];
            snprintf(label, sizeof(label), "Item %i", counter++);

            list_it = elm_list_item_prepend(li, label, NULL, NULL, NULL, NULL);
            elm_list_go(li);
            if (!list_it) printf("Error adding item\n");
        }
}

    EAPI_MAIN int
elm_main(int argc, char **argv)
{
    Evas_Object *win, *label, *label2;

    elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

    win = elm_win_util_standard_add("Main", "Hello, World!");
    elm_win_autodel_set(win, EINA_TRUE);
    evas_object_resize(win, 400, 400);

    Evas_Object *list, *icon, *button;
    list = elm_list_add(win);
    /*elm_list_horizontal_set(list, EINA_TRUE);*/ //uncoment to get horizontal
    //size giving scrollbar
    evas_object_resize(list, 320, 300);
    elm_list_mode_set(list, ELM_LIST_LIMIT);
    //    elm_scroller_bounce_set(list, EINA_TRUE, EINA_TRUE);

    //first item: text
    elm_list_item_append(list, "Text item", NULL, NULL, NULL, NULL);

    //second item: icon
    icon = elm_icon_add(list);
    elm_icon_standard_set(icon, "chat");
    elm_list_item_append(list, "Icon item", icon, NULL, NULL, NULL);

    //third item: button
    button = elm_button_add(list);
    elm_object_text_set(button, "Button");
    Elm_Object_Item *itembutton=elm_list_item_append(list, "Button item", NULL, button, NULL, NULL);


    elm_list_go(list);
    evas_object_show(list);

    evas_object_smart_callback_add(list, "selected", _prepend_itembutton_cb, itembutton);

    evas_object_show(win);

    elm_run();

    return 0;
}
ELM_MAIN()

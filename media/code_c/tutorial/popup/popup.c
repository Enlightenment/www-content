#include <Elementary.h>

static void
_popup_close_cb(void *data, Evas_Object *obj EINA_UNUSED,
                void *event_info EINA_UNUSED)
{
   Evas_Object *popup = data;
   //delete popup
   evas_object_del(popup);
}

static void
_btn_click_cb(void *data, Evas_Object *obj EINA_UNUSED,
              void *event_info EINA_UNUSED)
{
   // Add an elm popup
   Evas_Object *popup;
   Evas_Object *btn;

   popup = elm_popup_add(data);
   elm_object_text_set(popup, "This Popup has content area and "
                       "action area set, action area has one button Close");

   // popup buttons
   btn = elm_button_add(popup);
   elm_object_text_set(btn, "Close");
   elm_object_part_content_set(popup, "button1", btn);
   evas_object_smart_callback_add(btn, "clicked", _popup_close_cb, popup);

   // popup show should be called after adding all the contents and the buttons
   // of popup to set the focus into popup's contents correctly.
   evas_object_show(popup);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *btn;

   win = elm_win_util_standard_add("Popup", "Popup Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   //win 400x400 px
   evas_object_resize(win, 400, 400);

   btn = elm_button_add(win);
   elm_object_text_set(btn, "popup");
   evas_object_resize(btn, 100, 50);
   evas_object_move(btn, 150, 150);
   evas_object_show(btn);
   evas_object_smart_callback_add(btn, "clicked", _btn_click_cb, win);

   evas_object_show(win);
   elm_run();
   return 0;
}
ELM_MAIN()

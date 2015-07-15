#include <Elementary.h>

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *layout, *button, *btn_up;
   win = elm_win_util_standard_add("Edje Animation", "Edje Animation Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);

   layout = elm_layout_add(win);

   elm_layout_file_set(layout, "edje_animation.edj", "my_layout");

   // Creation button in the app window
   button = elm_button_add(win);
   elm_object_text_set(button, "Rotate");
   // Add the button to the edje layout container called "btn/rotate"
   elm_object_part_content_set(layout, "btn/rotate", button);
   evas_object_show(button);

   // Creation a up button in the app window
   btn_up = elm_button_add(win);
   // Add the button to the edje layout container called "btn/grow"
   elm_object_text_set(btn_up, "Grow");
   elm_object_part_content_set(layout, "btn/grow", btn_up);
   evas_object_show(btn_up);

   evas_object_resize(layout, 400, 400);
   evas_object_show(layout);
   evas_object_resize(win, 400, 400);
   evas_object_show(win);
   elm_run();
   elm_shutdown();
   return 0;
}
ELM_MAIN()

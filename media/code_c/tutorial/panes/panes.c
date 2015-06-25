#include <Elementary.h>

// clicked callback
static void
_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
   printf("Clicked\n");
}

// press callback
static void
_press_cb(void *data, Evas_Object *obj, void *event_info)
{
   printf("Pressed\n");
}

// unpress callback
static void
_unpress_cb(void *data, Evas_Object *obj, void *event_info)
{
   printf("Unpressed, size : %f\n", elm_panes_content_left_size_get(obj));
}

// double clicked callback
static void
_clicked_double_cb(void *data, Evas_Object *obj, void *event_info)
{
   static double size = 0.0;
   double tmp_size = 0.0;
   tmp_size = elm_panes_content_left_size_get(obj);
   if (tmp_size > 0)
     {
        elm_panes_content_left_size_set(obj, 0.0);
        printf("Double clicked, hidden.\n");
     }
   else
     {
        elm_panes_content_left_size_set(obj, size);
        printf("Double clicked, restoring size.\n");
     }
   size = tmp_size;
}

    EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win;

   win = elm_win_util_standard_add("Panes", "Panes Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   //win 400x400 px
   evas_object_resize(win, 400, 400);

   Evas_Object *panes, *panes_h, *bt;

   // Add an elm_panes
   panes = elm_panes_add(win);
   evas_object_size_hint_weight_set(panes, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, panes);
   evas_object_show(panes);

   // Add a horizontal elm_panes
   panes_h = elm_panes_add(win);
   elm_panes_horizontal_set(panes_h, EINA_TRUE);
   elm_object_part_content_set(panes, "left", panes_h);

   // Create a button object
   bt = elm_button_add(win);
   elm_object_text_set(bt, "Right");
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(bt);

   // and set it to the "right" part of the vertical Panes
   elm_object_part_content_set(panes, "right", bt);

   // Create a "Up" button
   bt = elm_button_add(win);
   elm_object_text_set(bt, "Up");
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(bt);
   elm_object_part_content_set(panes_h, "left", bt);

   // Create a "Down" button
   bt = elm_button_add(win);
   elm_object_text_set(bt, "Down");
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(bt);
   elm_object_part_content_set(panes_h, "right", bt);

   // Set the proportion of the panes to 80%
   elm_panes_content_left_size_set(panes, 0.8);
   elm_panes_content_left_size_set(panes_h, 0.8);

   //panes callbacks
   evas_object_smart_callback_add(panes, "clicked", _clicked_cb, panes);
   evas_object_smart_callback_add(panes, "press", _press_cb, panes);
   evas_object_smart_callback_add(panes, "unpress", _unpress_cb, panes);
   evas_object_smart_callback_add(panes, "clicked,double", _clicked_double_cb,
           panes);

   //panes_h callbacks
   evas_object_smart_callback_add(panes_h, "clicked", _clicked_cb, panes_h);
   evas_object_smart_callback_add(panes_h, "press", _press_cb, panes_h);
   evas_object_smart_callback_add(panes_h, "unpress", _unpress_cb, panes_h);
   evas_object_smart_callback_add(panes_h, "clicked,double", _clicked_double_cb,
           panes_h);

   evas_object_show(win);
   elm_run();
   return 0;
}
ELM_MAIN()

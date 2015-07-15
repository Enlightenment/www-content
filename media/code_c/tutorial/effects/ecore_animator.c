#include <Elementary.h>

static Eina_Bool
_do_rotate(void *data, double pos)
{
   // Get the animation target
   Evas_Object *obj = data;
   // Declaration of an `Evas_Map`
   Evas_Map *m;
   // Variables to store the target size and position
   int x, y, w, h;

   // Getting the size and position of the target
   evas_object_geometry_get(obj, &x, &y, &w, &h);
   // Creation of an `Evas_Map` of 4 points
   m = evas_map_new(4);
   // Populate source and destination map points to match exactly object.
   evas_map_util_points_populate_from_object(m, obj);
   // Create a rotation of 360° with x+(w/2) "x" center and y +(h/2) "y" center.
   evas_map_util_rotate(m, 360.0 * pos, x + (w / 2), y + (h / 2));
   // Setting the object to "animate" in the `Evas_Map`
   evas_object_map_set(obj, m);
   // Starting the Animation
   evas_object_map_enable_set(obj, EINA_TRUE);
   // Free used memory
   evas_map_free(m);

   return EINA_TRUE;
}

static void
_btn_rotate_cb(void *data, Evas_Object *btn, void *ev)
{
   Evas_Object *target = data;
   ecore_animator_timeline_add(1, _do_rotate, target);
}

static Eina_Bool
_do_zoom(void *data, double pos)
{
   Evas_Object *obj = data;
   Evas_Map *m;
   int x, y, w, h;

   evas_object_geometry_get(obj, &x, &y, &w, &h);
   m = evas_map_new(4);
   evas_map_util_points_populate_from_object(m, obj);
   evas_map_util_zoom(m, 2 * pos, 2 * pos, x , y);
   evas_object_map_set(obj, m);
   evas_object_map_enable_set(obj, EINA_TRUE);
   evas_map_free(m);

   return EINA_TRUE;
}

static void _btn_zoom_cb(void *data, Evas_Object *btn, void *ev)
{
   Evas_Object *target = data;
   ecore_animator_timeline_add(1, _do_zoom, target);
}

static Eina_Bool
_do_3d(void *data, double pos)
{
   Evas_Object *obj = data;
   Evas_Map *m;
   int x, y, w, h;

   evas_object_geometry_get(obj, &x, &y, &w, &h);
   m = evas_map_new(4);
   evas_map_util_points_populate_from_object(m, obj);
   evas_map_util_3d_rotate(m, pos * 360, pos * 360, pos * 360, x + (w / 3), y + 60, 0);
   evas_object_map_set(obj, m);
   evas_object_map_enable_set(obj, EINA_TRUE);
   evas_map_free(m);

   return EINA_TRUE;
}

static void
_btn_3d_cb(void *data, Evas_Object *btn, void *ev)
{
   Evas_Object *target = data;
   ecore_animator_timeline_add(1, _do_3d, target);
}

static Eina_Bool
_do_drop(void *data, double pos)
{
   Evas_Object *obj = data;
   int x, y, w, h;
   double frame = pos;
   frame = ecore_animator_pos_map(pos, ECORE_POS_MAP_BOUNCE, 2, 4);

   evas_object_geometry_get(obj, &x, &y, &w, &h);
   evas_object_move(obj, x, 600 * frame);

   return EINA_TRUE;
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *label, *bt1, *bt2, *bt3, *target;
   win = elm_win_util_standard_add("Ecore Animator", "Ecore Animator Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);

   if (elm_win_wm_rotation_supported_get(win))
     {
        int rots[4] = { 0, 90, 180, 270 };
        elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
     }

   // Application title
   label = elm_label_add(win);
   elm_object_text_set(label, "Ecore Animator Tutorial");
   evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, label);
   evas_object_show(label);

   // Animation target
   // Setting the image path
   char buf[PATH_MAX];
   snprintf(buf, sizeof(buf), "icon.png");
   // Adding the image
   target = elm_image_add(win);
   // Setting the image path
   if (!elm_image_file_set(target, buf, NULL))
        printf("error: could not load image \"%s\"\n", buf);
   evas_object_size_hint_weight_set(target, EVAS_HINT_FILL, EVAS_HINT_FILL);
   //Moving the image
   evas_object_move(target, 130, 100);
   //Resizing the image
   evas_object_resize(target, 200, 100);
   //Showing the image
   evas_object_show(target);

   // Button 1 : Rotation effect
   bt1 = elm_button_add(win);
   elm_object_text_set(bt1, "Rotate");
   evas_object_size_hint_weight_set(bt1, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_move(bt1, 25, 0);
   evas_object_resize(bt1, 90, 70);
   evas_object_smart_callback_add(bt1, "clicked", _btn_rotate_cb, target);
   evas_object_show(bt1);

   // Button 2 : Zoom Effect
   bt2 = elm_button_add(win);
   elm_object_text_set(bt2, "Zoom");
   evas_object_size_hint_weight_set(bt2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_move(bt2, 315, 0);
   evas_object_resize(bt2, 90, 70);
   evas_object_smart_callback_add(bt2, "clicked", _btn_zoom_cb, target);
   evas_object_show(bt2);

   // Button 3 : 3D Rotation Effect
   bt3 = elm_button_add(win);
   elm_object_text_set(bt3, "3D");
   evas_object_size_hint_weight_set(bt3, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_move(bt3, 170, 0);
   evas_object_resize(bt3, 90, 70);
   evas_object_smart_callback_add(bt3, "clicked", _btn_3d_cb, target);
   evas_object_show(bt3);

   //drop and bounce effects
   ecore_animator_timeline_add(2, _do_drop, bt1);
   ecore_animator_timeline_add(2.3, _do_drop, bt2);
   ecore_animator_timeline_add(2.5, _do_drop, bt3);

   evas_object_resize(win, 480, 800);
   evas_object_show(win);
   elm_run();
   elm_shutdown();
   return EXIT_SUCCESS;
}
ELM_MAIN()

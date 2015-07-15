#include <Elementary.h>

typedef struct _Animations
{
   Evas_Object *button;
   Evas_Object *buttonbck;
   float *rt_angle;
   float *zto;
   float *zfrom;
} Animations;

/**************
 * Resize
 *************/
static void
_resize_effect(Evas_Object *obj)
{
   // Elementary Transition declaration and creation
   Elm_Transit *trans = elm_transit_add();

   // Adding the transition target object
   elm_transit_object_add(trans, obj);

   // Setting the resize effect
   elm_transit_effect_resizing_add(trans, 100, 50, 300, 150);

   // Setting the transition duration
   elm_transit_duration_set(trans, 3.0);

   // Starting the transition
   elm_transit_go(trans);
}

static void
_btn_resize_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;

   // Starting the rotation effect 360 degrees
   //evas_object_resize(button, 100, 50);
   elm_object_text_set(anim->button, "Resize");
   _resize_effect(anim->button);
}

/*************
 * Rotation
 *************/
static void
_rotation_effect(Evas_Object *obj, float angle)
{
   Elm_Transit *trans = elm_transit_add();
   elm_transit_object_add(trans, obj);

   // rotates the object from its original angle to given degrees to the right
   elm_transit_effect_rotation_add(trans, 0.0, angle);
   elm_transit_duration_set(trans, 2.0);
   elm_transit_go(trans);
}

static void
_btn_rotate_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;

   // Setting the button text
   elm_object_text_set(anim->button, "Rotate");
   _rotation_effect(anim->button, *(anim->rt_angle));
}

/**************
 *   Zoom
 *************/
static void
_zoom_effect(Evas_Object *obj, float from, float to)
{
   Elm_Transit *trans = elm_transit_add();
   elm_transit_object_add(trans, obj);

   elm_transit_effect_zoom_add(trans, from, to);
   elm_transit_duration_set(trans, 2.0);
   elm_transit_go(trans);
}

static void
_btn_zoom_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;

   // Starting the rotation effect 360 degrees
   //evas_object_resize(anim->button, 100, 50);
   elm_object_text_set(anim->button, "Zoom");
   _zoom_effect(anim->button, *(anim->zfrom), *(anim->zto));
}

/**************
 *   Flip
 *************/
static void
_flip_effect(Evas_Object *obj, Evas_Object *obj2)
{
   Elm_Transit *trans;

   trans = elm_transit_add();
   elm_transit_object_add(trans, obj);
   elm_transit_object_add(trans, obj2);
   elm_transit_effect_flip_add(trans, ELM_TRANSIT_EFFECT_FLIP_AXIS_X, EINA_TRUE);

   elm_transit_duration_set(trans, 3.0);
   elm_transit_go(trans);
}

static void
_btn_flip_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;

   // Setting the button text
   elm_object_text_set(anim->button, "Flip");
   _flip_effect(anim->button, anim->buttonbck);
}

/**************
 *   Blend
 *************/
static void
_blend_effect(Evas_Object *obj, Evas_Object *obj2)
{
   Elm_Transit *trans;

   trans = elm_transit_add();
   elm_transit_object_add(trans, obj);
   elm_transit_object_add(trans, obj2);
   elm_transit_effect_blend_add(trans);
   elm_transit_duration_set(trans, 3.0);
   elm_transit_go(trans);
}

static void
_btn_blend_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;

   // Setting the button text
   elm_object_text_set(anim->button, "Blend");
   _blend_effect(anim->button, anim->buttonbck);
}

/**************
 *   Fade
 *************/
static void
_fade_effect(Evas_Object *obj, Evas_Object *obj2)
{
   Elm_Transit *trans;

   trans = elm_transit_add();
   elm_transit_object_add(trans, obj);
   elm_transit_object_add(trans, obj2);
   elm_transit_effect_fade_add(trans);
   elm_transit_duration_set(trans, 3.0);
   elm_transit_go(trans);
}

static void
_btn_fade_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;


   // Setting the button text
   elm_object_text_set(anim->button, "Fade");
   _fade_effect(anim->button, anim->buttonbck);
}

/**************
 *   FlipY
 *************/
static void
_flip_y_effect(Evas_Object *obj, Evas_Object *obj2)
{
  Elm_Transit *trans;

   trans = elm_transit_add();
   elm_transit_object_add(trans, obj);
   elm_transit_object_add(trans, obj2);
   elm_transit_effect_flip_add(trans, ELM_TRANSIT_EFFECT_FLIP_AXIS_Y, EINA_TRUE);
   elm_transit_duration_set(trans, 3.0);
   elm_transit_go(trans);
}

static void
_btn_flip_y_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;


   // Setting the button text
   elm_object_text_set(anim->button, "Flip 2");
   _flip_y_effect(anim->button, anim->buttonbck);
}

/**************
 *   Wipe
 *************/
static void
_wipe_effect(Evas_Object *obj)
{
   Elm_Transit *trans;

   trans = elm_transit_add();
   elm_transit_object_add(trans, obj);
   elm_transit_effect_wipe_add(trans, ELM_TRANSIT_EFFECT_WIPE_TYPE_HIDE, ELM_TRANSIT_EFFECT_WIPE_DIR_RIGHT);
   elm_transit_duration_set(trans, 3.0);
   elm_transit_go(trans);
}

static void
_btn_wipe_cb(void *data, Evas_Object *btn, void *ev)
{
   Animations *anim = (Animations *)data;

   // Starting the rotation effect 360 degrees
   //evas_object_resize(anim->button, 100, 50);
   // Setting the button text
   elm_object_text_set(anim->button, "Wipe");
   _wipe_effect(anim->button);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *label, *hbox, *left_vbox, *center_vbox, *right_vbox;
   Evas_Object *button, *buttonbck;
   float rt_angle, zto, zfrom;

   win = elm_win_util_standard_add("Elementary Animations", "Elementary Animations Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   if (elm_win_wm_rotation_supported_get(win))
     {
        int rots[4] = { 0, 90, 180, 270 };
        elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
     }

   //set the values for animations
   rt_angle = 360.0;
   zfrom = 1.0;
   zto = 2.0;

   /* Label*/
   label = elm_label_add(win);
   elm_object_text_set(label, "Effects Tutorial");
   evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_move(label, 100, 0);
   evas_object_resize(label, 200, 50);
   evas_object_show(label);

   /* Creation a button in the app window*/
   button = elm_button_add(win);
   evas_object_move(button, 100, 100);      // Moving the button to x=50 y=100
   evas_object_resize(button, 200, 50);    // Resizing the button 100x50
   evas_object_show(button);               // Showing the button
   /* Creation a back button in the app window*/
   buttonbck = elm_button_add(win);
   elm_object_text_set(buttonbck, "Button back");
   evas_object_move(buttonbck, 100, 100);
   evas_object_resize(buttonbck, 200, 50);

   /*set the structure of pointeurs*/
   Animations anim = { button, buttonbck, &rt_angle, &zto, &zfrom };

   /***********************************************************************************************************************
                                                   *Boxes*
   ***********************************************************************************************************************/
   // Creation of the main container box
   hbox = elm_box_add(win);
   elm_box_horizontal_set(hbox, EINA_TRUE);
   elm_box_homogeneous_set(hbox, EINA_TRUE);
   evas_object_move(hbox, 130, 200);
   evas_object_show(hbox);

   // Creation of the first column
   left_vbox = elm_box_add(hbox);
   elm_box_horizontal_set(left_vbox, EINA_FALSE);
   elm_box_homogeneous_set(left_vbox, EINA_TRUE);
   evas_object_show(left_vbox);
   elm_box_pack_start(hbox, left_vbox);

   // Creation of the second column
   center_vbox = elm_box_add(hbox);
   elm_box_horizontal_set(center_vbox, EINA_FALSE);
   elm_box_homogeneous_set(center_vbox, EINA_TRUE);
   evas_object_show(center_vbox);
   elm_box_pack_end(hbox, center_vbox);

   // Creation of the last column
   right_vbox = elm_box_add(hbox);
   elm_box_horizontal_set(right_vbox, EINA_FALSE);
   elm_box_homogeneous_set(right_vbox, EINA_TRUE);
   evas_object_show(right_vbox);
   elm_box_pack_end(hbox, right_vbox);

   /***********************************************************************************************************************
                                                   *Buttons*
   ***********************************************************************************************************************/
   // The resize button
   Evas_Object *btn_resize = elm_button_add(win);
   elm_object_text_set(btn_resize, "Resize");                                      // Setting the button text
   evas_object_size_hint_weight_set(btn_resize, EVAS_HINT_FILL, EVAS_HINT_FILL);   // Setting the hint weight policy
   evas_object_show(btn_resize);                                                   // Showing the button
   evas_object_smart_callback_add(btn_resize, "clicked", _btn_resize_cb, &anim);   // Setting the "clicked" callback
   elm_box_pack_end(left_vbox, btn_resize);                                        // Adding the button to the first column

   // The rotation button
   Evas_Object *btn_rotate = elm_button_add(win);
   elm_object_text_set(btn_rotate, "Rotate");
   evas_object_size_hint_weight_set(btn_rotate, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn_rotate);
   evas_object_smart_callback_add(btn_rotate, "clicked", _btn_rotate_cb, &anim);
   elm_box_pack_end(center_vbox, btn_rotate);

   // The zoom button
   Evas_Object *btn_zoom = elm_button_add(win);
   elm_object_text_set(btn_zoom, "Zoom");
   evas_object_size_hint_weight_set(btn_zoom, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn_zoom);
   evas_object_smart_callback_add(btn_zoom, "clicked", _btn_zoom_cb, &anim);
   elm_box_pack_end(right_vbox, btn_zoom);

   // The flip button
   Evas_Object *btn_flip = elm_button_add(win);
   elm_object_text_set(btn_flip, "Flip x");
   evas_object_size_hint_weight_set(btn_flip, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn_flip);
   evas_object_smart_callback_add(btn_flip, "clicked", _btn_flip_cb, &anim);
   elm_box_pack_end(left_vbox, btn_flip);

   // The blend button
   Evas_Object *btn_blend = elm_button_add(win);
   elm_object_text_set(btn_blend, "Blend");
   evas_object_size_hint_weight_set(btn_blend, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn_blend);
   evas_object_smart_callback_add(btn_blend, "clicked", _btn_blend_cb, &anim);
   elm_box_pack_end(center_vbox, btn_blend);

   // The fade button
   Evas_Object *btn_fade = elm_button_add(win);
   elm_object_text_set(btn_fade, "Fade");
   evas_object_size_hint_weight_set(btn_fade, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn_fade);
   evas_object_smart_callback_add(btn_fade, "clicked", _btn_fade_cb, &anim);
   elm_box_pack_end(right_vbox, btn_fade);

   // The flip y button
   Evas_Object *btn_flip_y = elm_button_add(win);
   elm_object_text_set(btn_flip_y, "Flip y");
   evas_object_size_hint_weight_set(btn_flip_y, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn_flip_y);
   evas_object_smart_callback_add(btn_flip_y, "clicked", _btn_flip_y_cb, &anim);
   elm_box_pack_end(left_vbox, btn_flip_y);

   // The wipe button
   Evas_Object *btn_wipe = elm_button_add(win);
   elm_object_text_set(btn_wipe, "Wipe");
   evas_object_size_hint_weight_set(btn_wipe, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn_wipe);
   evas_object_smart_callback_add(btn_wipe, "clicked", _btn_wipe_cb, &anim);
   elm_box_pack_end(right_vbox, btn_wipe);

   evas_object_resize(win, 400, 400);
   evas_object_show(win);
   elm_run();
   elm_shutdown();
   return 0;
}
ELM_MAIN()

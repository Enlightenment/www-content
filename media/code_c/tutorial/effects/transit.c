#include <Elementary.h>

/* store naviframe pointeurs */
typedef struct _Navi
{
   Evas_Object *navi;
   Evas_Object *navi2;
} Navi;

static void
rotation_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Elm_Transit *transit = elm_transit_add();

   // 360 degree rotation effect in the clock-wise direction
   elm_transit_object_add(transit, navi);
   elm_transit_effect_rotation_add(transit, 0, 360);
   elm_transit_duration_set(transit, 1);
   elm_transit_go(transit);
}

static void
zoom_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   // Zoom out to scale 0.6
   Elm_Transit *transit = elm_transit_add();
   elm_transit_smooth_set(transit, EINA_FALSE);
   elm_transit_object_add(transit, navi);
   elm_transit_effect_zoom_add(transit, 1.0, 0.4);
   elm_transit_duration_set(transit, 0.5);

   // Zoom in to the original size
   Elm_Transit *transit2 = elm_transit_add();
   elm_transit_smooth_set(transit2, EINA_FALSE);
   elm_transit_object_add(transit2, navi);
   elm_transit_effect_zoom_add(transit2, 0.4, 1.0);
   elm_transit_duration_set(transit2, 0.5);

   elm_transit_chain_transit_add(transit, transit2);
   elm_transit_go(transit);
}

static void
blend_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Evas_Object *navi2=navis->navi2;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_object_add(transit, navi2);
   elm_transit_effect_blend_add(transit);
   elm_transit_duration_set(transit, 3.0);
   elm_transit_objects_final_state_keep_set(transit, EINA_TRUE);
   elm_transit_go(transit);

}

static void
fade_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Evas_Object *navi2=navis->navi2;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_object_add(transit, navi2);
   elm_transit_effect_fade_add(transit);
   elm_transit_duration_set(transit, 3.0);
   elm_transit_objects_final_state_keep_set(transit, EINA_TRUE);
   elm_transit_go(transit);

}

static void
flip_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Evas_Object *navi2=navis->navi2;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_object_add(transit, navi2);
   elm_transit_effect_flip_add(transit, ELM_TRANSIT_EFFECT_FLIP_AXIS_X, EINA_TRUE);
   elm_transit_duration_set(transit, 3.0);
   elm_transit_objects_final_state_keep_set(transit, EINA_TRUE);
   elm_transit_go(transit);
}

static void
resizable_flip_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Evas_Object *navi2=navis->navi2;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_object_add(transit, navi2);
   elm_transit_effect_resizable_flip_add(transit, ELM_TRANSIT_EFFECT_FLIP_AXIS_Y, EINA_TRUE);
   elm_transit_duration_set(transit, 3.0);
   elm_transit_objects_final_state_keep_set(transit, EINA_TRUE);
   elm_transit_go(transit);
}

static void
wipe_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_effect_wipe_add(transit, ELM_TRANSIT_EFFECT_WIPE_TYPE_HIDE, ELM_TRANSIT_EFFECT_WIPE_DIR_RIGHT);
   elm_transit_duration_set(transit, 3.0);
   elm_transit_go(transit);
}

static void
translation_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_effect_translation_add(transit, 0, 0, 50, 100);
   elm_transit_duration_set(transit, 3.0);
   elm_transit_go(transit);
}

static void
color_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_effect_color_add(transit,0,0,0,0,255,255,0,255);
   elm_transit_duration_set(transit, 3.0);
   elm_transit_go(transit);
}

static void
custom_cb(void *data, Evas_Object *obj, void *event_info)
{
   Navi *navis = data;
   Evas_Object *navi=navis->navi;
   Evas_Object *navi2=navis->navi2;
   Elm_Transit *transit = elm_transit_add();

   elm_transit_object_add(transit, navi);
   elm_transit_object_add(transit, navi2);
   elm_transit_effect_color_add(transit,0,0,0,0,255,255,0,255);
   elm_transit_effect_flip_add(transit, ELM_TRANSIT_EFFECT_FLIP_AXIS_Y, EINA_TRUE);
   elm_transit_duration_set(transit, 3.0);

   Elm_Transit *transit2 = elm_transit_add();
   elm_transit_object_add(transit2, navi2);
   elm_transit_object_add(transit2, navi);
   elm_transit_effect_color_add(transit2,0,0,0,0,180,255,0,255);
   elm_transit_effect_zoom_add(transit2, 1.0, 0.1);
   elm_transit_duration_set(transit2, 3.0);

   elm_transit_chain_transit_add(transit, transit2);
   elm_transit_go(transit);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *navi, *navi2, *list, *list2;

   win = elm_win_util_standard_add("Transition", "Transition Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   if (elm_win_wm_rotation_supported_get(win))
     {
        int rots[4] = { 0, 90, 180, 270 };
        elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
     }

   Elm_Object_Item *nf_it, *nf_it2;

   /* add two naviframes and two lists to switch
    * from one to another in some transitions */
   navi2 = elm_naviframe_add(win);
   navi = elm_naviframe_add(win);
   list = elm_list_add(navi);
   list2 = elm_list_add(navi2);
   elm_list_mode_set(list, ELM_LIST_COMPRESS);
   elm_list_mode_set(list2, ELM_LIST_COMPRESS);

   /* store naviframe pointeurs to pass them
    * in data pointeur parameter */
   Navi navis = {navi, navi2};
   Navi navis2 = {navi2, navi};

   /* first list items */
   elm_list_item_append(list, "Blend", NULL, NULL, blend_cb, &navis);
   elm_list_item_append(list, "Color", NULL, NULL, color_cb, &navis);
   elm_list_item_append(list, "Fade", NULL, NULL, fade_cb, &navis);
   elm_list_item_append(list, "Flip", NULL, NULL, flip_cb, &navis);
   elm_list_item_append(list, "Rotation", NULL, NULL, rotation_cb, &navis);
   elm_list_item_append(list, "ResizableFlip", NULL, NULL, resizable_flip_cb, &navis);
   elm_list_item_append(list, "Translation", NULL, NULL, translation_cb, &navis);
   elm_list_item_append(list, "Wipe", NULL, NULL, wipe_cb, &navis);
   elm_list_item_append(list, "Zoom", NULL, NULL, zoom_cb, &navis);
   elm_list_item_append(list, "Custom", NULL, NULL, custom_cb, &navis);
   elm_list_go(list);

   /* second list items*/
   elm_list_item_append(list2, "Blend2", NULL, NULL, blend_cb, &navis2);
   elm_list_item_append(list2, "Color2", NULL, NULL, color_cb, &navis2);
   elm_list_item_append(list2, "Fade2", NULL, NULL, fade_cb, &navis2);
   elm_list_item_append(list2, "Flip2", NULL, NULL, flip_cb, &navis2);
   elm_list_item_append(list2, "Rotation2", NULL, NULL, rotation_cb, &navis2);
   elm_list_item_append(list2, "ResizableFlip2", NULL, NULL, resizable_flip_cb, &navis2);
   elm_list_item_append(list2, "Translation2", NULL, NULL, translation_cb, &navis2);
   elm_list_item_append(list2, "Wipe2", NULL, NULL, wipe_cb, &navis2);
   elm_list_item_append(list2, "Zoom2", NULL, NULL, zoom_cb, &navis2);
   elm_list_item_append(list2, "Custom2", NULL, NULL, custom_cb, &navis2);
   elm_list_go(list2);

   nf_it = elm_naviframe_item_push(navi, "Transit", NULL, NULL, list, NULL);
   nf_it2 = elm_naviframe_item_push(navi2, "Transit2", NULL, NULL, list2, NULL);

   evas_object_show(navi);
   evas_object_show(navi2);
   evas_object_show(list);
   evas_object_show(list2);
   evas_object_resize(navi2, 400, 400);
   evas_object_resize(navi, 400, 400);
   evas_object_resize(win, 400, 400);
   evas_object_show(win);
   elm_run();
   elm_shutdown();
   return 0;
}
ELM_MAIN()

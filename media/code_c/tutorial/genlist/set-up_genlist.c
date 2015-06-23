#include <Elementary.h>

static char *
_genlist_text_get(void *data, Evas_Object *obj , const char *part)
{
   if (strcmp(part, "elm.text") == 0)
     {
        char *buf = malloc(16);
        snprintf(buf, 16, "Entry %d.", (int)(uintptr_t)data);

        return buf;
     }
   else return NULL;
}

static Evas_Object *
_genlist_content_get(void *data, Evas_Object *obj, const char *part)
{
   int i = (int) (uintptr_t) data;

   if (strcmp(part, "elm.swallow.icon") == 0)
     {
         Evas_Object *bg = elm_bg_add(obj);
         elm_bg_color_set(bg, 255 * cos(i / (double) 10), 0, i % 255);

         return bg;
     }
   else if (strcmp(part, "elm.swallow.end") == 0)
     {
         Evas_Object *bg = elm_bg_add(obj);
         elm_bg_color_set(bg, 0, 255 * sin(i / (double) 10), i % 255);

         return bg;
     }
   else return NULL;
}

static void
_genlist_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
   Elm_Object_Item *it = (Elm_Object_Item*) event_info;

   elm_genlist_item_item_class_update(it, data);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win;

   win = elm_win_util_standard_add("Genlist", "Genlist Basic Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   //win 400x400 px
   evas_object_resize(win, 400, 400);

   //GENLIST here
   Evas_Object *list;
   list = elm_genlist_add(win);

   Elm_Genlist_Item_Class *_itc = elm_genlist_item_class_new();
   _itc->item_style        = "default";
   _itc->func.text_get     = _genlist_text_get;
   _itc->func.content_get  = _genlist_content_get;
   _itc->func.state_get    = NULL;
   _itc->func.del          = NULL;

   Elm_Genlist_Item_Class *_itc2 = elm_genlist_item_class_new();
   _itc2->item_style        = "group_index";
   _itc2->func.text_get     = _genlist_text_get;
   _itc2->func.content_get  = _genlist_content_get;
   _itc2->func.state_get    = NULL;
   _itc2->func.del          = NULL;

   int i=0;
   for (i=0; i<20; i++)
     {
        elm_genlist_item_append(list,
                _itc,
                (void *)(uintptr_t) i,   // Item data
                NULL,                    // Parent item for trees, NULL if none
                ELM_GENLIST_ITEM_NONE,   // Item type; this is the common one
                _genlist_selected_cb,    // Callback on selection of the item
                _itc2                    // Data for that callback function
                );
     }

   evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, list);
   evas_object_show(list);

   evas_object_show(win);
   elm_run();
   return 0;
}
ELM_MAIN()

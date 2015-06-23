#include <Elementary.h>

static char *
_genlist_text_get_size(void *data, Evas_Object *obj , const char *part)
{
   char buf[20];
   snprintf(buf, sizeof(buf), "Entry %d", (int)(uintptr_t)data);
   return strdup(buf);
}

static char *
_genlist_text_get_nosize(void *data, Evas_Object *obj , const char *part)
{
   char buf[20];
   snprintf(buf, sizeof(buf), "OHOHO %d", (int)(uintptr_t)data);
   return strdup(buf);
}

static Evas_Object *
_genlist_content_get_bg(void *data, Evas_Object *obj, const char *part)
{
   int i = (int) (uintptr_t) data;

   Evas_Object *bg = elm_bg_add(obj);
   elm_bg_color_set(bg, 255 * cos(i / (double) 10), 0, i % 255);

   return bg;
}

static void
_tree_item_expand_request(void *data, Evas_Object *o, void *event_info)
{
   Elm_Object_Item *it = (Elm_Object_Item*) event_info;

   elm_genlist_item_item_class_update(it, data);

   elm_genlist_item_expanded_set(it, EINA_TRUE);
}

static void
_tree_item_contract_request(void *data, Evas_Object *o, void *event_info)
{
   Elm_Object_Item *it = (Elm_Object_Item*) event_info;

   elm_genlist_item_item_class_update(it, data);

   elm_genlist_item_expanded_set(it, EINA_FALSE);
}

static void
_tree_item_expanded(void *data, Evas_Object *o, void *event_info)
{
   Elm_Object_Item *it_parent = (Elm_Object_Item*) event_info;
   int i_parent = (int)(uintptr_t)elm_object_item_data_get(it_parent);
   Elm_Object_Item *list = o;
   Elm_Genlist_Item_Class *itc = data;

   int i;
   for (i = 0; i < 10; i++)
     {
        elm_genlist_item_append(list, itc,
                (void *)(uintptr_t) (i + i_parent),
                it_parent,
                ELM_GENLIST_ITEM_NONE,
                NULL,
                NULL
                );
     }
}

static void
_tree_item_contracted(void *data, Evas_Object *o, void *event_info)
{
   Elm_Object_Item *it_parent = (Elm_Object_Item*) event_info;

   elm_genlist_item_subitems_clear(it_parent);
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

   Evas_Object *list;
   list = elm_genlist_add(win);
   evas_object_resize(list, 400, 400);

   Elm_Genlist_Item_Class *_itc_child = elm_genlist_item_class_new();
   _itc_child->item_style        = "default_style";
   _itc_child->func.text_get     = _genlist_text_get_size;
   _itc_child->func.content_get  = _genlist_content_get_bg;
   _itc_child->func.state_get    = NULL;
   _itc_child->func.del          = NULL;

   Elm_Genlist_Item_Class *_itc_parent = elm_genlist_item_class_new();
   _itc_parent->item_style       = "default_style";
   _itc_parent->func.text_get    = _genlist_text_get_nosize;
   _itc_parent->func.content_get = _genlist_content_get_bg;
   _itc_parent->func.state_get   = NULL;
   _itc_parent->func.del         = NULL;

   int i,j;
   Elm_Object_Item *it = NULL;

   for (i = 0; i < 100; i++)
     {
        it = elm_genlist_item_append(list, _itc_parent,
                (void *)(uintptr_t) (10 * i),
                NULL,
                ELM_GENLIST_ITEM_TREE,
                NULL,
                NULL
                );
     }

   evas_object_size_hint_weight_set(list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

   evas_object_smart_callback_add(list, "expand,request",
           _tree_item_expand_request, _itc_parent);
   evas_object_smart_callback_add(list, "expanded", _tree_item_expanded,
           _itc_child);

   evas_object_smart_callback_add(list, "contract,request",
           _tree_item_contract_request, _itc_child);
   evas_object_smart_callback_add(list, "contracted", _tree_item_contracted,
           NULL);

   evas_object_show(list);
   evas_object_show(win);
   elm_run();
   return 0;
}
ELM_MAIN()

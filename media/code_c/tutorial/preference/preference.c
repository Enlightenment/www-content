#include <Elementary.h>

static void
_save_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *prefs;
   Evas_Object *label;
   prefs = obj;
   label = (Evas_Object *) elm_prefs_item_object_get(prefs, "main:label");
   elm_object_text_set(label, "<i>Preferences have been saved.</i>");
}

static void
_action_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *prefs;
   Elm_Prefs_Data *prefs_data;
   Elm_Prefs_Item_Type type;
   Eina_Value value;
   int value_int = -1;
   Evas_Object *button;
   char buf[64];
   prefs = obj;
   prefs_data = elm_prefs_data_get(prefs);
   if (elm_prefs_data_value_get(prefs_data, "main:universe", &type, &value))
     {
        eina_value_get(&value, &value_int);
        snprintf(buf, sizeof(buf), "Value: %d", value_int);
        button = (Evas_Object *) elm_prefs_item_object_get(prefs, "main:buttons:action");
        elm_object_text_set(button, buf);
     }
}
static void
_changed_cb(void *data, Elm_Prefs_Data_Event_Type type, Elm_Prefs_Data *prefs_data, void *event_info)
{
   Evas_Object *prefs;
   Elm_Prefs_Data_Event_Changed *event;
   int value_int;
   Evas_Object *label;
   char buf[64];
   prefs = data;
   event = event_info;
   if (strcmp(event->key, "main:another")) return;
   eina_value_get(event->value, &value_int);
   snprintf(buf, sizeof(buf), "Spinner: %d", value_int);
   label = (Evas_Object *) elm_prefs_item_object_get(prefs, "main:label");
   elm_object_text_set(label, buf);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *conform;
   win = elm_win_util_standard_add("main", "Preferences Tutorial");
   elm_win_conformant_set(win, EINA_TRUE);
   evas_object_show(win);
   evas_object_resize(win, 480, 800);
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   conform = elm_conformant_add(win);
   evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, conform);
   evas_object_show(conform);
   Evas_Object *prefs;
   prefs = elm_prefs_add(win);
   evas_object_size_hint_weight_set(prefs, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_content_set(conform, prefs);
   evas_object_show(prefs);
   elm_prefs_autosave_set(prefs, EINA_FALSE);
   elm_prefs_file_set(prefs, "preference.epb", NULL);
   Elm_Prefs_Data *prefs_data;
   prefs_data = elm_prefs_data_new("preference.cfg", NULL, EET_FILE_MODE_READ_WRITE);
   elm_prefs_data_set(prefs, prefs_data);
   evas_object_smart_callback_add(prefs, "page,saved", _save_cb, NULL);
   evas_object_smart_callback_add(prefs, "action", _action_cb, NULL);
   elm_prefs_data_event_callback_add(prefs_data, ELM_PREFS_DATA_EVENT_ITEM_CHANGED, _changed_cb, prefs);
   elm_run();
   elm_shutdown();
   return EXIT_SUCCESS;
}
ELM_MAIN()


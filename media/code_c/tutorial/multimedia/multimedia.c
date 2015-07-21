#include <Elementary.h>
#include <Emotion.h>

#define FILE "<pathToYourVideo>/big_buck_bunny_1080p_h264.mov"

static Evas_Object *nav;
static Eina_Bool info; //if displaying info item

/* Time position and duration update */
static void
_player_info_time_update(void *data, Evas_Object *obj, void *event_info)
{
    Evas_Object *emotion = obj, *label = data;
    char buf[256];

    //switch on main item
    if (!info)
      {
         evas_object_smart_callback_del(emotion, "position_update", _player_info_time_update);
         evas_object_smart_callback_del(emotion, "length_change", _player_info_time_update);
         return;
      }

    //update
    double position = emotion_object_position_get(emotion);
    double duration = emotion_object_play_length_get(emotion);
    int p_sec = (int) position % 60;
    int p_min = position / 60;
    int p_hour = position / 3600;
    int d_sec = (int) duration % 60;
    int d_min = duration / 60;
    int d_hour = duration / 3600;
    snprintf(buf, sizeof(buf), "%d:%02d:%02d / %d:%02d:%02d", p_hour, p_min, p_sec, d_hour, d_min, d_sec);
    elm_object_text_set(label, buf);
}

/* get update status */
static void
_player_info_status_update(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *emotion = obj, *label = data;
   char buf[256];

   //switch on main item
   if (!info)
     {
        evas_object_smart_callback_del(obj, "playback_finished", _player_info_status_update);
        return;
     }

   //update
   double position = emotion_object_position_get(emotion);
   double duration = emotion_object_play_length_get(emotion);
   if (emotion_object_play_get(emotion))
        elm_object_text_set(label, "<b>Playing</b>");
   else if (position < duration)
        elm_object_text_set(label, "<b>Paused</b>");
   else
        elm_object_text_set(label, "<b>Ended</b>");
}

/* del info item callback */
static Eina_Bool
_player_info_del_cb(void *data, Elm_Object_Item *it)
{
    info = EINA_FALSE;
    return EINA_TRUE;
}

/* info callback */
static void
_player_info_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *video = data, *emotion;
   Evas_Object *table, *label;
   char buf[256];

   emotion = elm_video_emotion_get(video);
   info = EINA_TRUE;
   table = elm_table_add(obj);
   elm_table_padding_set(table, 8, 8);
   evas_object_size_hint_weight_set(table, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_show(table);

   /* display the playing status in label */
   label = elm_label_add(table);
   evas_object_show(label);
   _player_info_status_update(label, emotion, NULL);
   elm_table_pack(table, label, 0, 0, 2, 1);
   evas_object_smart_callback_add(emotion, "playback_finished", _player_info_status_update, label);

   /* get the file name and location */
   //set file label
   label = elm_label_add(table);
   elm_object_text_set(label, "File:");
   evas_object_show(label);
   elm_table_pack(table, label, 0, 1, 1, 1);

   //set file name label
   const char *file = emotion_object_file_get(emotion);
   label = elm_label_add(table);
   elm_object_text_set(label, ecore_file_file_get(file));
   evas_object_show(label);
   elm_table_pack(table, label, 1, 1, 1, 1);

   //set location label
   label = elm_label_add(table);
   elm_object_text_set(label, "Location:");
   evas_object_show(label);
   elm_table_pack(table, label, 0, 2, 1, 1);

   //set location path label
   label = elm_label_add(table);
   elm_object_text_set(label, ecore_file_dir_get(file));
   elm_object_text_set(label,"/home/efl/videos");
   evas_object_show(label);
   elm_table_pack(table, label, 1, 2, 1, 1);

   /* get the video position and duration */
   //set time label
   label = elm_label_add(table);
   elm_object_text_set(label, "Time:");
   evas_object_show(label);
   elm_table_pack(table, label, 0, 3, 1, 1);

   //set position-duration label
   label = elm_label_add(table);
   double position = elm_video_play_position_get(video);
   double duration = elm_video_play_length_get(video);
   int p_sec = (int) position % 60;
   int p_min = position / 60;
   int p_hour = position / 3600;
   int d_sec = (int) duration % 60;
   int d_min = duration / 60;
   int d_hour = duration / 3600;
   snprintf(buf, sizeof(buf), "%d:%02d:%02d / %d:%02d:%02d", p_hour, p_min, p_sec, d_hour, d_min, d_sec);
   elm_object_text_set(label, buf);
   elm_table_pack(table, label, 1, 3, 1, 1);
   evas_object_show(label);
   evas_object_smart_callback_add(emotion, "position_update", _player_info_time_update, label);
   evas_object_smart_callback_add(emotion, "length_change", _player_info_time_update, label);

   /* get the video dimensions */
   label = elm_label_add(table);
   elm_object_text_set(label, "Size:");
   evas_object_show(label);
   elm_table_pack(table, label, 0, 4, 1, 1);
   label = elm_label_add(table);
   int w, h;
   emotion_object_size_get(emotion, &w, &h);
   snprintf(buf, sizeof(buf), "%d × %d", w, h);
   elm_object_text_set(label, buf);
   evas_object_show(label);
   elm_table_pack(table, label, 1, 4, 1, 1);

   /* push info in a separate naviframe item */
   Elm_Object_Item *it = elm_naviframe_item_push(nav, "Information", NULL, NULL, table, NULL);
   elm_naviframe_item_pop_cb_set(it, _player_info_del_cb, NULL);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win;
   info = EINA_FALSE;
   win = elm_win_util_standard_add("main", "Multimedia Tutorial");
   evas_object_show(win);
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   nav = elm_naviframe_add(win);
   evas_object_size_hint_weight_set(nav, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, nav);
   evas_object_show(nav);

   Evas_Object *video;
   video = elm_video_add(win);
   evas_object_size_hint_weight_set(video, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_video_file_set(video, FILE);
   elm_video_play(video);
   evas_object_show(video);

   Evas_Object *player;
   player = elm_player_add(win);
   evas_object_size_hint_weight_set(player, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_object_content_set(player, video);
   evas_object_smart_callback_add(player, "info,clicked", _player_info_cb, video);
   evas_object_show(player);

   Elm_Object_Item *it = elm_naviframe_item_push(nav, "Video", NULL, NULL, player, NULL);
   elm_naviframe_item_title_enabled_set(it, EINA_FALSE, EINA_FALSE);

   elm_run();
   elm_shutdown();
   return EXIT_SUCCESS;
}
ELM_MAIN()

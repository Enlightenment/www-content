#include <Elementary.h>

    EAPI_MAIN int
elm_main(int argc, char **argv)
{
    Evas_Object *win;

    elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

    win = elm_win_util_standard_add("Main", "Hello, World!");
    elm_win_autodel_set(win, EINA_TRUE);
    //win 400x400
    evas_object_resize(win, 400, 400);

    /*basic tutorial code*/
    //text_label
    Evas_Object *label_text;
    label_text = elm_label_add(win);

    elm_object_text_set(label_text,"My label");
    evas_object_color_set(label_text, 0, 0, 255, 255);

    evas_object_resize(label_text, 90, 30);
    evas_object_show(label_text);

    //sliding text
    Evas_Object *label_slide;
    label_slide = elm_label_add(win);

    elm_object_text_set(label_slide, "<b>Some long bold text for our label_slide, that is long but</b>"
    "<b>not too long.</b>");

    elm_object_style_set(label_slide,"slide_bounce");
    elm_label_slide_duration_set(label_slide, 3);
    elm_label_slide_mode_set(label_slide, ELM_LABEL_SLIDE_MODE_ALWAYS);

    elm_label_slide_go(label_slide);

    evas_object_resize(label_slide, 200, 15);
    evas_object_move(label_slide,0,40);
    evas_object_show(label_slide);

    evas_object_show(win);
    elm_run();
    return 0;
}
ELM_MAIN()

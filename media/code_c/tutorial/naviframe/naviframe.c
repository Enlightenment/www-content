#include <Elementary.h>

#define __UNUSED__ __attribute__((__unused__))

// NOTE: A zipper is a datastructure for an ordered set of elements and a
// cursor in this set, meaning there are elements before the cursor (which are
// stored inside the naviframe) and after (which are stored in the "popped"
// list.
struct naviframe_zipper
{
   Evas_Object *naviframe;
   Eina_List *popped;
};

static struct naviframe_zipper *
_naviframe_add(Evas_Object *parent)
{
   struct naviframe_zipper *z = malloc(sizeof(struct naviframe_zipper));
   z->naviframe = elm_naviframe_add(parent);
   z->popped = NULL;

   evas_object_size_hint_weight_set(z->naviframe, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(z->naviframe, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(z->naviframe);
   // By default, objects are destroyed when they are popped from the naviframe
   // To save and re-use them, enable "preserve_on_pop"
   elm_naviframe_content_preserve_on_pop_set(z->naviframe, EINA_TRUE);

   return z;
}

// forward declaration of the _button function since there is a circular
// reference below
static Evas_Object * _button(struct naviframe_zipper *, int direction);

// Save the element that is popped from the naviframe
// callback of the prev button
static void
_naviframe_prev(void *data, Evas_Object *o __UNUSED__, void *event_info __UNUSED__)
{
   struct naviframe_zipper *z = data;
   //if more than one item push in naviframe
   if (elm_naviframe_bottom_item_get(z->naviframe) != elm_naviframe_top_item_get(z->naviframe))
     {
        z->popped = eina_list_prepend(z->popped, elm_naviframe_item_pop(z->naviframe));
     }
}

// Set the first element after the current one available and push it to the
// naviframe
// callback of the next button
static void
_naviframe_next(void *data, Evas_Object *o __UNUSED__, void *event_info __UNUSED__)
{
   struct naviframe_zipper *z = data;
   Evas_Object *label, *prev, *next;
   const char *text;
   Elm_Object_Item *it;

   label = eina_list_data_get(z->popped);
   z->popped = eina_list_remove_list(z->popped, z->popped);
   if (label != NULL)
     {
        // The widget is saved inside the naviframe but nothing more; we need
        // to create new buttons and set the title text again (copy the one
        // from the label that is saved).
        text = elm_object_text_get(label);
        // The _button function creates a button which is either "Previous" (-1) or
        // "Next" (1)
        prev = _button(z, -1);
        next = _button(z, 1);
        it = elm_naviframe_item_push(z->naviframe, text, prev, next, label, NULL);
     }
}

// Build either a "Previous" or a "Next" button
static Evas_Object *
_button(struct naviframe_zipper *z, int direction)
{
   Evas_Object *button;
   Evas_Smart_Cb callback;
   const char *text;
   if (direction < 0)
     {
        text = "Previous";
        callback = _naviframe_prev;
     }
   else
     {
        text = "Next";
        callback = _naviframe_next;
     }
   button = elm_button_add(z->naviframe);
   elm_object_text_set(button, text);
   evas_object_smart_callback_add(button, "clicked", callback, z);
   return button;
}

// Generic naviframe-populate function:
// Its third (and last) parameter is a callback for customization, i.e. pushes
// the new items to a specific position; it returns a "context" value that is
// used between its calls and enables behaviors such as "push after the
// previously-pushed item"
static struct naviframe_zipper*
_naviframe_populate_gen(Evas_Object *parent, const char *id,
        void * (*populate_cb) (Evas_Object *nav, const char *title, Evas_Object
            *prev, Evas_Object *next, Evas_Object *label, Elm_Object_Item *context)
        )
{
   struct naviframe_zipper *z;
   Evas_Object *label,*label2, *prev, *next;
   Elm_Object_Item *context = NULL;
   char buf[256];
   int i;

   z = _naviframe_add(parent);

   for (i = 0; i < 20; i++)
     {
        label = elm_label_add(z->naviframe);
        label2 = elm_label_add(z->naviframe);
        snprintf(buf, sizeof(buf), "%s [%d]", id, i);
        elm_object_text_set(label, buf);
        evas_object_show(label);
        evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
        // The _button function creates a button which is either "Previous" (-1) or
        // "Next" (1)
        prev = _button(z, -1);
        next = _button(z, 1);
        // Use the populate_cb callback to provide the customization of the way the
        // elements are added inside the naviframe
        context = populate_cb(z->naviframe, buf, prev, next, label, context);
     }
   return z;
}

// Push items one after the other
static Elm_Object_Item *
_populate_cb__push(Evas_Object *nav, const char *title,
        Evas_Object *prev, Evas_Object *next, Evas_Object *label,
        Elm_Object_Item *context)
{
   return elm_naviframe_item_push(nav, title, prev, next, label, NULL);
}

// Push items one after the other but use insert_after for it
static Elm_Object_Item *
_populate_cb__push_then_insert_after(Evas_Object *nav, const char *title,
        Evas_Object *prev, Evas_Object *next, Evas_Object *label,
        Elm_Object_Item *context)
{
   if (context == NULL)
     {
        return elm_naviframe_item_push(nav, title, prev, next, label, NULL);
     }
   else
     {
        return elm_naviframe_item_insert_after(nav, context, title, prev, next, label, NULL);
     }
}

// Push one item and repeatedly insert new items before the last inserted
// item
static Elm_Object_Item *
_populate_cb__push_then_insert_before(Evas_Object *nav, const char *title,
        Evas_Object *prev, Evas_Object *next, Evas_Object *label,
        Elm_Object_Item *context)
{
   if (context == NULL)
     {
        return elm_naviframe_item_push(nav, title, prev, next, label, NULL);
     }
   else
     {
        return elm_naviframe_item_insert_before(nav, context, title, prev, next, label, NULL);
     }
}

static void
_delete_cb(void *data, Evas_Object *obj, void *event_info)
{
   struct naviframe_zipper **z = data;
   free(*z);
   free(*(z+1));
   free(*(z+2));
   free(z);
   evas_object_del(obj);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win;

   win = elm_win_util_standard_add("Naviframe", "Naviframe Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);

   Evas_Object *box;
   struct naviframe_zipper **z = malloc(3*sizeof(struct naviframe_zipper *));

   box = elm_box_add(win);
   elm_box_horizontal_set(box, EINA_FALSE);
   elm_box_homogeneous_set(box, EINA_TRUE);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(box);
   elm_win_resize_object_add(win, box);

   z[0] = _naviframe_populate_gen(win, "Before", (void *)_populate_cb__push_then_insert_before);
   elm_box_pack_end(box, (*z)->naviframe);

   z[1] = _naviframe_populate_gen(win, "After", (void *)_populate_cb__push_then_insert_after);
   elm_box_pack_end(box, (*(z+1))->naviframe);

   z[2] = _naviframe_populate_gen(win, "Push", (void *)_populate_cb__push);
   elm_box_pack_end(box, (*(z+2))->naviframe);

   evas_object_smart_callback_add(win, "delete,request", _delete_cb, z);
   //win 400x400 px
   evas_object_resize(win, 400, 400);
   evas_object_show(win);
   elm_run();
   return 0;
}
ELM_MAIN()

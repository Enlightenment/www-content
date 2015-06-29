#include <Elementary.h>

#define ICON_PATH "<your_path_to_contact_icons_directory>"
typedef struct _Contact Contact;

struct _Contact
{
   const char *name;
   const char *mobile;
   const char *address;
   const char *email;
   const char *icon;
};

static Contact contacts[] =
{
   {"Alexander Holmes", "+1234567896", "", "alexander_holmes@tizen.org",    "c1.svg"},
   {"Lara Alvaréz",     "+9876543216", "", "lara_alvares@tizen.org",        "c2.svg"},
   {"Aksel Møller",     "+1679432846", "", "aksel_moller@tizen.org",        "c3.svg"},
   {"Anir Amghar",      "+1679432846", "", "anir_amghar@tizen.org",         "c4.svg"},
   {"Noémie Cordier",   "+1679432846", "", "noemie_cordier@tizen.org",      "c5.svg"},
   {"Henry Thompson",   "+1679432846", "", "henry_thompson@tizen.org",      "c6.svg"},
   {"Mai Phan",         "+1679432846", "", "mai_phan@tizen.org",            "c7.svg"},
};

static const char *form_items[] =
{
   "name :", "mobile :", "address :", "email :"
};

static Evas_Object *nav;
static Elm_Genlist_Item_Class *itc = NULL;

//contact form called in item callback
static Evas_Object *
_create_contact_form(Evas_Object *parent, Contact *contact)
{
   //Create the vbox
   Evas_Object *vbox, *ic;
   int i;
   vbox = elm_box_add(parent);
   elm_box_align_set(vbox, 0, 0);
   evas_object_show(vbox);

   //add the icon to the vbox
   ic = elm_icon_add(vbox);
   char filename[PATH_MAX];
   snprintf(filename, sizeof(filename), "%s%s", ICON_PATH, contact->icon);
   elm_image_file_set(ic, filename, NULL);
   evas_object_size_hint_min_set(ic, 96, 96);
   evas_object_show(ic);
   elm_box_pack_end(vbox, ic);

   //create the entries for contact information
   for (i = 0; i < EINA_C_ARRAY_LENGTH(form_items); i++)
     {
        Evas_Object *hbox, *label, *edit;
        const char *str;

        //hbox
        hbox = elm_box_add(vbox);
        elm_box_horizontal_set(hbox, EINA_TRUE);
        elm_box_padding_set(hbox, 32, 32);
        evas_object_size_hint_weight_set(hbox, EVAS_HINT_EXPAND, 0);
        evas_object_size_hint_align_set(hbox, EVAS_HINT_FILL, 0);
        evas_object_show(hbox);

        //label
        label = elm_label_add(hbox);
        elm_object_text_set(label, form_items[i]);
        evas_object_size_hint_weight_set(label, 0, 0);
        evas_object_size_hint_align_set(label, 0, 0);
        evas_object_show(label);

        //edit
        edit = elm_entry_add(hbox);

        if(!strcmp(form_items[i], "name :")) str = contact->name;
        else if(!strcmp(form_items[i], "mobile :")) str = contact->mobile;
        else if(!strcmp(form_items[i], "address :")) str = contact->address;
        else if(!strcmp(form_items[i], "email :")) str = contact->email;
        else str = NULL;

        elm_object_text_set(edit, str);
        evas_object_size_hint_weight_set(edit, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_align_set(edit, EVAS_HINT_FILL, EVAS_HINT_FILL);
        evas_object_show(edit);

        elm_box_pack_end(hbox, label);
        elm_box_pack_end(hbox, edit);

        elm_box_pack_end(vbox, hbox);
     }
   return vbox;
}

//item callback
static void
_contact_selected_cb(void *data, Evas_Object *obj, void *event_info)
{
   Evas_Object *form;
   Contact *contact = data;
   //Create a new contact form
   form = _create_contact_form(nav, contact);
   //Push the form on top of naviframe
   elm_naviframe_item_push(nav, NULL, NULL, NULL, form, NULL);
}

//set item text
static char *
_genlist_text_get(void *data, Evas_Object *obj EINA_UNUSED, const char *part)
{
   Contact *contact = data;

   //Return a new allocated string for the contact name
   return strdup(contact->name);
}

//set item content
static Evas_Object *
_genlist_content_get(void *data, Evas_Object *obj, const char *part)
{
   Contact *contact = data;

   //Test which part is being created
   if (!strcmp(part, "elm.swallow.icon"))
     {
        char filename[PATH_MAX];
        // Create a new icon
        Evas_Object *ic = elm_icon_add(obj);
        // Set the filename of the file which is to be loaded
        snprintf(filename, sizeof(filename), "%s%s", ICON_PATH, contact->icon);
        elm_image_file_set(ic, filename, NULL);
        // Keep the ratio squared
        evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);

        // Return the icon
        return ic;
     }
   return NULL;
}

static Evas_Object *
_create_contact_list(Evas_Object *parent)
{
   Evas_Object *list;
   int i;
   //Create a new genlist
   list = elm_genlist_add(parent);
   evas_object_show(list);
   // Create a new item class for the genlist
   itc = elm_genlist_item_class_new();
   itc->item_style = "default";
   // Set the callback which will be used when the genlist text will be created
   itc->func.text_get = _genlist_text_get;
   // Set the callback wich will be used when the content of the item will be created
   itc->func.content_get  = _genlist_content_get;
   itc->func.state_get = NULL;
   itc->func.del = NULL;
   // Create a genlist item for each item in the contacts array
   for (i = 0; i < EINA_C_ARRAY_LENGTH(contacts); i++)
     {
        // Append the item, add a callback when the item is selected, and use the
        // current contact item as data pointer for the callbacks.
        elm_genlist_item_append(
                list, itc,
                &contacts[i],             // Item data
                NULL,                     // Parent item for trees, NULL if none
                ELM_GENLIST_ITEM_NONE,    // Item type; this is the common one
                _contact_selected_cb,     // Callback on selection of the item
                &contacts[i]              // Data for that callback function
                );
     }
   return list;
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win;
   win = elm_win_util_standard_add("Form", "Form Tutorial");
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   elm_win_autodel_set(win, EINA_TRUE);
   //win 400x400 px
   evas_object_resize(win, 400, 400);

   //Create the naviframe
   nav = elm_naviframe_add(win);
   evas_object_size_hint_weight_set(nav, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, nav);
   evas_object_show(nav);

   // Create the list of contacts
   Evas_Object *list = _create_contact_list(win);

   // Push the list on top of the naviframe
   elm_naviframe_item_push(nav, NULL, NULL, NULL, list, NULL);

   evas_object_show(win);
   elm_run();
   return 0;
}
ELM_MAIN()

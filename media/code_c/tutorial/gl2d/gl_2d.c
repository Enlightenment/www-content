#include <Elementary.h>
#include <Evas_GL.h>

typedef struct _GLData GLData;
// GL related data here..
struct _GLData
{
   Evas_GL_API  *glapi;
   GLuint       program;
   GLuint       vtx_shader;
   GLuint       fgmt_shader;
   GLuint       vbo;
   GLuint       vertexID;
   GLuint       colorID;
   GLuint       mvpLoc;
   GLuint       positionLoc;
   GLuint       colorLoc;
   GLfloat      model[16], mvp[16];
   GLfloat      view[16];
   GLfloat      xangle;
   GLfloat      yangle;
   GLfloat      zangle;
   Eina_Bool    mouse_down : 1;
   Eina_Bool    initialized : 1;
   Evas_Object  *slx;
   Evas_Object  *sly;
   Evas_Object  *slz;
   float        slx_value;
   float        sly_value;
   float        slz_value;
};

const float unit_matrix[] =
{
   1.0f, 0.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 0.0f, 1.0f
};

static const float vertices[] =
{
   // Front
   -0.5f, 0.5f, 0.5f,
   -0.5f, -0.5f, 0.5f,
   0.5f, 0.5f, 0.5f,
   0.5f, 0.5f, 0.5f,
   -0.5f, -0.5f, 0.5f,
   0.5f, -0.5f, 0.5f,
   // Right
   0.5f, 0.5f, 0.5f,
   0.5f, -0.5f, 0.5f,
   0.5f, 0.5f, -0.5f,
   0.5f, 0.5f, -0.5f,
   0.5f, -0.5f, 0.5f,
   0.5f, -0.5f, -0.5f,
   // Back
   0.5f, 0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   -0.5f, 0.5f, -0.5f,
   -0.5f, 0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   // Left
   -0.5f, 0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, 0.5f, 0.5f,
   -0.5f, 0.5f, 0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f, 0.5f,
   // Top
   -0.5f, 0.5f, -0.5f,
   -0.5f, 0.5f, 0.5f,
   0.5f, 0.5f, -0.5f,
   0.5f, 0.5f, -0.5f,
   -0.5f, 0.5f, 0.5f,
   0.5f, 0.5f, 0.5f,
   // Bottom
   -0.5f, -0.5f, 0.5f,
   -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, 0.5f,
   0.5f, -0.5f, 0.5f,
   -0.5f, -0.5f, -0.5f,
   0.5f, -0.5f, -0.5f
};

static const float colors[] =
{
   // Front
   0.0625f, 0.57421875f, 0.92578125f, 1.0f,
   0.0625f, 0.57421875f, 0.92578125f, 1.0f,
   0.0625f, 0.57421875f, 0.92578125f, 1.0f,
   0.0625f, 0.57421875f, 0.92578125f, 1.0f,
   0.0625f, 0.57421875f, 0.92578125f, 1.0f,
   0.0625f, 0.57421875f, 0.92578125f, 1.0f,
   // Right
   0.29296875f, 0.66796875f, 0.82578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.82578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.82578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.82578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.82578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.82578125f, 1.0f,
   // Back
   0.52734375f, 0.76171875f, 0.72578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.72578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.72578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.72578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.72578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.72578125f, 1.0f,
   // Left
   0.0625f, 0.57421875f, 0.62578125f, 1.0f,
   0.0625f, 0.57421875f, 0.62578125f, 1.0f,
   0.0625f, 0.57421875f, 0.62578125f, 1.0f,
   0.0625f, 0.57421875f, 0.62578125f, 1.0f,
   0.0625f, 0.57421875f, 0.62578125f, 1.0f,
   0.0625f, 0.57421875f, 0.62578125f, 1.0f,
   // Top
   0.29296875f, 0.66796875f, 0.52578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.52578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.52578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.52578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.52578125f, 1.0f,
   0.29296875f, 0.66796875f, 0.52578125f, 1.0f,
   // Bottom
   0.52734375f, 0.76171875f, 0.42578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.42578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.42578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.42578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.42578125f, 1.0f,
   0.52734375f, 0.76171875f, 0.42578125f, 1.0f
};

static void
customLoadIdentity(float matrix[16])
{
   for (int i = 0; i < 16; i++)
        matrix[i] = unit_matrix[i];
}

static void
customMutlMatrix(float matrix[16], const float matrix0[16], const float matrix1[16])
{
   int i, row, column;
   float temp[16];
   for (column = 0; column < 4; column++)
     {
        for (row = 0; row < 4; row++)
          {
             temp[column * 4 + row] = 0.0f;
             for (i = 0; i < 4; i++)
                  temp[column * 4 + row] += matrix0[i * 4 + row] * matrix1[column * 4 + i];
          }
     }
   for (i = 0; i < 16; i++)
        matrix[i] = temp[i];
}

static void
customScale(float matrix[16], const float sx, const float sy, const float sz)
{
   matrix[0]  *= sx;
   matrix[1]  *= sx;
   matrix[2]  *= sx;
   matrix[3]  *= sx;

   matrix[4]  *= sy;
   matrix[5]  *= sy;
   matrix[6]  *= sy;
   matrix[7]  *= sy;

   matrix[8]  *= sz;
   matrix[9]  *= sz;
   matrix[10] *= sz;
   matrix[11] *= sz;
}

static void
customRotate(float matrix[16], const float anglex, const float angley, const float anglez)
{
   const float pi = 3.141592f;
   float temp[16];
   float rz = 2.0f * pi * anglez / 360.0f;
   float rx = 2.0f * pi * anglex / 360.0f;
   float ry = 2.0f * pi * angley / 360.0f;
   float sy = sinf(ry);
   float cy = cosf(ry);
   float sx = sinf(rx);
   float cx = cosf(rx);
   float sz = sinf(rz);
   float cz = cosf(rz);

   customLoadIdentity(temp);

   temp[0] = cy * cz - sx * sy * sz;
   temp[1] = cz * sx * sy + cy * sz;
   temp[2] = -cx * sy;

   temp[4] = -cx * sz;
   temp[5] = cx * cz;
   temp[6] = sx;

   temp[8] = cz * sy + cy * sx * sz;
   temp[9] = -cy * cz * sx + sy * sz;
   temp[10] = cx * cy;

   customMutlMatrix(matrix, matrix, temp);
}

static int
customFrustum(float result[16], const float left, const float right, const float bottom, const float top, const float near, const float far)
{
   if ((right - left) == 0.0f || (top - bottom) == 0.0f || (far - near) == 0.0f) return 0;

   result[0] = 2.0f / (right - left);
   result[1] = 0.0f;
   result[2] = 0.0f;
   result[3] = 0.0f;

   result[4] = 0.0f;
   result[5] = 2.0f / (top - bottom);
   result[6] = 0.0f;
   result[7] = 0.0f;

   result[8] = 0.0f;
   result[9] = 0.0f;
   result[10] = -2.0f / (far - near);
   result[11] = 0.0f;

   result[12] = -(right + left) / (right - left);
   result[13] = -(top + bottom) / (top - bottom);
   result[14] = -(far + near) / (far - near);
   result[15] = 1.0f;

   return 1;
}

static int
init_shaders(GLData *gld)
{
   Evas_GL_API *gl = gld->glapi;

   GLbyte vertex_shader[] =
       "#ifdef GL_ES\n"
       "precision mediump float;\n"
       "#endif\n"
       "attribute vec4 a_position;\n"
       "attribute vec4 a_color;\n"
       "uniform mat4 u_mvp_mat;\n"
       "varying vec4 v_color;\n"
       "void main()\n"
       "{\n"
       "   gl_Position = u_mvp_mat*a_position;\n"
       "   v_color = a_color;\n"
       "}";
   GLbyte fragment_shader[] =
       "#ifdef GL_ES\n"
       "precision highp float;\n"
       "#endif\n"
       "varying vec4 v_color;\n"
       "void main()\n"
       "{\n"
       "   gl_FragColor = v_color;\n"
       "}";

   GLint compiled;
   const char *p = vertex_shader;

   //vertex shader
   gld->vtx_shader = gl->glCreateShader(GL_VERTEX_SHADER);
   gl->glShaderSource(gld->vtx_shader, 1, &p, NULL);
   gl->glCompileShader(gld->vtx_shader);
   gl->glGetShaderiv(gld->vtx_shader, GL_COMPILE_STATUS, &compiled);
   if (!compiled)
     {
        GLint info_len = 0;
        gl->glGetShaderiv(gld->vtx_shader, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1)
          {
             char* info_log = malloc(sizeof(char) * info_len);
             gl->glGetShaderInfoLog(gld->vtx_shader, info_len, NULL, info_log);
             printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, p);
             free(info_log);
          }
        gl->glDeleteShader(gld->vtx_shader);
     }

   //fragment shader
   p = fragment_shader;
   gld->fgmt_shader = gl->glCreateShader(GL_FRAGMENT_SHADER);
   gl->glShaderSource(gld->fgmt_shader, 1, &p, NULL);
   gl->glCompileShader(gld->fgmt_shader);
   gl->glGetShaderiv(gld->fgmt_shader, GL_COMPILE_STATUS, &compiled);
   if (!compiled)
     {
        GLint info_len = 0;
        gl->glGetShaderiv(gld->fgmt_shader, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1)
          {
             char* info_log = malloc(sizeof(char) * info_len);
             gl->glGetShaderInfoLog(gld->fgmt_shader, info_len, NULL, info_log);
             printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, p);
             free(info_log);
          }
        gl->glDeleteShader(gld->fgmt_shader);
     }

   gld->program = gl->glCreateProgram();

   GLint linked;
   // Load the vertex/fragment shaders
   gl->glAttachShader(gld->program, gld->vtx_shader);
   gl->glAttachShader(gld->program, gld->fgmt_shader);
   gl->glDeleteShader(gld->vtx_shader);
   gl->glDeleteShader(gld->fgmt_shader);

   gl->glBindAttribLocation(gld->program, 0, "a_position");
   gl->glLinkProgram(gld->program);
   gl->glGetProgramiv(gld->program, GL_LINK_STATUS, &linked);
   if (!linked)
     {
        GLint info_len = 0;
        gl->glGetProgramiv(gld->program, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1)
          {
             char* info_log = malloc(sizeof(char) * info_len);
             gl->glGetProgramInfoLog(gld->program, info_len, NULL, info_log);
             printf("Error linking program:\n%s\n", info_log);
             free(info_log);
          }
        gl->glDeleteProgram(gld->program);
        return 0;
     }
   gld->mvpLoc     = gl->glGetUniformLocation(gld->program, "u_mvp_mat");
   gld->positionLoc = gl->glGetAttribLocation(gld->program, "a_position");
   gld->colorLoc   = gl->glGetAttribLocation(gld->program, "a_color");
   return 1;
}

// Callbacks
// intialize callback that gets called once for intialization
static void
_init_gl(Evas_Object *obj)
{
   int w, h;
   GLData *gld = evas_object_data_get(obj, "gld");
   Evas_GL_API *gl = gld->glapi;

   elm_glview_size_get(obj, &w, &h);

   if (!gld->initialized)
     {
        if (!init_shaders(gld))
          {
             printf("Error Initializing Shaders\n");
             return;
          }

        gl->glGenBuffers(1, &gld->vertexID);
        gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vertexID);
        gl->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        gl->glGenBuffers(1, &gld->colorID);
        gl->glBindBuffer(GL_ARRAY_BUFFER, gld->colorID);
        gl->glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        gld->initialized = EINA_TRUE;
     }
}

// draw callback is where all the main GL rendering happens
static void
_draw_gl(Evas_Object *obj)
{
   Evas_GL_API *gl = elm_glview_gl_api_get(obj);
   GLData *gld = evas_object_data_get(obj, "gld");
   if(!gld) return;
   int w, h;
   int r, g, b, a;
   //scale
   double scalex = elm_slider_value_get(gld->slx);
   double scaley = elm_slider_value_get(gld->sly);
   double scalez = elm_slider_value_get(gld->slz);

   r = 255; g = 255; b = 0; a = 0;

   elm_glview_size_get(obj, &w, &h);

   gl->glClearDepthf(1.0f);
   gl->glClearColor(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
   gl->glEnable(GL_CULL_FACE);

   gl->glViewport(0, 0, w, h);
   gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   gl->glUseProgram(gld->program);

   gl->glEnableVertexAttribArray(gld->positionLoc);
   gl->glBindBuffer(GL_ARRAY_BUFFER, gld->vertexID);
   gl->glVertexAttribPointer(gld->positionLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

   gl->glEnableVertexAttribArray(gld->colorLoc);
   gl->glBindBuffer(GL_ARRAY_BUFFER, gld->colorID);
   gl->glVertexAttribPointer(gld->colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

   customLoadIdentity(gld->model);
   customRotate(gld->model, gld->xangle, gld->yangle, gld->zangle++);
   //scale
   customScale(gld->model, scalex, scaley, scalez);
   customMutlMatrix(gld->mvp, gld->view, gld->model);

   gl->glUniformMatrix4fv(gld->mvpLoc, 1, GL_FALSE, gld->mvp);
   gl->glDrawArrays(GL_TRIANGLES, 0, 36);
   gl->glFlush();
}

// resize callback gets called every time object is resized
static void
_resize_gl(Evas_Object *obj)
{
   int w, h;
   GLData *gld = evas_object_data_get(obj, "gld");
   Evas_GL_API *gl = gld->glapi;
   float aspect;

   elm_glview_size_get(obj, &w, &h);
   customLoadIdentity(gld->view);

   if (w > h)
     {
        aspect = (float) w / h;
        customFrustum(gld->view, -1.0 * aspect, 1.0 * aspect, -1.0, 1.0, -1.0, 1.0);
     }
   else
     {
        aspect = (float) h / w;
        customFrustum(gld->view, -1.0, 1.0, -1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
     }
}
// delete callback gets called when glview is deleted
static void
_del_gl(Evas_Object *obj)
{
   GLData *gld = evas_object_data_get(obj, "gld");
   if (!gld)
     {
        printf("Unable to get GLData. \n");
        return;
     }

   Evas_GL_API *gl = gld->glapi;
   gl->glDeleteShader(gld->vtx_shader);
   gl->glDeleteShader(gld->fgmt_shader);
   gl->glDeleteProgram(gld->program);
   evas_object_data_del((Evas_Object*) obj, "..gld");
}

// just need to notify that glview has changed so it can render
static Eina_Bool
_anim(void *data)
{
   elm_glview_changed_set(data);
   return EINA_TRUE;
}
static void
_mouse_down_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
   GLData *gld = data;
   gld->mouse_down = EINA_TRUE;
}

static void
_mouse_up_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
   GLData *gld = data;
   gld->mouse_down = EINA_FALSE;
}

static void
_mouse_move_cb(void *data, Evas *e , Evas_Object *obj , void *event_info)
{
   Evas_Event_Mouse_Move *ev;
   ev = (Evas_Event_Mouse_Move *)event_info;
      GLData *gld = data;
   float dx = 0, dy = 0;

   if(gld->mouse_down)
     {
        dx = ev->cur.canvas.x - ev->prev.canvas.x;
        dy = ev->cur.canvas.y - ev->prev.canvas.y;
        gld->xangle += dy;
        gld->yangle += dx;
     }
}

static void
_on_done(void *data, Evas_Object *obj, void *event_info)
{
   evas_object_del((Evas_Object*)data);
   elm_exit();
}
static void
_del(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
   Ecore_Animator *ani = evas_object_data_get(obj, "ani");
   ecore_animator_del(ani);
}

static Eina_Bool
animate_reset_cb(void *data, double pos)
{
   GLData *gld = data;
   double frame = pos;
   float x, y, z;

   frame = ecore_animator_pos_map(pos, ECORE_POS_MAP_BOUNCE, 1.8, 7);
   x = gld->slx_value * (1 - frame) + 0.75 * frame;
   y = gld->sly_value * (1 - frame) + 0.75 * frame;
   z = gld->slz_value * (1 - frame) + 0.75 * frame;

   elm_slider_value_set(gld->slx, x);
   elm_slider_value_set(gld->sly, y);
   elm_slider_value_set(gld->slz, z);

   return EINA_TRUE;
}

static void btn_reset_cb(void *data, Evas_Object *obj,  void *event_info)
{
   GLData *gld = data;
   gld->slx_value = elm_slider_value_get(gld->slx);
   gld->sly_value = elm_slider_value_get(gld->sly);
   gld->slz_value = elm_slider_value_get(gld->slz);
   ecore_animator_timeline_add(1, animate_reset_cb, gld);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win, *bx, *inner_box, *bt, *gl, *btn_reset;
   Ecore_Animator *ani;
   GLData *gld = NULL;
   if (!(gld = calloc(1, sizeof(GLData)))) return 1;
   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);
   win = elm_win_util_standard_add("glview simple", "GLView Simple");
   elm_win_autodel_set(win, EINA_TRUE);
   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_show(bx);
   inner_box = elm_box_add(bx);
   evas_object_size_hint_weight_set(inner_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_show(inner_box);

   //-//-//-// THIS IS WHERE GL INIT STUFF HAPPENS (ALA EGL)
   //-//
   // create a new glview object
   gl = elm_glview_add(win);
   gld->glapi = elm_glview_gl_api_get(gl);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   // mode is simply for supporting alpha, depth buffering, and stencil
   // buffering.
   elm_glview_mode_set(gl, ELM_GLVIEW_ALPHA | ELM_GLVIEW_DEPTH);
   // resize policy tells glview what to do with the surface when it
   // resizes.  ELM_GLVIEW_RESIZE_POLICY_RECREATE will tell it to
   // destroy the current surface and recreate it to the new size
   elm_glview_resize_policy_set(gl, ELM_GLVIEW_RESIZE_POLICY_RECREATE);
   // render policy tells glview how it would like glview to render
   // gl code. ELM_GLVIEW_RENDER_POLICY_ON_DEMAND will have the gl
   // calls called in the pixel_get callback, which only gets called
   // if the object is visible, hence ON_DEMAND.  ALWAYS mode renders
   // it despite the visibility of the object.
   elm_glview_render_policy_set(gl, ELM_GLVIEW_RENDER_POLICY_ON_DEMAND);
   // initialize callback function gets registered here
   elm_glview_init_func_set(gl, _init_gl);
   // delete callback function gets registered here
   elm_glview_del_func_set(gl, _del_gl);
   elm_glview_resize_func_set(gl, _resize_gl);
   elm_glview_render_func_set(gl, _draw_gl);
   //-//
   //-//-//-// END GL INIT BLOB
   elm_box_pack_end(bx, gl);
   evas_object_show(gl);
   elm_object_focus_set(gl, EINA_TRUE);
   // animating - just a demo. as long as you trigger an update on the image
   // object via elm_glview_changed_set() it will be updated.
   //
   // NOTE: if you delete gl, this animator will keep running trying to access
   // gl so you'd better delete this animator with ecore_animator_del().
   ani = ecore_animator_add(_anim, gl);
   evas_object_data_set(gl, "ani", ani);
   evas_object_data_set(gl, "gld", gld);
   evas_object_event_callback_add(gl, EVAS_CALLBACK_DEL, _del, gl);
   evas_object_event_callback_add(gl, EVAS_CALLBACK_MOUSE_DOWN, _mouse_down_cb, gld);
   evas_object_event_callback_add(gl, EVAS_CALLBACK_MOUSE_UP, _mouse_up_cb, gld);
   evas_object_event_callback_add(gl, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move_cb, gld);
   /* Set rotation variables */
   gld->xangle = 45.0f;
   gld->yangle = 45.0f;
   gld->zangle = 0.0f;
   gld->mouse_down = EINA_FALSE;
   gld->initialized = EINA_FALSE;
   // add an 'OK' button to end the program
   bt = elm_button_add(win);
   elm_object_text_set(bt, "OK");
   evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
   elm_box_pack_end(bx, bt);
   evas_object_show(bt);
   evas_object_smart_callback_add(bt, "clicked", _on_done, win);

   // Slider for X-axis scale
   gld->slx = elm_slider_add(inner_box);
   evas_object_size_hint_align_set(gld->slx, EVAS_HINT_FILL, 0);
   elm_slider_horizontal_set(gld->slx, EINA_TRUE);
   elm_slider_unit_format_set(gld->slx, "%1.2f units");
   elm_slider_indicator_format_set(gld->slx, "%1.2f units");
   elm_slider_indicator_show_set(gld->slx, EINA_TRUE);
   elm_slider_min_max_set(gld->slx, 0, 1.5);
   elm_slider_value_set(gld->slx, 0.75);
   evas_object_color_set(gld->slx, 0.0, 0.0, 120, 255);
   elm_box_pack_end(inner_box, gld->slx);
   evas_object_show(gld->slx);

   // Slider for Y-axis scale
   gld->sly = elm_slider_add(inner_box);
   evas_object_size_hint_align_set(gld->sly, EVAS_HINT_FILL, 0);
   elm_slider_horizontal_set(gld->sly, EINA_TRUE);
   elm_slider_unit_format_set(gld->sly, "%1.2f units");
   elm_slider_indicator_format_set(gld->sly, "%1.2f units");
   elm_slider_indicator_show_set(gld->sly, EINA_TRUE);
   elm_slider_min_max_set(gld->sly, 0, 1.5);
   elm_slider_value_set(gld->sly, 0.75);
   evas_object_color_set(gld->sly, 0.0, 0.0, 120, 255);
   elm_box_pack_end(inner_box, gld->sly);
   evas_object_show(gld->sly);

   // Slider for Z-axis scale
   gld->slz = elm_slider_add(inner_box);
   evas_object_size_hint_align_set(gld->slz, EVAS_HINT_FILL, 0);
   elm_slider_horizontal_set(gld->slz, EINA_TRUE);
   elm_slider_unit_format_set(gld->slz, "%1.2f units");
   elm_slider_indicator_format_set(gld->slz, "%1.2f units");
   elm_slider_indicator_show_set(gld->slz, EINA_TRUE);
   elm_slider_min_max_set(gld->slz, 0, 1.5);
   elm_slider_value_set(gld->slz, 0.75);
   evas_object_color_set(gld->slz, 0.0, 0.0, 120, 255);
   elm_box_pack_end(inner_box, gld->slz);
   evas_object_show(gld->slz);

   // Reset button
   btn_reset = elm_button_add(inner_box);
   elm_object_text_set(btn_reset, "Reset");
   evas_object_smart_callback_add(btn_reset, "clicked", btn_reset_cb, gld);
   evas_object_size_hint_align_set(btn_reset, EVAS_HINT_FILL, 0);
   elm_box_pack_end(inner_box, btn_reset);
   evas_object_show(btn_reset);

   evas_object_resize(inner_box, 100, 100);
   evas_object_move(inner_box, 0, 5);
   evas_object_resize(bx, 800, 800);
   evas_object_resize(win, 800, 800);
   evas_object_show(win);
   // run the mainloop and process events and callbacks
   elm_run();
   free(gld);
   elm_shutdown();
   return 0;
}
ELM_MAIN()

//
//  My_File.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "My_File.h"

G_DEFINE_TYPE(MyFile, my_file, G_TYPE_OBJECT)

#define MY_FILE_GET_PRIVATE(object) G_TYPE_INSTANCE_GET_PRIVATE((object), MY_TYPE_FILE, MyFilePrivate)

typedef struct _MyFilePrivate MyFilePrivate;
struct _MyFilePrivate {
    GString *name;
    GIOChannel *file;
};

enum PROPERTY_FILE {
    PROPERTY_FILE_0,
    PROPERTY_FILE_NAME,
};

static void my_file_dispose(GObject *object) {
    MyFile *self = MY_FILE(object);
    MyFilePrivate *priv = MY_FILE_GET_PRIVATE(self);
    if (priv->file) {
        g_io_channel_unref(priv->file);
        priv->file = NULL;
    }
    G_OBJECT_CLASS(my_file_parent_class)->dispose(object);
}

static void my_file_finalize(GObject *object) {
    MyFile *self = MY_FILE(object);
    MyFilePrivate *priv = MY_FILE_GET_PRIVATE(self);
    g_string_free(priv->name, TRUE);
    
    G_OBJECT_CLASS(my_file_parent_class)->finalize(object);
}

static void my_file_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
    MyFile *self = MY_FILE(object);
    MyFilePrivate *priv = MY_FILE_GET_PRIVATE(self);
    
    switch (property_id) {
        case PROPERTY_FILE_NAME:
            if (priv->name) {
                g_string_free(priv->name, TRUE);
            }
            priv->name = g_string_new(g_value_get_string(value));
            priv->file = g_io_channel_new_file(priv->name->str, "a+", NULL);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void my_file_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
    MyFile *self = MY_FILE(object);
    MyFilePrivate *priv = MY_FILE_GET_PRIVATE(self);
    
    switch (property_id) {
        case PROPERTY_FILE_NAME:
            g_value_set_string(value, priv->name->str);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void my_file_init(MyFile *self) {
    
}

static void my_file_class_init(MyFileClass *klass) {
    g_type_class_add_private(klass, sizeof(MyFilePrivate));
    
    GObjectClass *base_class = G_OBJECT_CLASS(klass);
    base_class->set_property = my_file_set_property;
    base_class->get_property = my_file_get_property;
    base_class->dispose = my_file_dispose;
    base_class->finalize = my_file_finalize;
    
    GParamSpec *pspec = g_param_spec_string("name", "Name", "File Name", NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT);
    g_object_class_install_property(base_class, PROPERTY_FILE_NAME, pspec);
    //系统会先调用g_strdelimit把"_"转化为"-"再存储signal_name 因此，在调用g_singal_emit_by_name时，detailed_signal参数中的分隔符必须是"-"
    /**
     我们来解释一下GSignalFlags中各个特征标志的含义：

     G_SIGNAL_RUN_FIRST:调用回调函数时，"per-object handler"对应的回调函数将第一个调用
     G_SIGNAL_RUN_LAST:调用回调函数时，"per-object handler"对应的回调函数将在用户用g_signal_connect连接的回调函数之后调用，并在用户用g_signal_connect_after连接的回调函数之前调用
     G_SIGNAL_RUN_CLEANUP:调用回调函数时，"per-object handler"对应的回调函数将最后一个调用
     G_SIGNAL_NO_RECURSE:信号发射时，如果信号的上次发射还没有结束，那么本次信号发射将不再进行，而只是使上次的信号发射重新开始。
     G_SIGNAL_DETAILED:信号名字可以使用"signal_name::detailed"的形式。
     G_SIGNAL_ACTION:程序员可以在代码中自由地调用g_signal_emit族的函数来发射信号，而不需要把g_signal_emit族的函数放在一段代码中再来调用。
     G_SIGNAL_NO_HOOKS:信号发射过程中不支持钩子函数。
     */
    
    /**
     GSignalCMarshaller c_marshaller:该参数是一个GSignalCMarshall类型的函数指针，其值反映了回调函数的返回值类型和额外参数类型（所谓“额外参数”，即指除回调函数中instance和user_data以外的参数）。
     例如，g_closure_marshal_VOID_VOID说明该signal的回调函数为以下的callback类型：

     typedef void (*callback)  (gpointer instance, gpointer user_data);

     而g_closure_marshal_VOID_POINTER则说明该signal的回调函数为以下的callback类型：

     typedef void (*callback)  (gpointer instance, gpointer arg1, gpointer user_data);

     如果默认提供的GClosureMarshall中没有你需要的，你可以用glib-genmarshall生成它，具体可参见devhelp中有关glib-genmarshall的说明。
     
     GType return_type:该参数的值应为回调函数的返回值在GType类型系统中的ID。
     guint n_params:该参数的值应为回调函数的额外参数的个数。
     ...:这一系列的参数的值应为回调函数的额外参数在GType类型系统中的ID，且这一系列参数中第一个参数的值为回调函数的第一个额外参数在GType类型系统中的ID，依次类推
     */
    g_signal_new("file_changed", MY_TYPE_FILE, G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}

void my_file_write(MyFile *self, gchar *buffer) {
    MyFilePrivate *priv = MY_FILE_GET_PRIVATE(self);
    g_io_channel_write_chars(priv->file, buffer, -1, NULL, NULL);
    g_io_channel_flush(priv->file, NULL);
    
    g_signal_emit_by_name(self, "file-changed");
}

//
//  main.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/13.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "My_File.h"
#include "signal-demo.h"

static void file_print(gpointer gobject, gpointer user_data) {
    g_print("invoking file_print\n");
}

static void file_print_xml(gpointer gobject, gpointer user_data) {
    g_print("invoking file_print_xml!\n");
}

static void file_print_tex(gpointer gobject, gpointer user_data) {
    g_print("invoking file_print_tex!\n");
}

int main_6() {
    MyFile *file = g_object_new(MY_TYPE_FILE, "name", "test.txt", NULL);
    
    g_signal_connect(file, "file-changed", G_CALLBACK(file_print), NULL);
    g_signal_connect(file, "file-changed", G_CALLBACK(file_print_xml), NULL);
    g_signal_connect(file, "file-changed", G_CALLBACK(file_print_tex), NULL);
    
    my_file_write(file, "hello world\n");
    g_object_unref(file);
    return 0;
}

//接收单个参数
static void
my_signal_handler (gpointer *instance, gchar *buffer, gpointer userdata)
{
    g_print ("my_signal_handler said: %s\n", buffer);
    if (userdata == NULL) {
        g_print ("my_signal_handler said: userdata == NULL");
    } else {
        g_print ("my_signal_handler said: %s\n", (gchar *)userdata);
    }
}

//接收多个参数
static void
my_signal_handler2 (gpointer instance, const gchar *buffer1 ,const gchar *buffer2 , gpointer userdata)
{
    g_print("my_signal_handler2 said buffer1: %s\n", buffer1);
    g_print("my_signal_handler2 said buffer2: %s\n", buffer2);
    g_print("my_signal_handler2 said userdata: %s\n", (char *)userdata);
//    g_print("Default handler said userdata: %s\n", buffer);
}

//信号accumulatr测试
static guint
my_signal_handler_accumulator (gpointer *instance, gchar *buffer, gpointer userdata)
{
    g_print ("my_signal_handler said: %s\n", buffer);
    if (userdata == NULL) {
        g_print ("my_signal_handler said: userdata == NULL");
    } else {
        g_print ("my_signal_handler said: %s\n", (gchar *)userdata);
    }
    return 1;
}

SignalDemo *sd_obj;
void signal_emit(guint signal_id,guint num, ...);

int main (void)
{
//    g_type_init ();
    gchar *userdata = "This is userdata";
    sd_obj = g_object_new (SIGNAL_TYPE_DEMO, NULL);
    /** 信号连接 */
    //方式1：
//    g_signal_connect (sd_obj, "hello",
//                      G_CALLBACK (my_signal_handler),
//                      userdata);
    
    //方式2：
//    g_signal_connect_closure_by_id(sd_obj,
//                                   g_signal_lookup("hello", G_OBJECT_TYPE(sd_obj)),
//                                   0,
//                                   g_cclosure_new(G_CALLBACK(my_signal_handler), userdata, NULL),
//                                   FALSE);
    
    /** 信号发射 */
    //方式1：
//    g_signal_emit_by_name (sd_obj,
//                           "hello",
//                           "This is the second param",
//                           G_TYPE_NONE);
    
    //方式2：
//    GSignalQuery query;
//    g_signal_query (g_signal_lookup ("hello", SIGNAL_TYPE_DEMO), &query);
//    signal_emit(query.signal_id,1, "hello www1");
//    signal_emit(query.signal_id,2, "hello www1", "hello www2");
    
    
    /** 使用信号accumulator */
//    gint val = 0;
//    /* 信号连接 */
//    g_signal_connect (sd_obj, "hello",
//                      G_CALLBACK (my_signal_handler),
//                      userdata);
//    /* 发射信号 */
//    g_signal_emit_by_name (sd_obj,
//                           "hello",
//                           "This is the second param", &val);
    /**
     [注]：
     g_signal_emit_by_name函数的调用多出一个无用的参数val。之所以说这个参数没有用，是因为在本文的示例中，
     我们使用了信号accumulator。如果我们没有使用信号accumulator的话，这个val参数可以保存最后一个信号闭包
     的返回值。虽然它在本文中没有用，但是他的存在是有意义的，可保证本文的示例不会出现段错误。
     */
    
    /* signal-name::detail形式测试 */
    GQuark quark = g_quark_from_string("test");
//    /* 信号连接*/
    g_signal_connect (sd_obj, "hello",
                      G_CALLBACK (my_signal_handler),
                      userdata);
    g_signal_connect_closure_by_id(sd_obj,
                                   g_signal_lookup("hello", G_OBJECT_TYPE(sd_obj)),
                                   quark,
                                   g_cclosure_new(G_CALLBACK(my_signal_handler), userdata, NULL), FALSE);
//
//    g_signal_emit_by_name(sd_obj, "hello::test", "this is detail signal test");
//    g_signal_emit_by_name(sd_obj, "hello", "this is detail signal test");
    //使用g_signal_emitv发送信号
    GValue instance = G_VALUE_INIT;
    g_value_init(&instance, SIGNAL_TYPE_DEMO);
    g_value_set_instance(&instance, sd_obj);
    
    GValue parm = G_VALUE_INIT;
    g_value_init(&parm, G_TYPE_STRING);
    g_assert(G_VALUE_HOLDS_STRING(&parm));
    g_value_set_string(&parm, "g_signal_emitv");
    GValue value[] = {instance, parm};
    guint signal_id = g_signal_lookup("hello", signal_demo_get_type());
    GValue ret = G_VALUE_INIT;
    g_signal_emitv(value, signal_id, quark, &ret);
    /**
     [注]:
     使用detail信号会输出2次
     g_signal_emitv(value, signal_id, quark, &ret); 如下：
     my_signal_handler said: g_signal_emitv
     my_signal_handler said: This is userdata
     my_signal_handler said: g_signal_emitv
     my_signal_handler said: This is userdata
     
     g_signal_emitv(value, signal_id, 0, &ret);只调用一次，如下：
     my_signal_handler said: g_signal_emitv
     my_signal_handler said: This is userdata
     */
    
    
    
    /** 错误尝试 */
    //参数接收va_list
//    guint signal_id = g_signal_lookup("hello", signal_demo_get_type());
//    g_signal_emit_valist(sd_obj, signal_id, 0, "hello www",...);
    
    //使用g_signal_emitv发送信号
//    GValue instance_and_params[3] = {{0},{0},{0}};
//    GValue instance_and_params = {0};
//    GValue receiving_success_val = {0,};
//    gboolean receiving_success = 0;
//
//    g_value_init(&receiving_success_val, G_TYPE_BOOLEAN);
//    g_value_set_boolean(&receiving_success_val, TRUE);
//
//
//    receiving_success = G_TYPE_IS_VALUE(SIGNAL_TYPE_DEMO);
//    receiving_success = g_type_check_is_value_type(SIGNAL_TYPE_DEMO);
//    memset(&instance_and_params,0,sizeof(instance_and_params));
//    g_value_init(&instance_and_params, SIGNAL_TYPE_DEMO);
//    g_value_set_object(&instance_and_params, sd_obj);
//    receiving_success = G_TYPE_IS_VALUE(SIGNAL_TYPE_DEMO);

//    g_signal_emitv(&instance_and_params, signal_id, 0, &receiving_success_val);
//    receiving_success = g_value_get_boolean (&receiving_success_val);
//
//    g_value_unset (&instance_and_params);
//    g_debug ("Request to start receiving %s", receiving_success ? "succeeded" : "failed");
    
    
    return 0;
}

void signal_emit(guint signal_id, guint num,...) {
    va_list va;
    va_start(va, num);
//    printf("zz %s\n", va_arg(va, char *));
    //va_arg会将可变参数从va中取出，之后就不会传递取出的那个参数了
    /*printf未注释打印结果
     zz hello www
     Default handler said buffer:
     my_signal_handler said:
     my_signal_handler said: This is userdata
     
     注释后的打印结果
     Default handler said buffer: hello www
     my_signal_handler said: hello www
     my_signal_handler said: This is userdata
     */
    va_end(va);
    g_signal_emit_valist(sd_obj, signal_id, 0, va);
}


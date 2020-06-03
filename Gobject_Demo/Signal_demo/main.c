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

static void
my_signal_handler (gpointer *instance, gchar *buffer, gpointer userdata)
{
    g_print ("my_signal_handler said: %s\n", buffer);
    g_print ("my_signal_handler said: %s\n", (gchar *)userdata);
}

int main (void)
{
    gchar *userdata = "This is userdata";
    SignalDemo *sd_obj = g_object_new (SIGNAL_TYPE_DEMO, NULL);
    /* 信号连接*/
    g_signal_connect (sd_obj, "hello",
                      G_CALLBACK (my_signal_handler),
                      userdata);
    /* 发射信号 */
    g_signal_emit_by_name (sd_obj,
                           "hello",
                           "This is the second param",
                           G_TYPE_NONE);
    return 0;
}


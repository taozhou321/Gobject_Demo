//
//  main.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/13.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "My_File.h"

static void file_print(gpointer gobject, gpointer user_data) {
    g_print("invoking file_print\n");
}

static void file_print_xml(gpointer gobject, gpointer user_data) {
    g_print("invoking file_print_xml!\n");
}

static void file_print_tex(gpointer gobject, gpointer user_data) {
    g_print("invoking file_print_tex!\n");
}

int main() {
    MyFile *file = g_object_new(MY_TYPE_FILE, "name", "test.txt", NULL);
    
    g_signal_connect(file, "file-changed", G_CALLBACK(file_print), NULL);
    g_signal_connect(file, "file-changed", G_CALLBACK(file_print_xml), NULL);
    g_signal_connect(file, "file-changed", G_CALLBACK(file_print_tex), NULL);
    
    my_file_write(file, "hello world\n");
    g_object_unref(file);
    return 0;
}

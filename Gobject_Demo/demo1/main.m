////
////  main.m
////  Gstreamer_Demo2
////  <#Description#>
////  Created by zhoutao on 2019/12/10.
////  Copyright © 2019 zhoutao. All rights reserved.
////
//
//#include <gst/gst.h>
//
//int main (int argc, char *argv[])
//{
//  GstElement *pipeline;
//  GstBus *bus;
//  GstMessage *msg;
//
//  /* Initialize GStreamer */
//  gst_init (&argc, &argv);
//  gboolean result =  gst_update_registry();
//    GError *error = NULL;//g_error_new(12, 22, "test error");
//  /* Build the pipeline */
////  pipeline = gst_parse_launch ("playbin uri=file:///Users/xtkj20190315/Downloads/ttttt.mp4", &error);
//    pipeline = gst_parse_launch ("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);
//
//  /* Start playing */
//  gst_element_set_state (pipeline, GST_STATE_PLAYING);
//
//  /* Wait until error or EOS */
//  bus = gst_element_get_bus (pipeline);
//  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
//      GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
//
//  /* Free resources */
////  if (msg != NULL)
////  gst_message_unref (msg);
////  gst_object_unref (bus);
////  gst_element_set_state (pipeline, GST_STATE_NULL);
////  gst_object_unref (pipeline);
//  return 0;
//}


//#include <gst/gst.h>
//
//int main (int argc, char *argv[])
//{
//  GstElement *pipeline, *source, *filter, *sink;
//  GstBus *bus;
//  GstMessage *msg;
//  GstStateChangeReturn ret;
//
//  /* Initialize GStreamer */
//  gst_init (&argc, &argv);
//
//  /* Create the elements */
//  source = gst_element_factory_make ("videotestsrc", "source");
//  filter = gst_element_factory_make ("timeoverlay", "filter");
//  sink = gst_element_factory_make ("autovideosink", "sink");
//
//  /* Create the empty pipeline */
//  pipeline = gst_pipeline_new ("test-pipeline");
//
//  if (!pipeline || !source || !filter || !sink) {
//    g_printerr ("Not all elements could be created.\n");
//    return -1;
//  }
//
//  /* Build the pipeline */
//  gst_bin_add_many (GST_BIN (pipeline), source, filter, sink, NULL);
//  if (gst_element_link_many (source, filter, sink, NULL) != TRUE) {
//    g_printerr ("Elements could not be linked.\n");
//    gst_object_unref (pipeline);
//    return -1;
//  }
//
//  /* Modify the source's properties */
//  g_object_set (source, "pattern", 0, NULL);
//
//  /* Start playing */
//  ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
//  if (ret == GST_STATE_CHANGE_FAILURE) {
//    g_printerr ("Unable to set the pipeline to the playing state.\n");
//    gst_object_unref (pipeline);
//    return -1;
//  }
//
//  /* Wait until error or EOS */
//  bus = gst_element_get_bus (pipeline);
//  msg =
//      gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
//      GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
//
//  /* Parse message */
//  if (msg != NULL) {
//    GError *err;
//    gchar *debug_info;
//
//    switch (GST_MESSAGE_TYPE (msg)) {
//      case GST_MESSAGE_ERROR:
//        gst_message_parse_error (msg, &err, &debug_info);
//        g_printerr ("Error received from element %s: %s\n",
//            GST_OBJECT_NAME (msg->src), err->message);
//        g_printerr ("Debugging information: %s\n",
//            debug_info ? debug_info : "none");
//        g_clear_error (&err);
//        g_free (debug_info);
//        break;
//      case GST_MESSAGE_EOS:
//        g_print ("End-Of-Stream reached.\n");
//        break;
//      default:
////         We should not reach here because we only asked for ERRORs and EOS
//        g_printerr ("Unexpected message received.\n");
//        break;
//    }
//    gst_message_unref (msg);
//  }
//
//  /* Free resources */
//  gst_object_unref (bus);
//  gst_element_set_state (pipeline, GST_STATE_NULL);
//  gst_object_unref (pipeline);
//  return 0;
//}


#include "Gobject_demo1.h"

void gValue_test();

int main_1() {
//    g_type_init();
//    int i;
//
//    PMDList *list;
//    for (i = 0; i < 3; i++) {
//        list = g_object_new(PM_TYPE_DLIST, NULL);
//        g_object_unref(list);
//    }
//
//    list = g_object_new (PM_TYPE_DLIST, NULL);
//    if (G_IS_OBJECT (list)) {
//        g_print ("\t this is a GObject！\n");
//    }
    
//    PMDList *list;
//    /*实例化PMDList类对象，参数可变，第一个是类型，最后一个是NULL；中间参数成对出现，一对参数中，第一个参数是变量名称，第二个变量是变量内容。*/
//    list = g_object_new (PM_TYPE_DLIST,
//                         "head", NULL,
//                         "tail", NULL,
//                         NULL);
//    /*可以通过g_object_get_property 或g_object_set_property 获取和设置属性*/
//    GValue val = {0};
//    GValue val2 = {0};
//    g_value_init (&val,G_TYPE_POINTER);
//    g_value_init(&val2, G_TYPE_POINTER);
////    g_object_get_property (G_OBJECT(list), "tail", &val);
//    g_object_set_property (G_OBJECT(list), "head", &val);
//
//    GValue val1;
//    g_object_get_property (G_OBJECT(list), "head", &val2);
////    g_print(<#const gchar *format, ...#>)
//    g_value_unset (&val);
//    g_value_unset(&val1);
//    /*也可以通过g_object_set 和 g_object_get 设置和获取属性，方法类似g_object_new*/
//    g_object_unref (list);
    
    gValue_test();
    
    return 0;
}


void gValue_test() {
    //GValue必须初始化后才能使用
    GValue a = G_VALUE_INIT;
    GValue b = G_VALUE_INIT;
    const gchar *message;
    
    g_assert(!G_VALUE_HOLDS_STRING(&a));
    
    g_value_init(&a, G_TYPE_STRING);
    g_assert(G_VALUE_HOLDS_STRING(&a));
    g_value_set_static_string(&a, "Hello, world!");
    g_print("%s\n", g_value_get_string(&a));
    
    //Clears the current value in value (if any) and "unsets" the type, this releases all resources associated with this GValue. An unset value is the same as an uninitialized (zero-filled) GValue structure.
    g_value_unset(&a);
    
    g_value_init(&a, G_TYPE_INT);
    g_value_set_int(&a, 42);
    
    g_value_init(&b, G_TYPE_STRING);
    
    g_assert(g_value_type_transformable(G_TYPE_INT, G_TYPE_STRING));
    
    g_value_transform(&a, &b);
    g_print("%s\n", g_value_get_string(&b));
    
    
}

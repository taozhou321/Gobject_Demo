//
//  signaldemo.h
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/6/3.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef signal_demo_h
#define signal_demo_h

#include <glib-object.h>

#define SIGNAL_TYPE_DEMO (signal_demo_get_type ())
#define SIGNAL_DEMO(object) \
    G_TYPE_CHECK_INSTANCE_CAST ((object), SIGNAL_TYPE_DEMO, SignalDemo)
#define SIGNAL_IS_DEMO(object) \
    G_TYPE_CHECK_INSTANCE_TYPE ((object), SIGNAL_TYPE_DEMO))
#define SIGNAL_DEMO_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_CAST ((klass), SIGNAL_TYPE_DEMO, SignalDemoClass))
#define SIGNAL_IS_DEMO_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE ((klass), SIGNAL_TYPE_DEMO))
#define SIGNAL_DEMO_GET_CLASS(object) (\
    G_TYPE_INSTANCE_GET_CLASS ((object), SIGNAL_TYPE_DEMO, SignalDemoClass))

typedef struct _SignalDemo SignalDemo;
struct _SignalDemo {
    GObject parent;
};

typedef struct _SignalDemoClass SignalDemoClass;
struct _SignalDemoClass {
GObjectClass parent_class;
    //单个参数
    void (*default_handler) (gpointer instance, const gchar *buffer, gpointer userdata);
    //多个参数
    void (*default_handler2) (gpointer instance, const gchar *buffer1, const gchar *buffer2, gpointer userdata);
    //accumulator测试回调
    guint (*default_accumulator_handler) (gpointer instance, const gchar *buffer, gpointer userdata);
};
GType signal_demo_get_type (void);

#endif /* signaldemo_h */

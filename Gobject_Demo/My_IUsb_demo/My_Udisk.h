//
//  My_Udisk.h
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef My_Udisk_h
#define My_Udisk_h

#include "MyIUSb.h"

#define MY_TYPE_UDISK (my_udisk_get_type())
#define MY_UDISK(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_UDISK, MyUdisk))
#define MY_IS_UDISK(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_UDISK))
#define MY_UDISK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), MY_TYPE_UDISK, MyUdiskClass))
#define My_IS_UDISK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), MY_TYPE_UDISK))
#define MY_UDISK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), MY_TYPE_UDISK, MyUdiskClass))

typedef struct _MyUdisk MyUdisk;
struct _MyUdisk {
    GObject parent;
    GString *data;
};

typedef struct _MyUdiskClass MyUdiskClass;
struct _MyUdiskClass {
    GObjectClass parent_class;
};

GType my_udisk_get_type(void);

#endif /* My_Udisk_h */

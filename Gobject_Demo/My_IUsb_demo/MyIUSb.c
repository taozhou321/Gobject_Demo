//
//  MyIUSb.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "MyIUSb.h"

G_DEFINE_INTERFACE(MyIUsb, my_iusb, G_TYPE_INVALID);
//G_DEFINE_TYPE(MyIUsb, my_iusb, G_)

/** my_iusb_default_init 是 G_DEFINE_INTERFACE 宏的展开代码中声明的一个函数，其中可以放置接口的一些初始化代码。如果没有这方面的需求，
 就让它表现为一个空函数即可，否则编译器会警告你，说你有一个函数声明了但没有实现。 */
static void my_iusb_default_init(MyIUsbInterface *iface) {
    
}

gchar * my_iusb_read(MyIUsb *self) {
    g_return_val_if_fail(MY_IS_IUSB(self), "self is not MyIUsb class");
    return MY_IUSB_GET_INTERFACE(self)->read(self);
}

void my_iusb_write(MyIUsb *self, const gchar *str) {
    g_return_if_fail(MY_IS_IUSB(self));
    MY_IUSB_GET_INTERFACE(self)->write(self, str);
}

//
//  My_Udisk.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "My_Udisk.h"

/**
 my_iusb_interface_init 函数声明必须要放在 G_DEFINE_TYPE_WITH_CODE 宏之前，因为这个宏的展开代码中需要使用这个函数；
 G_DEFINE_TYPE_WITH_CODE 是文档 [2-5] 中出现过的 G_DEFINE_TYPE 宏的“扩展版本”，在本例中可以向 my_udisk_get_type 函数（即 MY_TYPE_UDISK 宏展开的那个函数）中插入 C 代码。在本例中，这个宏所插入的 C 代码是“G_IMPLEMENT_INTERFACE(MY_TYPE_IUSB,my_iusb_interface_init)”，其中 G_IMPLEMENT_INTERFACE 宏的作用是将接口添加到  MyUdisk 类中；
 my_iusb_interface_init 函数的作用是表明 MyUdisk 类实现了 MyIUsb 所规定的接口。
*/
static void my_iusb_interface_init(MyIUsbInterface *iface);

G_DEFINE_TYPE_WITH_CODE(MyUdisk, my_udisk, G_TYPE_OBJECT, G_IMPLEMENT_INTERFACE(MY_TYPE_IUSB, my_iusb_interface_init));

static gchar * my_udisk_read(MyIUsb *iusb) {
    MyUdisk *udisk = MY_UDISK(iusb);
    return udisk->data->str;
}

static void my_udisk_write(MyIUsb *iusb, const gchar *str) {
    MyUdisk *udisk = MY_UDISK(iusb);
    g_string_assign(udisk->data, str);
}

static void my_udisk_init(MyUdisk *self) {
    self->data = g_string_new(NULL);
}

static void my_udisk_class_init(MyUdiskClass *self) {
    
}

static void my_iusb_interface_init(MyIUsbInterface *iface) {
    ///!!!:这里设置了接口指针指向的函数所以能调用my_udisk_read
    iface->read = my_udisk_read;
    iface->write = my_udisk_write;
}

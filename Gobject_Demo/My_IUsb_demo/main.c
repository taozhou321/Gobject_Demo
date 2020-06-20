//
//  main.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "My_Udisk.h"

int main_4() {
    MyUdisk *udisk = g_object_new(MY_TYPE_UDISK, NULL);
    
    my_iusb_write(MY_IUSB(udisk), "i am a u-disk");
    gchar *data = my_iusb_read(MY_IUSB(udisk));
    
    g_print("%s\n",data);
        
    g_print("Is udisk a MyIUsb object?\n");
    if (MY_IS_IUSB(udisk)) {
        g_print("YES\n");
    } else {
        g_print("NO\n");
    }
    
    g_print ("\nIs udisk a MyUdisk object?\n");
    if(MY_IS_UDISK(udisk)) {
        g_print ("Yes!\n");
    } else {
        g_print ("No!\n");
    }
    
    return 0;
}


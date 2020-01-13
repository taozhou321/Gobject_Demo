//
//  MyIUSb.h
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef MyIUSb_h
#define MyIUSb_h

#include <glib-object.h>
/*
写之前需要确定的三个名称如下(其中I表示接口)：
类名称：MyIUsb;对应的接口类(结构类)MyIUserInterface(MyIUserClass)
类型：MY_TYPE_IUSE(一般定义取类名的大写，中间加TYPE组合)
函数前缀：my_iuse(一般定义取类名的小写，中间加下划线组合)
*/

#define MY_TYPE_IUSB (my_iusb_get_type())
#define MY_IUSB(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_IUSB, MyIUsb))
#define MY_IS_IUSB(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_IUSB))
/** MY_IUSB_GET_INTERFACE 宏，用于从 MyIUsb 接口的实例结构体中取出类结构体指针，
 然后利用该指针访问接口对应的方法。至于 MyIUsb 接口的实例结构体是怎样与类结构体指针取得关联的，那是 GObject 的内幕，暂且不必关心。 */
#define MY_IUSB_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE((obj), MY_TYPE_IUSB, MyIUsbInterface))

typedef struct _MyIUsb MyIUsb;

typedef struct _MyIUsbInterface MyIUsbInterface;
struct _MyIUsbInterface {
    GTypeInterface parent_interface;
    
    //接口
    gchar* (*read)(MyIUsb *self);
    void (*write)(MyIUsb *self, const gchar *str);
};

GType my_iusb_get_type(void);
//接口定义
gchar* my_iusb_read(MyIUsb *self);
void my_iusb_write(MyIUsb *self, const gchar *str);

#endif /* MyIUSb_h */

/**
 [注]：
 对于 GObject 的子类化，那么在声明类的时候，在头文件中直接插入类似下面的一组宏定义：
 其中P表示项目名称，T表示类名称，PTPrivate表示私有数据结构体。
 #define P_TYPE_T (p_t_get_type ())
 #define P_T(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), P_TYPE_T, PT))
 #define P_IS_T(obj) G_TYPE_CHECK_INSTANCE_TYPE ((obj), P_TYPE_T))
 #define P_T_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), P_TYPE_T, PTClass))
 #define P_IS_T_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), P_TYPE_T))
 #define P_T_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), P_TYPE_T, PTClass))

 这些宏的用法总结如下：
 P_TYPE_T：仅在使用 g_object_new 进行对象实例化的时候使用一次，用于向 GObject 库的类型系统注册 PT 类；
 P_T (obj)：用于将 obj 对象的类型强制转换为 P_T 类的实例结构体类型；
 P_IS_T (obj)：用于判断 obj 对象的类型是否为 P_T 类的实例结构体类型；
 P_T_CLASS(klass)：用于将 klass 类结构体的类型强制转换为 P_T 类的类结构体类型；
 P_IS_T_CLASS(klass)：用于判断 klass 类结构体的类型是否为 P_T 类的类结构体类型；
 P_T_GET_CLASS(obj)：获取 obj 对象对应的类结构体类型。
 
 */

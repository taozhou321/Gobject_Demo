//
//  Gobject_demo1.h
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2019/12/26.
//  Copyright © 2019 zhoutao. All rights reserved.
//

#ifndef Gobject_demo1_h
#define Gobject_demo1_h
/**
 GObject子类化
 在 .h 文件中包含 glib-object.h；
 在 .h 文件中构建实例结构体与类结构体，并分别将 GObject 类的实例结构体与类结构体置于成员之首；
 在 .h 文件中定义 P_TYPE_T 宏，并声明 p_t_get_type 函数；
 在 .c 文件中调用 G_DEFINE_TYPE 宏产生类型注册代码。
 */
#include <glib-object.h>
/*定义子类类型，其中pm_dist字段是用户可以修改的内容，表示这个类的用途，
 后续所有的函数都必须以pm_dist开头，pm_dlist_get_type ()函数在下边定义*/
#define PM_TYPE_DLIST (pm_dlist_get_type ())

/*定义强制转换宏，可以将基类GObject转换为本子类*/
#define PM_DLIST(object) G_TYPE_CHECK_INSTANCE_CAST((object), PM_TYPE_DLIST, PMDList)

/*普通结构体，作为实例结构体的成员*/
typedef struct _PMDListNode PMDListNode;
struct _PMDListNode {
    PMDListNode *prev;
    PMDListNode *next;
    void *data;
};

/*实例结构体,类似于C++中实例化时，每个实例独有的内容，比如成员函数，成员变量等*/
typedef struct _PMDList PMDList;
struct _PMDList {
    GObject parent_instance;
};

/*类结构体,类似于C++中,属于类的部分，比如：static成员函数和static成员变量等*/
typedef struct _PMDListClass PMDListClass;
struct _PMDListClass {
    GObjectClass parent_class;
};


/*
 privae,定义获取类型函数,供PM_TYPE_DLIST调用，不建议直接调用
 向GObject库提供的类型管理系统提供要注册的PT类类型相关信息
 *****************************************
 因为 p_t_get_type 函数是 g_object_new 函数的参数，当我们首次调用 g_object_new
 函数进行对象实例化时，p_t_get_type 函数便会被 g_object_new 函数调用，从而引发 GObject
 库的类型管理系统去接受 PT 类类型（例如 PMDList 类型）的申请并为其分配一个类型标识码作为 p_t_get_type
 函数的返回值。当 g_object_new 函数从 p_t_get_type 函数那里获取 PT
 类类型标识码之后，便可以进行对象实例的内存分配及属性的初始化
 *****************************************
 */
GType pm_dlist_get_type(void);
#endif /* Gobject_demo1_h */

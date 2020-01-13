//
//  Gobject_demo1.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2019/12/26.
//  Copyright © 2019 zhoutao. All rights reserved.
//

#include "Gobject_demo1.h"
/**
 此宏有三个功能：
 1，函数GType pm_dlist_get_type (void)的实现，GObject帮我们具体实现
 2，注册函数前缀pm_dlist到GObject
 3，注册实例结构体名称PMDList到GObject
 通过此宏的调用，GObject知道了我们的三个信息：类型，类名称，函数前缀
 */
G_DEFINE_TYPE(PMDList, pm_dlist, G_TYPE_OBJECT);
/**
 G_DEFINE_TYPE展开如下：
 #define G_DEFINE_TYPE(TN, t_n, T_P)
  其中
  *TN  ---> TypeName
  *t_n ---> type_name
  *T_P ---> TYPE_PARENT
  *_f_ ---> 0
  *_c_ ---> {}
 
 以下为宏展开
 static void     type_name##_init              (TypeName        *self);
 static void     type_name##_class_init        (TypeName##Class *klass);
 static gpointer type_name##_parent_class = NULL;
 static gint     TypeName##_private_offset;

 static void     type_name##_class_intern_init (gpointer klass)
 {
   type_name##_parent_class = g_type_class_peek_parent (klass);
   if (TypeName##_private_offset != 0)
     g_type_class_adjust_private_offset (klass, &TypeName##_private_offset);
   type_name##_class_init ((TypeName##Class*) klass);
 }

 static inline gpointer
 type_name##_get_instance_private (TypeName *self)
 {
   return (G_STRUCT_MEMBER_P (self, TypeName##_private_offset));
 }

 GType
 type_name##_get_type (void)
 */

#define PM_DLIST_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), PM_TYPE_DLIST, PMDListPrivate))

/*普通结构体，作为实例结构体的私有成员*/
typedef struct _PMDListPrivate PMDListPrivate;
struct _PMDListPrivate {
    PMDListNode *head;
    PMDListNode *tail;
};

/** 属性对应的ID，真正属性ID不能为0，所以PROPERTY_DLIST_0是为了占位 */
enum PropertyList {
    PROPERTY_DLIST_0,
    PROPERTY_DLIST_HEAD,
    PROPERTY_DLIST_HEAD_PREV,
    PROPERTY_DLIST_HEAD_NEXT,
    PROPERTY_DLIST_TAIL,
    PROPERTY_DLIST_TAIL_PREV,
    PROPERTY_DLIST_TAIL_NEXT
};

/** set属性实现 */
static void pm_dlist_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pSpec) {
    PMDList *self = PM_DLIST(object);
    PMDListPrivate *priv = PM_DLIST_GET_PRIVATE(self);
    
    switch (property_id) {
        case PROPERTY_DLIST_HEAD:
            priv->head = g_value_get_pointer(value);
            break;
        case PROPERTY_DLIST_HEAD_PREV:
            priv->head->prev = g_value_get_pointer(value);
            break;
        case PROPERTY_DLIST_HEAD_NEXT:
            priv->head->next = g_value_get_pointer(value);
            break;
        case PROPERTY_DLIST_TAIL:
            priv->tail = g_value_get_pointer (value);
            break;
        case PROPERTY_DLIST_TAIL_PREV:
            priv->tail->prev = g_value_get_pointer (value);
            break;
        case PROPERTY_DLIST_TAIL_NEXT:
            priv->tail->next = g_value_get_pointer (value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pSpec);
            break;
    }
}

/** get属性实现 */
static void pm_dlist_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pSpec) {
    PMDList *self = PM_DLIST(object);
    PMDListPrivate *priv = PM_DLIST_GET_PRIVATE(self);
    
    switch (property_id) {
        case PROPERTY_DLIST_HEAD:
            g_value_set_pointer (value, priv->head);
            break;
        case PROPERTY_DLIST_HEAD_PREV:
            g_value_set_pointer (value, priv->head->prev);
            break;
        case PROPERTY_DLIST_HEAD_NEXT:
            g_value_set_pointer (value, priv->head->next);
            break;
        case PROPERTY_DLIST_TAIL:
            g_value_set_pointer (value, priv->tail);
            break;
        case PROPERTY_DLIST_TAIL_PREV:
            g_value_set_pointer (value, priv->tail->prev);
            break;
        case PROPERTY_DLIST_TAIL_NEXT:
            g_value_set_pointer (value, priv->tail->next);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pSpec);
            break;
    }
}

/** 实例结构体的实例化，类似于C++中的构造函数 */
static void pm_dlist_init(PMDList *self) {
//    g_print("\t实例结构体初始化！\n");
//    g_printerr("\t instance init！\n");
    
//    PMDListPrivate *priv = PM_DLIST_GET_PRIVATE (self);
//    priv->head = NULL;
//    priv->tail = NULL;
}

/**
    类结构提的初始化，类似于C++中的static变量的初始化，
    此函数只会在第一次类实例化的时候调用，后续类实例化不再调用
 */
static void pm_dlist_class_init(PMDListClass *kClass) {
//    g_print("类结构体初始化!\n");
//    g_printerr("class init !\n");
    g_type_class_add_private(kClass, sizeof(PMDListPrivate));
    
    GObjectClass *base_class = G_OBJECT_CLASS(kClass);
    base_class->set_property = pm_dlist_set_property;
    base_class->get_property = pm_dlist_get_property;
    
    GParamSpec *pSpec;
    pSpec = g_param_spec_pointer("head", "Head node", "The head node of the double list", G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT);
    g_object_class_install_property(base_class, PROPERTY_DLIST_HEAD, pSpec);
    pSpec = g_param_spec_pointer("head-prev", "The previous node of the head node", "The previos node of the head node of the double list", G_PARAM_READABLE | G_PARAM_WRITABLE );
    g_object_class_install_property(base_class, PROPERTY_DLIST_HEAD_PREV, pSpec);
    pSpec = g_param_spec_pointer("head-next", "The next node of the head node", "The next node of the head node of the double list", G_PARAM_READABLE | G_PARAM_WRITABLE );
    g_object_class_install_property(base_class, PROPERTY_DLIST_HEAD_NEXT, pSpec);
    
    pSpec = g_param_spec_pointer("tail", "tail node", "The tail node of the double list", G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_CONSTRUCT);
    g_object_class_install_property(base_class, PROPERTY_DLIST_TAIL, pSpec);
    pSpec = g_param_spec_pointer("tail-prev", "The previous node of the tail node", "The previos node of the tail node of the double list", G_PARAM_READABLE | G_PARAM_WRITABLE );
    g_object_class_install_property(base_class, PROPERTY_DLIST_TAIL_PREV, pSpec);
    pSpec = g_param_spec_pointer("tail-next", "The next node of the tail node", "The next node of the tail node of the double list", G_PARAM_READABLE | G_PARAM_WRITABLE );
    g_object_class_install_property(base_class, PROPERTY_DLIST_TAIL_NEXT, pSpec);
    
    
}

/**
 PM_DLIST (object) 宏的作用是将一个基类指针类型转换为 PMDList 类的指针类型，它需要 GObject 子类的设计者提供，我们可以将其定义为：
 #define PM_DLIST(object) \
         G_TYPE_CHECK_INSTANCE_CAST ((object), PM_TYPE_DLIST, PMDList))
 PROPERTY_DLIST_XXXX 宏，可以采用枚举类型实现。
 GValue 类型是一个变量容器，可用于存放各种变量的值，例如整型数、指针、GObject 子类等等，上述代码主要用 GValue 存放指针变量的值。
 GParamSpec 类型是比 GValue 高级一点的变量容器，它不仅可以存放各种变量的值，还能为这些值命名，因此它比较适合用于表示 g_object_new 函数的“属性名-属性值”结构。不过，在上述代码中，GParamSpec 类型只是昙花一现，没关系，反正下文它还会出现。
 
 */

//
//  ZTIAnimalInterface.h
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/4/30.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef ZTIAnimalInterface_h
#define ZTIAnimalInterface_h

#include <glib-object.h>

//仅在接口实现时使用一次，用于向 GObject 库的类型系统注册 PIT 接口；
//#define P_TYPE_IT (p_t_get_type ())
#define ZT_TYPE_IANIMAL (zt_ianimal_get_type())
//用于将 obj 对象的类型强制转换为 P_IT 接口的实例结构体类型；
//#define P_IT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), P_TYPE_IT, PIT))
#define ZT_IANIMAL(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), ZT_TYPE_IANIMAL, ZTIAnimal))
//用于判断 obj 对象的类型是否为 P_IT 接口的实例结构体类型；
//#define P_IS_IT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), P_TYPE_IT))
#define ZT_IS_IANIMAL(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZT_TYPE_IANIMAL))
//获取 obj 对象对应的 P_IT 接口的类结构体类型。
//#define P_IT_GET_INTERFACE(obj) \
(G_TYPE_INSTANCE_GET_INTERFACE ((obj), P_TYPE_IT, PItInterface))
#define ZT_IANIMAL_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE((obj), ZT_TYPE_IANIMAL, ZTIAnimalInterface))

//接口的实例结构体，它只是个名字，并没有具体实现。
typedef struct _ZTIAnimal ZTIAnimal;
//接口的类结构体
typedef struct _ZTIAnimalInterface ZTIAnimalInterface;
struct _ZTIAnimalInterface {
    GTypeInterface parent_interface;
        
    void (*run)(ZTIAnimal *self);
};

GType zt_ianimal_get_type(void);

void zt_ianimal_run(ZTIAnimal *self);
#endif /* ZTIAnimalInterface_h */

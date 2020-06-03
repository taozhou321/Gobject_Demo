//
//  zt_animal.h
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/4/30.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef zt_animal_h
#define zt_animal_h

#include <glib-object.h>
//仅在使用 g_object_new 进行对象实例化的时候使用一次，用于向 GObject 库的类型系统注册 PT 类；
//#define P_TYPE_T (p_t_get_type ())
#define ZT_TYPE_ANIMAL (zt_animal_get_type())
//用于将 obj 对象的类型强制转换为 P_T 类的实例结构体类型；
//#define P_T(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), P_TYPE_T, PT))
#define ZT_ANIMAL(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), ZT_TYPE_ANIMAL, ZTAnimal))
//用于判断 obj 对象的类型是否为 P_T 类的实例结构体类型；
//#define P_IS_T(obj) G_TYPE_CHECK_INSTANCE_TYPE ((obj), P_TYPE_T))
#define ZT_IS_ANIMAL(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZT_TYPE_ANIMAL))
//用于将 klass 类结构体的类型强制转换为 P_T 类的类结构体类型；
//#define P_T_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), P_TYPE_T, PTClass))
#define ZT_ANIMAL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), ZT_TYPE_ANIMAL, ZTAnimalClass))
//用于判断 klass 类结构体的类型是否为 P_T 类的类结构体类型；
//#define P_IS_T_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), P_TYPE_T))
#define ZT_IS_ANIMAL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), ZT_TYPE_ANIMAL))
//获取 obj 对象对应的类结构体类型。
//#define P_T_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), P_TYPE_T, PTClass))
#define ZT_ANIMAL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), ZT_TYPE_ANIMAL, ZTAnimalClass))

typedef struct _ZTAnimalPrivate ZTAnimalPrivate;

typedef struct _ZTAnimal ZTAnimal;
struct _ZTAnimal {
    GObject parent_instance;
    
    ZTAnimalPrivate *priv;
};

typedef struct _ZTAnimalClass ZTAnimalClass;
struct _ZTAnimalClass {
    GObjectClass parent_class;
};

GType zt_animal_get_type(void);

ZTAnimal* zt_animal_new (const gchar *species);
gchar* zt_animal_get_species(ZTAnimal *animal);


#endif /* zt_animal_h */

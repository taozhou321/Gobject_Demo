//
//  zt_cat.h
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/4/30.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef zt_cat_h
#define zt_cat_h

#include "zt_animal.h"

#define ZT_TYPE_CAT (zt_cat_get_type())
#define ZT_CAT(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), ZT_TYPE_CAT, ZTCat));
#define ZT_IS_CAT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), ZT_TYPE_CAT));
#define ZT_CAT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((obj), ZT_TYPE_CAT, ZTCat));
#define ZT_IS_CAT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((obj), ZT_TYPE_CAT));
#define ZT_CAT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), ZT_TYPE_CAT, ZTCatClass));

typedef struct _ZTCat ZTCat;
struct _ZTCat {
    ZTAnimal parent_instance;
};

typedef struct _ZTCatClass ZTCatClass;
struct _ZTCatClass {
    ZTAnimalClass parent_class;
};

GType zt_cat_get_type(void);
#endif /* zt_cat_h */

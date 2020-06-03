//
//  ZTIAnimalInterface.c
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/4/30.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "ZTIAnimalInterface.h"

G_DEFINE_INTERFACE(ZTIAnimal, zt_ianimal, G_TYPE_INVALID);

static void
zt_ianimal_default_init(ZTIAnimalInterface *iface) {
    
}

void
zt_ianimal_run(ZTIAnimal *self) {
    g_return_if_fail(ZT_IS_IANIMAL(self));
    
    ZT_IANIMAL_GET_INTERFACE(self)->run(self);
}

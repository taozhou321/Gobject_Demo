//
//  main.c
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/4/30.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include <stdio.h>
#include "zt_cat.h"


int main_5() {
//    g_type_init();
    ZTAnimal *animal = zt_animal_new("cat");
    gchar *species1 = zt_animal_get_species(animal);
    g_print("%s\n", species1);
    
    ZTAnimal *animal2 = zt_animal_new(NULL);
    gchar *species2 = zt_animal_get_species(animal2);
    g_print("%s\n", species2);
    
    
    return 0;
}

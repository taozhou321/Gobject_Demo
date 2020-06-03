//
//  zt_animal.c
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/4/30.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "zt_animal.h"

G_DEFINE_TYPE(ZTAnimal, zt_animal, G_TYPE_OBJECT)
#define ZT_ANIMAL_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), ZT_TYPE_ANIMAL, ZTAnimalPrivate))

enum {
    PROP_0,
    PROP_SPECIES
};

struct _ZTAnimalPrivate {
    gchar *species;
};

static void zt_animal_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pSpec);
static void zt_animal_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *spec);

static void
zt_animal_class_init(ZTAnimalClass *klass) {
    g_type_class_add_private(klass, sizeof(ZTAnimalPrivate));
    GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
    gobject_class->set_property = zt_animal_set_property;
    gobject_class->get_property = zt_animal_get_property;
    
    /**
     ZTAnimal:species
     */
    g_object_class_install_property(gobject_class, PROP_SPECIES, g_param_spec_string("species", "Animal Species", "The species of animal", "xxx", G_PARAM_READABLE | G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));
}

static void
zt_animal_init(ZTAnimal *self) {
    self->priv = ZT_ANIMAL_GET_PRIVATE(self);
    if (self->priv->species == NULL) {
        self->priv->species = "unkown";
    }
}

static void
zt_animal_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pSpec) {
    ZTAnimal *animal = ZT_ANIMAL(object);
    ZTAnimalPrivate *priv = ZT_ANIMAL_GET_PRIVATE(animal);
    switch (prop_id) {
        case PROP_SPECIES: {
                const gchar *cha = g_value_get_string(value);
                if (cha) {
                    priv->species = g_strdup(cha);
                }
            
            
            }break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pSpec);
            break;
    }
}

static void
zt_animal_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *spec) {
    ZTAnimal *animal = ZT_ANIMAL(object);
    
    switch (prop_id) {
        case PROP_SPECIES:
            g_value_set_pointer(value, animal->priv->species);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, spec);
            break;
    }
}

ZTAnimal *
zt_animal_new(const gchar *species) {
    return g_object_new(ZT_TYPE_ANIMAL, "species",species, NULL);
}

gchar* zt_animal_get_species(ZTAnimal *animal) {
    return g_strdup(animal->priv->species);
}

//
//  Kb_article.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "Kb_article.h"

G_DEFINE_TYPE(KbArticle, kb_article, KB_TYPE_BIBTEX);

#define KB_ARTICLE_GET_PRIVATE(object) (G_TYPE_INSTANCE_GET_PRIVATE((object), KB_TYPE_ARTICLE, KbArticlePrivate))

typedef struct _KbArticlePrivate KbArticlePrivate;
struct _KbArticlePrivate {
    GString *journal;
    GString *volume;
    GString *number;
    GString *pages;
};

enum PROPERTY_ARTICLE {
    PROPERTY_0,
    PROPERTY_JOURNAL,
    PROPERTY_VOLUME,
    PROPERTY_NUMBER,
    PROPERTY_PAGES,
    N_PROPERTIES,
};

static void kb_article_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec) {
    
    KbArticle *self = KB_ARTICLE(object);
    KbArticlePrivate *priv = KB_ARTICLE_GET_PRIVATE(object);
//    KbBibtex *parent = KB_BIBTEX(object);
//    
    switch (property_id) {
        case PROPERTY_JOURNAL:
            g_value_set_string(value, priv->journal->str);
            break;
        case PROPERTY_VOLUME:
            g_value_set_string(value, priv->volume->str);
            break;
        case PROPERTY_NUMBER:
            g_value_set_string(value, priv->number->str);
            break;
        case PROPERTY_PAGES:
            g_value_set_string(value, priv->pages->str);
            break;
        default:
            break;
    }
}

static void kb_article_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec) {
    KbArticle *self = KB_ARTICLE(object);
    KbArticlePrivate *priv = KB_ARTICLE_GET_PRIVATE(self);
    KbBibtex *parent = KB_BIBTEX(object);
    switch (property_id) {
        case PROPERTY_JOURNAL:
            if (priv->journal) {
                g_string_free(priv->journal, TRUE);
            }
            priv->journal = g_string_new(g_value_get_string(value));
            break;
        case PROPERTY_VOLUME:
            if (priv->volume) {
                g_string_free(priv->volume, TRUE);
            }
            priv->volume = g_string_new(g_value_get_string(value));
            break;
        case PROPERTY_NUMBER:
            if (priv->number) {
                g_string_free(priv->number, TRUE);
            }
            priv->number = g_string_new(g_value_get_string(value));
            break;
        case PROPERTY_PAGES:
            if (priv->pages) {
                g_string_free(priv->pages, TRUE);
            }
            priv->pages = g_string_new(g_value_get_string(value));
            break;
        default:
            break;
    }
}

static void kb_article_class_init(KbArticleClass *klass) {
    g_type_class_add_private(klass, sizeof(KbArticlePrivate));
    
    GObjectClass *base_class = G_OBJECT_CLASS(klass);
    base_class->set_property = kb_article_set_property;
    base_class->get_property = kb_article_get_property;
    
    GParamSpec *properties[N_PROPERTIES] = {NULL};
    properties[PROPERTY_JOURNAL] = g_param_spec_string("journal", "Journal", "Bibliograhpy journal", NULL, G_PARAM_READWRITE);
    properties[PROPERTY_VOLUME] = g_param_spec_string("volume", "Volume", "Bibliograhpy volume", NULL, G_PARAM_READWRITE);
    properties[PROPERTY_NUMBER] = g_param_spec_string("number", "Number", "Bibliograhy number", NULL, G_PARAM_READWRITE);
    properties[PROPERTY_PAGES] = g_param_spec_uint("pages", "Pages", "Bibliography pages", 0, G_MAXUINT, 0, G_PARAM_READWRITE);
    
    g_object_class_install_properties(base_class, N_PROPERTIES, properties);
}

static void kb_article_init(KbArticle *self) {
    
}


void kb_article_printf(KbArticle *self) {
    kb_bibtex_printf(&self->parent);
}

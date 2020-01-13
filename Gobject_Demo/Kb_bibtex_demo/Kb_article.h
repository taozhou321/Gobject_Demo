//
//  Kb_article.h
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef Kb_article_h
#define Kb_article_h

#include "Kb_bibtex.h"

#define KB_TYPE_ARTICLE (kb_article_get_type ())

#define KB_ARTICLE(object) G_TYPE_CHECK_INSTANCE_CAST((object), KB_TYPE_ARTICLE, KbArticle)

typedef struct _KbArticle KbArticle;
struct _KbArticle {
    KbBibtex parent;
};

typedef struct _KbArticleClass KbArticleClass;
struct _KbArticleClass {
    KbBibtexClass parent_class;
};

void kb_article_printf(KbArticle *self);

GType kb_article_get_type(void);
#endif /* Kb_article_h */

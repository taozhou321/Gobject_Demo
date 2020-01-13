//
//  Kb_bibtex.h
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/9.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef Kb_bibtex_h
#define Kb_bibtex_h

#include <glib-object.h>

//#define KB_TYPE_BIBTEX(kb_bibtex_get_type())
#define KB_TYPE_BIBTEX (kb_bibtex_get_type ())

#define KB_BIBTEX(object) G_TYPE_CHECK_INSTANCE_CAST((object), KB_TYPE_BIBTEX, KbBibtex)

typedef struct _KbBibtex KbBibtex;
struct _KbBibtex {
    GObject parent;
};

typedef struct _KbBibtexClass KbBibtexClass;
struct _KbBibtexClass {
    GObjectClass parent_class;
};

GType kb_bibtex_get_type(void);

void kb_bibtex_printf(KbBibtex *self);

#endif /* Kb_bibtex_h */

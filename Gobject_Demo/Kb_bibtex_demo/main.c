//
//  main.c
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/9.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include <stdio.h>
#include "Kb_bibtex.h"

int main_2() {
//    g_type_init();
    
    KbBibtex *entry = g_object_new(KB_TYPE_BIBTEX,
                                   "title", "The {\\TeX}Book",
                                   "author", "Knuth, D. E.",
                                   "publisher", "Addison-Wesley Professional",
                                   "year", 1984,
                                   NULL);
    
//    gchar *title, *author, *publisher;
//    guint year;
//    
//    g_object_get(G_OBJECT(entry),
//                 "title", &title,
//                 "author", &author,
//                 "publisher", &publisher,
//                 "year", &year,
//                 NULL);
//    
//    g_print("tile: %s\n"
//            "author: %s\n"
//            "publisher: %s\n"
//            "year: %d\n",
//            title, author, publisher, year);
//    g_free (title);
//    g_free (author);
//    g_free (publisher);
    
    kb_bibtex_printf(entry);
    g_object_unref (entry);
    return 0;
}

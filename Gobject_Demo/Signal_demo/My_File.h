//
//  My_File.h
//  Gstreamer_Demo2
//  <#Description#>
//  Created by zhoutao on 2020/1/10.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef My_File_h
#define My_File_h

#include <glib-object.h>

#define MY_TYPE_FILE (my_file_get_type())
#define MY_FILE(object) G_TYPE_CHECK_INSTANCE_CAST((object), MY_TYPE_FILE, MyFile)
#define MY_IS_FILE(object) G_TYPE_CHECK_INSTANCE_TYPE((object), MY_TYPE_FILE)
#define MY_FILE_CLASS(klass) G_TYPE_CHECK_CLASS_CAST((klass), MY_TYPE_FILE, MyFileClass)
#define MY_IS_FILE_CLASS(klass) G_TYPE_CHECK_CLASS_TYPE((klass), MY_TYPE_FILE)
#define MY_FILE_GET_CLASS(object) G_TYPE_INSTANCE_GET_CLASS((object), MY_TYPE_FILE, MyFileClass)

typedef struct _MyFile MyFile;
struct _MyFile {
    GObject parent;
};

typedef struct _MyFileClass MyFileClass;
struct _MyFileClass {
    GObjectClass parent_class;
};

void my_file_write(MyFile *self, gchar *buffer);

GType my_file_get_type(void);
#endif /* My_File_h */

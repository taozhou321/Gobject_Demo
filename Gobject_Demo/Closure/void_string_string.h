//
//  void_string_string.h
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/6/19.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#ifndef void_string_string_h
#define void_string_string_h
#include <glib-object.h>
void
g_cclosure_user_marshal_VOID__STRING_STRING (GClosure     *closure,
                                             GValue       *return_value G_GNUC_UNUSED,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint G_GNUC_UNUSED,
                                             gpointer      marshal_data);

#endif /* void_string_string_h */

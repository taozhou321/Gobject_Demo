//
//  signaldemo.c
//  Gobject_Demo
//  <#Description#>
//  Created by zhoutao on 2020/6/3.
//  Copyright © 2020 zhoutao. All rights reserved.
//

#include "signal-demo.h"
#include "../Closure/void_string_string.h"

G_DEFINE_TYPE (SignalDemo, signal_demo, G_TYPE_OBJECT);

#define g_marshal_value_peek_string(v) (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v) (v)->data[0].v_pointer

void
g_cclosure_user_marshal_INT_STRING(GClosure *closure,
                                   GValue *return_value G_GNUC_UNUSED,
                                   guint n_param_values,
                                   const GValue *param_values,
                                   gpointer invocation_hint G_GNUC_UNUSED,
                                   gpointer marshal_data) {
    typedef gint (*GMarshalFunc_INT_STRING)(gpointer data1, gpointer data2, gpointer data3);
    register GMarshalFunc_INT_STRING callback;
    register GCClosure *cc = (GCClosure *)closure;
    register gpointer data1, data2;
    gint v_return;
    
    g_return_if_fail(return_value != NULL);
    g_return_if_fail(n_param_values == 2);
    
    if (G_CCLOSURE_SWAP_DATA(closure)) {
        data1 = closure->data;
        data2 = g_value_peek_pointer(param_values + 0);
    } else {
        data1 = g_value_peek_pointer(param_values + 0);
        data2 = closure->data;
    }
    
    callback = (GMarshalFunc_INT_STRING)(marshal_data ? marshal_data : cc->callback);
    
    v_return = callback(data1, g_marshal_value_peek_string(param_values + 1), data2);
    
    g_value_set_int(return_value, v_return);
}

gboolean
signal_demo_accumulator(GSignalInvocationHint *iHant,
                        GValue *return_accu,
                        const GValue *handler_return,
                        gpointer data) {
    g_print("%d\n", g_value_get_int(handler_return));
    g_print("%s\n", (gchar *)data);
    return TRUE;
}

static void
signal_demo_default_handler2 (gpointer instance, const gchar *buffer1, const gchar *buffer2, gpointer userdata)
{
    g_print("Default handler said buffer1: %s\n", buffer1);
    g_print("Default handler said buffer2: %s\n", buffer2);
//    g_print("Default handler said userdata: %s\n", buffer);
}

static void
signal_demo_default_handler (gpointer instance, const gchar *buffer, gpointer userdata)
{
    g_print("Default handler said buffer: %s\n", buffer);
    g_print("Default handler said userdata: %s\n", (char *)userdata);
}

static guint
signal_demo_default_accumulator_handler (gpointer instance, const gchar *buffer, gpointer userdata)
{
    g_print("Default handler said buffer: %s\n", buffer);
    g_print("Default handler said userdata: %s\n", (char *)userdata);
    return 2;
}

void
signal_demo_init (SignalDemo *self)
{
}

void
signal_demo_class_init (SignalDemoClass *klass)
{
    //单个参数测试
    klass->default_handler = signal_demo_default_handler;
    g_signal_new ("hello",
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_FIRST | G_SIGNAL_DETAILED,
                  G_STRUCT_OFFSET (SignalDemoClass, default_handler),
                  NULL,
                  NULL,
                  g_cclosure_marshal_VOID__STRING,
                  G_TYPE_NONE,
                  1,
                  G_TYPE_STRING);
    /**
     [注]:
     若采用"signal-name::detail"的形式，如下
      g_signal_emit_by_name(sd_obj, "hello::test", "this is detail signal test");
     第3个GSignalFlags无G_SIGNAL_DETAILED会导致如下报错
     (process:1506): GLib-GObject-[1;33mWARNING[0m **: [34m14:40:37.128[0m: ../gobject/gsignal.c:2342: signal id '2' does not support detail (60)
     */

    
    //多个参数测试
//    klass->default_handler2 = signal_demo_default_handler2;
    //方式1：
//    g_signal_new ("hello",
//                  G_TYPE_FROM_CLASS (klass),
//                  G_SIGNAL_RUN_FIRST | G_SIGNAL_DETAILED,
//                  0,//G_STRUCT_OFFSET (SignalDemoClass, default_handler2)
//                  NULL,
//                  NULL,
//                  g_cclosure_user_marshal_VOID__STRING_STRING, //g_cclosure_marshal_VOID__STRING,
//                  G_TYPE_NONE,
//                  2,
//                  G_TYPE_STRING, G_TYPE_STRING);
    //方式2：
//    GType types[2] = {G_TYPE_STRING, G_TYPE_STRING};
//    g_signal_newv("hello",
//                  G_TYPE_FROM_CLASS(klass),
//                  G_SIGNAL_RUN_FIRST | G_SIGNAL_DETAILED,
//                  0,
//                  NULL, NULL,
//                  g_cclosure_user_marshal_VOID__STRING_STRING,
//                  G_TYPE_NONE, 2, types);
    
    //accumulator测试
//    klass->default_accumulator_handler = signal_demo_default_accumulator_handler;
//    g_signal_new ("hello",
//                  G_TYPE_FROM_CLASS (klass),
//                  G_SIGNAL_RUN_LAST,
//                  G_STRUCT_OFFSET (SignalDemoClass, default_accumulator_handler),
//                  signal_demo_accumulator,
//                  "hahaha ha",
//                  g_cclosure_user_marshal_INT_STRING,
//                  G_TYPE_INT,
//                  1,
//                  G_TYPE_STRING);
    //[注]:
    //信号的accumulator需要信号存在返回值
}

/**
 g_signal_new函数的参数：
 ·第一个参数是字符串"hello",它表示信号
 ·第二个参数是SignalDemo类的类型ID,可以使用 G_TYPE_FROM_CLASS 宏从 SignalDemoClass 结构体中获取，
  也可直接使用 signal-demo.h 中定义的宏 SIGNAL_TYPE_DEMO。
 ·第 3 个参数GSignalFlags解释如下方。
 ·第 4 个参数比较关键，它是一个内存偏移量，主要用于从 SignalDemoClass 结构体中找到 default_handler 指针的位置，
  可以使用 G_STRUCT_OFFSET    宏来获取，也可以直接根据 signal-demo.h 中的 SignalDemoClass 结构体的定义，
  使用 sizeof (GObjectClass) 来得到内存偏移量，因为 default_handler 指针之前只有一个 GObjectClass 结构体成员。
 ·第 5 个参数是accumulator，其类型为GSignalAccumulator
  gboolean (*GSignalAccumulator) (GSignalInvocationHint *ihint,
                                  GValue *return_accu,
                                  const GValue *handler_return,
                                  gpointer data);
 ·第 6 个参数accu_data会被g_signal_new传递于accumulator所指向的函数作为后者的第4个参数data
 ·第 7 个参数设定闭包的  marshal。在文档“函数指针、回调函数与 GObject 闭包” 中，描述了 GObject 的闭包的概念与结构，
  我们可以将它视为回调函数 + 上下文环境而构成的一种数据结构，或者再简单一点，将其视为回调函数。另外，在那篇文档中，我们也对 marshal 的概念进行了一些粗浅的解释。事实上marshal主要是用来“翻译”闭包的参数和返回值类型的，它将翻译的结果传递给闭包。之所以不直接调用闭包，
  而是在其外加了一层 marshal 的包装，主要是方便 GObject 库与其他语言的绑定。例如，我们可以写一个 pyg_closure_marshal_VOID__STRING 函数，
  其中可以调用 python 语言编写的“闭包”并将其计算结果传递给 GValue 容器，然后再从 GValue 容器中提取计算结果。
 ·第 8 个参数指定 marshal 函数的返回值类型。由于本例的第 7 个参数所指定的 marshal 是 g_cclosure_marshal_VOID__STRING 函数的返回值是
  void，而 void 类型在 GObject 库的类型管理系统是 G_TYPE_NONE 类型。
 ·第 9 个参数指定 g_signal_new 函数向 marshal 函数传递的参数个数，由于本例使用的 marshal 函数是 g_cclosure_marshal_VOID__STRING
  函数，g_signal_new 函数只向其传递 1 个参数。
 ·第 10 个参数是可变参数，其数量由第 8 个参数决定，用于指定 g_signal_new 函数向 marshal 函数传递的参数类型。由于本例使用的 marshal 函数是
  g_cclosure_marshal_VOID__STRING 函数，并且 g_signal_new 函数只向其传递一个参数，所以传入的参数类型为 G_TYPE_STRING（GObject 库类型管理系统中的字符串类型）。
 [注1]：
 在上述的g_signal_new函数的第7个参数的解释中，我提到了闭包。事实上，g_signal_new函数并没有闭包类型的参数，
 但是它在内部的确是构建了一个闭包，而且是通过它的第4个参数实现的。因为g_signal_new函数在其内部调用了
 g_signal_type_cclosure_new函数，后者所做的工作就是从一个给定的类结构体中通过内存偏移地址获得回调函数指针，
 然后构建闭包返于g_signal_new函数。既然g_signal_new函数的内部是需要闭包的，那么它的第7~10个参数自然都是为那个闭包准备的。
 需要注意，g_cclosure_marshal_VOID__STRING所约定的回调函数类型为：
 void (*callback) (gpointer instance, const gchar *arg1, gpointer user_data)
 这表明g_cclosure_marshal_VOID_STRING需要使用者向其回调函数传入3个参数，其中前两个参数是回调函数的必要参数，
 而第3个参数，即userdata，是为使用者留的"后门"，使用者可以通过这个参数传入自己所需要的任意数据。
 由于GObject闭包约定了回调函数的第一个参数必须是对象本身，所以g_cclosure_marshal_VOID__STRING函数
 实际上要求使用者向其传入2个参数，但是在本例中g_signal_new只向其传递了1个类型为G_TYPE_STRING类型的参数，这有些蹊跷。
 
 这是因为g_signal_new函数所构建闭包指示让信号所关联的数据类型能够有一次可以自我表现的机会，即可以在信号被触发的时候，
 能够自动调用该数据类型的某个方法，例如SignalDemo类结构体的default_handler指针所指向的函数。也就是说，
 SignalDemo类自身是没有必要向闭包传递那个"userdata"参数的，试试信号的使用者有这种需求。这就是g_signal_new的参数
 中只表明它向闭包传递了1个G_TYPE_STRING类型参数的缘故。
 
 现在总结一下：g_signal_new函数内部所构建的闭包，它在被调用的时候，肯定是被传入了3个参数，它们被信号所关联的闭包分成了
 以下层次：
 ·第 1 个参数是信号的默认闭包（信号注册阶段出现）和信号使用者提供的闭包（信号连接阶段出现）所必需的，但是这个参数是隐式存在的，由 g_signal_new 暗自向闭包传递。
 ·第 2 个参数是显式的，同时也是信号的默认闭包和信号使用者提供的闭包所必须的，这个参数由信号的发射函数（例如 g_signal_emit_by_name）向闭包传递。
 ·第 3 个参数也是显式的，且只被信号使用者提供的闭包所关注，这个参数由信号的连接函数（例如 g_signal_connect）向闭包传递
 
 [注2]：
 g_cclosure_marshal_VOID__STRING只能传递1个字符串参数
 要传递2个字符串参数只能自己去写了，如g_cclosure_user_marshal_VOID__STRING_STRING
 
 [注3]：
 简单来说，accumulator所指向的函数会在信号所连接的每个闭包（包括在信号注册阶段生成的信号默认闭包，
 以及信号连接阶段中信号使用者所提供的闭包）执行之后被调用，他的主要功能就是手机信号所连接的各个闭包
 的返回值（简称”信号返回值“）
 */

/**
 GSignalFlags解释
 g_signal_new函数的第3个参数，我们将其设为G_SIGNAL_RUN_FIRST。实际上，这个参数是枚举类型，是信号默认闭包的调用阶段的标识，
 可以是下面7种形式中1种，也可以是多种组合
 typedef enum
 {
   G_SIGNAL_RUN_FIRST = 1 << 0, 信号的默认闭包要先于信号使用者的闭包被调用
   G_SIGNAL_RUN_LAST = 1 << 1, 信号的默认闭包要迟于信号使用者的表白而调用
   G_SIGNAL_RUN_CLEANUP = 1 << 2, 在最后一个发射状态调用对象方法处理程序
   G_SIGNAL_NO_RECURSE = 1 << 3, 当一个对象当前处于发射状态时，该对象发射的信号不会递归地发射，这会导致第一个发射被重启
   G_SIGNAL_DETAILED = 1 << 4, 信号支持在处理程序连接即发射时将"::detail"附加到信号名后的形式，即"signal-name::detail"形式
   G_SIGNAL_ACTION = 1 << 5,
   G_SIGNAL_NO_HOOKS = 1 << 6,
   G_SIGNAL_MUST_COLLECT = 1 << 7,
   G_SIGNAL_DEPRECATED   = 1 << 8
 } GSignalFlags;
 */



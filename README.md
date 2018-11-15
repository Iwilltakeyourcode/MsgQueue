# msgqueue

此链表用户使用的 API 请看 msgqueue.h

test.c文件是用来简单测试该链表的

目前只实现了以下功能：
1，头插入，尾插入；
2，头节点删除，尾节点删除；
3，遍历功能：测试用的遍历功能会打印节点信息；另外定义一个遍历用的宏 foreach_element是用遍历的方式查找节点。

/**11-8 更新/

1，增加头读取，尾读取
2，增加缓存链表数据到文件，读取缓存到链表
3，修改文件结构，宏定义相关封装到c文件，头文件只留接口函数


/*11-11 更新*/
1，更改程序逻辑，listApi.c 实现对struct list 的增删改查操作；
2，msgqueue.c 封装listApi.h 提供的接口函数，实现对具体的链表元素操作（即操作struct msg）

/*11-15 更新*/
1，修改struct msg 的结构，增加 void 指针用来接收任何结构体，而对应结构体大小保存到size
====================================================
   typedef struct msg{                    typedef struct msg{
      struct list list;         ===>           struct list list;
      char *msg;                               unsigned int size;
   }msg_t;                                     void *msg;
                                           }msg_t;
====================================================                            
2，增加缓存链表到文件和从文件读取出来的函数

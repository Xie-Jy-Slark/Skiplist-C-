# Skiplist-C-
详细的skiplist C++实现
> 增加了向前指针的链表叫作跳表。跳表全称叫做跳跃表，简称跳表。跳表是一个随机化的数据结构，实质就是一种可以进行二分查找的有序链表。跳表在原有的有序链表上面增加了多级索引，通过索引来实现快速查找。跳表不仅能提高搜索性能，同时也可以提高插入和删除操作的性能。(引用自百度百科）
## 功能
跳表Skiplist。支持插入，查找和删除操作。Method:
1. Skiplist<Key, Vaule> skiplist; // 创建一个空的跳表，键类型为Key，值类型为Value
2. skiplist.put(key, kalue);      // 在跳表中增添一个键值对
3. if (skiplist.exist(key))       // 查询跳表中有无key，若有则返回对应的value
4. ... = skiplist.get(key);   // 注意，每次get前需要判断exist,否则可能返回错误
5. skiplist.erase(key);          // 在跳表中删除一个键值对
## 其他事项
1. **调用本库时无需将.cpp文件添加到解决方案管理器，但需要将.cpp文件和.h文件放在同一个文件夹里。**原因是.h文件中有下面这句话：
`#include "skiplist.cpp"`
2. tryskiplist.cpp文件可以用来测试本skiplist的效果

#ifndef _skiplist_h_
#define _skiplist_h_
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

//用户无需调用的skiplist节点Entry类
template <typename Key, typename Value>
class SkiplistEntry;

/*
 * 跳表Skiplist。Method:
 * Skiplist<Key, Vaule> skiplist; // 创建一个空的跳表，键类型为Key，值类型为Value
 * skiplist.put(key, kalue);      // 在跳表中增添一个键值对
 * if (skiplist.exist(key))       // 查询跳表中有无key，若有则返回对应的value
 *     ... = skiplist.get(key);   // 注意，每次get前需要判断exist,否则可能返回错误
 * skiplist.delete(key);          // 在跳表中删除一个键值对
 */
template <typename Key, typename Value>
class Skiplist {
  friend SkiplistEntry<Key, Value>;
public:
  /*
   * Constructor: Skiplist
   * Usage: Skiplist<Key, Value> Skiplist;
   * -------------------------------------
   * 默认构造函数
   */
  Skiplist() : _quadlist{ std::vector< SkiplistEntry<Key, Value>* >() }{};

  /*
   * Destructor: ~Skiplist
   * Usage: (usually implicit)
   * -------------------------
   * 析构函数
   */
  ~Skiplist();

  /*
   * Method: exist(Key)
   * Usage: if(skiplist.exist(Key)) ...
   * ----------------------------------
   * 查询跳表里有没有Key对应的键值对
   */
  bool exist(const Key&);

  /*
   * Method: get(Key)
   * Usage: value = skiplist.get(Key);
   * ---------------------------------
   * 第一个实现的外部接口函数，获得Key对应的Value，时间复杂度为O(logn)
   * 注意必须在exist返回true时才能得到正确结果
   */
  const Value& get(const Key&);

  /*
   * Method: put(Key, Value)
   * Usage: skiplist.put(Key, Value);
   * --------------------------------
   * 在跳表中增添一个键值对
   */
  bool put(const Key&, const Value&);

  /*
   * Method: erase(Key)
   * Usage: skiplist.erase(Key);
   * ---------------------------
   * 在跳表中删除一个键值对，如果删除成功，返回true，否则返回false
   */
  bool erase(const Key&);
private:
  bool update(SkiplistEntry<Key, Value>* fpentry, unsigned floor);     //将某一Entry向上扩展一层
  std::vector< SkiplistEntry<Key, Value>* > _quadlist;                 //储存跳表的数据
  bool pushfront(Key, Value, unsigned floor);                          //如果这一层为空，那么在这一层增添一个元素
  bool insertback(SkiplistEntry<Key, Value>*&, Key, Value);            //在第一个参数指向的Entry后面插入一个新元素
};

template <typename Key, typename Value>
class SkiplistEntry {
  friend Skiplist<Key, Value>;
protected:
  /*
   * Constructor: SkiplistEntry
   * Usage: SkiplistEntry<Key, Value> skiplistEntry;
   *        SkiplistEntry<Key, Value> skiplistEntry(Key, Value);
   *        SkiplistEntry<Key, Value> skiplistEntry(const skiplistEntry<Key, Value>&);
   * -----------------------------------------------
   *  1:默认构造函数
   *  2:使用key 和 value 初始化对象
   *  3:复制构造函数，强复制，一般情况会导致多次delete，导致出现bug
   */
  SkiplistEntry() :_key(Key()), _value(Value())\
    , _pup(nullptr), _pdown(nullptr), _pleft(nullptr), _pright(nullptr) {}
  SkiplistEntry(Key pkey, Value pvalue) : _key(pkey), _value(pvalue)\
    , _pup(nullptr), _pdown(nullptr), _pleft(nullptr), _pright(nullptr) {}
  SkiplistEntry<Key, Value>(const SkiplistEntry<Key, Value>&) = default;
  /*
   * Destructor: ~SkiplistEntry
   * Usage: (usually implicit)
   * ==========================
   * 析构函数
   */
  ~SkiplistEntry() {
    //    std::cout << _key << ' ' << _value << std::endl;
    if (_pright != nullptr) {
      delete _pright;
      //不加下面这句话，更容易发现bug
      _pright = nullptr;
    }
  }
private:
  /*
   * Method: insertback
   * Usage: skiplistEntry.insertback(Key, Value);
   * --------------------------------------------
   * 在本entry右面创建一个新的skiplistEntry对象
   */
  void insertback(Key, Value);
private:
  Key _key;                                                           //每个节点的key,value
  Value _value;
  SkiplistEntry<Key, Value>* _pup;                                    //分别储存上下左右的
  SkiplistEntry<Key, Value>* _pdown;                                  //节点指针
  SkiplistEntry<Key, Value>* _pleft;
  SkiplistEntry<Key, Value>* _pright;
};
#include "skiplist.cpp"

#endif
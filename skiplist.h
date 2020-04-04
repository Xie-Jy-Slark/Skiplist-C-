#ifndef _skiplist_h_
#define _skiplist_h_
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

//�û�������õ�skiplist�ڵ�Entry��
template <typename Key, typename Value>
class SkiplistEntry;

/*
 * ����Skiplist��Method:
 * Skiplist<Key, Vaule> skiplist; // ����һ���յ�����������ΪKey��ֵ����ΪValue
 * skiplist.put(key, kalue);      // ������������һ����ֵ��
 * if (skiplist.exist(key))       // ��ѯ����������key�������򷵻ض�Ӧ��value
 *     ... = skiplist.get(key);   // ע�⣬ÿ��getǰ��Ҫ�ж�exist,������ܷ��ش���
 * skiplist.delete(key);          // ��������ɾ��һ����ֵ��
 */
template <typename Key, typename Value>
class Skiplist {
  friend SkiplistEntry<Key, Value>;
public:
  /*
   * Constructor: Skiplist
   * Usage: Skiplist<Key, Value> Skiplist;
   * -------------------------------------
   * Ĭ�Ϲ��캯��
   */
  Skiplist() : _quadlist{ std::vector< SkiplistEntry<Key, Value>* >() }{};

  /*
   * Destructor: ~Skiplist
   * Usage: (usually implicit)
   * -------------------------
   * ��������
   */
  ~Skiplist();

  /*
   * Method: exist(Key)
   * Usage: if(skiplist.exist(Key)) ...
   * ----------------------------------
   * ��ѯ��������û��Key��Ӧ�ļ�ֵ��
   */
  bool exist(const Key&);

  /*
   * Method: get(Key)
   * Usage: value = skiplist.get(Key);
   * ---------------------------------
   * ��һ��ʵ�ֵ��ⲿ�ӿں��������Key��Ӧ��Value��ʱ�临�Ӷ�ΪO(logn)
   * ע�������exist����trueʱ���ܵõ���ȷ���
   */
  const Value& get(const Key&);

  /*
   * Method: put(Key, Value)
   * Usage: skiplist.put(Key, Value);
   * --------------------------------
   * ������������һ����ֵ��
   */
  bool put(const Key&, const Value&);

  /*
   * Method: erase(Key)
   * Usage: skiplist.erase(Key);
   * ---------------------------
   * ��������ɾ��һ����ֵ�ԣ����ɾ���ɹ�������true�����򷵻�false
   */
  bool erase(const Key&);
private:
  bool update(SkiplistEntry<Key, Value>* fpentry, unsigned floor);     //��ĳһEntry������չһ��
  std::vector< SkiplistEntry<Key, Value>* > _quadlist;                 //�������������
  bool pushfront(Key, Value, unsigned floor);                          //�����һ��Ϊ�գ���ô����һ������һ��Ԫ��
  bool insertback(SkiplistEntry<Key, Value>*&, Key, Value);            //�ڵ�һ������ָ���Entry�������һ����Ԫ��
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
   *  1:Ĭ�Ϲ��캯��
   *  2:ʹ��key �� value ��ʼ������
   *  3:���ƹ��캯����ǿ���ƣ�һ������ᵼ�¶��delete�����³���bug
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
   * ��������
   */
  ~SkiplistEntry() {
    //    std::cout << _key << ' ' << _value << std::endl;
    if (_pright != nullptr) {
      delete _pright;
      //����������仰�������׷���bug
      _pright = nullptr;
    }
  }
private:
  /*
   * Method: insertback
   * Usage: skiplistEntry.insertback(Key, Value);
   * --------------------------------------------
   * �ڱ�entry���洴��һ���µ�skiplistEntry����
   */
  void insertback(Key, Value);
private:
  Key _key;                                                           //ÿ���ڵ��key,value
  Value _value;
  SkiplistEntry<Key, Value>* _pup;                                    //�ֱ𴢴��������ҵ�
  SkiplistEntry<Key, Value>* _pdown;                                  //�ڵ�ָ��
  SkiplistEntry<Key, Value>* _pleft;
  SkiplistEntry<Key, Value>* _pright;
};
#include "skiplist.cpp"

#endif
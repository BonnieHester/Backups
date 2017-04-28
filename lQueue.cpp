#include "dllist.cpp"
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

template <typename AnyType> class myQueue {

  doublyLinkedList<AnyType> list;

public:

  void enqueue(AnyType e) {
    list.addEnd(e);
  }

  AnyType dequeue() {
    AnyType temp = list.getFront();
    list.removeFront();
    return temp;
  }

  AnyType getFront() {
    return list.getFront();
  }

  bool isEmpty() {
    return (list.listSize() == 0);
  }

  size_t getSize() {
    return list.listSize();
  }
};

BOOST_AUTO_TEST_CASE( int_tests ) {

  myQueue<int> s;
  s.enqueue(3);
  s.enqueue(8);
  s.enqueue(-4);
  
  BOOST_CHECK(s.getSize() == 3);
  BOOST_CHECK(!s.isEmpty());
  BOOST_CHECK(s.getFront() == 3);
  BOOST_CHECK(s.dequeue() == 3);
  BOOST_CHECK(s.getFront() == 8);
  BOOST_CHECK(s.dequeue() == 8);
  BOOST_CHECK(s.getFront() == -4);
  BOOST_CHECK(s.dequeue() == -4);
  BOOST_CHECK(s.isEmpty());
}

BOOST_AUTO_TEST_CASE( string_tests ) {

  myQueue<string> q;
  q.enqueue("hello");
  q.enqueue("world");

  BOOST_CHECK(q.getSize() == 2);
  BOOST_CHECK(!q.isEmpty());
  BOOST_CHECK(q.getFront().compare("hello") == 0);
  BOOST_CHECK(q.dequeue().compare("hello") == 0);
  q.dequeue();
  BOOST_CHECK(q.isEmpty());
}

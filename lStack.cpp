#include "dllist.cpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

template <typename AnyType> class myStack {

  doublyLinkedList<AnyType> list;

public:

  void push(AnyType e) {
    list.addFront(e);
  }

  AnyType pop() {
    AnyType temp = list.getFront();
    list.removeFront();
    return temp;
  }

  AnyType peek() {
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

  myStack<int> s;
  s.push(3);
  s.push(8);
  s.push(-4);

  BOOST_CHECK(s.getSize() == 3);
  BOOST_CHECK(!s.isEmpty());
  BOOST_CHECK(s.peek() == -4);
  BOOST_CHECK(s.pop() == -4);
  BOOST_CHECK(s.peek() == 8);
  BOOST_CHECK(s.pop() == 8);
  BOOST_CHECK(s.peek() == 3);
  BOOST_CHECK(s.pop() == 3);
  BOOST_CHECK(s.isEmpty());
}

BOOST_AUTO_TEST_CASE( string_tests ) {

  myStack<string> q;
  q.push("hello");
  q.push("world");

  BOOST_CHECK(q.getSize() == 2);
  BOOST_CHECK(!q.isEmpty());
  BOOST_CHECK(q.peek().compare("world") == 0);
  BOOST_CHECK(q.pop().compare("world") == 0);
  q.pop();
  BOOST_CHECK(q.isEmpty());
}

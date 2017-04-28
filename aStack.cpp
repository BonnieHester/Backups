#include "dllist.cpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
//#include <boost/test/unit_test.hpp>

template <typename AnyType> class myStack {

  AnyType array[1000];
  int s;

public:

  myStack() {
    s = 0;
  }

  void push(AnyType e) {
    array[s++] = e;
  }

  AnyType pop() {
    if (s == 0) {
      cout << "Error: stack is empty." << endl;
      exit(1);
    } 
    AnyType temp = array[s-1];
    s--;
    return temp;
  }

  AnyType peek() {
    if (s == 0) {
      cout << "Error: stack is empty." << endl;
      exit(1);
    }
    return array[s-1];
  }

  bool isEmpty() {
    return (s == 0);
  }

  size_t getSize() {
    return s;
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

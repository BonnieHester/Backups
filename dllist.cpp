#include <iostream>
using namespace std;

template <typename sData> class node;
template <typename sData> class doublyLinkedList;

template <typename sData> class node {

  friend class doublyLinkedList<sData>;

  node * next;
  node * prev;
  sData info;

  node () {
    next = NULL;
    prev = NULL;
  }

  node (sData value) {
    info = value;
    next = NULL;
    prev = NULL;
  }

};

template <typename sData> class doublyLinkedList {
public:

  node<sData> * head = new node<sData>();

  doublyLinkedList() {
    head->next = head;
    head->prev = head;
  }

  void addFront(sData value) {                                                                                                           
    node<sData> * temp = new node<sData>(value);                                                                                                                                   
    temp->prev = head;         //new first element’s prev will point to header cell
    temp->next = head->next;               //set new first element’s next to point to previous first element 
    (head->next)->prev = temp;               //set what is now the second element’s prev to point to the new first element
    head->next = temp;                     //reset head to point to new first element
  } 
                                                                                      
  void addEnd(sData value) {
    node<sData> * temp = new node<sData>(value);
    temp->prev = head->prev;    //set new last element's prev to previous last element
    (head->prev)->next = temp;  //set previous last element's next to point to new last element                                                                                   
    temp->next = head;    //set new last element's next to head
    head->prev = temp;          //set head's prev to point to new last element
  }

  void removeFront() {
    node<sData> * temp = head->next;
    (temp->next)->prev = head;        //set new first element's prev to head
    head->next = temp->next;                //set head to new first element
    free(temp);
  }

  void removeEnd() {
    node<sData> * temp = head->prev;
    (temp->prev)->next = head;       //set new last element's next to head
    head->prev = temp->prev;               //set head's prev to new last element
    free(temp);
  }

  void addAtIndex (sData value, int index) { //indexing from 0, so front is 0, end is size - 1 (inserting in front of node at given index)
    if (index < 0 || index >= this->listSize())
      throw out_of_range("Invalid index; element not added.");
    else if (index == 0) 
      this->addFront(value);
    else if (index == this->listSize())
      this->addEnd(value);
    
    else {
      node<sData> * temp = new node<sData>(value);
      node<sData> * left = head;
      
      for (int i = 1; i != index; i++) //starting at 1 b/c if they entered 1 then left is already what it should be
        left = left->next;
      temp->prev = left;         //set inserted element's prev to element to its left
      temp->next = left->next;   //set inserted element's next to element to its right
      (left->next)->prev = temp; //set right element's prev to inserted element
      left->next = temp;         //set left element's next to inserted element
    }
  }
  
  void removeAtIndex (int index) {
    if (index < 0 || index >= this->listSize())
      throw out_of_range("Invalid index; element not removed.");
    else if (index == 0)
      this->removeFront();
    else if (index == this->listSize())
      this->removeEnd();
    
    else {
      node<sData> * temp = head;
      
      for (int i = 0; i != index; i++)
        temp = temp->next;
      (temp->prev)->next = temp->next; //setting left element's next to point to right element
      (temp->next)->prev = temp->prev; //setting right element's prev to point to left element
      free(temp);
    }
  }

  void displayList() {
    if (head->next == head) {
      cout << "List empty; nothing to display." << endl;
      return;
    }
    else {
      node<sData> * temp = head->next;
      do {
        cout << temp->info << " ";
        temp = temp->next;
      } while(temp != head);
      cout << endl;
    }
  }

  size_t listSize() {
    if (head->next == head) return 0;
    node<sData> * temp = head->next;
    int count = 0;
    do {
      count++;
      temp = temp->next;
    } while(temp != head);
    return count;
  }

  sData getFront() {
    return (head->next)->info;
  }

  sData getEnd() {
    return (head->prev)->info;
  }

  sData getAtIndex(int index) {
    if (index < 0 || index >= this->listSize())
      throw out_of_range("Invalid index.");
    else {
      node<sData> * temp = head->next;
      for (int i = 0; i != index; i++)
        temp = temp->next;
      return temp->info;
    }
  }

};

int main() {

  doublyLinkedList<string> sdl;

  sdl.addFront("hi");
  sdl.addEnd("im");
  sdl.addEnd("paul");
  sdl.displayList(); //hi im paul
  cout << "Removing last element. New list: ";
  sdl.removeEnd();
  sdl.displayList(); //hi im

  doublyLinkedList<int> dl;

  dl.addFront(3);
  dl.addEnd(5);
  cout << "Size of list: " << dl.listSize() << endl;

  dl.displayList(); //3 5
  dl.removeFront();
  dl.displayList(); //5
  dl.addFront(33);
  dl.addEnd(203);
  dl.displayList(); //33 5 203
  dl.removeEnd(); 
  dl.displayList(); //33 5
  dl.addAtIndex(57, 1);
  dl.addAtIndex(0, 0); 
  dl.addAtIndex(400, 2);
  dl.addAtIndex(29, 3);
  dl.displayList(); //0 33 400 29 57 5
  
  dl.removeAtIndex(2);
  dl.displayList(); //0 33 29 57 5

  cout << "Front: " << dl.getFront() << endl;
  cout << "End: " << dl.getEnd() << endl;
  cout << "Size: " << dl.listSize() << endl;
  cout << "End through index: " << dl.getAtIndex(dl.listSize() - 1) << endl;
  cout << "Third: " << dl.getAtIndex(2) << endl;

  return 0;
}

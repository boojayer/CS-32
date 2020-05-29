#include <string>
#include <iostream>

#ifndef MAP_DEC
#define MAP_DEC


using KeyType = std::string;
using ValueType = double;


class Map
{
public:
    //added fucntions
    Map(const Map& src);   //Copy constructor

    Map& operator=(const Map& src);     //Assignment operator

    ~Map();        // Destruct map
    //end of added functions



    Map();         // Create an empty map (i.e., one with no key/value pairs)

    bool empty() const;  // Return true if the map is empty, otherwise false.

    int size() const;    // Return the number of key/value pairs in the map.

    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).

    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).

    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.

    bool contains(const KeyType& key) const;
    // Return true if key is equal to a key currently in the map, otherwise
    // false.

    bool get(const KeyType& key, ValueType& value) const;
    // If key is equal to a key currently in the map, set value to the
    // value in the map which that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.

    bool get(int i, KeyType& key, ValueType& value) const;
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)

    void swap(Map& other);
    // Exchange the contents of this map with the other one.

private:
    struct Node  //set up the node struct for the linked lists
    {
        KeyType k;
        ValueType v;
        Node* next;
        Node* previous;
    };


    class LinkedList
    {
    public:
        LinkedList()   //initializes the linbked list
        {
            head = nullptr;
            tail = nullptr;
        }

        void addToFront(KeyType key, ValueType val)  //adds a new node to the from of the lnked list
        {
            Node* p;
            p = new Node;   //creates node
            p->v = val;     //sets nodes values
            p->k = key;
            if (head != nullptr)   //checks if other nodes have been created before
            { 
                p->next = head;          //if nodes have been created; set next to node after
                p->previous = nullptr;   //no nodes before
                head = p;                 //sets head pointer to new node
                Node* temp = p->next;        //selects the node before
                temp->previous = p;           //change the "previous" value of that node
            }
            else;                    //if no node ahs been created yet
            {
                p->next = head;            //sets equal to nullptr
                p->previous = tail;        //sets equal to nullptr
                head = p;             //head is equal to new node
                tail = p;             //tail is equal to new node
            }
           
        }

        void addToRear(KeyType key, ValueType val)
        {
            if (head == nullptr)    //if it is the first node call "addToFront
            {
                addToFront(key, val);
            }
            else                  //if at least one node has been already initialized
            {
                Node* i = new Node;
                i->k = key;
                i->v = val;
                i->next = nullptr;   //no values after so equal to nullptr
                tail->next = i;      //the last node before this one "next"vaule equal to new node
                tail = i;            //tail is equal to new node
            }
        }

        void deleteItem(KeyType key)
        {
            if (head == nullptr)   //if no nodes are left
            {
                return;    //if there are no nodes then stop function
            }
            if (head->k == key)   //if head node is equal to the key
            {
                Node* killMe = head;    //select head pointer
                head = killMe->next;      //head equal to node after
                delete killMe;         //delete node
                if (head == nullptr)   //if no items are left in linked list
                {
                    tail = nullptr;     //set tail to nullptr
                }
                else     //if items are in linked list 
                {
                    head->previous = nullptr;    //the "previous" value is noew nullptr
                    return;    
                }
            }
            Node *p = head;
            while (p != nullptr)  //while items are still in linked list
            {
                if (p->next != nullptr && p->next->k == key) //look for value
                {
                    break;   //breaks while loop if value is found
                }
                p = p->next;    //goes to next item if while loop continues
            }
            if (p != nullptr) //if key is found
            {
                Node* killMe = p->next;    //create new pointer
                if (killMe->next == nullptr)    //if pointer is last in list
                {
                    delete killMe;      //delte pointer 
                    p->next = nullptr;     //set the previous node's "next" value to nullptr
                    tail = p;     //set tail to previous pointer
                }
                else
                {
                    Node* after = killMe->next;  //
                    after->previous = p;      //sets the after pointer's prev value to the one befreo delted
                    p->next = after;     //p's next after deleted node
                    delete killMe;
                }
            }
        }

        bool findItem(KeyType key) const
        {
            Node* p = head;
            while (p != nullptr)    //while nodes still exist
            {
                if (p->k == key)   //if key is equal to a value in linked list
                    return true;
                p = p->next;   //go to next node
            }
            return false;   //if item does not exist
        }

        bool changeItem(KeyType key, ValueType val)
        {
            Node* p = head;
            while (p != nullptr)    //while nodes still exist
            {
                if (p->k == key)   //if key is equal to a value in linked list
                {
                    p->v = val;    //sets value to new one
                    return true;
                }
                p = p->next;     //keep looping until key is found or reaches end of list
            }
            return false;
        }

        void getItem(const KeyType& key, ValueType& val) const
        {
            Node* p = head;       //have node point to head node
            while (p != nullptr)   //while within linked list
            {
                if (p->k == key)      //if key is equal to one in list
                {
                    val = p->v;    //copy value parameter
                    return;
                }
                p = p->next;   //loop until key is foud or reach end of list
            }
        }

        bool goTo(int n, KeyType& key, ValueType& val) const
        {
            int l = 0;           
            Node* p = head;
            while (p != nullptr)
            {
                if (l == n)   //while "n" doesnt equal "l"
                {
                    key = p->k;   //copy over value and key at int at "n" node
                    val = p->v;
                    return true;
                }
                p = p->next;      //loop until "n" is equal to "l"
                l++;
            }
            return false;
        }

        ~LinkedList()   //deconstructor
        {
            Node* p;
            p = head;
            while (p != nullptr)  //deletes all nodes until the last
            {
                Node* n = p->next;  ///sets pointer "n" to equal next node
                delete p;   //deletes currenbt node
                p = n;   //sets p eqal to the next node
            }
        }

    private:
        Node* head;
        Node* tail;
    };
    
    int m_size;
    LinkedList m_list;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif //MAP_DEC

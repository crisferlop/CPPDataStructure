#include "list/IList.h"
#include "list/Node.h"

#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H
#define Null 0

template <class E>
class CircularList : IList<E>{
    Node<E> *head,*tail;



    Node<E>* getNode(int index){
        Node<E> *actualNode = head;
        for (int from = 0; from <index; from++){
            actualNode = actualNode->getNext();
        }
        return actualNode;
    }

public:
    CircularList() {
        tail = Null;
        head = Null;
    }

    void addi(E data){
        if(head == Null){
            head = new Node<E>(data);
            tail = head;
        }
        else{
            Node<E> *newNode = new Node<E>(data);
            newNode->setNext(head);
            head = newNode;
            tail->setNext(head);
        }
        this->lenght++;
    }

    void add(E data){
        if (head == Null){
            head = new Node<E>(data);
            tail = head;
        }
        else{
            Node<E> *newNode = new Node<E>(data);
            tail->setNext(newNode);
            tail = newNode;
            tail->setNext(head);
        }
        this->lenght++;

    }
    bool add(E data,int index){
        if (0 <= index && index <= this->lenght){
            if (index == 0){
                addi(data);
            }
            else if (this->lenght == index){
                add(data);
            }
            else{
                Node<E> *previousNode = getNode(index-1);
                Node<E> *insertionNode = new Node<E>(data,previousNode->getNext());
                previousNode->setNext(insertionNode);
                this->lenght++;
            }
            return true;
        }
        else{
            std::cerr << "index out bounds";
            throw index;
            return false;
        }

    }
    bool remove(int index){
        if (0 <= index && index < this->lenght){
            if(this->lenght == 1){
                delete head;
                head = 0;
                tail = 0;
            }
            else if (index == 0){
                Node<E> *deleteNode = head;
                head = head->getNext();
                tail->setNext(head);
                delete deleteNode;
            }
            else if (this->lenght-1 == index){
                Node<E> *deleteNode = tail;
                tail = getNode(index-1);
                tail->setNext(head);
                delete deleteNode;
            }
            else{
                Node<E> *previousNode = getNode(index-1);
                Node<E> *deleteNode = previousNode->getNext();
                previousNode->setNext(deleteNode->getNext());
                delete deleteNode;
            }
            this->lenght--;
            return true;
        }
        else{
            std::cerr << "index out bounds";
            throw index;
            return false;
        }
    }
    void set(int index,E data){
        if (0 <= index && index < this->lenght){
            getNode(index)->setData(data);
        }
        else{
            std::cerr << "index out bounds";
            throw index;

        }
    }


    E get(int index){
        if (0 <= index && index < this->lenght){
            return getNode(index)->getData();
        }
        else{
            std::cerr << "index out bounds";
            throw index;
        }
    }
    //virtual Iterator getIterator() = 0;
    //virtual setComparator(IComparator) = 0;
    //virtual IComparator getComparator() = 0;
    void print() const{
        if (this->lenght > 0){
            Node<E> *actualNode = head;
            std::cout << "[ ";
            for(int actualIndex = 0; actualIndex < this->lenght-1; actualIndex++){
                actualNode->print();
                std::cout << ", ";
                actualNode = actualNode->getNext();
            }
            actualNode->print();
            std::cout << "]" << std::endl;
        }
        else{
            std::cout << "[]" << std::endl;
        }
    }
    virtual ~CircularList(){
        Node<E> *actualNode = head;
        std::cout << "Deleting CircularList...\n";
        while(this->lenght != 0){
            actualNode = head;
            head = head->getNext();
            delete actualNode;
            this->lenght--;
        }
        std::cout << "CircularList deleted!\n";
    }
};

#endif // CIRCULARLIST_H

package homework3_third;
import java.util.AbstractList;
import java.util.List;
/**
 * Custom LinkedList class named LDLinkedList
 * @author Barış Batuhan Bolat
 */
public class LDLinkedList<E> extends AbstractList<E> implements List<E>{
    Node<E> head = null;
    Node<E> tail = null;
    private int size;
    private int sizeDeleted;
    /**
     * Inner class for representing LinkedList nodes
     */
    private class Node<E>{
        E data;
        Node<E> next;
        boolean deleted;
        /**
         * Node class defult constructor
         */
        Node(E data) {
            this.data = data;
            next = null;
            deleted = false;
        }
    }
    /**
     * LDLinkedList default constructor. Calls other constructor with invalid parameters
     */
    public LDLinkedList() {
        this(0);
    }
    /**
     * LDLinkedList constructor.
     */
    public LDLinkedList(int size) {
        this.head = null;
        this.tail = null;
        this.size = size;
        this.sizeDeleted = 0;
    }
    /**
     * @return Integer variable to represent net size of list
     */
    @Override
    public int size() {
       return size - sizeDeleted;
    }
    /**
     * This method returns the data for the given index
     * @return Integer variable to represent the data of given index
     */
    @Override
    public E get(int index) {
        if (index < 0 || index >= size) {
            System.out.println("Index is out of bounds.");
        }

        Node<E> current = head;
        int i = 0;
        while (current != null) {
            if (!current.deleted) {
                if (i == index) {
                    return current.data;
                }
                i++;
            }
            current = current.next;
        }
        throw new IndexOutOfBoundsException();
    }
    /**
     * Appends the specified element to the end of this list.
     * @param data element to be appended to this list
     * @return true if add method works fine
     */
    @Override
    public boolean add(E data){
        Node<E> newNode = new Node<E>(data);
        if(head == null){
            head = newNode;
        }
        else{
            tail.next = newNode;
        }
        ++size;
        tail = newNode;
        return true;
    }
    /**
     * Removes the first occurrence of the specified element from this list
     *
     * @param obj element to be removed from this list, if present
     * @return true if this list contained the specified element
     */
    @Override
    public boolean remove(Object obj){
        int index = indexOf(obj); //O(n)
        if(index == -1){
            return false;
        }
        remove(index); //O(n)
        return true;
    }
    /**
     * Removes the element at the specified position in this list.
     *
     * @param index the index of the element to be removed
     * @return the element previously at the specified position
     */
    @Override
    public E remove(int index){
        if (index < 0 || index >= size) {
            System.out.println("Index is out of bounds.");
        }
        Node<E> current = head;
        Node<E> previous = null;
        for (int i = 0; i < index; i++) {
            previous = current;
            current = current.next;
        }
        current.deleted = true;
        sizeDeleted++;
        if(sizeDeleted == 2){
            removeDeleteds();
        }
        return current.data;
    }
    /**
     * Pyhsically removes the lazy deleted nodes
     */
    public void removeDeleteds(){
        Node<E> current = head;
        Node<E> previous = null;
        while (current != null) {
            if (current.deleted) {
                if (previous == null) {
                    head = current.next;
                } 
                else {
                    previous.next = current.next;
                }
                if (current.next == null) {
                    tail = previous;
                }
                size--;
                sizeDeleted--;
            } 
            else {
                previous = current;
            }
            current = current.next;
        }
    }
    /**
     * Removes all of the elements from this list (optional operation).
     * The list will be empty after this call returns.
     */
    @Override
    public void clear() {
        head = null;
        tail = null;
        size = 0;
        sizeDeleted = 0;
    }
    /**
     * Returns true if this list contains no elements.
     *
     * @return true if this list contains no elements
     */
    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    /**
     * Returns true if this list contains the specified element.
     *
     * @param obj element whose presence in this list is to be tested
     * @return true if this list contains the specified element
     */
    @Override
    public boolean contains(Object obj) {
        Node<E> current = head;
        while (current != null) {
            if (!current.deleted && obj.equals(current.data)) {
                return true;
            }
            current = current.next;
        }
        return false;
    }

}

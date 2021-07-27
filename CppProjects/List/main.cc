//--------------------------------------------
// NAME: Krassen Angelov
// CLASS: XIa
// NUMBER: 14
// PROBLEM: #1
// FILE NAME: main.cc
// FILE PURPOSE:
// The purpose of this file is to make our own List.
//
//---------------------------------------------
#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>
using namespace std;

template<class T> 
class MyList{
	struct Elem{
		T data_;
		Elem* next_;
		Elem* prev_;

		Elem( T val)
		:data_(val),
		 next_(0),
		 prev_(0)
		{}
	};

	Elem* head_;
	Elem* tail_;
	int number_of_elements_;
public:
	// MyIterator
	// Create class MyIterator which will be used
	// to tour the list which has been created.
	class MyIterator{
		Elem* current;
	public:
		MyIterator(Elem* init_loc){
			current = init_loc;
		}
		MyIterator& operator++(); // 1.5
		MyIterator operator++(int); // 1.5
		bool operator==(const MyIterator&) const; // 1.5
		bool operator!=(const MyIterator&) const; // 1.5
		T& operator*(); // 1.5
		T* operator->(); // 1.5
	};
	// ConstMyIterator
	// This is the constant form of the Iterator.
	class ConstMyIterator{
		Elem* current;
	public:
		ConstMyIterator(Elem* init_loc){
			current = init_loc;
 		}
		ConstMyIterator& operator++(); // 1.6
		ConstMyIterator operator++(int); // 1.6
		bool operator==(const ConstMyIterator&) const; // 1.6
		bool operator!=(const ConstMyIterator&) const; // 1.6
		const T& operator*(); // 1.6
		const T* operator->(); // 1.6
	};

	// ReverseMyIterator
	// This is the reversed form of the Iterator.
	// From the end to the beginning of the list.
	class ReverseMyIterator{
		Elem* current;
	public:
		ReverseMyIterator(Elem* init_loc){
			current = init_loc;
		}
		ReverseMyIterator& operator++(); // 1.6
		ReverseMyIterator operator++(int); // 1.6
		bool operator==(const ReverseMyIterator&) const; // 1.6
		bool operator!=(const ReverseMyIterator&) const; // 1.6
		T& operator*(); // 1.6
		T* operator->(); // 1.6
	};

	// ConstReverseMyIterator
	// This is constant and reversed form of the Iterator.
	class ConstReverseMyIterator{
		Elem* current;
	public:
		ConstReverseMyIterator(Elem* init_loc){
			current = init_loc;
		}
		ConstReverseMyIterator& operator++(); // 1.6
		ConstReverseMyIterator operator++(int); // 1.6
		bool operator==(const ConstReverseMyIterator&) const; // 1.6
		bool operator!=(const ConstReverseMyIterator&) const; // 1.6
		const T& operator*(); // 1.6
		const T* operator->(); // 1.6
	};

	MyList(); // 1.1
	MyList(const MyList&); // 1.4
	~MyList(); // 1.1
	MyList& operator=(const MyList& other); // 1.4

	void print(); // It's mine func!

	void push_back(const T&); // 1.2
	void pop_back(); // 1.2
	void push_front(const T&); // 1.2
	void pop_front(); // 1.2
	T& front(); // 1.2
	const T& front() const; // 1.2
	T& back(); // 1.2
	const T& back() const; // 1.2

	int size() const; // 1.3
	bool empty() const; // 1.3
	void clear(); // 1.3 // ne moje da se dobavq sled kato se izpolzva
	void swap(MyList&); // 1.3 // ne e napraven

	MyIterator begin(); // 1.5
	MyIterator end(); // 1.5
	
	ConstMyIterator begin() const; // 1.6
	ConstMyIterator end() const; // 1.6

	ReverseMyIterator rbegin(); // 1.6
	ReverseMyIterator rend(); // 1.6

	ConstReverseMyIterator rbegin() const; // 1.6
	ConstReverseMyIterator rend() const; // 1.6

	MyIterator insert(MyIterator, const T&); // 1.7
	MyIterator erase(MyIterator&); // 1.7
	MyIterator erase(MyIterator&, MyIterator&); // 1.7
};

//----------------------------------------------
//MyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5 This is Prefix ++
typename MyList<T>::MyIterator&
MyList<T>::MyIterator::operator++(){
	current = current->next_;
	return *this; 
}

//--------------------------------------------
// FUNCTION: operator++
// This is Postfix ++.
// PARAMETERS:
// int param
// - param: The place where the iterator is.
//----------------------------------------------
template<class T> // 1.5 This is Postfix ++
typename MyList<T>::MyIterator
MyList<T>::MyIterator::operator++(int param){
	MyList<T>::MyIterator miter(current);
	++(*this);
	return miter;
}

//--------------------------------------------
// FUNCTION: operator==
// Operator for comparison.
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.5
bool
MyList<T>::MyIterator::operator==(const MyIterator& itera) const{
	return current == itera.current;
}

//--------------------------------------------
// FUNCTION: operator!=
// Operator for comparison(negative).
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.5
bool
MyList<T>::MyIterator::operator!=(const MyIterator& itera) const{
	return current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
T&
MyList<T>::MyIterator::operator*(){
	return current->data_;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
T*
MyList<T>::MyIterator::operator->(){
	return &(current->data_);
}

//------------------------------------------------
// ConstMyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6 This is Prefix ++
typename MyList<T>::ConstMyIterator&
MyList<T>::ConstMyIterator::operator++(){
	current = current->next_;
	return *this;
}

//--------------------------------------------
// FUNCTION: operator++
// This is Postfix ++.
// PARAMETERS:
// int param
// - param: The place where the iterator is.
//----------------------------------------------
template<class T> // 1.6 This is Postfix ++
typename MyList<T>::ConstMyIterator
MyList<T>::ConstMyIterator::operator++(int param){
	MyList<T>::ConstMyIterator miter(current);
	++(*this);
	return miter;
}

//--------------------------------------------
// FUNCTION: operator==
// Operator for comparison.
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.6
bool
MyList<T>::ConstMyIterator::operator==(const ConstMyIterator& itera) const{
	return current == itera.current;
}

//--------------------------------------------
// FUNCTION: operator!=
// Operator for comparison(negative).
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.6
bool
MyList<T>::ConstMyIterator::operator!=(const ConstMyIterator& itera) const{
	return current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the constant value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
const T&
MyList<T>::ConstMyIterator::operator*(){
	return current->data_;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the constant address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
const T*
MyList<T>::ConstMyIterator::operator->(){
	return &(current->data_);
}

//----------------------------------------------
// ReverseMyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6 This is Prefix ++
typename MyList<T>::ReverseMyIterator&
MyList<T>::ReverseMyIterator::operator++(){
	current = current->prev_;
	return *this;
}

//--------------------------------------------
// FUNCTION: operator++
// This is Postfix ++.
// PARAMETERS:
// int param
// - param: The place where the iterator is.
//----------------------------------------------
template<class T> // 1.6 This is Postfix ++
typename MyList<T>::ReverseMyIterator
MyList<T>::ReverseMyIterator::operator++(int param){
	MyList<T>::ReverseMyIterator miter(current);
	--(*this);
	return miter;
}

//--------------------------------------------
// FUNCTION: operator==
// Operator for comparison.
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.6
bool
MyList<T>::ReverseMyIterator::operator==(const ReverseMyIterator& itera) const{
	return current == itera.current;
}

//--------------------------------------------
// FUNCTION: operator!=
// Operator for comparison(negative).
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.6
bool
MyList<T>::ReverseMyIterator::operator!=(const ReverseMyIterator& itera) const{
	return current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
T&
MyList<T>::ReverseMyIterator::operator*(){
	return current->data_;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
T*
MyList<T>::ReverseMyIterator::operator->(){
	return &(current->data_);
}

//------------------------------------------------
// ConstReverseMyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6 This is Prefix ++
typename MyList<T>::ConstReverseMyIterator&
MyList<T>::ConstReverseMyIterator::operator++(){
	current = current->prev_;
	return *this;
}

//--------------------------------------------
// FUNCTION: operator++
// This is Postfix ++.
// PARAMETERS:
// int param
// - param: The place where the iterator is.
//----------------------------------------------
template<class T> // 1.6 This is Postfix ++
typename MyList<T>::ConstReverseMyIterator
MyList<T>::ConstReverseMyIterator::operator++(int param){
	MyList<T>::ConstReverseMyIterator miter(current);
	--(*this);
	return miter;
}

//--------------------------------------------
// FUNCTION: operator==
// Operator for comparison.
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.6
bool
MyList<T>::ConstReverseMyIterator::operator==(const ConstReverseMyIterator& itera) const{
	return current == itera.current;
}

//--------------------------------------------
// FUNCTION: operator!=
// Operator for comparison(negaive).
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.6
bool
MyList<T>::ConstReverseMyIterator::operator!=(const ConstReverseMyIterator& itera) const{
	return current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the constant value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
const T&
MyList<T>::ConstReverseMyIterator::operator*(){
	return current->data_;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the constant address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
const T*
MyList<T>::ConstReverseMyIterator::operator->(){
	return &(current->data_);
}

//----------------------------------------------------
// MyIterator begin, end

//--------------------------------------------
// FUNCTION: begin
// Returns the address of the first element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
typename MyList<T>::MyIterator
MyList<T>::begin(){ // 1.5
	return MyIterator(head_);
}
//--------------------------------------------
// FUNCTION: end
// Returns the address of the last element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
typename MyList<T>::MyIterator
MyList<T>::end(){ // 1.5
	return MyIterator(tail_->next_);
}

//-----------------------------------------------------
// ConstMyIterator begin, end - const

//--------------------------------------------
// FUNCTION: begin
// Returns the address of the first element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
typename MyList<T>::ConstMyIterator
MyList<T>::begin() const{ // 1.6
	return ConstMyIterator(head_);
}

//--------------------------------------------
// FUNCTION: end
// Returns the address of the last element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
typename MyList<T>::ConstMyIterator
MyList<T>::end() const{ // 1.6
	return ConstMyIterator(tail_->next_);
}

//-----------------------------------------------------
// ReverseMyIterator rbegin, rend

//--------------------------------------------
// FUNCTION: rbegin
// Returns the address of the last element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
typename MyList<T>::ReverseMyIterator
MyList<T>::rbegin(){ // 1.6
	return ReverseMyIterator(tail_->next_);
}

//--------------------------------------------
// FUNCTION: rend
// Returns the address of the first element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
typename MyList<T>::ReverseMyIterator
MyList<T>::rend(){ // 1.6
	return ReverseMyIterator(head_);
}

//------------------------------------------------------
// ConstReverseMyIterator rbegin, rend - const

//--------------------------------------------
// FUNCTION: rbegin
// Returns the address of the last element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
typename MyList<T>::ConstReverseMyIterator
MyList<T>::rbegin() const{ // 1.6
	return ConstReverseMyIterator(tail_->next_);
}

//--------------------------------------------
// FUNCTION: rend
// Returns the address of the first element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
typename MyList<T>::ConstReverseMyIterator
MyList<T>::rend() const{ // 1.6
	return ConstReverseMyIterator(head_);
}
//------------------------------------------------------

//--------------------------------------------
// FUNCTION: MyList
// Constructor of the list (MyList).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.1
MyList<T>::MyList()
:head_(NULL),
 tail_(NULL),
 number_of_elements_(0)
{}

//--------------------------------------------
// FUNCTION: MyList
// Copy constructor.
// PARAMETERS:
// const MyList& other
// - other: the list which will be copied.
//----------------------------------------------
template<class T> // 1.4
MyList<T>::MyList(const MyList& other){
	head_ = other.head_;
	tail_ = other.tail_;
}

//--------------------------------------------
// FUNCTION: operator=
// Assignment operator.
// PARAMETERS:
// const MyList& other
// - other: the list which we assign.
//----------------------------------------------
template<class T> // 1.4
MyList<T>& MyList<T>::operator=(const MyList& other){
	other.swap(*this);
	return *this;
}

//--------------------------------------------
// FUNCTION: ~MyList
// Deconstructor of the list (MyList).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.1
MyList<T>::~MyList(){
	clear();
}

//--------------------------------------------
// FUNCTION: push_back
// Adds new element after the last element of the list.
// PARAMETERS:
// const T& element
// - element: this is the element, which is added to the end of the list.
//----------------------------------------------
template<class T> // 1.2
void MyList<T>::push_back(const T& element){
	
	Elem* new_elem = new Elem(element);

	if(empty()){
		head_ = new_elem;
		tail_ = new_elem;	
	}
	else{
		new_elem->prev_ = tail_;
		tail_->next_ = new_elem;
		tail_ = new_elem;
		tail_->next_ = NULL;
	}

	number_of_elements_++;
}

//--------------------------------------------
// FUNCTION: pop_back
// Delete the last element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.2
void MyList<T>::pop_back(){
	if(empty()){
		throw exception();
	}
	else if(head_ != NULL && head_ == tail_){
		head_ = NULL;
		tail_ = NULL;
		number_of_elements_--;		
	}
	else{
		Elem* back = tail_;
		Elem* new_back = back->prev_;
		
		new_back->next_= NULL;
		tail_ = new_back;

		delete back;
		number_of_elements_--;
	}
}

//--------------------------------------------
// FUNCTION: push_front
// Adds new element after the first element of the list.
// PARAMETERS:
// const T& element
// - element: this is the element, which is added to the beginning of the list.
//----------------------------------------------
template<class T> // 1.2
void MyList<T>::push_front(const T& element){
	Elem* new_elem = new Elem(element);

	if(empty()){
		head_ = new_elem;
		tail_ = new_elem;	
	}
	else{
		new_elem->next_ = head_;
		head_->prev_ = new_elem;
		head_ = new_elem;
		head_->prev_ = NULL;
	}

	number_of_elements_++;	
}

//--------------------------------------------
// FUNCTION: pop_front
// Delete the first element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.2
void MyList<T>::pop_front(){
	if(empty()){
		throw exception();
	}
	else if(head_ != NULL && head_ == tail_){
		head_ = NULL;
		tail_ = NULL;
		number_of_elements_--;		
	}
	else{
		Elem* front = head_;
		Elem* new_front = front->next_;
		
		new_front->prev_= NULL;
		head_ = new_front;

		delete front;
		number_of_elements_--;
	}
}

//--------------------------------------------
// FUNCTION: print
// Print all elements from the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // It's mine func!
void MyList<T>::print(){
	Elem* temp = head_;

	while(temp != NULL){
		cout << temp->data_ << " ";
		temp = temp->next_;
	}
	cout << endl;
}

//--------------------------------------------
// FUNCTION: front
// Returns a reference to the first element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.2
T& MyList<T>::front(){
	if(empty()){
		throw exception();
	}
	return head_->data_;
}

//--------------------------------------------
// FUNCTION: front
// Returns a constant reference to the first element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.2
const T& MyList<T>::front() const{
	if(empty()){
		throw exception();
	}
	return head_->data_;
}

//--------------------------------------------
// FUNCTION: back
// Returns a reference to the last element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.2
T& MyList<T>::back(){
	if(empty()){
		throw exception();
	}
	return tail_->data_;
}

//--------------------------------------------
// FUNCTION: back
// Returns a constant reference to the last element of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.2
const T& MyList<T>::back() const{
	if(empty()){
		throw exception();
	}
	return tail_->data_;
}

//--------------------------------------------
// FUNCTION: size
// Returns the size of the list (the number of elements in the list).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.3
int MyList<T>::size() const{
	return number_of_elements_;
}

//--------------------------------------------
// FUNCTION: empty
// Returns true, if the list is empty (i.e. number_of_elements_ == 0).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.3
bool MyList<T>::empty() const{
	if(number_of_elements_==0)
		return true;
	else
		return false;
}

//--------------------------------------------
// FUNCTION: clean
// Delete all of the elements of the list.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.3 
void MyList<T>::clear(){
	Elem *temp = head_;

    while (temp != NULL) {
        head_ = head_->next_;
        delete temp;
        temp = head_;
    }
    head_ = NULL; 
    tail_ = NULL;
}

//--------------------------------------------
// FUNCTION: swap
// Swapping two lists.
// PARAMETERS:
// MyList& other
//  - other: the list which will be swapped with our list.   
//----------------------------------------------
template<class T> // 1.4
void MyList<T>::swap(MyList& other){
	std::swap(other.tail_, tail_);
	std::swap(other.head_, head_);
}

//--------------------------------------------
// FUNCTION: insert
// Insert a new element in the list, before the item for which it is directed
// iterator pos.
// PARAMETERS:
// MyIterator pos, const T& element
// - pos: serves to indicate where it is directed iterator.
// - element: the element that adds to the list.
//----------------------------------------------
template<class T> // 1.7
typename MyList<T>::MyIterator 
MyList<T>::insert(MyIterator pos, const T& x){
	Elem* new_elem = new Elem(x);
	if(empty()){
		head_ = new_elem;
		tail_ = new_elem;	
	}  
	else{
		
		Elem* after = pos.current;
		Elem* before = after->prev_;  
		new_elem->prev_ = before;
		new_elem->next_ = after;

		number_of_elements_++;
		return MyIterator(new_elem);
	}
}

int main(int argc, char *argv[]) {

  MyList<int> l1;
  MyList<int> l2;

  int first_argv;
  first_argv = atoi(argv[1]);
  int second_argv;
  second_argv = atoi(argv[2]);
  int third_argv;
  third_argv = atoi(argv[3]);
  int fourth_argv;
  fourth_argv = atoi(argv[4]);

  for(int element = first_argv; element < second_argv; element++)
    l1.push_back(element);

  for(int element = third_argv; element < fourth_argv; element++)
    l2.push_back(element);

  // 1.8.2
  cout << "l1: {";
  for(MyList<int>::MyIterator iter = l1.begin(); iter != l1.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  cout << "l2: {";
  for(MyList<int>::MyIterator iter = l2.begin(); iter != l2.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  // 1.8.3
  int equal = 0;
  for(MyList<int>::MyIterator iter1 = l1.begin(); iter1 != l1.end(); ++iter1)
    for(MyList<int>::MyIterator iter2 = l2.begin(); iter2 != l2.end(); ++iter2)
      if(*iter1 == *iter2)
        equal++;

  cout << "equal element in l1 and l2: " << equal << endl;

  // 1.8.4
  l1.push_back(-100);
  l2.push_back(-100);

  cout << "l1: {";
  for(MyList<int>::MyIterator iter = l1.begin(); iter != l1.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  cout << "l2: {";
  for(MyList<int>::MyIterator iter = l2.begin(); iter != l2.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  // 1.8.5
  MyList<int> l(l2);
  cout << "l: {";
  for(MyList<int>::MyIterator iter = l.begin(); iter != l.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  return 0;
}

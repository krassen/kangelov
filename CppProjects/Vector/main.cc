//--------------------------------------------
// NAME: Krassen Angelov
// CLASS: XIa
// NUMBER: 14
// PROBLEM: #1
// FILE NAME: main.cc
// FILE PURPOSE:
// The purpose of this file is to make our own Vector.
//
//---------------------------------------------
#include <iostream>
#include <cstdlib>
using namespace std;

// Create class MyVector
template<class T>
class MyVector{
  int capacity_;
  int size_;
  T* buffer_;

public:

  // MyIterator
  // Create class MyIterator which will be used
  // to tour the Vector which has been created.
  class MyIterator{
    T* current;
  public:
    MyIterator(T* init_loc){
      current = init_loc;
    }
    MyIterator& operator++(); // 1.4
    MyIterator operator++(int); // 1.4
    bool operator==(const MyIterator&) const; // 1.4
    bool operator!=(const MyIterator&) const; // 1.4
    T& operator*(); // 1.4
    T* operator->(); // 1.4
  };
  // ConstMyIterator
  // This is the constant form of the Iterator.
  class ConstMyIterator{
    T* current;
  public:
    ConstMyIterator(T* init_loc){
      current = init_loc;
    }
    ConstMyIterator& operator++(); // 1.4
    ConstMyIterator operator++(int); // 1.4
    bool operator==(const ConstMyIterator&) const; // 1.4
    bool operator!=(const ConstMyIterator&) const; // 1.4
    const T& operator*(); // 1.5
    const T* operator->(); // 1.5
  };

  // ReverseMyIterator
  // This is the reversed form of the Iterator.
  // From the end to the beginning of the Vector.
  class ReverseMyIterator{
    T* current;
  public:
    ReverseMyIterator(T* init_loc){
      current = init_loc;
    }
    ReverseMyIterator& operator++(); // 1.4
    ReverseMyIterator operator++(int); // 1.4
    bool operator==(const ReverseMyIterator&) const; // 1.4
    bool operator!=(const ReverseMyIterator&) const; // 1.4
    T& operator*(); // 1.4
    T* operator->(); // 1.4
  };

  // ConstReverseMyIterator
  // This is constant and reversed form of the Iterator.
  class ConstReverseMyIterator{
    T* current;
  public:
    ConstReverseMyIterator(T* init_loc){
      current = init_loc;
    }
    ConstReverseMyIterator& operator++(); // 1.4
    ConstReverseMyIterator operator++(int); // 1.4
    bool operator==(const ConstReverseMyIterator&) const; // 1.4
    bool operator!=(const ConstReverseMyIterator&) const; // 1.4
    const T& operator*(); // 1.5
    const T* operator->(); // 1.5
  };

  MyVector(int capacity_ = 20); // 1.1
  MyVector(const MyVector&); //copy constructor 1.3
  ~MyVector(); // 1.1
  MyVector& operator=(const MyVector&); // 1.3
  int size() const; // 1.2
  bool empty() const; // 1.2
  T& operator[](int); // 1.2
  const T& operator[](int) const; // 1.2
  void clear(); // 1.2
  void alloc_new(); // new
  int capacity() const; // 1.2
  T& front(); // 1.6
  const T& front() const; // 1.6
  T& back(); // 1.6
  const T& back() const; // 1.6
  void push_back(const T&); // 1.6
  void pop_back(); // 1.6

  MyIterator begin(); // 1.4
  MyIterator end(); // 1.4

  ConstMyIterator begin() const; // 1.5
  ConstMyIterator end() const; // 1.5

  ReverseMyIterator rbegin(); // 1.5
  ReverseMyIterator rend(); // 1.5

  ConstReverseMyIterator rbegin() const; // 1.5
  ConstReverseMyIterator rend() const; // 1.5

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
template<class T> // 1.4 This is Prefix ++
typename MyVector<T>::MyIterator&
MyVector<T>::MyIterator::operator++(){
  current++;
  return *this;
}

//--------------------------------------------
// FUNCTION: operator++
// This is Postfix ++.
// PARAMETERS:
// int param
// - param: The place where the iterator is.
//----------------------------------------------
template<class T> // 1.4 This is Postfix ++
typename MyVector<T>::MyIterator
MyVector<T>::MyIterator::operator++(int param){
  MyVector<T>::MyIterator miter(current);
  current++;
  return miter;
}

//--------------------------------------------
// FUNCTION: operator==
// Operator for comparison.
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.4
bool
MyVector<T>::MyIterator::operator==(const MyIterator& itera) const{
  return this->current == itera.current;
}

//--------------------------------------------
// FUNCTION: operator!=
// Operator for comparison(negative).
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.4
bool
MyVector<T>::MyIterator::operator!=(const MyIterator& itera) const{
  return this->current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.4
T&
MyVector<T>::MyIterator::operator*(){
  return *current;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T>
T*
MyVector<T>::MyIterator::operator->(){
  return &current;
}

//------------------------------------------------
// ConstMyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5 This is Prefix ++
typename MyVector<T>::ConstMyIterator&
MyVector<T>::ConstMyIterator::operator++(){
  current++;
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
typename MyVector<T>::ConstMyIterator
MyVector<T>::ConstMyIterator::operator++(int param){
  MyVector<T>::ConstMyIterator miter(current);
  current++;
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
MyVector<T>::ConstMyIterator::operator==(const ConstMyIterator& itera) const{
  return this->current == itera.current;
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
MyVector<T>::ConstMyIterator::operator!=(const ConstMyIterator& itera) const{
  return this->current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the constant value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
const T&
MyVector<T>::ConstMyIterator::operator*(){
  return *current;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the constant address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
const T*
MyVector<T>::ConstMyIterator::operator->(){
  return &current;
}

//----------------------------------------------
// ReverseMyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5 This is Prefix ++
typename MyVector<T>::ReverseMyIterator&
MyVector<T>::ReverseMyIterator::operator++(){
  current--;
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
typename MyVector<T>::ReverseMyIterator
MyVector<T>::ReverseMyIterator::operator++(int param){
  MyVector<T>::ReverseMyIterator miter(current);
  current++;
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
MyVector<T>::ReverseMyIterator::operator==(const ReverseMyIterator& itera) const{
  return this->current == itera.current;
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
MyVector<T>::ReverseMyIterator::operator!=(const ReverseMyIterator& itera) const{
  return this->current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
T&
MyVector<T>::ReverseMyIterator::operator*(){
  return *current;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
T*
MyVector<T>::ReverseMyIterator::operator->(){
  return &current;
}

//------------------------------------------------
// ConstReverseMyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5 This is Prefix ++
typename MyVector<T>::ConstReverseMyIterator&
MyVector<T>::ConstReverseMyIterator::operator++(){
  current--;
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
typename MyVector<T>::ConstReverseMyIterator
MyVector<T>::ConstReverseMyIterator::operator++(int param){
  MyVector<T>::ConstReverseMyIterator miter(current);
  current++;
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
MyVector<T>::ConstReverseMyIterator::operator==(const ConstReverseMyIterator& itera) const{
  return this->current == itera.current;
}

//--------------------------------------------
// FUNCTION: operator!=
// Operator for comparison(negaive).
// PARAMETERS:
// const MyIterator& itera
// - itera: Compare the iterator with it.
//----------------------------------------------
template<class T> // 1.5
bool
MyVector<T>::ConstReverseMyIterator::operator!=(const ConstReverseMyIterator& itera) const{
  return this->current != itera.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the constant value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
const T&
MyVector<T>::ConstReverseMyIterator::operator*(){
  return *current;
}

//--------------------------------------------
// FUNCTION: operator->
// The operator serves to take the constant address of the iterator.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
const T*
MyVector<T>::ConstReverseMyIterator::operator->(){
  return &current;
}

//----------------------------------------------------
// MyIterator begin, end

//--------------------------------------------
// FUNCTION: begin
// Returns the address of the first element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.4
typename MyVector<T>::MyIterator
MyVector<T>::begin(){ // 1.4
  return MyIterator(buffer_);
}
//--------------------------------------------
// FUNCTION: end
// Returns the address of the "last element + 1" of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.4
typename MyVector<T>::MyIterator
MyVector<T>::end(){ // 1.4
  return MyIterator(buffer_ + size_);
}

//-----------------------------------------------------
// ConstMyIterator begin, end - const

//--------------------------------------------
// FUNCTION: begin
// Returns the address of the first element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
typename MyVector<T>::ConstMyIterator
MyVector<T>::begin() const{ // 1.5
  return ConstMyIterator(buffer_);
}

//--------------------------------------------
// FUNCTION: end
// Returns the address of the "last element + 1" of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
typename MyVector<T>::ConstMyIterator
MyVector<T>::end() const{ // 1.5
  return ConstMyIterator(buffer_ + size_);
}

//-----------------------------------------------------
// ReverseMyIterator rbegin, rend

//--------------------------------------------
// FUNCTION: rbegin
// Returns the address of the last element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
typename MyVector<T>::ReverseMyIterator
MyVector<T>::rbegin(){ // 1.5
  return ReverseMyIterator(buffer_ + size_ - 1);
}

//--------------------------------------------
// FUNCTION: rend
// Returns the address of the "first element - 1" of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.4
typename MyVector<T>::ReverseMyIterator
MyVector<T>::rend(){ // 1.4
  return ReverseMyIterator(buffer_ - 1);
}

//------------------------------------------------------
// ConstReverseMyIterator rbegin, rend - const

//--------------------------------------------
// FUNCTION: rbegin
// Returns the address of the last element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
typename MyVector<T>::ConstReverseMyIterator
MyVector<T>::rbegin() const{ // 1.5
  return ConstReverseMyIterator(buffer_ + size_ - 1);
}

//--------------------------------------------
// FUNCTION: rend
// Returns the address of the "first element - 1" of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.5
typename MyVector<T>::ConstReverseMyIterator
MyVector<T>::rend() const{ // 1.4
  return ConstReverseMyIterator(buffer_ - 1);
}
//------------------------------------------------------

//--------------------------------------------
// FUNCTION: insert
// Insert a new element in the vector, before the item for which it is directed
// iterator pos.
// PARAMETERS:
// MyIterator pos, const T& element
// - pos: serves to indicate where it is directed iterator.
// - element: the element that adds to the vector.
//----------------------------------------------
template<class T> // 1.7
typename MyVector<T>::MyIterator
MyVector<T>::insert(MyIterator pos, const T& element){
MyVector<T> vec;
MyVector<T>::MyIterator iter = vec.begin();

if(size_ + 1 == capacity_){
  alloc_new();
}

for(MyVector<T>::MyIterator it = begin(); it!=end(); it++){
  if(vec.size_ + 1 == vec.capacity_){
    vec.alloc_new();
  }
  if(it == pos){
    vec.push_back(element);
    iter = it;
  }
  vec.push_back(*it);
}
if(pos == end())
  vec.push_back(element);

capacity_ = vec.capacity();
size_ = vec.size();

for(int i=0; i<size_; ++i) {
  buffer_[i] = vec.buffer_[i];
}
return iter;
}

//--------------------------------------------
// FUNCTION: erase
// Erase a element in the vector, where the iterator is directed.
// PARAMETERS:
// MyIterator &pos
// - pos: serves to indicate where it is directed iterator.
//----------------------------------------------
template<class T> // 1.7
typename MyVector<T>::MyIterator
MyVector<T>::erase(MyIterator &pos){
	MyIterator miter = pos;
	while(miter != end()){
		miter++;
	}
	size_--;
	return miter;
}

//--------------------------------------------
// FUNCTION: erase
// Erase the elements between 'iterator first' and 'iterator second' in the vector.
// PARAMETERS:
// MyIterator &first, MyIterator &second
// - first: start iterator.
// - second: end iterator.
//----------------------------------------------
template<class T> // 1.7
typename MyVector<T>::MyIterator
MyVector<T>::erase(MyIterator &first, MyIterator &last){
  int cheker = 0;
  MyIterator miter = first;
  while(first != last){
    first++;
    size_--;
  }
}
//------------------------------------------------------

//--------------------------------------------
// FUNCTION: MyVector
// Constructor of the vector (MyVector).
// PARAMETERS:
// int capacity
// - capacity: serves to determine the capacity of the vector.
//----------------------------------------------
template<class T> // OK 1.2
MyVector<T>::MyVector(int capacity)
: capacity_(capacity),
  size_(0),
  buffer_(new T[capacity])
{}

//--------------------------------------------
// FUNCTION: MyVector
// Copy constructor.
// PARAMETERS:
// const MyVector& other
// - other: the vector which will be copied.
//----------------------------------------------
template<class T> // OK 1.3
MyVector<T>::MyVector(const MyVector& other){
  capacity_ = other.capacity_;
  size_ = other.size_;
  buffer_ = new T[capacity_];
  for(int i=0; i<=capacity_; i++)
    buffer_[i] = other.buffer_[i];
}

//--------------------------------------------
// FUNCTION: ~MyVector
// Deconstructor of the vector (MyVector).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // OK 1.2
MyVector<T>::~MyVector(){
  delete [] buffer_;
}

//--------------------------------------------
// FUNCTION: operator=
// Assignment operator.
// PARAMETERS:
// const MyVector& other
// - other: the vector which we assign.
//----------------------------------------------
template<class T> // OK 1.3
MyVector<T>& MyVector<T>::operator=(const MyVector& other){
  // a=a; this and other are the same object
  if(this != &other) {
    delete [] buffer_;
    capacity_ = other.capacity_;
		size_ = other.size_;
		buffer_ = new T[capacity_];
		for(int i=0; i<=capacity_; i++)
			buffer_[i] = other.buffer_[i];
  }
	 return *this;
}

//--------------------------------------------
// FUNCTION: size
// Returns the size of the vector (the number of elements in the vector).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // OK 1.2
int MyVector<T>::size() const{
  return size_;
}

//--------------------------------------------
// FUNCTION: empty
// Returns true, if the vector is empty (i.e. size () == 0).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // OK 1.2
bool MyVector<T>::empty() const{
  if(size() == 0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: operator[]
// Returns a reference to the n-th element of the vector (the element with index n).
// PARAMETERS:
// int n
// - n: the element which value we want to know.
//----------------------------------------------
template<class T> // OK 1.2
T& MyVector<T>::operator[](int n){
  //cout << "non-const" << endl;
  return buffer_[n];
}

//--------------------------------------------
// FUNCTION: operator[]
// Returns a constant reference to the n-th element of the vector (the element with index n).
// PARAMETERS:
// int n
// - n: the element which value we want to know.
//----------------------------------------------
template<class T> // Maybe OK 1.2
const T& MyVector<T>::operator[](int n) const{
  //cout << "const" << endl;
  return buffer_[n];
}

//--------------------------------------------
// FUNCTION: clean
// Delete all of the elements of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // OK 1.2
void MyVector<T>::clear(){
  size_ = 0;
}

//--------------------------------------------
// FUNCTION: capacity
// Returns the number of items for which it is allocated memory. The method capacity()
// always returns a value that is greater than or equal to the size().
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // OK 1.2
int MyVector<T>::capacity() const{
  return capacity_;
}

//-------------------------------------

//--------------------------------------------
// FUNCTION: alloc_new
// When the vector is filled it allocates double more
// memory for the new buffer(buffer_).
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // mine
void MyVector<T>::alloc_new(){
  capacity_ = 2*size_;
  T* tmp = new T[capacity_];
  for(int i=0; i<size_; i++)
    tmp[i] = buffer_[i];
  delete [] buffer_;
  buffer_ = tmp;
}

//--------------------------------------------
// FUNCTION: front
// Returns a reference to the first element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
T& MyVector<T>::front(){
  return buffer_[0];
}

//--------------------------------------------
// FUNCTION: front
// Returns a constant reference to the first element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
const T& MyVector<T>::front() const{
  return buffer_[0];
}

//--------------------------------------------
// FUNCTION: back
// Returns a reference to the last element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
T& MyVector<T>::back(){
  return buffer_[size_-1];
}

//--------------------------------------------
// FUNCTION: back
// Returns a constant reference to the last element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
const T& MyVector<T>::back() const{
  return buffer_[size_-1];
}

//--------------------------------------------
// FUNCTION: push_back
// Adds new element after the last element of the vector.
// PARAMETERS:
// const T& element
// - element: this is the element, which is added to the end of the vector.
//----------------------------------------------
template<class T> // 1.6 no gi napisah v 1.4 oshte
void MyVector<T>::push_back(const T& element){
  if(size_+1>capacity_)
    alloc_new();
  buffer_[size_] = element;
  size_++;
}

//--------------------------------------------
// FUNCTION: pop_back
// Delete the last element of the vector.
// PARAMETERS:
// Not
//----------------------------------------------
template<class T> // 1.6
void MyVector<T>::pop_back(){
  --size_;
}

//--------------

int main(int argc, char *argv[]) {

  // cout << "Have " << argc << " arguments:" << endl;
  // for (int i = 0; i < argc; ++i) {
  //     cout << argv[i] << endl;
  // }
  // 1.8.1
  MyVector<int> v1;
  MyVector<int> v2;

  int first_argv;
  first_argv = atoi(argv[1]);
  int second_argv;
  second_argv = atoi(argv[2]);
  int third_argv;
  third_argv = atoi(argv[3]);
  int fourth_argv;
  fourth_argv = atoi(argv[4]);

  for(int element = first_argv; element < second_argv; element++)
    v1.push_back(element);

  for(int element = third_argv; element < fourth_argv; element++)
    v2.push_back(element);

  // 1.8.2
  cout << "v1: {";
  for(MyVector<int>::MyIterator iter = v1.begin(); iter != v1.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  cout << "v2: {";
  for(MyVector<int>::MyIterator iter = v2.begin(); iter != v2.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  // 1.8.3
  int equal = 0;
  for(MyVector<int>::MyIterator iter1 = v1.begin(); iter1 != v1.end(); ++iter1)
    for(MyVector<int>::MyIterator iter2 = v2.begin(); iter2 != v2.end(); ++iter2)
      if(*iter1 == *iter2)
        equal++;

  cout << "equal element in v1 and v2: " << equal << endl;

  // 1.8.4
  v1.push_back(-100);
  v2.push_back(-100);

  cout << "v1: {";
  for(MyVector<int>::MyIterator iter = v1.begin(); iter != v1.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  cout << "v2: {";
  for(MyVector<int>::MyIterator iter = v2.begin(); iter != v2.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  // 1.8.5
  MyVector<int> v(v2);
  cout << "v: {";
  for(MyVector<int>::MyIterator iter = v.begin(); iter != v.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  // 1.8.6
  MyVector<int>::MyIterator it = v.begin();
  for(MyVector<int>::ReverseMyIterator iter = v1.rbegin(); iter != v1.rend(); ++iter)
    //cout << *iter << " ";
    v.insert(it, *iter);
  //cout << endl;

  cout << "v: {";
  for(MyVector<int>::MyIterator iter = v.begin(); iter != v.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;

  // 1.8.7
  MyVector<int>::MyIterator bit = v.begin();
  int cheker = 0;

  while(bit != v.end()){
    if(*bit == -100)
      cheker = 1;
    if(cheker == 1)
      v.erase(bit);
    if(cheker == 0)
      bit++;
  }

  cout << "v: {";
  for(MyVector<int>::MyIterator iter = v.begin(); iter != v.end(); ++iter)
    cout << *iter << ",";
  cout << "}" << endl;


  return 0;
}

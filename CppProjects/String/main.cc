//--------------------------------------------
// NAME: Krassen Angelov
// CLASS: XIa
// NUMBER: 14
// PROBLEM: #1
// FILE NAME: main.cc
// FILE PURPOSE:
// The purpose of this file is to make our own String.
//
//---------------------------------------------
#include <iostream>
#include <string.h>
#include <exception>

using namespace std;

// Create class MyString
class MyString {
  int capacity_;
  int size_;
  char* buffer_;
  friend ostream& operator<<(ostream& out, const MyString& str);
public:

  // MyIterator
  // Create class MyIterator which will be used
  // to tour the String which has been created.
  class MyIterator{
    char *current;
  public:
  	MyIterator(char *other)
  	: current(other)
  	{}
    MyIterator& operator++(); // 1.4
    MyIterator operator++(int); // 1.4
    bool operator==(const MyIterator&) const; // 1.4
    bool operator!=(const MyIterator&) const; // 1.4
    char& operator*(); // 1.4
  };

  MyString(int capacit); // 1.1
  MyString(const char* str); // 1.1
  ~MyString(); // 1.1

  MyString(const MyString&); //copy constructor 1.3
  MyString& operator=(const MyString&); // 1.3

  int size() const; // 1.2
  int length() const; // 1.2
  int capacity() const; // 1.2
  bool empty() const; // 1.2
  void clear(); // 1.2
  char& operator[](int); // 1.2
  char& at(int); // 1.2

  bool operator==(const MyString&); // 1.2
  bool operator!=(const MyString&); // 1.2

  bool operator<(const MyString&); // 1.2
  bool operator>(const MyString&); // 1.2

  bool operator<=(const MyString&); // 1.2
  bool operator>=(const MyString&); // 1.2

  MyString& append(const MyString&); // 1.5
  MyString& operator+=(const MyString&); // 1.5
  void push_back(char); // 1.5
  MyString operator+(const MyString&); // 1.5

  MyIterator begin(); // 1.4
  MyIterator end(); // 1.4

};

//----------------------------------------------
//MyIterator
//--------------------------------------------
// FUNCTION: operator++
// This is Prefix ++.
// PARAMETERS:
// Not
//----------------------------------------------
// 1.4
MyString::MyIterator&
MyString::MyIterator::operator++(){
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
// 1.4
MyString::MyIterator
MyString::MyIterator::operator++(int param){
  MyString::MyIterator miter(current);
  current++;
  return miter;
}

//--------------------------------------------
// FUNCTION: operator==
// Operator for comparison.
// PARAMETERS:
// const MyIterator& other
// - other: Compare the iterator with it.
//----------------------------------------------
// 1.4
bool
MyString::MyIterator::operator==(const MyIterator& other) const{
  return this->current == other.current;
}

//--------------------------------------------
// FUNCTION: operator!=
// Operator for comparison(negative).
// PARAMETERS:
// const MyIterator& other
// - other: Compare the iterator with it.
//----------------------------------------------
// 1.4
bool
MyString::MyIterator::operator!=(const MyIterator& other) const{
  return this->current != other.current;
}

//--------------------------------------------
// FUNCTION: operator*
// The operator serves to take the value of the memory, which the iterator points.
// PARAMETERS:
// Not
//----------------------------------------------
// 1.4
char&
MyString::MyIterator::operator*(){
  return *current;
}

//----------------------------------------------------
// MyIterator begin, end

//--------------------------------------------
// FUNCTION: begin
// Returns the address of the first element of the string.
// PARAMETERS:
// Not
//----------------------------------------------
// 1.4
MyString::MyIterator
MyString::begin(){
  return MyIterator(buffer_);
}

//--------------------------------------------
// FUNCTION: end
// Returns the address of the "last element + 1" of the string.
// PARAMETERS:
// Not
//----------------------------------------------
// 1.4
MyString::MyIterator
MyString::end(){
  return MyIterator(buffer_ + size_);
}

//--------------------------------------------
// FUNCTION: MyString
// Constructor of the string (MyString).
// PARAMETERS:
// int capacity
// - capacity: serves to determine the capacity of the string.
//----------------------------------------------
// 1.1
MyString::MyString(int capacity)
: capacity_(capacity),
  size_(0),
  buffer_(new char[capacity_])
{}

//--------------------------------------------
// FUNCTION: MyString
// Constructor of the string (MyString).
// PARAMETERS:
// const char* str
// - str: the string which will be taken.
//----------------------------------------------
// 1.1
MyString::MyString(const char* str)
: capacity_(0),
  size_(0),
  buffer_(0)
{
  size_ = strlen(str);
  capacity_ = size_+1;
  buffer_ = new char[capacity_];
  strcpy(buffer_, str);
}

//--------------------------------------------
// FUNCTION: ~MyString
// Deconstructor of the string (MyString).
// PARAMETERS:
// Not
//----------------------------------------------
// 1.1
MyString::~MyString(){
  delete [] buffer_;
}

//--------------------------------------------
// FUNCTION: MyString
// Copy constructor.
// PARAMETERS:
// const MyString& other
// - other: the string which will be copied.
//----------------------------------------------
// 1.3
MyString::MyString(const MyString& other){
  capacity_ = other.capacity_;
  size_ = other.size_;
  buffer_ = new char[capacity_];
  for(int i=0; i<=capacity_; i++)
  buffer_[i] = other.buffer_[i];
}

//--------------------------------------------
// FUNCTION: operator=
// Assignment operator.
// PARAMETERS:
// const MyString& other
// - other: the string which we assign.
//----------------------------------------------
// 1.3
MyString& MyString::operator=(const MyString& other){
  if(this != &other) {
    delete [] buffer_;
    capacity_ = other.capacity_;
		size_ = other.size_;
		buffer_ = new char[capacity_];
		for(int i=0; i<=capacity_; i++)
			buffer_[i] = other.buffer_[i];
  }
	 return *this;
}

//--------------------------------------------
// FUNCTION: size
// Returns the size of the string (the number of elements in the string).
// PARAMETERS:
// Not
//----------------------------------------------
// 1.2
int MyString::size() const{
  return size_;
}

//--------------------------------------------
// FUNCTION: length
// Returns the length of the string (the number of elements in the string).
// PARAMETERS:
// Not
//----------------------------------------------
// 1.2
int MyString::length() const{
  return size_;
}

//--------------------------------------------
// FUNCTION: capacity
// Returns the number of items for which it is allocated memory. The method capacity()
// always returns a value that is greater than or equal to the size().
// PARAMETERS:
// Not
//----------------------------------------------
// 1.2
int MyString::capacity() const{
  return capacity_;
}

//--------------------------------------------
// FUNCTION: empty
// Returns true, if the string is empty (i.e. size () == 0).
// PARAMETERS:
// Not
//----------------------------------------------
// 1.2
bool MyString::empty() const{
  if(size() == 0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: clean
// Delete all of the elements of the string.
// PARAMETERS:
// Not
//----------------------------------------------
// 1.2
void MyString::clear(){
  size_ = 0;
}

//--------------------------------------------
// FUNCTION: operator[]
// Returns a reference to the n-th element of the string (the element with index n).
// PARAMETERS:
// int index
// - index: the element which value we want to know.
//----------------------------------------------
// 1.2
char& MyString::operator[](int index){
  return buffer_[index];
}

//--------------------------------------------
// FUNCTION: at
// Returns a reference to the n-th element of the string (the element with index n).
// This method checks the value of the parameter index for validity and
// if it is not valid generate an exception.
// PARAMETERS:
// int index
// - index: the element which value we want to know.
//----------------------------------------------
// 1.2
char& MyString::at(int index){
  if(index < size())
    return buffer_[index];
  else
    throw exception();
}

//--------------------------------------------
// FUNCTION: operator<<
// This method inserts string into stream.
// This method inserts the sequence of characters that
// conforms value of str into out.
// PARAMETERS:
// ostream& out, const MyString& str
// - out: ostream object where characters are inserted. 
// - str: string object with the content to insert.
//----------------------------------------------
// 1.2
ostream& operator<<(ostream& out, const MyString& str){
  out << str.buffer_;
  return out;
}

//--------------------------------------------
// FUNCTION: operator==
// This method compares buffers from two String objects.
// If they are equal - return true;
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be compared with buffer_. 
//----------------------------------------------
// 1.2
bool MyString::operator==(const MyString& other){
  if(strcmp(buffer_, other.buffer_)==0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: operator!=
// This method compares buffers from two String objects.
// If they are not equal - return true;
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be compared with buffer_.
//----------------------------------------------
// 1.2
bool MyString::operator!=(const MyString& other){
  if(strcmp(buffer_, other.buffer_)!=0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: operator<
// This method compares buffers from two String objects.
// If the first buffer is less then second - return true;
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be compared with buffer_.
//----------------------------------------------
// 1.2
bool MyString::operator<(const MyString& other){
  if(strcmp(buffer_, other.buffer_)<0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: operator>
// This method compares buffers from two String objects.
// If the first buffer is greater then second - return true;
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be compared with buffer_.
//----------------------------------------------
// 1.2
bool MyString::operator>(const MyString& other){
  if(strcmp(buffer_, other.buffer_)>0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: operator<=
// This method compares buffers from two String objects.
// If the first buffer is less then or equal to second - return true;
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be compared with buffer_.
//----------------------------------------------
// 1.2
bool MyString::operator<=(const MyString& other){
  if(strcmp(buffer_, other.buffer_)<=0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: operator>=
// This method compares buffers from two String objects.
// If the first buffer is greater then or equal to second - return true;
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be compared with buffer_.
//----------------------------------------------
// 1.2
bool MyString::operator>=(const MyString& other){
  if(strcmp(buffer_, other.buffer_)>=0)
    return true;
  else
    return false;
}

//--------------------------------------------
// FUNCTION: append
// This method adds new string to the current string que.    
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be concatenate with buffer_.
//----------------------------------------------
// 1.5
MyString& MyString::append(const MyString& other){
  MyString mstr(capacity_);
  strcat(mstr.buffer_, buffer_);
  capacity_ += other.capacity_;
  size_ += other.size_;
  buffer_ = new char[capacity_];
  strcat(buffer_, mstr.buffer_);
  strcat(buffer_, other.buffer_);
  return *this;
}

//--------------------------------------------
// FUNCTION: operator+=
// This method adds new string to the current string que.    
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be concatenate with buffer_.
//----------------------------------------------
// 1.5
MyString& MyString::operator+=(const MyString& other){
  MyString mstr(capacity_);
  strcat(mstr.buffer_, buffer_);
  capacity_ += other.capacity_;
  size_ += other.size_;
  buffer_ = new char[capacity_];
  strcat(buffer_, mstr.buffer_);
  strcat(buffer_, other.buffer_);
  return *this;
}

//--------------------------------------------
// FUNCTION: push_back
// Adds new element after the last element of the string.
// PARAMETERS:
// char ch
// - ch: this is the element, which is added to the end of the string.
//----------------------------------------------
// 1.5
void MyString::push_back(char ch){
  if(size_+1>capacity_)
    capacity_ += 1;
  buffer_[size_] = ch;
  size_++;
}

//--------------------------------------------
// FUNCTION: operator+
// This metod concatenates two strings.
// PARAMETERS:
// const MyString& other
// - other: String object.
// His buffer (object.buffer_) will be concatenate with buffer_.
//----------------------------------------------
// 1.5
MyString MyString::operator+(const MyString& other){
  MyString mstr(capacity_ + other.capacity_);
  mstr.size_ = size_ + other.size_;
  mstr.buffer_ = new char[mstr.capacity_];
  strcat(mstr.buffer_, buffer_);
  strcat(mstr.buffer_, other.buffer_);
  return mstr;
}

// 1.6.1
int main(int argc, char *argv[]){

	// 1.6.2
	MyString str1(argv[1]);
	MyString str2(argv[2]);

	// 1.6.3
	cout << "string 1: <" << str1 << ">" << endl;
	cout << "string 2: <" << str2 << ">" << endl;
	cout << endl;

	// 1.6.4
	cout << "string 1 lenght: " << str1.length() << endl;
	cout << "string 2 lenght: " << str2.length() << endl;
	cout << endl;

	// 1.6.5
	int number_of_spaces_str1 = 0, number_of_spaces_str2 = 0; 
	for(MyString::MyIterator iter1 = str1.begin(); iter1 != str1.end(); ++iter1)
		if(*iter1 == ' ')
			number_of_spaces_str1++;

	for(MyString::MyIterator iter2 = str2.begin(); iter2 != str2.end(); ++iter2)
		if(*iter2 == ' ')
			number_of_spaces_str2++;
	cout << "string 1 spaces: " << number_of_spaces_str1 << endl;
	cout << "string 2 spaces: " << number_of_spaces_str2 << endl;
	cout << endl;

	// 1.6.6
	bool grt;
	grt = str1 > str2;
	if(grt == true || grt == 1)
	  cout << "<"<< str1 << ">"
	  << " is greater then " <<
	  "<" << str2 << ">" << endl;
	  else
	  cout << "<"<< str1 << ">"
	  << " is not greater then " <<
	  "<" << str2 << ">" << endl;
	cout << endl;

	// 1.6.7
	str1.push_back('!');
	str2.push_back('!');
	cout << "string 1: <" << str1 << ">" << endl;
	cout << "string 2: <" << str2 << ">" << endl;
	cout << endl;

	// 1.6.8
	MyString str = str1 + str2;
	cout << "concatenation: <" << str << ">" << endl;
	cout << endl;

	// 1.6.9
	cout << "concatenation length: " << str.length() << endl;
	cout << endl;

	// 1.6.10
	int number_of_spaces_str = 0;
	for(MyString::MyIterator iter = str.begin(); iter != str.end(); ++iter)
		if(*iter == ' ')
			number_of_spaces_str++;
	cout << "concatenation spaces: " << number_of_spaces_str << endl;
	cout << endl;

  return 0;
}

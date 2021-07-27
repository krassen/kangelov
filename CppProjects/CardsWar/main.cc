#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int Suit, Rank;

const Suit  hearts = 0, clubs = 1,   diamonds = 2,  spades = 3;

const Rank  two = 0,    three = 1,   four = 2,      five = 3,
            six = 4,    seven = 5,   eight = 6,     nine = 7,
            ten = 8,     jack = 9,   queen = 10,    king = 11,
            ace = 12;

class Card {
  Suit suit;
  Rank rank;
public:
  Card(Suit s, Rank r)
  : suit(s), rank(r)
  {}

  bool operator==(Card c){
    return rank == c.rank;
  }
  bool operator<(Card c){
    return rank < c.rank;
  }
};

class Deck {
protected:
  vector<Card> cards;
public:
  Deck() {
    for (Rank r = two; r <= ace; ++r)
      for (Suit s = hearts; s <= spades; ++s)
        cards.push_back(Card(s,r));
      random_shuffle(cards.begin(), cards.end());
  }

  void shuffle(){
    random_shuffle(cards.begin(), cards.end());
  }

  void draw(){
    cards.pop_back();
  }

  void print(){
    copy(cards.begin(), cards.end(),
            std::ostream_iterator<int>(cout, "\n"));
  }

};

int main(){

cout << "1234" << endl;

Deck d;
// for (std::vector<Card>::iterator it = d.cards.begin() ; it != d.cards.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';


  return 0;
}

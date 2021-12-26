# Getting Started
Please note that this guide assumes that you have ``gcc/g++`` installed on your computer. You will need it to compile this program. If you do not, please see a guide on how to do that for your operating system. This guide **will not** go over how to do that.


### Windows
You can compile the provided programs by running the ``compile_windows.bat`` script.

If you would like to compile and run the programs yourself,

To run the test
- Compile it with ``g++ test.cpp``
Then run ``a.exe``

To run the card games
- Compile it with ``g++ main.cpp``
Then run ``a.exe``


### Linux 
You can compile the provided programs by running the ``compile_linux.sh`` script (``./compile_linux.sh`` in the terminal)

If you would like to compile and run the programs yourself,

To run the test
- Compile it with ``g++ test.cpp``
- Run it with ``./a.out``

To run the card games
- Compile it with ``g++ main.cpp``
- Run it with ``./a.out``


### MacOS
You can compile the provided programs by running the ``compile_mac.sh`` script (``./compile_mac.sh`` in the terminal)

If you would like to compile and run the programs yourself,

To run the test
- Compile it with ``g++ test.cpp -std=gnu++11``
- Run it with ``./a.out`` 

To run the card games
- Compile it with``g++ main.cpp -std=gnu++11`` 
- Run it with ``./a.out``


# CPP-Cards
Text-based card game engine in C++

You can test and see some basic implementations of the engine by compiling and running ``test.cpp``, and reading through its source code. It goes over the function overloading and the use of most of the available functions.

Most of this information is also commented in the code, so please be sure to check out the comments as well if anything doesn't make sense to you.

I highly recommend using the overloaded operators shown in ``Overloads.h``. They do most of the things that are in ``Paint.h`` but are more intuitive to understand.

This is currently a work in progress. I plan on implementing a few games using this engine.


# Cards.h

### maps
``suitToStr<Suit, string>`` converts the Suit tokens into strings.

``rankToStr<Rank, string>`` converts the Rank tokens into strings.

``rankToChar<Rank, char>`` converts all Ranks into chars. Used for "painting" (asciifying) the cards.


## Card class
Initializing cards

You can easily initialize a Card object with ``Card c = Card(Ace, Spade)``.

You can also initialize an empty Card object ``Card c = Card()``. This will automatically set the card with ``NullR`` and ``NullS`` as its Rank and Suit respectively. You can then use ``c.setCard(King, Diamond)`` to set its attributes.


### Getting 

Say we have the same Card object ``c`` from earlier.

You can use ``c.getRank()`` and ``c.getSuit()`` to get Rank and the Suit respectively. 

You can use ``c.getPair()`` to get a ``std::pair`` of the Rank and Suit.

You can use ``c.getInfo()`` to return the cards rank in suit in the form of "Rank of Suit" (i.e, Ace of Spades).

You can use ``c.printInfo()``, which just prints out what ``getInfo()`` returns.


### Compare functions

Say we have two Card objects ``card1``, and ``card2``.

You can use ``card1.samePair(card2)`` to see if ``card1`` is the exact same card as ``card2``.

You can use ``card1.sameRank(card2)`` to see if ``card1`` and ``card2`` have the same Rank.

You can use ``card1.sameSuit(card2)`` to see if both cards have the same Suit.



## Functions

``vector<Card> createDeck(int numDecks=1, bool shuffle=true, bool verbose=true)`` can take 3 arguments (minimum 0). 
This function will return a Card vector.
- ``numDecks`` is the number of 52-card decks that the Card vector will take (1 by default). 
- ``shuffle`` will shuffle the deck after creating it (true by default).
- ``verbose`` will output messages describing what is currently going on (this will always be true by default).


``shuffleCards(vector<Card> &cards, bool animate=true, bool verbose=true)`` can take 3 arguments (minimum 1). This function will modify a card vector directly.
- ``cards`` is the card vector that you are shuffling (Typically, the deck, but can be any vector you want to use)
- ``animate`` will show shuffle animation, takes a few seconds to do, so you should turn it off while debugging. (true by default)
- ``verbose`` see previous ``verbose()``



``drawCards(vector<Card> &cardVect, int numDrawn=1, bool verbose=true)`` can take 3 arguments (minimum 1). This function will modify a vector directly and return another one (the cards that were "drawn").
- ``cardVect`` is the card vector that is being drawn from.
- ``numDrawn`` is the number of cards drawn from the card vector.
- ``verbose`` see previous ``verbose()``

# Paint.h

"Painting" refers to turning the Card objects into ASCII art. All logic that deals with turning the Card objects into its ASCII form is handled in this file.

Please note that the option to use overloaded operators is available as well. They will probably be syntactically easier to use and write and are recommended. You can see how they work in the ``Overloads.h`` file and later in the README.

How the cards are painted:

Each card Suit and facedown cards are represented in array strings (``spadeCard``, ``diamondCard``, ``facedownCard``... etc.) with a 'Z' character as the placeholder for a Rank. The 'Z' is later replaced with the appropriate character when its being painted to represent a proper card (10 is handled manually because it is 2 characters long)


## Functions

``paintCards(vector<Card> cardVect, int numPainted=-1, int facedown=0)`` can take 3 arguments (minimum 1). This function paints the entire card vector, and does not stack them on top of each other.
- ``cardVect`` The card vector to paint.
- ``numPainted`` You can choose to not paint the entire vector. This number will determine amount of cards to paint.
- ``facedown`` You can paint cards facing down. This variable determines the number of cards that are facedown.


``paintStacked(vector<Card> cardVect, int numPainted, int facedown, bool topRHS)`` can take 4 arguments (minimum 1). This function does the same as ``paintCards()`` except that it paints the cards as if they are stacked on top of each other. Depending on the value of the bool ``topRHS``, the top side can either be on the right (if true), or the left hand side (if false).
- ``cardVect`` The card vector being painted
- ``numPainted`` See ``paintCards()``
- ``facedown`` See ``paintCards()``
- ``topRHS`` If this value is true, the cards will be painted with the top card on the right hand side. If its false, the top card will be on the left hand side.

The image below illustrates the 3 different stack modes that you can use.

![Stack Modes](https://i.imgur.com/mqG9v0V.jpg)

``paintSingle(Card c)`` takes 1 argument (minimum 1). Does exactly what the other paint functions do, but for lone Card objects.
- ``c`` The card being painted.


``shuffleAnimation(verbose=true)`` takes 1 argument (minimum zero). Shows a shuffling animation, this animation happens in ``createDeck()`` by default. This function does not actually shuffle a Card vector, it simply does the animation.
- ``verbose`` If this is true, messages will be displayed along with the shuffling animation.

# Overloads.h

In the ``Overloads.h`` file, there is a global variable named ``verboseOverloads``. You can set this variable true or false in any file at any time if you wish to change verbose output to show or not when using overloaded operators (This variable has no effect when calling the paint functions directly, only when using any of the overloaded operators)

``Overloads.h`` contains all the overloaded operators that can be used with the Card objects and vectors. For example, you can paint a card directly by using the `<<` operator, or even use `+=` to add a Card object to a vector.

The purpose of these overloads is to abstract the "painting" of cards and to provide a short-hand alternative method to paint the cards.   

Below is a comprehensive list of all the overloaded operations available. These implementations will also be demonstrated in some provided examples. These notes are taken directly from the comments from the source code, so if you are unsure of how an implementation works, either check the examples in ``test.cpp``, or check ``Overloads.h`` for more details.


### Printing 

- ``ostream& operator<<(ostream& out, Card c);``
Directly print Card objects through output stream with '<<'.

- ``ostream& operator<<(ostream& out, vector<Card> cardVect);``
Directly print Card vectors through output stream with '<<'.

### Addition operations

- ``vector<Card> operator+(vector<Card> cardVect, Card c);``
Return a Card object added to a Card vector.
Does not modify original vector.

- ``vector<Card> operator+(Card c, vector<Card> cardVect);``
Reversed. This way of inserting is much less efficient and should not be used often.

- ``void operator+=(vector<Card> &cardVect, Card c);``
Append a Card object to a Card vector with '+='.

- ``vector<Card> operator+(vector<Card> a, vector<Card> b);``
Return two Card vectors combined into one.
Does not modify original vectors.

- ``vector<Card> operator+(Card a, Card b);``
Return a vector made from 2 Card objects.

- ``void operator+=(vector<Card> &a, vector<Card> b);``
Combine two Card vectors.
Directly modifies the left vector operand.

### Subtraction operations

- ``void operator-=(vector<Card> &cardVect, Card c);``
Remove the first instance of Card object found in the vector if it exists.
Directly modifies the Card vector

- ``void operator-=(vector<Card> &a, vector<Card> b);``
Remove the first instance of all cards in vector b from vector a. 
Directly modifies the Card vector

- ``vector<Card> operator-(vector<Card> cardVect, Card c);``
Return the  card Vector, "minus" the card specified. 
Only removes the first instance of the card if multiple exist.
Does not directly modify the Card vector

- ``vector<Card> operator-(vector<Card> a, vector<Card> b);``
Return the Card vector a, minus all the cards in Card vector b that are found in a.
Does not directly modify the Card vector

- ``string operator-(vector<Card> cardVect, int n);``
Subtracting an int, n from a Card vector will return the painted cards with n-cards facedown. 
Example use: ``cout << cardVect-2 << endl;``.
This will paint all cards in cardVect but with 2 facing down.


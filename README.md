# CPP-Cards
Text-based card game engine in C++

Currently, I have made a small war game demo as an example of how an implementation using the engine may look. You can test it out by compiling ``Examples/wardemo.cpp``, and running the binary.

This is currently a work in progress.

TO DO:
- Finish readme
- Ensure no bugs are in newly implemented overloads
- Create some examples to show the implementation of the engine

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

You can use ``card.getRank()`` and ``card.getSuit()`` to get Rank and the Suit respectively. 

You can use ``card.getPair()`` to get a ``std::pair`` of the Rank and Suit.

You can use ``card.getInfo()`` to return the cards rank in suit in the form of "Rank of Suit" (i.e, Ace of Spades).

You can use ``card.printInfo()``, which just prints out what ``getInfo()`` returns.


### Compare functions

You can use ``card1.samePair(card2)`` to see if ``card1`` is the exact same card as ``card2``.

You can use ``card1.sameRank(card2)`` to see if ``card1`` and ``card2`` have the same Rank.

You can use ``card1.sameSuit(card2)`` to see if both have cards the same Suit.



## Functions

``vector<Card> createDeck(numDecks=1, shuffle=true, verbose=true)`` can take 3 arguments (minimum 0). 
This function will return a Card vector.
- ``numDecks`` is the number of 52-card decks that the Card vector will take (1 by default). 
- ``shuffle`` will shuffle the deck after creating it (true by default).
- ``verbose`` will output messages describing what is currently going on (this will always be true by default).


``shuffleCards(cards, animate=true, verbose=true)`` can take 3 arguments (minimum 1). This function will modify a card vector directly.
- ``cards`` is the card vector that you are shuffling (Typically, the deck, but can be any vector you want to use)
- ``animate`` will show shuffle animation, takes a few seconds to do, so you should turn it off while debugging. (true by default)
- ``verbose`` see previous verbose()



``drawCards(cardVect, numDrawn=1, verbose=true)`` can take 3 arguments (minimum 1). This function will modify a vector directly and return another one (the cards that were "drawn").
- ``cardVect`` is the card vector that is being drawn from.
- ``numDrawn`` is the number of cards drawn from the card vector.
- ``verbose`` see previous verbose()

# Paint.h

"Painting" refers to turning the Card objects into ASCII art. All logic that deals with turning the art into its ASCII form is handled in this file.

The way it works:


Each card Suit and facdown cards are represented in array strings (spadeCard, diamondCard, facedownCard... etc.) with a 'Z' character as the placeholder for a Rank. The 'Z' is later replaced with the appropriate character when its being painted to represent a proper card (10 is handled manually because it is 2 characters long)


### Functions

``paintCards(cardVect, numPainted=-1, facedown=0)`` can take 3 arguments (minimum 1). This function paints the entire card, and does not stack them on top of each other.
- ``cardVect`` The card vector to paint.
- ``numPainted`` You can choose to not paint the entire card. This card will paint the amount of cards specified by this variable.
- ``facedown`` You can paint cards facing down. This variable determines the number that are facedown.


``paintStacked(cardVect, numPainted, facedown, topRHS)`` can take 4 arguments (minimum 1). This function does the same as ``paintCards()`` except that it paints the cards as if they are stacked on top of each other. Depending on the value of the bool ``topRHS``, the top side can either be on the right (if true), or the left hand side (if false).
- ``cardVect`` The card vector being paintedS
- ``numPainted`` See paintCards()
- ``facedown`` See paintCards()
- ``topRHS`` If this value is true, the cards will be painted with the top card on the right hand side. If its false, the top card will be on the left hand side.


``paintSingle(Card c)`` takes 1 argument (minimum 1). Does exactly what the other paint functions do, but for lone Card objects.
- ``c`` The card being painted.


``shuffleAnimation(verbose=true)`` takes 1 argument (minimum zero). Shows a shuffling animation, this animation happens in ``createDeck()`` by default. This function does not actually shuffle a Card vector, it simply does the animation.
- ``verbose`` If this is true, messages will be displayed along with the shuffling animation.


To be continued...

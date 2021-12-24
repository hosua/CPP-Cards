# CPP-Cards
Text-based card game engine in C++

Currently, I have made a small war game demo as an example of how an implementation using the engine may look. You can test it out by compiling ``Examples/wardemo.cpp``, and running the binary.

This is currently a work in progress.

# Some notes about the card game engine

## Cards.h

### maps
``suitToStr<Suit, string>`` converts the Suit tokens into strings.

``rankToStr<Rank, string>`` converts the Rank tokens into strings.

``rankToChar<Rank, char>`` converts all Ranks into chars. Used for "painting" (asciifying) the cards.


### Card class
Initializing cards

You can easily initialize one by doing ``Card c = Card(Ace, Spade)``.

You can also initialize an empty card ``Card c = Card()``. This will automatically set the card with ``NullR`` and ``NullS`` as its Rank and Suit respectively. You can then use ``c.setCard(King, Diamond)`` to set its attributes.


#### Getting 

You can use ``getRank()`` and ``getSuit()`` to get Rank and Suit.

You can use ``getPair()`` to get a ``std::pair`` of the Rank and Suit.

You can use ``getInfo()`` to return the cards rank in suit in the form of "Rank of Suit" (i.e, Ace of Spades).

You can use ``printInfo()``, which just prints out what ``getInfo()`` returns.


#### Compare functions

You can use ``card1.samePair(card2)`` to see if ``card1`` is the exact same card as ``card2``.

You can use ``card1.sameRank(card2)`` to see if ``card1`` and ``card2`` have the same Rank.

You can use ``card1.sameSuit(card2)`` to see if both have cards the same Suit.



## Functions

``vector<Card> createDeck(numDecks=1, shuffle=true, verbose=true)`` can take 3 arguments. 
This function will return a Card vector.
``numDecks`` is the number of 52-card decks that the Card vector will take (1 by default). 
``shuffle`` will shuffle the deck after creating it (true by default).
``verbose`` will output messages describing what is currently going on (this will always be true by default).


``shuffleCards(cards, animate=true, verbose=true)`` can take 3 arguments. This function will modify a card vector directly.
``cards`` is the card vector that you are shuffling (Typically, the deck, but can be any vector you want to use)
``animate`` will show shuffle animation, takes a few seconds to do, so you should turn it off while debugging. (true by default)
``verbose`` see previous verbose()



``drawCards(cardVect, numDrawn=1, verbose=true)`` can take 3 arguments. This function will modify a vector directly and return another one (the cards that were "drawn").
``cardVect`` is the card vector that is being drawn from.
``numDrawn`` is the number of cards drawn from the card vector.
``verbose`` see previous verbose()

To be continued...
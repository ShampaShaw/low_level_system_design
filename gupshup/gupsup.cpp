#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Map to handle card value ranks
map<string, int> valueRank = {
    {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6},
    {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"J", 11},
    {"Q", 12}, {"K", 13}, {"A", 14}
};

class Card {
public:
    char suit;
    string value;

    Card(char suit, string value) : suit(suit), value(value) {}

    // Comparison functions
    static bool isLess(const Card& a, const Card& b) {
        if (a.suit == b.suit) {
            return valueRank[a.value] < valueRank[b.value];
        }
        string suits_order = "CDHS";
        return suits_order.find(a.suit) < suits_order.find(b.suit);
    }

    static bool isGreater(const Card& a, const Card& b) {
        return !isLess(a, b) && !isEqual(a, b);
    }

    static bool isEqual(const Card& a, const Card& b) {
        return a.suit == b.suit && a.value == b.value;
    }

    friend ostream& operator<<(ostream& os, const Card& card) {
        os << card.suit << card.value;
        return os;
    }
};

class Player {
public:
    string name;
    vector<Card> cards;

    Player(string name) : name(name) {}

    void addCard(const string& card_str) {
        cards.emplace_back(card_str[0], card_str.substr(1));
    }
};

class Game {
public:
    map<string, Player> players;
    vector<Card> played_cards;
    char trump;
    vector<string> player_names;

    Game(const vector<string>& player_names, char trump) 
        : trump(trump), player_names(player_names) {
        for (const auto& name : player_names) {
            players[name] = Player(name);
        }
    }

    void addCardToPlayer(const string& player_name, const string& card_str) {
        players[player_name].addCard(card_str);
        played_cards.push_back(Card(card_str[0], card_str.substr(1)));
    }

    Card getOptimalCard(const Player& self) {
        Card highest_card = played_cards.empty() ? Card('\0', "") : played_cards[0];

        for (const auto& card : played_cards) {
            if ((card.suit == highest_card.suit && Card::isGreater(card, highest_card)) || 
                (card.suit == trump && highest_card.suit != trump)) {
                highest_card = card;
            }
        }

        for (const auto& card : self.cards) {
            if (card.suit == highest_card.suit && Card::isGreater(card, highest_card)) {
                return card;
            }
        }

        return getSmallestCard(self.cards, '\0');
    }

private:
    Card getSmallestCard(const vector<Card>& cards, char suit) {
        Card smallest_card = Card('\0', "");
        for (const auto& card : cards) {
            if (suit == '\0' || card.suit == suit) {
                if (smallest_card.suit == '\0' || Card::isLess(card, smallest_card)) {
                    smallest_card = card;
                }
            }
        }
        return smallest_card;
    }
};

// Example usage
int main() {
    vector<string> player_names = {"Alice", "Bob", "Carol", "Dave"};
    char trump = 'H';  // Hearts as trump suit
    Game game(player_names, trump);

    game.addCardToPlayer("Alice", "H7");
    game.addCardToPlayer("Bob", "C8");
    game.addCardToPlayer("Carol", "H10");
    game.addCardToPlayer("Dave", "D9");

    Player& alice = game.players["Alice"];
    Card optimal_card = game.getOptimalCard(alice);
    cout << "Optimal card for Alice: " << optimal_card << endl;

    return 0;
}


#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <type_traits>
#include <random>

// 获得一个离散分布的函数对象
std::uniform_int_distribution<size_t>& dist()
{
    static std::uniform_int_distribution<size_t> d;

    return d;
}

// 获得一个随机数生成器
std::default_random_engine& rng()
{
    static std::default_random_engine engine { std::random_device()() };
    
    return engine;
}

enum class Suit : size_t {
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

enum class Face : size_t {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

using Card = std::pair<Suit, Face>;
using Hand = std::list<Card>;
using Deck = std::list<Card>;
using Hands = std::vector<Hand>;
using Range = std::uniform_int_distribution<size_t>::param_type;

std::ostream& operator<<(std::ostream& out, const Card& card)
{
    static std::array<std::string, 4> suits { "C", "D", "H", "S" };
    static std::array<std::string, 13> values { "2", "3", "4", "5", "6", "7", "8",
                                                "9", "X", "J", "Q", "K", "A" };
    std::string suit { suits[static_cast<size_t>(card.first)] };
    std::string value { values[static_cast<size_t>(card.second)] };
    
    return out << std::setw(2) << value << suit;
}

// the cards is ordered after initialized
void init_deck(Deck& deck)
{
    static std::array<Suit, 4> suits { Suit::Clubs, Suit::Diamonds, Suit::Hearts, Suit::Spades };
    static std::array<Face, 13> values { Face::Two, Face::Three, Face::Four, Face::Five, Face::Six, Face::Seven,
                                         Face::Eight, Face::Nine, Face::Ten, Face::Jack, Face::Queen, Face::King,
                                         Face::Ace };

    deck.clear();

    for (const auto & suit : suits) {
        for (const auto & value : values) {
            deck.emplace_back(Card{suit, value});
            // size_t s = static_cast<typename std::underlying_type<Suit>::type>(deck.back().first);
            // size_t f = static_cast<typename std::underlying_type<Face>::type>(deck.back().second);
            // std::cout << s << ":" << f << "|" << deck.back() << std::endl;
        }
    }
}

// distribute the cards
void deal(Hands& hands, Deck& deck)
{
    auto d = dist();
    
    while (! deck.empty()) {
        for (auto & hand : hands) {
            size_t max_index = deck.size() - 1;
            d.param(Range{ 0, max_index });
            auto iter = std::begin(deck);
            std::advance(iter, d(rng()));
            hand.push_back(*iter);
            deck.erase(iter);
        }
    }   
}

// sort cards in hands
void sort_hands(Hands& hands)
{
    for (auto && hand : hands) {
        hand.sort([](const Card& crd1, const Card& crd2) {
            return crd1.first < crd2.first || (crd1.first == crd2.first && crd1.second < crd2.second);
        });
    }
}

void show_hands(const Hands& hands)
{
    for (auto && hand : hands) {
        std::copy(std::begin(hand), std::end(hand), std::ostream_iterator<Card>{ std::cout, " " });
        std::cout << std::endl;
    }
}

int main()
{
    Deck deck;
    init_deck(deck);
    
    Hands hands(4);
    deal(hands, deck);
    
    sort_hands(hands);
    show_hands(hands);
    
    return 0;
}
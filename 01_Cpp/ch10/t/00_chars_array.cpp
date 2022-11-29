
#include <stdio.h>

constexpr const char* sentence_1 = "It's better to be alone than to be with someone you're not happy to be with.";
constexpr const char* sentence_2 = "That's always the case.";
constexpr const char* sentence_3 = "Get over yourself.";

constexpr const char* sentences[] = {
    sentence_1,
    sentence_2,
    sentence_3
};


int main()
{
    printf("sizeof(sentences) = %ld\n", sizeof(sentences));
    printf("sizeof(sentence_1) = %ld\n", sizeof(sentence_1));

    size_t size = sizeof(sentences) / sizeof(const char*);
    printf("size = %ld\n", size);

    for (size_t i = 0; i < size; i++) {
        printf("=> %s\n", sentences[i]);
    }

    return 0;
}
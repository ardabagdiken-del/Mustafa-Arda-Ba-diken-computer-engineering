#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h> // strcasecmp için bazı sistemlerde gerekebilir

// Maksimum aday sayısı
#define MAX 9

// Aday yapısı
typedef struct
{
    string name;
    int    votes;
} candidate;

candidate candidates[MAX];
int candidate_count;

// Fonksiyon prototipleri
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name  = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

// ─────────────────────────────────────────────────────────────────────────────
// vote(): Verilen isme göre adayı bulur ve oy sayısını artırır
// ─────────────────────────────────────────────────────────────────────────────
bool vote(string name)
{
    // Adaylar dizisini tara
    for (int i = 0; i < candidate_count; i++)
    {
        // strcasecmp kullanarak büyük/küçük harf duyarsız karşılaştırma yap
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    // Eşleşme bulunamadıysa false dön
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// print_winner(): En çok oyu alan aday(lar)ı yazdırır
// ─────────────────────────────────────────────────────────────────────────────
void print_winner(void)
{
    int max_votes = 0;

    // 1. Adım: En yüksek oy sayısını bul
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // 2. Adım: Oyu en yüksek oya (max_votes) eşit olan herkesi yazdır
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

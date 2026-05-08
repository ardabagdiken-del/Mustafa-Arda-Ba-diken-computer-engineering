#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Harflerin puan değerleri (A=0, B=1, ... Z=25)
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Her iki oyuncudan kelimeleri al
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Skorları hesapla
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Kazananı ilan et
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// ---------------------------------------------------------------------------
// compute_score: Kelimenin toplam Scrabble puanını hesaplar
// ---------------------------------------------------------------------------
int compute_score(string word)
{
    int score = 0;

    // Kelimenin her karakterini tek tek kontrol et
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Karakterin büyük harf olup olmadığını kontrol et
        if (isupper(word[i]))
        {
            // 'A' karakterini çıkartarak 0-25 arası bir indeks elde ederiz
            // Örn: 'C' (67) - 'A' (65) = 2. İndeks (POINTS[2])
            score += POINTS[word[i] - 'A'];
        }
        // Karakterin küçük harf olup olmadığını kontrol et
        else if (islower(word[i]))
        {
            // 'a' karakterini çıkartarak yine 0-25 arası indeksi buluruz
            score += POINTS[word[i] - 'a'];
        }
        // Harf olmayan karakterler (boşluk, !, ?) otomatik olarak 0 puan sayılır (işlem yapılmaz)
    }

    return score;
}

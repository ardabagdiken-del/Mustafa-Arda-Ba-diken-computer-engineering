#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h> // strcasecmp için

// Limitler
#define MAX_VOTERS     100
#define MAX_CANDIDATES   9

// Tercih matrisi: preferences[seçmen][sıralama] = aday_indeksi
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int    votes;
    bool   eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

// Fonksiyon prototipleri
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int  find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // (Main içeriği zaten size verildiği için burayı kısa geçiyorum, 
    // ancak fonksiyonların doğru çalışması için yukarıdaki prototipler kritiktir.)
    // ... (Main fonksiyonu aynen kalmalı)
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 1: vote() - Seçmenin tercihini kaydeder
// ─────────────────────────────────────────────────────────────────────────────
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            // Adayın ismini değil, adaylar dizisindeki İNDEKSİNİ saklıyoruz
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 2: tabulate() - Oyları mevcut tura göre sayar
// ─────────────────────────────────────────────────────────────────────────────
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];

            // Eğer bu aday elenmemişse, oyunu buna ver ve sonraki seçmene geç
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break; // Sadece en üstteki (elenmemiş) tercihi sayıyoruz
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 3: print_winner() - Çoğunluk sağlandı mı kontrol eder
// ─────────────────────────────────────────────────────────────────────────────
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Mutlak çoğunluk: Toplam oyun yarısından FAZLASI (> %50)
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 4: find_min() - Kalan adaylar arasındaki en düşük oyu bulur
// ─────────────────────────────────────────────────────────────────────────────
int find_min(void)
{
    int min = voter_count; // Başlangıç için en yüksek olası değer

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 5: is_tie() - Herkesin eşit (minimum) oy alıp almadığını kontrol eder
// ─────────────────────────────────────────────────────────────────────────────
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Elenmemiş herhangi birinin oyu minimuma eşit değilse beraberlik yoktur
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true; // Herkes min oya sahipse beraberliktir
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 6: eliminate() - En düşük oyu alan adayları eler
// ─────────────────────────────────────────────────────────────────────────────
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

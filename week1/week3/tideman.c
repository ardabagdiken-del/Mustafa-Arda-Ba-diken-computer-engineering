#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// ── Limits ────────────────────────────────────────────────────────────────────
#define MAX 9

// ── Data ──────────────────────────────────────────────────────────────────────
int preferences[MAX][MAX];
bool locked[MAX][MAX];

typedef struct
{
    int winner;
    int loser;
} pair;

string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// ── Function prototypes ───────────────────────────────────────────────────────
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool creates_cycle(int start, int end);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        int ranks[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 1: vote() - Aday ismini bulup ranks dizisine indeksini kaydeder
// ─────────────────────────────────────────────────────────────────────────────
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 2: record_preferences() - Her seçmenin ikili tercihlerini matrise işler
// ─────────────────────────────────────────────────────────────────────────────
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // ranks[i], ranks[j]'den daha üstte olduğu için i tercih edilir
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 3: add_pairs() - Kazanan ve kaybeden ikilileri oluşturur
// ─────────────────────────────────────────────────────────────────────────────
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 4: sort_pairs() - İkilileri zafer gücüne göre (büyükten küçüğe) sıralar
// ─────────────────────────────────────────────────────────────────────────────
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            if (strength1 < strength2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
}

// ── Cycle Detection (Yardımcı Fonksiyon) ──────────────────────────────────────
bool creates_cycle(int start, int end)
{
    // Eğer bitiş noktası başlangıç noktasına ulaştıysa döngü oluşmuştur
    if (end == start)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // Eğer mevcut 'end' adayından 'i' adayına kilitli bir kenar varsa
        if (locked[end][i])
        {
            // 'i' noktasından 'start'a ulaşıp ulaşamadığımızı kontrol et (Recursive)
            if (creates_cycle(start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 5: lock_pairs() - Döngü oluşturmayan ikilileri kilitler
// ─────────────────────────────────────────────────────────────────────────────
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Eğer bu ikiliyi bağlamak başlangıç noktasına geri dönmüyorsa kilitle
        if (!creates_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// TODO 6: print_winner() - Grafiğin "kaynağını" (üstüne ok gelmeyeni) bulur
// ─────────────────────────────────────────────────────────────────────────────
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // Eğer herhangi bir adaydan i adayına kilitli bir kenar varsa i kaynak değildir
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }

        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

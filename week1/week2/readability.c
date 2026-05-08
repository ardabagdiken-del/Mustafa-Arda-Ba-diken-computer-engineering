#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Fonksiyon prototipleri
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Kullanıcıdan metni al
    string text = get_string("Text: ");

    // Harf, kelime ve cümle sayılarını hesapla
    int letters   = count_letters(text);
    int words     = count_words(text);
    int sentences = count_sentences(text);

    // L ve S değerlerini hesapla (100 kelime başına ortalamalar)
    // Önemli: Bölme işleminde hassasiyet için float'a cast ediyoruz
    float L = 100.0 * letters / words;
    float S = 100.0 * sentences / words;

    // Coleman-Liau formülünü uygula ve yuvarla
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Sonucu kurallara göre yazdır
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// ---------------------------------------------------------------------------
// Harf Sayma: Sadece alfabetik karakterleri sayar
// ---------------------------------------------------------------------------
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
// Kelime Sayma: Boşlukları sayarak kelime sayısını bulur
// ---------------------------------------------------------------------------
int count_words(string text)
{
    // Cümlede hiç boşluk olmasa bile en az 1 kelime vardır varsayımıyla 1'den başlarız
    int count = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
// Cümle Sayma: '.', '!', veya '?' işaretlerini sayar
// ---------------------------------------------------------------------------
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

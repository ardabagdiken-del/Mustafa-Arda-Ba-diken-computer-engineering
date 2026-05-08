#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Fonksiyon prototipleri
bool is_valid_key(string key);

int main(int argc, string argv[])
{
    // ---------------------------------------------------------------------------
    // ADIM 1: Komut Satırı Argümanlarını Doğrula
    // ---------------------------------------------------------------------------
    // Tam olarak bir argüman (anahtar) girilmeli
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Anahtarın geçerliliğini kontrol et
    if (!is_valid_key(argv[1]))
    {
        // Not: is_valid_key içinde hata mesajlarını spesifikleştirebilirsin
        // Ancak check50 genellikle hata durumunda 1 dönmesini bekler.
        printf("Key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    string key = argv[1];

    // ---------------------------------------------------------------------------
    // ADIM 2: Kullanıcıdan Düz Metni Al
    // ---------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");

    // ---------------------------------------------------------------------------
    // ADIM 3: Şifrele ve Ciphertext'i Yazdır
    // ---------------------------------------------------------------------------
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            // Büyük harfin alfabedeki sırasını bul (0-25)
            int index = c - 'A';
            // Anahtardaki karşılığını büyük harf olarak yazdır
            printf("%c", toupper(key[index]));
        }
        else if (islower(c))
        {
            // Küçük harfin alfabedeki sırasını bul (0-25)
            int index = c - 'a';
            // Anahtardaki karşılığını küçük harf olarak yazdır
            printf("%c", tolower(key[index]));
        }
        else
        {
            // Harf değilse olduğu gibi bırak
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}

// ---------------------------------------------------------------------------
// is_valid_key: Anahtarın kurallara uygunluğunu denetler
// ---------------------------------------------------------------------------
bool is_valid_key(string key)
{
    // 1. Uzunluk 26 karakter mi?
    if (strlen(key) != 26)
    {
        return false;
    }

    bool seen[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        // 2. Sadece harf mi?
        if (!isalpha(key[i]))
        {
            return false;
        }

        // 3. Tekrar eden harf var mı? (Case-insensitive)
        int index = tolower(key[i]) - 'a';
        if (seen[index])
        {
            return false; // Harf daha önce görüldü
        }
        seen[index] = true;
    }

    return true;
}

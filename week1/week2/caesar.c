#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonksiyon prototipleri
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // ---------------------------------------------------------------------------
    // ADIM 1: Komut Satırı Argümanlarını Doğrula
    // ---------------------------------------------------------------------------
    // Program tam olarak bir argümanla çağrılmalıdır: ./caesar KEY
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1; // Hata durumunda programı sonlandır
    }

    // ---------------------------------------------------------------------------
    // ADIM 2: Anahtarı String'den Int'e Çevir
    // ---------------------------------------------------------------------------
    int key = atoi(argv[1]);

    // ---------------------------------------------------------------------------
    // ADIM 3: Kullanıcıdan Düz Metni (Plaintext) Al
    // ---------------------------------------------------------------------------
    string plaintext = get_string("plaintext:  ");

    // ---------------------------------------------------------------------------
    // ADIM 4: Şifrele ve Ciphertext'i Yazdır
    // ---------------------------------------------------------------------------
    printf("ciphertext: ");

    // Her karakter üzerinde döngü kur ve rotate fonksiyonunu çağır
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char encrypted_char = rotate(plaintext[i], key);
        printf("%c", encrypted_char);
    }

    // Sonunda bir yeni satır karakteri yazdır
    printf("\n");

    return 0; // Başarı durumunda 0 döndür
}

// ---------------------------------------------------------------------------
// only_digits: Metnin sadece rakamlardan oluşup oluşmadığını kontrol eder
// ---------------------------------------------------------------------------
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Eğer bir karakter bile rakam değilse false döndür
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// rotate: Karakteri n pozisyon kadar ileri kaydırır
// ---------------------------------------------------------------------------
char rotate(char c, int n)
{
    // Eğer karakter büyük harfse
    if (isupper(c))
    {
        // 'A' çıkartarak alfabeyi 0-25 arasına çekiyoruz, n ekleyip modu alıyoruz,
        // sonra tekrar ASCII değerine ('A') geri dönüyoruz.
        return (c - 'A' + n) % 26 + 'A';
    }
    // Eğer karakter küçük harfse
    else if (islower(c))
    {
        // Alfabeyi 0-25 arasına ('a') çekiyoruz
        return (c - 'a' + n) % 26 + 'a';
    }
    // Eğer harf değilse (noktalama, boşluk vb.) olduğu gibi döndür
    else
    {
        return c;
    }
}

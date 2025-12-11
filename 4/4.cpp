#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <openssl/evp.h>
#include <cstring>

using namespace std;

int main()
{
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    int round = 0;

    while (true)
    {
        // Build message with current round
        string candidate = "iwrupvqb" + to_string(round);

        // Hash candidate
        EVP_MD_CTX *ctx = EVP_MD_CTX_new();
        EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);
        EVP_DigestUpdate(ctx, candidate.data(), candidate.size());
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hash_len;
        EVP_DigestFinal_ex(ctx, hash, &hash_len);
        EVP_MD_CTX_free(ctx);

        // Convert to hex
        ostringstream oss;
        for (unsigned int i = 0; i < hash_len; i++)
            oss << hex << setw(2) << setfill('0') << (int)hash[i];
        string hex_str = oss.str();
        string first5 = hex_str.substr(0, 6);

        // Check condition
        if (first5 == "000000")
        {
            cout << "Message: " << candidate << "\n";
            cout << "Hash: " << hex_str << "\n";
            cout << "First 5 symbols: " << first5 << "\n";
            cout << "Found hash with leading 5 zeros!\n";
            cout << "at round: " << round << "\n";
            break;
        }

        // Increment for next candidate
        round++;
    }

    return 0;
}
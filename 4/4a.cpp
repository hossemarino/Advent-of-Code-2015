#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <openssl/evp.h>
#include <cstring>
#include <omp.h>

using namespace std;


int main() {
    bool found = false;
    int solution_round = -1;
    string solution_msg, solution_hash;

    // Parallel region
    #pragma omp parallel
    {
        // Each thread gets its own local variables
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hash_len;

        // Distribute iterations across threads
        #pragma omp for schedule(static)
        for (int round = 0; round < 20000000; ++round) {
            if (found) continue; // quick exit if another thread found it

            string candidate = "iwrupvqb" + to_string(round);

            // Hash candidate
            EVP_MD_CTX *ctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);
            EVP_DigestUpdate(ctx, candidate.data(), candidate.size());
            EVP_DigestFinal_ex(ctx, hash, &hash_len);
            EVP_MD_CTX_free(ctx);

            // Convert to hex
            ostringstream oss;
            for (unsigned int i = 0; i < hash_len; i++)
                oss << hex << setw(2) << setfill('0') << (int)hash[i];
            string hex_str = oss.str();
            string first6 = hex_str.substr(0, 6);

            if (first6 == "000000") {
                #pragma omp critical
                {
                    if (!found) {
                        found = true;
                        solution_round = round;
                        solution_msg = candidate;
                        solution_hash = hex_str;
                    }
                }
            }
        }
    }

    if (found) {
        cout << "Message: " << solution_msg << "\n";
        cout << "Hash: " << solution_hash << "\n";
        cout << "Found at round: " << solution_round << "\n";
    } else {
        cout << "No solution found in search range.\n";
    }

    return 0;
}
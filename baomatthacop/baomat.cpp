#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>
using namespace std;

// ===== Ham tien ich =====
string to_upper_nospace(string s) {
    string res;
    for (size_t i = 0; i < s.size(); i++)
        if (isalpha(s[i]))
            res += toupper(s[i]);
    return res;
}

int char_to_int(char c) { return c - 'A'; }
char int_to_char(int i) { return 'A' + (i % 26); }

// ===== Ma Caesar =====
string caesar_encrypt(string text, int shift) {
    text = to_upper_nospace(text);
    string result = "";
    for (size_t i = 0; i < text.size(); i++)
        result += int_to_char((char_to_int(text[i]) + shift) % 26);
    return result;
}

string caesar_decrypt(string text, int shift) {
    return caesar_encrypt(text, 26 - (shift % 26));
}

// ===== Ma Affine =====
int modinv(int a, int m) {
    for (int i = 1; i < m; ++i)
        if ((a * i) % m == 1)
            return i;
    return -1;
}

string affine_encrypt(string text, int a, int b) {
    text = to_upper_nospace(text);
    string result = "";
    for (size_t i = 0; i < text.size(); i++)
        result += int_to_char((a * char_to_int(text[i]) + b) % 26);
    return result;
}

string affine_decrypt(string text, int a, int b) {
    int a_inv = modinv(a, 26);
    if (a_inv == -1) return "a khong hop le";
    text = to_upper_nospace(text);
    string result = "";
    for (size_t i = 0; i < text.size(); i++)
        result += int_to_char((a_inv * (char_to_int(text[i]) - b + 26)) % 26);
    return result;
}

// ===== Ma Hoan Vi (Permutation) =====
string permute_encrypt(string text, vector<int> perm) {
    text = to_upper_nospace(text);
    int block = (int)perm.size();
    while (text.size() % block != 0)
        text += 'X'; // them ky tu pad
    string result = "";
    for (size_t i = 0; i < text.size(); i += block) {
        for (int j = 0; j < block; j++)
            result += text[i + perm[j]];
    }
    return result;
}

string permute_decrypt(string text, vector<int> perm) {
    int block = (int)perm.size();
    string result = "";
    vector<int> rev_perm(block);
    for (int i = 0; i < block; ++i)
        rev_perm[perm[i]] = i;

    for (size_t i = 0; i < text.size(); i += block) {
        string temp(block, ' ');
        for (int j = 0; j < block; ++j)
            temp[rev_perm[j]] = text[i + j];
        result += temp;
    }
    return result;
}

// ===== Ma Vigenere =====
string vigenere_encrypt(string text, string key) {
    text = to_upper_nospace(text);
    key = to_upper_nospace(key);
    string result = "";
    int m = (int)key.size();
    for (size_t i = 0; i < text.size(); ++i) {
        int shift = char_to_int(key[i % m]);
        result += int_to_char((char_to_int(text[i]) + shift) % 26);
    }
    return result;
}

string vigenere_decrypt(string text, string key) {
    key = to_upper_nospace(key);
    string result = "";
    int m = (int)key.size();
    for (size_t i = 0; i < text.size(); ++i) {
        int shift = char_to_int(key[i % m]);
        result += int_to_char((char_to_int(text[i]) - shift + 26) % 26);
    }
    return result;
}

// ===== Ma Playfair =====
pair<int, int> find_pos(char c, const vector<string>& table) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (table[i][j] == c)
                return make_pair(i, j);
    return make_pair(-1, -1);
}

vector<string> build_playfair_table(string key) {
    key = to_upper_nospace(key);
    key.erase(remove(key.begin(), key.end(), 'J'), key.end()); // Loai J
    string full = key;
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c == 'J') continue;
        if (full.find(c) == string::npos)
            full += c;
    }
    vector<string> table(5, string(5, ' '));
    for (int i = 0; i < 25; ++i)
        table[i / 5][i % 5] = full[i];
    return table;
}

string preprocess_playfair(string text) {
    text = to_upper_nospace(text);
    text.erase(remove(text.begin(), text.end(), 'J'), text.end());
    string result = "";
    for (size_t i = 0; i < text.size(); i++) {
        char a = text[i];
        char b = (i + 1 < text.size()) ? text[i + 1] : 'X';
        if (a == b) {
            result += a;
            result += 'X';
        } else {
            result += a;
            if (i + 1 < text.size()) {
                result += b;
                i++;
            } else {
                result += 'X';
            }
        }
    }
    if (result.size() % 2 != 0) result += 'X';
    return result;
}

string playfair_encrypt(string text, string key) {
    vector<string> table = build_playfair_table(key);
    text = preprocess_playfair(text);
    string result = "";
    for (size_t i = 0; i < text.size(); i += 2) {
        pair<int,int> pos1 = find_pos(text[i], table);
        pair<int,int> pos2 = find_pos(text[i + 1], table);
        int r1 = pos1.first, c1 = pos1.second;
        int r2 = pos2.first, c2 = pos2.second;
        if (r1 == r2) {
            result += table[r1][(c1 + 1) % 5];
            result += table[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            result += table[(r1 + 1) % 5][c1];
            result += table[(r2 + 1) % 5][c2];
        }
        else {
            result += table[r1][c2];
            result += table[r2][c1];
        }
    }
    return result;
}

string playfair_decrypt(string text, string key) {
    vector<string> table = build_playfair_table(key);
    string result = "";
    for (size_t i = 0; i < text.size(); i += 2) {
        pair<int,int> pos1 = find_pos(text[i], table);
        pair<int,int> pos2 = find_pos(text[i + 1], table);
        int r1 = pos1.first, c1 = pos1.second;
        int r2 = pos2.first, c2 = pos2.second;
        if (r1 == r2) {
            result += table[r1][(c1 + 4) % 5];
            result += table[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2) {
            result += table[(r1 + 4) % 5][c1];
            result += table[(r2 + 4) % 5][c2];
        }
        else {
            result += table[r1][c2];
            result += table[r2][c1];
        }
    }
    return result;
}

// ===== Ham chinh =====
int main() {
    cout << "=== Thu vien Ma hoa co dien (C++) ===\n";
    string text, key;
    int choice;
    cout << "1. Caesar\n2. Affine\n3. Hoan vi\n4. Vigenere\n5. Playfair\nLua chon (1-5): ";
    cin >> choice;
    cin.ignore();
    cout << "Nhap van ban: ";
    getline(cin, text);

    if (choice == 1) {
        int shift;
        cout << "Nhap so dich (0-25): ";
        cin >> shift;
        string cipher = caesar_encrypt(text, shift);
        cout << "Ma hoa: " << cipher << "\nGiai ma: " << caesar_decrypt(cipher, shift) << "\n";
    }
    else if (choice == 2) {
        int a, b;
        cout << "Nhap a (nguyen to cung 26) va b: ";
        cin >> a >> b;
        string cipher = affine_encrypt(text, a, b);
        cout << "Ma hoa: " << cipher << "\nGiai ma: " << affine_decrypt(cipher, a, b) << "\n";
    }
    else if (choice == 3) {
        int n;
        cout << "Nhap kich thuoc block: ";
        cin >> n;
        vector<int> perm;
        cout << "Nhap hoan vi (chi so cach nhau boi dau cach, bat dau tu 0): ";
        for (int i = 0; i < n; i++) {
            int val; cin >> val;
            perm.push_back(val);
        }
        string cipher = permute_encrypt(text, perm);
        cout << "Ma hoa: " << cipher << "\nGiai ma: " << permute_decrypt(cipher, perm) << "\n";
    }
    else if (choice == 4) {
        cout << "Nhap khoa: ";
        getline(cin, key);
        string cipher = vigenere_encrypt(text, key);
        cout << "Ma hoa: " << cipher << "\nGiai ma: " << vigenere_decrypt(cipher, key) << "\n";
    }
    else if (choice == 5) {
        cout << "Nhap khoa: ";
        getline(cin, key);
        string cipher = playfair_encrypt(text, key);
        cout << "Ma hoa: " << cipher << "\nGiai ma: " << playfair_decrypt(cipher, key) << "\n";
    }
    else {
        cout << "Lua chon khong hop le\n";
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <random>
#include <iomanip> 
using namespace std;

// Функция замены байтов на соответствующие байты из S-BOX
void sub_bytes(vector<unsigned char>& line) {
    vector<unsigned char> Sbox = {
        // Таблица S-BOX для замены байтов
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
    };

    vector<unsigned char> stolb;
    for (auto i : line) {
        stolb.push_back(Sbox[i]);
    }
    line = stolb;
}

// Функция замены байтов на соответствующие байты из обратной S-BOX
void inv_sub_bytes(vector<unsigned char>& line) {
    vector<unsigned char> inv_sbox_data = {
        // Таблица обратного S-BOX для замены байтов
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
    };

    vector<unsigned char> stolb;
    for (auto i : line) {
        stolb.push_back(inv_sbox_data[i]);
    }
    line = stolb;
}

// Функция для генерации 128-битного мастер-ключа
void generate_master_key(vector<unsigned char>& MASTER_KEY, mt19937_64& mt) {
    // Генерация случайных символов и цифр
    uniform_int_distribution<int> char_and_number('a', 'z' + 10);

    // Заполнение мастер-ключа 8 парами символ-цифра
    for (int i = 0; i < 16; i += 2) {
        unsigned char c = char_and_number(mt);
        MASTER_KEY.push_back(c);
        MASTER_KEY.push_back(char_and_number(mt));
    }
}

// Функция для циклического сдвига строки влево
void shift_rows(vector<unsigned char>& line) {
    if (line.empty()) return;

    unsigned char first = line.front();
    for (size_t i = 0; i < line.size() - 1; ++i) {
        line[i] = line[i + 1];
    }
    line.back() = first;
}

// Функция для циклического сдвига строки вправо
void inv_shift_rows(vector<unsigned char>& line) {
    if (line.empty()) return;

    unsigned char last = line.back();
    for (size_t i = line.size() - 1; i > 0; --i) {
        line[i] = line[i - 1];
    }
    line.front() = last;
}

// Функция для сложения двух векторов по модулю 2 (XOR)
vector<unsigned char> add_round_key(vector<unsigned char>& FIRST, vector<unsigned char>& SECOND) {
    vector<unsigned char> stolb;

    if (FIRST.size() != SECOND.size()) {
        throw invalid_argument("Vectors must have the same size");
    }
    for (int i = 0; i < FIRST.size(); ++i) {
        stolb.push_back(FIRST[i] ^ SECOND[i]);
    }
    return stolb;
}

// Функция для расширения ключа для алгоритма шифрования
void key_expansion(vector<unsigned char>& MASTER_KEY, vector<vector<unsigned char>>& ROUND_KEYS) {
    const int Nk = 4; // Количество 32-битных слов в исходном ключе
    const int Nb = 4; // Количество столбцов в состоянии (всегда 4 для AES)
    const int Nr = 10; // Количество раундов (10 для AES-128)
    vector<unsigned char> Rcon = {
        // Константы Rcon для расширения ключа
        0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a
    };

    ROUND_KEYS.resize(Nb * (Nr + 1), vector<unsigned char>(4));

    // Копирование исходного ключа в раундовые ключи
    for (int i = 0; i < Nk; ++i) {
        ROUND_KEYS[i] = { MASTER_KEY[4 * i], MASTER_KEY[4 * i + 1], MASTER_KEY[4 * i + 2], MASTER_KEY[4 * i + 3] };
    }

    // Расширение ключа
    for (int i = Nk; i < Nb * (Nr + 1); ++i) {
        vector<unsigned char> temp = ROUND_KEYS[i - 1];
        if (i % Nk == 0) {
            shift_rows(temp);  // Сдвиг строки
            sub_bytes(temp);  // Замена байтов через S-BOX
            temp[0] ^= Rcon[i / Nk - 1];  // Применение Rcon
        }
        ROUND_KEYS[i] = {
            static_cast<unsigned char>(ROUND_KEYS[i - Nk][0] ^ temp[0]),
            static_cast<unsigned char>(ROUND_KEYS[i - Nk][1] ^ temp[1]),
            static_cast<unsigned char>(ROUND_KEYS[i - Nk][2] ^ temp[2]),
            static_cast<unsigned char>(ROUND_KEYS[i - Nk][3] ^ temp[3])
        };
    }
}

// Функция умножения в поле Галуа
unsigned char galois_multiply(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    unsigned char carry;

    for (int i = 0; i < 8; ++i) {
        if (b & 1) {
            result ^= a;
        }
        carry = a & 0x80;
        a <<= 1;
        if (carry) {
            a ^= 0x1b;
        }
        b >>= 1;
    }
    return result;
}

// Функция создания таблицы умножения в поле Галуа
vector<unsigned char> generate_mult_table(unsigned char constant) {
    vector<unsigned char> mult_table(256);
    for (int i = 0; i < 256; ++i) {
        mult_table[i] = galois_multiply(i, constant);
    }
    return mult_table;
}

// Генерация таблиц умножения для различных констант
vector<unsigned char> mult_by_2 = generate_mult_table(2);
vector<unsigned char> mult_by_3 = generate_mult_table(3);
vector<unsigned char> mult_by_14 = generate_mult_table(14);
vector<unsigned char> mult_by_9 = generate_mult_table(9);
vector<unsigned char> mult_by_13 = generate_mult_table(13);
vector<unsigned char> mult_by_11 = generate_mult_table(11);

// Функция для смешивания колонок
void mix_column(vector<unsigned char>& line, const vector<unsigned char>& mult_by_2, const vector<unsigned char>& mult_by_3) {
    vector<unsigned char> stolb;
    stolb.push_back(mult_by_2[line[0]] ^ mult_by_3[line[1]] ^ line[2] ^ line[3]);
    stolb.push_back(mult_by_2[line[1]] ^ mult_by_3[line[2]] ^ line[0] ^ line[3]);
    stolb.push_back(mult_by_2[line[2]] ^ mult_by_3[line[3]] ^ line[0] ^ line[1]);
    stolb.push_back(mult_by_2[line[3]] ^ mult_by_3[line[0]] ^ line[1] ^ line[2]);
    line = stolb;
}

// Функция для обратного смешивания колонок
void inv_mix_columns(vector<unsigned char>& line, const vector<unsigned char>& mult_by_14, const vector<unsigned char>& mult_by_9, const vector<unsigned char>& mult_by_13, const vector<unsigned char>& mult_by_11) {
    vector<unsigned char> stolb;
    stolb.push_back(mult_by_14[line[0]] ^ mult_by_9[line[1]] ^ mult_by_13[line[2]] ^ mult_by_11[line[3]]);
    stolb.push_back(mult_by_14[line[1]] ^ mult_by_9[line[2]] ^ mult_by_13[line[3]] ^ mult_by_11[line[0]]);
    stolb.push_back(mult_by_14[line[2]] ^ mult_by_9[line[3]] ^ mult_by_13[line[0]] ^ mult_by_11[line[1]]);
    stolb.push_back(mult_by_14[line[3]] ^ mult_by_9[line[0]] ^ mult_by_13[line[1]] ^ mult_by_11[line[2]]);
    line = stolb;
}

// Функция для генерации блоков из текста
void block_generate(string& text, vector<vector<vector<unsigned char>>>& BLOCK) {
    // Добавление пробелов в конец текста, чтобы его длина была кратна 16
    while (text.size() % 16 != 0) {
        text += ' ';
    }

    vector<vector<vector<unsigned char>>> stolb;
    vector<vector<unsigned char>> sixteen(4, vector<unsigned char>(4));

    // Разделение текста на блоки и заполнение матрицы
    for (int i = 0; i < text.size(); ++i) {
        int a = (i % 16) % 4; // Выбор строки внутри блока
        int b = (i % 16) / 4; // Выбор столбца внутри блока
        sixteen[a][b] = text[i];

        // Если блок заполнен, добавляем его в вектор и начинаем новый блок
        if ((i + 1) % 16 == 0) {
            stolb.push_back(sixteen);
            sixteen = vector<vector<unsigned char>>(4, vector<unsigned char>(4));
        }
    }
    BLOCK = stolb;
}

// Функция для шифрования блока
vector<vector<unsigned char>> CIPHER(vector<vector<unsigned char>>& BLOCK, vector<vector<unsigned char>>& ROUND_KEYS, vector<unsigned char> MASTER_KEY) {
    vector<vector<unsigned char>> stolb(4, vector<unsigned char>(4, 0));

    // Первый раунд - AddRoundKey с исходным ключом
    for (int i = 0; i < 4; ++i) {
        stolb[i] = add_round_key(BLOCK[i], ROUND_KEYS[i]);
    }

    // Прохождение через 9 раундов шифрования
    for (int i = 1; i <= 9; i++) {
        for (int j = 0; j <= 3; j++) {
            sub_bytes(stolb[j]); // Замена байтов
            shift_rows(stolb[j]); // Сдвиг строк
            mix_column(stolb[j], mult_by_2, mult_by_3); // Смешивание колонок
            stolb[j] = add_round_key(stolb[j], ROUND_KEYS[i]); // Добавление раундового ключа
        }
    }

    // Финальный раунд шифрования
    for (int j = 0; j <= 3; j++) {
        sub_bytes(stolb[j]);
        shift_rows(stolb[j]);
        stolb[j] = add_round_key(stolb[j], ROUND_KEYS[10]);
    }

    return stolb;
}

// Функция для расшифрования блока
vector<vector<unsigned char>> DECIPHER(vector<vector<unsigned char>>& BLOCK, vector<vector<unsigned char>>& ROUND_KEYS, vector<unsigned char> MASTER_KEY) {
    vector<vector<unsigned char>> round_keys(44, vector<unsigned char>(4));
    key_expansion(MASTER_KEY, round_keys);

    vector<vector<unsigned char>> stolb(4, vector<unsigned char>(4, 0));

    // Первый этап - AddRoundKey с последним раундовым ключом
    for (int j = 0; j <= 3; j++) {
        stolb[j] = add_round_key(BLOCK[j], ROUND_KEYS[10]);
    }

    // Прохождение через 9 раундов расшифрования
    for (int i = 9; i >= 1; i--) {
        for (int j = 0; j <= 3; j++) {
            stolb[j] = add_round_key(stolb[j], ROUND_KEYS[i]);
            inv_mix_columns(stolb[j], mult_by_14, mult_by_9, mult_by_13, mult_by_11); // Обратное смешивание колонок
            inv_shift_rows(stolb[j]); // Обратный сдвиг строк
            inv_sub_bytes(stolb[j]); // Обратная замена байтов
        }
    }

    // Финальный этап расшифрования
    for (int j = 0; j <= 3; j++) {
        stolb[j] = add_round_key(stolb[j], ROUND_KEYS[0]);
    }
    for (int j = 0; j <= 3; j++) {
        inv_shift_rows(stolb[j]);
        inv_sub_bytes(stolb[j]);
    }

    return stolb;
}

int main() {
    SetConsoleCP(1251);        // Установка кодировки консоли для корректного ввода/вывода русских символов
    SetConsoleOutputCP(1251);

    mt19937_64 mt(random_device{}());
    string text;
    cout << "Input text for cipher >> ";
    getline(cin, text);

    vector<vector<vector<unsigned char>>> BLOCK;   // Генерация блоков из текста
    block_generate(text, BLOCK);
    cout << "----------------------------------------------";
    cout << "\nThe encryption block: \n";
    for (auto i : BLOCK) {
        for (auto j : i) {
            for (auto k : j) {
                cout << setw(4) << k << " ";
            }
            cout << endl;
        }
    }
    cout << "\n----------------------------------------------" << endl;

    vector<unsigned char> MASTER_KEY;
    generate_master_key(MASTER_KEY, mt); // Генерация случайного ключа
    cout << "128-bit master key: ";
    for (auto i : MASTER_KEY) {
        cout << i;
    }
    cout << "\n----------------------------------------------\n";

    vector<vector<unsigned char>> ROUND_KEYS;
    key_expansion(MASTER_KEY, ROUND_KEYS); // Генерация раундовых ключей
    cout << "Generated keys: \n";
    for (auto i : ROUND_KEYS) {
        for (auto j : i) {
            cout << hex << setw(4) << static_cast<int>(j) << " ";
        }
        cout << endl;
    }
    cout << "\n----------------------------------------------" << endl;

    vector<vector<unsigned char>> PREV(4, vector<unsigned char>(4, 0));
    vector<vector<unsigned char>> DEFOLT = PREV;
    vector<vector<unsigned char>> TEK;
    vector<vector<vector<unsigned char>>> ECRYPT;

    // Шифрование блоков
    for (int i = 0; i < BLOCK.size(); i++) {
        vector<vector<unsigned char>> res(4, vector<unsigned char>(4, 0));
        vector<vector<unsigned char>> B = BLOCK[i];
        TEK = CIPHER(PREV, ROUND_KEYS, MASTER_KEY); // Шифрование текущего блока

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res[i][j] = (TEK[i][j] ^ B[i][j]); // XOR с предыдущим зашифрованным блоком
            }
        }
        ECRYPT.push_back(res); // Добавление зашифрованного блока в результат
        PREV = TEK; // Обновление предыдущего блока
    }

    cout << "The final cipher after encryption:\n" << endl;
    for (auto t : ECRYPT) {
        for (auto i : t) {
            for (auto j : i) {
                cout << setw(4) << j << " ";
            }
            cout << endl;
        }
    }

    cout << "\n----------------------------------------------\n";

    PREV = DEFOLT;
    vector<vector<vector<unsigned char>>> DECRYPT;

    // Дешифрование блоков
    for (int i = 0; i < ECRYPT.size(); ++i) {
        vector<vector<unsigned char>> res(4, vector<unsigned char>(4, 0));
        vector<vector<unsigned char>> B = ECRYPT[i];

        TEK = CIPHER(PREV, ROUND_KEYS, MASTER_KEY); // Шифрование предыдущего блока

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res[i][j] = (B[i][j] ^ TEK[i][j]); // XOR с текущим зашифрованным блоком
            }
        }
        DECRYPT.push_back(res); // Добавление расшифрованного блока в результат
        PREV = TEK; // Обновление предыдущего блока
    }

    vector<vector<vector<unsigned char>>> DECRYPT_1;

    // Финальное расшифрование блоков
    for (int i = 0; i < ECRYPT.size(); ++i) {
        vector<vector<unsigned char>> res(4, vector<unsigned char>(4, 0));
        vector<vector<unsigned char>> B = ECRYPT[i];

        TEK = DECIPHER(B, ROUND_KEYS, MASTER_KEY); // Дешифрование текущего блока

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res[i][j] = TEK[i][j]; // Копирование расшифрованных байтов
            }
        }
        DECRYPT_1.push_back(res); // Добавление расшифрованного блока в результат
    }

    cout << "Message after decryption:\n" << endl;
    for (int i = 0; i < DECRYPT.size(); i++) {
        vector<vector<unsigned char>>& decrypt = DECRYPT[i];
        for (int j = 0; j < decrypt.size(); j++) {
            for (int k = 0; k < decrypt[j].size(); k++) {
                cout << decrypt[k][j]; // Вывод расшифрованного сообщения
            }
        }
    }
    cout << "\n----------------------------------------------\n" << endl;

    return 0;
}

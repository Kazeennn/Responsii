#include <iostream>
#include <fstream>
using namespace std;

const int MAKS_MATKUL = 100;
const int PANJANG_NAMA = 50;

struct Matkul {
    char nama[PANJANG_NAMA];
    int sks;
    int nilai;
};

Matkul daftarMatkul[MAKS_MATKUL];
int jumlahMatkul = 0;

// Fungsi salin string (pengganti strcpy)
void salinString(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Fungsi banding string (pengganti strcmp)
int bandingkanString(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

void tambahMatkul() {
    if (jumlahMatkul >= MAKS_MATKUL) {
        cout << "Data penuh!\n";
        return;
    }

    cout << "\nMasukkan nama matkul: ";
    cin.ignore();
    cin.getline(daftarMatkul[jumlahMatkul].nama, PANJANG_NAMA);
    cout << "Masukkan jumlah SKS: ";
    cin >> daftarMatkul[jumlahMatkul].sks;
    cout << "Masukkan nilai: ";
    cin >> daftarMatkul[jumlahMatkul].nilai;

    jumlahMatkul++;
    cout << "Matkul berhasil ditambahkan!\n";
}

void hitungSPP() {
    int totalSKS = 0;
    for (int i = 0; i < jumlahMatkul; i++) {
        totalSKS += daftarMatkul[i].sks;
    }
    int spp = totalSKS * 150000;
    cout << "Total SKS: " << totalSKS << "\n";
    cout << "Total SPP yang harus dibayar: Rp" << spp << "\n";
}

void sortingNilai(bool ascending) {
    for (int i = 0; i < jumlahMatkul - 1; i++) {
        for (int j = i + 1; j < jumlahMatkul; j++) {
            bool kondisi = ascending
                ? (daftarMatkul[i].nilai > daftarMatkul[j].nilai)
                : (daftarMatkul[i].nilai < daftarMatkul[j].nilai);
            if (kondisi) {
                Matkul temp = daftarMatkul[i];
                daftarMatkul[i] = daftarMatkul[j];
                daftarMatkul[j] = temp;
            }
        }
    }

    cout << "\n--- Nilai Setelah Sorting ---\n";
    for (int i = 0; i < jumlahMatkul; i++) {
        cout << daftarMatkul[i].nama << " - Nilai: " << daftarMatkul[i].nilai << "\n";
    }
}

void cariMatkul() {
    char dicari[PANJANG_NAMA];
    cout << "Masukkan nama matkul yang dicari: ";
    cin.ignore();
    cin.getline(dicari, PANJANG_NAMA);

    bool ditemukan = false;
    for (int i = 0; i < jumlahMatkul; i++) {
        if (bandingkanString(daftarMatkul[i].nama, dicari) == 0) {
            cout << "Ditemukan: " << daftarMatkul[i].nama
                 << " | SKS: " << daftarMatkul[i].sks
                 << " | Nilai: " << daftarMatkul[i].nilai << "\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Matkul tidak ditemukan.\n";
    }
}

void simpanKRSkeFile() {
    ofstream file("krs.txt");
    if (!file) {
        cout << "Gagal menyimpan file!\n";
        return;
    }

    file << "=== KARTU RENCANA STUDI ===\n";
    for (int i = 0; i < jumlahMatkul; i++) {
        file << daftarMatkul[i].nama << " | SKS: " << daftarMatkul[i].sks
             << " | Nilai: " << daftarMatkul[i].nilai << "\n";
    }
    file.close();
    cout << "KRS berhasil disimpan ke file krs.txt\n";
}

void lihatKRSdariFile() {
    ifstream file("krs.txt");
    if (!file) {
        cout << "File krs.txt tidak ditemukan!\n";
        return;
    }

    char baris[200];
    while (file.getline(baris, 200)) {
        cout << baris << "\n";
    }
    file.close();
}

int main() {
    int pilihan;
    do {
        cout << "\n===== PORTAL MAHASISWA =====\n";
        cout << "1. Tambah Mata Kuliah\n";
        cout << "2. Hitung Pembayaran SPP\n";
        cout << "3. Sorting Nilai\n";
        cout << "4. Cari Mata Kuliah\n";
        cout << "5. Simpan KRS ke File\n";
        cout << "6. Lihat KRS dari File\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahMatkul(); break;
            case 2: hitungSPP(); break;
            case 3: {
                int mode;
                cout << "1. Sorting Ascending\n2. Sorting Descending\nPilih: ";
                cin >> mode;
                sortingNilai(mode == 1);
                break;
            }
            case 4: cariMatkul(); break;
            case 5: simpanKRSkeFile(); break;
            case 6: lihatKRSdariFile(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}


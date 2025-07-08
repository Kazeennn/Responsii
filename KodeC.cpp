#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAKS_MATKUL = 100;

struct Matkul {
    string nama;
    int sks;
    int nilai;
};

Matkul daftarMatkul[MAKS_MATKUL];
int jumlahMatkul = 0;

void tambahMatkul() {
    if (jumlahMatkul >= MAKS_MATKUL) {
        cout << "Data penuh!\n";
        return;
    }

    cout << "\nMasukkan nama matkul: ";
    cin.ignore();
    getline(cin, daftarMatkul[jumlahMatkul].nama);
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
            bool kondisi = ascending ? (daftarMatkul[i].nilai > daftarMatkul[j].nilai) :
                                       (daftarMatkul[i].nilai < daftarMatkul[j].nilai);
            if (kondisi) {
                swap(daftarMatkul[i], daftarMatkul[j]);
            }
        }
    }

    cout << "\n--- Nilai Setelah Sorting ---\n";
    for (int i = 0; i < jumlahMatkul; i++) {
        cout << daftarMatkul[i].nama << " - Nilai: " << daftarMatkul[i].nilai << "\n";
    }
}

void cariMatkul() {
    string dicari;
    cout << "Masukkan nama matkul yang dicari: ";
    cin.ignore();
    getline(cin, dicari);

    bool ditemukan = false;
    for (int i = 0; i < jumlahMatkul; i++) {
        if (daftarMatkul[i].nama == dicari) {
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
        file << daftarMatkul[i].nama << " | SKS: " << daftarMatkul[i].sks << " | Nilai: " << daftarMatkul[i].nilai << "\n";
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

    string baris;
    while (getline(file, baris)) {
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

#include <iostream>
#include <string>
#include <fstream> // <=== Tambahan penting
using namespace std;

const int MAKS_BARANG = 100;

struct Barang {
    string nama;
    int harga;
    int stok;
    string kategori;
};

Barang daftarBarang[MAKS_BARANG];
int jumlahBarang = 0;

void tambahBarang() {
    if (jumlahBarang >= MAKS_BARANG) {
        cout << "Data penuh!\n";
        return;
    }

    cout << "Masukkan nama barang: ";
    cin.ignore();
    getline(cin, daftarBarang[jumlahBarang].nama);
    cout << "Masukkan harga: ";
    cin >> daftarBarang[jumlahBarang].harga;
    cout << "Masukkan stok: ";
    cin >> daftarBarang[jumlahBarang].stok;
    cin.ignore();
    cout << "Masukkan kategori: ";
    getline(cin, daftarBarang[jumlahBarang].kategori);

    jumlahBarang++;
    cout << "Barang berhasil ditambahkan!\n";
}

void tampilkanBarang() {
    if (jumlahBarang == 0) {
        cout << "Tidak ada data barang.\n";
        return;
    }

    cout << "\nDaftar Barang:\n";
    for (int i = 0; i < jumlahBarang; i++) {
        cout << i + 1 << ". " << daftarBarang[i].nama
             << " | Harga: " << daftarBarang[i].harga
             << " | Stok: " << daftarBarang[i].stok
             << " | Kategori: " << daftarBarang[i].kategori << "\n";
    }
}

void cariBarang() {
    if (jumlahBarang == 0) {
        cout << "Data kosong.\n";
        return;
    }

    string keyword;
    cout << "Masukkan nama barang yang dicari: ";
    cin.ignore();
    getline(cin, keyword);

    bool ditemukan = false;
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].nama == keyword) {
            cout << "Ditemukan: " << daftarBarang[i].nama
                 << " | Harga: " << daftarBarang[i].harga
                 << " | Stok: " << daftarBarang[i].stok
                 << " | Kategori: " << daftarBarang[i].kategori << "\n";
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Barang tidak ditemukan.\n";
    }
}

void editBarang() {
    string namaCari;
    cout << "Masukkan nama barang yang ingin diubah: ";
    cin.ignore();
    getline(cin, namaCari);

    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].nama == namaCari) {
            cout << "Masukkan nama baru: ";
            getline(cin, daftarBarang[i].nama);
            cout << "Masukkan harga baru: ";
            cin >> daftarBarang[i].harga;
            cout << "Masukkan stok baru: ";
            cin >> daftarBarang[i].stok;
            cin.ignore();
            cout << "Masukkan kategori baru: ";
            getline(cin, daftarBarang[i].kategori);
            cout << "Barang berhasil diubah.\n";
            return;
        }
    }

    cout << "Barang tidak ditemukan.\n";
}

void urutkanBarang() {
    if (jumlahBarang == 0) {
        cout << "Tidak ada data untuk diurutkan.\n";
        return;
    }

    int pilihanSort;
    cout << "\n=== PILIHAN SORTING ===\n";
    cout << "1. Urutkan berdasarkan Nama (A-Z)\n";
    cout << "2. Urutkan berdasarkan Kategori (A-Z)\n";
    cout << "3. Urutkan berdasarkan Harga (Termurah - Termahal)\n";
    cout << "Pilihan: ";
    cin >> pilihanSort;

    for (int i = 0; i < jumlahBarang - 1; i++) {
        for (int j = 0; j < jumlahBarang - i - 1; j++) {
            bool tukar = false;
            switch (pilihanSort) {
                case 1:
                    if (daftarBarang[j].nama > daftarBarang[j + 1].nama)
                        tukar = true;
                    break;
                case 2:
                    if (daftarBarang[j].kategori > daftarBarang[j + 1].kategori)
                        tukar = true;
                    break;
                case 3:
                    if (daftarBarang[j].harga > daftarBarang[j + 1].harga)
                        tukar = true;
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
                    return;
            }

            if (tukar) {
                Barang temp = daftarBarang[j];
                daftarBarang[j] = daftarBarang[j + 1];
                daftarBarang[j + 1] = temp;
            }
        }
    }

    cout << "Data berhasil diurutkan!\n";
}

void laporanSimulasi() {
    cout << "\n=== Simulasi Laporan Barang (layar) ===\n";

    ofstream file("laporan_barang.txt");
    if (!file) {
        cout << "Gagal membuka file untuk ditulis!\n";
        return;
    }

    for (int i = 0; i < jumlahBarang; i++) {
        cout << daftarBarang[i].nama << "," << daftarBarang[i].harga
             << "," << daftarBarang[i].stok << "," << daftarBarang[i].kategori << "\n";

        file << daftarBarang[i].nama << "," << daftarBarang[i].harga
             << "," << daftarBarang[i].stok << "," << daftarBarang[i].kategori << "\n";
    }

    cout << "=== Akhir Laporan ===\n";
    file.close();
    cout << "Laporan juga telah disimpan ke file 'laporan_barang.txt'.\n";
}

int main() {
    int pilihan;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Cari Barang\n";
        cout << "4. Edit Barang\n";
        cout << "5. Urutkan Barang\n";
        cout << "6. Lihat Simulasi Laporan (.txt)\n";
        cout << "7. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahBarang(); break;
            case 2: tampilkanBarang(); break;
            case 3: cariBarang(); break;
            case 4: editBarang(); break;
            case 5: urutkanBarang(); break;
            case 6: laporanSimulasi(); break;
            case 7: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 7);

    return 0;
}

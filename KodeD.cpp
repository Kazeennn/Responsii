#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAKS_TIKET = 100;

struct Tiket {
    string namaPenumpang;
    string maskapai;
    string tujuan;
    int harga;
};

Tiket daftarTiket[MAKS_TIKET];
int jumlahTiket = 0;

void tambahTiket() {
    if (jumlahTiket >= MAKS_TIKET) {
        cout << "Data tiket penuh.\n";
        return;
    }

    cout << "Nama Penumpang: ";
    cin.ignore();
    getline(cin, daftarTiket[jumlahTiket].namaPenumpang);
    cout << "Maskapai: ";
    getline(cin, daftarTiket[jumlahTiket].maskapai);
    cout << "Tujuan: ";
    getline(cin, daftarTiket[jumlahTiket].tujuan);
    cout << "Harga Tiket: ";
    cin >> daftarTiket[jumlahTiket].harga;

    jumlahTiket++;
    cout << "Tiket berhasil ditambahkan.\n";
}

void tampilkanTiket() {
    if (jumlahTiket == 0) {
        cout << "Belum ada tiket.\n";
        return;
    }

    cout << "=== Daftar Tiket ===\n";
    for (int i = 0; i < jumlahTiket; i++) {
        cout << i + 1 << ". " << daftarTiket[i].namaPenumpang
             << " | " << daftarTiket[i].maskapai
             << " | " << daftarTiket[i].tujuan
             << " | Rp" << daftarTiket[i].harga << endl;
    }
}

void pesanTiket() {
    string maskapaiCari;
    int budget;
    cout << "Masukkan Maskapai: ";
    cin.ignore();
    getline(cin, maskapaiCari);
    cout << "Masukkan Budget Anda: ";
    cin >> budget;

    bool ditemukan = false;
    for (int i = 0; i < jumlahTiket; i++) {
        if (daftarTiket[i].maskapai == maskapaiCari && daftarTiket[i].harga <= budget) {
            cout << "Tiket Tersedia: " << daftarTiket[i].namaPenumpang
                 << " | " << daftarTiket[i].tujuan
                 << " | Rp" << daftarTiket[i].harga << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) cout << "Tiket tidak ditemukan sesuai kriteria.\n";
}

void editTiket() {
    tampilkanTiket();
    int index;
    cout << "Pilih nomor tiket yang ingin diedit: ";
    cin >> index;

    if (index < 1 || index > jumlahTiket) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    int i = index - 1;
    cout << "Edit Nama Penumpang (sebelumnya " << daftarTiket[i].namaPenumpang << "): ";
    cin.ignore();
    getline(cin, daftarTiket[i].namaPenumpang);
    cout << "Edit Maskapai (sebelumnya " << daftarTiket[i].maskapai << "): ";
    getline(cin, daftarTiket[i].maskapai);
    cout << "Edit Tujuan (sebelumnya " << daftarTiket[i].tujuan << "): ";
    getline(cin, daftarTiket[i].tujuan);
    cout << "Edit Harga Tiket (sebelumnya Rp" << daftarTiket[i].harga << "): ";
    cin >> daftarTiket[i].harga;

    cout << "Tiket berhasil diperbarui.\n";
}

void hapusTiket() {
    tampilkanTiket();
    int index;
    cout << "Pilih nomor tiket yang ingin dihapus: ";
    cin >> index;

    if (index < 1 || index > jumlahTiket) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    for (int i = index - 1; i < jumlahTiket - 1; i++) {
        daftarTiket[i] = daftarTiket[i + 1];
    }

    jumlahTiket--;
    cout << "Tiket berhasil dihapus.\n";
}

void simpanKeFile() {
    ofstream file("tiket_pesawat.txt");
    for (int i = 0; i < jumlahTiket; i++) {
        file << daftarTiket[i].namaPenumpang << ","
             << daftarTiket[i].maskapai << ","
             << daftarTiket[i].tujuan << ","
             << daftarTiket[i].harga << endl;
    }
    file.close();
    cout << "Data tiket berhasil disimpan ke tiket_pesawat.txt\n";
}

int main() {
    int pilihan;
    do {
        cout << "\n=== MENU TIKET PESAWAT ===\n";
        cout << "1. Tambah Tiket\n";
        cout << "2. Tampilkan Tiket\n";
        cout << "3. Pesan Tiket Berdasarkan Maskapai & Harga\n";
        cout << "4. Edit Tiket\n";
        cout << "5. Hapus Tiket\n";
        cout << "6. Simpan ke File\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahTiket(); break;
            case 2: tampilkanTiket(); break;
            case 3: pesanTiket(); break;
            case 4: editTiket(); break;
            case 5: hapusTiket(); break;
            case 6: simpanKeFile(); break;
            case 7: cout << "Keluar program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 7);

    return 0;
}

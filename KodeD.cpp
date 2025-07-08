#include <iostream>
#include <fstream>
using namespace std;

const int MAKS_TIKET = 100;
const int PANJANG = 50;

struct Tiket {
    char namaPenumpang[PANJANG];
    char maskapai[PANJANG];
    char tujuan[PANJANG];
    int harga;
};

Tiket daftarTiket[MAKS_TIKET];
int jumlahTiket = 0;

void salinString(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int bandingString(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

void tambahTiket() {
    if (jumlahTiket >= MAKS_TIKET) {
        cout << "Data tiket penuh.\n";
        return;
    }

    cout << "Nama Penumpang: ";
    cin.ignore();
    cin.getline(daftarTiket[jumlahTiket].namaPenumpang, PANJANG);
    cout << "Maskapai: ";
    cin.getline(daftarTiket[jumlahTiket].maskapai, PANJANG);
    cout << "Tujuan: ";
    cin.getline(daftarTiket[jumlahTiket].tujuan, PANJANG);
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
    char maskapaiCari[PANJANG];
    int budget;
    cout << "Masukkan Maskapai: ";
    cin.ignore();
    cin.getline(maskapaiCari, PANJANG);
    cout << "Masukkan Budget Anda: ";
    cin >> budget;

    bool ditemukan = false;
    for (int i = 0; i < jumlahTiket; i++) {
        if (bandingString(daftarTiket[i].maskapai, maskapaiCari) == 0 &&
            daftarTiket[i].harga <= budget) {
            cout << "Tiket Tersedia: " << daftarTiket[i].namaPenumpang
                 << " | " << daftarTiket[i].tujuan
                 << " | Rp" << daftarTiket[i].harga << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan)
        cout << "Tiket tidak ditemukan sesuai kriteria.\n";
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
    cin.getline(daftarTiket[i].namaPenumpang, PANJANG);
    cout << "Edit Maskapai (sebelumnya " << daftarTiket[i].maskapai << "): ";
    cin.getline(daftarTiket[i].maskapai, PANJANG);
    cout << "Edit Tujuan (sebelumnya " << daftarTiket[i].tujuan << "): ";
    cin.getline(daftarTiket[i].tujuan, PANJANG);
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


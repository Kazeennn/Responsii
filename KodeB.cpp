#include <iostream>
#include <fstream>
using namespace std;

const int MAKS_SISWA = 100;
const int MAKS_MAPEL = 10;
const int PANJANG_NAMA = 50;

struct Siswa {
    char nama[PANJANG_NAMA];
    int nilai[MAKS_MAPEL];
};

Siswa daftarSiswa[MAKS_SISWA];
char namaMapel[MAKS_MAPEL][PANJANG_NAMA];
int jumlahSiswa = 0, jumlahMapel = 0;

// Fungsi untuk menyalin string (pengganti strcpy)
void salinString(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Fungsi untuk membandingkan string (pengganti strcmp)
int bandingkanString(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

void inputMapel() {
    cout << "Masukkan jumlah mata pelajaran: ";
    cin >> jumlahMapel;
    cin.ignore();
    for (int i = 0; i < jumlahMapel; i++) {
        cout << "Nama mapel ke-" << i + 1 << ": ";
        cin.getline(namaMapel[i], PANJANG_NAMA);
    }
}

void tambahDataSiswa() {
    if (jumlahSiswa >= MAKS_SISWA) {
        cout << "Kapasitas siswa penuh!\n";
        return;
    }

    cin.ignore();
    cout << "Masukkan nama siswa: ";
    cin.getline(daftarSiswa[jumlahSiswa].nama, PANJANG_NAMA);

    for (int i = 0; i < jumlahMapel; i++) {
        cout << "Nilai " << namaMapel[i] << ": ";
        cin >> daftarSiswa[jumlahSiswa].nilai[i];
    }

    jumlahSiswa++;
    cout << "Data siswa berhasil ditambahkan.\n";
}

void tampilkanData() {
    cout << "\nData Nilai Siswa:\n";
    for (int i = 0; i < jumlahSiswa; i++) {
        cout << daftarSiswa[i].nama << ": ";
        for (int j = 0; j < jumlahMapel; j++) {
            cout << namaMapel[j] << "=" << daftarSiswa[i].nilai[j];
            if (j != jumlahMapel - 1) cout << ", ";
        }
        cout << "\n";
    }
}

void statistikMapel() {
    for (int i = 0; i < jumlahMapel; i++) {
        int total = 0, max = -1, min = 101;
        char siswaMax[PANJANG_NAMA], siswaMin[PANJANG_NAMA];

        for (int j = 0; j < jumlahSiswa; j++) {
            int nilai = daftarSiswa[j].nilai[i];
            total += nilai;
            if (nilai > max) {
                max = nilai;
                salinString(siswaMax, daftarSiswa[j].nama);
            }
            if (nilai < min) {
                min = nilai;
                salinString(siswaMin, daftarSiswa[j].nama);
            }
        }

        float rata = (float)total / jumlahSiswa;
        cout << "\nMapel: " << namaMapel[i] << "\n";
        cout << "Rata-rata: " << rata << "\n";
        cout << "Tertinggi: " << max << " oleh " << siswaMax << "\n";
        cout << "Terendah: " << min << " oleh " << siswaMin << "\n";
    }
}

void histogramSimulasi() {
    for (int i = 0; i < jumlahMapel; i++) {
        cout << "\nDistribusi nilai untuk " << namaMapel[i] << ":\n";
        int rentang[5] = {0};

        for (int j = 0; j < jumlahSiswa; j++) {
            int nilai = daftarSiswa[j].nilai[i];
            if (nilai < 60) rentang[0]++;
            else if (nilai < 70) rentang[1]++;
            else if (nilai < 80) rentang[2]++;
            else if (nilai < 90) rentang[3]++;
            else rentang[4]++;
        }

        const char* label[5] = {"<60", "60-69", "70-79", "80-89", "90-100"};
        for (int k = 0; k < 5; k++) {
            cout << label[k] << ": ";
            for (int x = 0; x < rentang[k]; x++) cout << "*";
            cout << " (" << rentang[k] << ")\n";
        }
    }
}

void laporanSimulasi() {
    ofstream file("laporan_nilai.txt");

    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }

    file << "=== LAPORAN NILAI SISWA ===\n\n";
    file << "Nama Siswa\t";
    for (int i = 0; i < jumlahMapel; i++) {
        file << namaMapel[i] << "\t";
    }
    file << "Total\tRata-rata\n";

    for (int i = 0; i < jumlahSiswa; i++) {
        int totalNilai = 0;
        file << daftarSiswa[i].nama << "\t";
        for (int j = 0; j < jumlahMapel; j++) {
            int nilai = daftarSiswa[i].nilai[j];
            file << nilai << "\t";
            totalNilai += nilai;
        }
        float rata = (float)totalNilai / jumlahMapel;
        file << totalNilai << "\t" << rata << "\n";
    }

    file << "\n=== STATISTIK PER MATA PELAJARAN ===\n";

    for (int i = 0; i < jumlahMapel; i++) {
        int total = 0, max = -1, min = 101;
        char siswaMax[PANJANG_NAMA], siswaMin[PANJANG_NAMA];

        for (int j = 0; j < jumlahSiswa; j++) {
            int nilai = daftarSiswa[j].nilai[i];
            total += nilai;
            if (nilai > max) {
                max = nilai;
                salinString(siswaMax, daftarSiswa[j].nama);
            }
            if (nilai < min) {
                min = nilai;
                salinString(siswaMin, daftarSiswa[j].nama);
            }
        }

        float rata = (float)total / jumlahSiswa;
        file << "\nMata Pelajaran: " << namaMapel[i] << "\n";
        file << "Rata-rata: " << rata << "\n";
        file << "Nilai Tertinggi: " << max << " oleh " << siswaMax << "\n";
        file << "Nilai Terendah: " << min << " oleh " << siswaMin << "\n";
    }

    file.close();
    cout << "Laporan lengkap berhasil disimpan ke 'laporan_nilai.txt'.\n";
}

int main() {
    int pilihan;
    inputMapel();

    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah data siswa\n";
        cout << "2. Tampilkan semua data\n";
        cout << "3. Statistik per mata pelajaran\n";
        cout << "4. Distribusi nilai (histogram)\n";
        cout << "5. Simulasi laporan nilai ke file\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahDataSiswa(); break;
            case 2: tampilkanData(); break;
            case 3: statistikMapel(); break;
            case 4: histogramSimulasi(); break;
            case 5: laporanSimulasi(); break;
            case 6: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}


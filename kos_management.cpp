#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

void header() {
    cout << "=======================================" << endl;
    cout << "      SISTEM PENGELOLAAN KOS" << endl;
    cout << "        3 TINGKAT KUALITAS" << endl;
    cout << "=======================================" << endl;
}

void garis() {
    cout << "---------------------------------------" << endl;
}

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void bersihLayar() {
    system("cls");
}

void menu() {
    cout << "\n======== MENU UTAMA ========" << endl;
    cout << "1. Tambah Penyewa Baru" << endl;
    cout << "2. Lihat Status Kamar" << endl;
    cout << "3. Lihat Data Penyewa" << endl;
    cout << "4. Update Status Bayar" << endl;
    cout << "5. Hapus Data Penyewa" << endl;
    cout << "6. Backup Data ke File" << endl;
    cout << "0. Keluar Program" << endl;
    cout << "=============================" << endl;
    cout << "Masukkan pilihan Anda: ";
}

void simpanDataKeFile(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], int totalPenyewa) {
    ofstream file("data_penyewa.txt");
    
    if (!file.is_open()) {
        cout << "Error: Tidak bisa membuka file untuk menyimpan!" << endl;
        return;
    }
    
    file << totalPenyewa << endl;
    
    for (int i = 0; i < totalPenyewa; i++) {
        file << nama[i] << endl;
        file << kamar[i] << endl;
        file << durasi[i] << endl;
        file << bayar[i] << endl;
        file << telepon[i] << endl;
    }
    
    file.close();
    cout << "Data berhasil disimpan ke file 'data_penyewa.txt'" << endl;
}

int muatDataDariFile(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], string statusKamar[]) {
    ifstream file("data_penyewa.txt");
    int totalPenyewa = 0;
    
    if (!file.is_open()) {
        cout << "File 'data_penyewa.txt' tidak ditemukan. Memulai dengan data kosong." << endl;
        return 0;
    }
    
    file >> totalPenyewa;
    file.ignore();
    
    for (int i = 0; i < totalPenyewa; i++) {
        getline(file, nama[i]);
        file >> kamar[i];
        file >> durasi[i];
        file >> bayar[i];
        file >> telepon[i];
        file.ignore();
        
        statusKamar[kamar[i]] = "Terisi";
    }
    
    file.close();
    cout << "Data berhasil dimuat dari file. Total penyewa: " << totalPenyewa << endl;
    return totalPenyewa;
}

void backupData(string nama[], int kamar[], int durasi[], string bayar[], string telepon[], int totalPenyewa, string tipeKamar[], int hargaKamar[]) {
    string namaFile = "backup_data_penyewa.txt";
    ofstream file(namaFile.c_str());
    
    if (!file.is_open()) {
        cout << "Error: Tidak bisa membuat file backup!" << endl;
        return;
    }
    
    file << "=====================================================================" << endl;
    file << "                    SISTEM PENGELOLAAN KOS" << endl;
    file << "                      DATA PENYEWA KOS" << endl;
    file << "=====================================================================" << endl;
    file << "Total Penyewa Terdaftar: " << totalPenyewa << " orang" << endl;
    file << "=====================================================================" << endl;
    file << endl;
    
    if (totalPenyewa == 0) {
        file << "Tidak ada data penyewa yang terdaftar." << endl;
        file.close();
        cout << "Backup berhasil dibuat: " << namaFile << endl;
        return;
    }
    
    file << "+----+---------------+-------+--------+---------+----------+---------------+" << endl;
    file << "| No |     Nama      | Kamar | Durasi |  Tipe   |  Status  |  Total Biaya  |" << endl;
    file << "+----+---------------+-------+--------+---------+----------+---------------+" << endl;
    
    for (int i = 0; i < totalPenyewa; i++) {
        int totalBiaya = hargaKamar[kamar[i]] * durasi[i];
        file << "| " << setw(2) << (i+1) << " | " 
             << setw(13) << nama[i] << " |   " 
             << setw(2) << kamar[i] << "  |  " 
             << setw(2) << durasi[i] << " bl | " 
             << setw(7) << tipeKamar[kamar[i]] << " | " 
             << setw(8) << bayar[i] << " | Rp " 
             << setw(10) << totalBiaya << " |" << endl;
    }
    
    file << "+----+---------------+-------+--------+---------+----------+---------------+" << endl;
    file << endl;
    
    file << "=====================================================================" << endl;
    file << "                        DETAIL LENGKAP" << endl;
    file << "=====================================================================" << endl;
    
    for (int i = 0; i < totalPenyewa; i++) {
        file << endl;
        file << "PENYEWA #" << (i+1) << endl;
        file << "---------------------------------------------------------------------" << endl;
        file << "Nama Lengkap    : " << nama[i] << endl;
        file << "Nomor Telepon   : " << telepon[i] << endl;
        file << "Nomor Kamar     : " << kamar[i] << " (Tipe " << tipeKamar[kamar[i]] << ")" << endl;
        file << "Durasi Sewa     : " << durasi[i] << " bulan" << endl;
        file << "Harga per Bulan : Rp " << hargaKamar[kamar[i]] << endl;
        file << "Status Bayar    : " << bayar[i] << endl;
        file << "Total Biaya     : Rp " << (hargaKamar[kamar[i]] * durasi[i]) << endl;
        file << "---------------------------------------------------------------------" << endl;
    }
    
    file << endl;
    file << "=====================================================================" << endl;
    file << "                       INFORMASI KAMAR" << endl;
    file << "=====================================================================" << endl;
    file << "TIPE REGULER (Kamar 1-5)  : Rp 500.000/bulan" << endl;
    file << "TIPE VIP     (Kamar 6-10) : Rp 800.000/bulan" << endl;
    file << "TIPE PREMIUM (Kamar 11-15): Rp 1.200.000/bulan" << endl;
    file << "=====================================================================" << endl;
    
    file.close();
    cout << "Backup berhasil dibuat: " << namaFile << endl;
}

void tampilStatusKamar(string status[], int harga[], string tipe[]) {
    cout << "\n========== STATUS KAMAR ==========" << endl;
    cout << "+--------+----------+---------+---------------+" << endl;
    cout << "| Kamar  |  Status  |  Tipe   |     Harga     |" << endl;
    cout << "+--------+----------+---------+---------------+" << endl;
    
    for (int i = 1; i <= 15; i++) {
        cout << "|   " << setw(2) << i << "   | " << setw(8) << status[i] 
             << " | " << setw(7) << tipe[i] 
             << " | Rp " << setw(9) << harga[i] << " |" << endl;
    }
    cout << "+--------+----------+---------+---------------+" << endl;
}

void tampilDataPenyewa(string nama[], int kamar[], int durasi[], 
                      string bayar[], string tipe[], int harga[], int total) {
    cout << "\n================ DATA PENYEWA ================" << endl;
    
    if (total == 0) {
        cout << "Belum ada data penyewa yang terdaftar." << endl;
        return;
    }
    
    cout << "+----+---------------+-------+--------+---------+----------+---------------+" << endl;
    cout << "| No |     Nama      | Kamar | Durasi |  Tipe   |  Status  |  Total Biaya  |" << endl;
    cout << "+----+---------------+-------+--------+---------+----------+---------------+" << endl;
    
    for (int i = 0; i < total; i++) {
        int totalBiaya = harga[kamar[i]] * durasi[i];
        cout << "| " << setw(2) << (i+1) << " | " << setw(13) << nama[i] 
             << " |   " << setw(2) << kamar[i] 
             << "  |  " << setw(2) << durasi[i] << " bl | " << setw(7) << tipe[kamar[i]]
             << " | " << setw(8) << bayar[i] 
             << " | Rp " << setw(10) << totalBiaya << " |" << endl;
    }
    cout << "+----+---------------+-------+--------+---------+----------+---------------+" << endl;
}

void tampilKamarKosong(string status[], int harga[], string tipe[]) {
    cout << "\nKamar yang tersedia:" << endl;
    garis();
    
    bool adaKosong = false;
    
    for (int i = 1; i <= 15; i++) {
        if (status[i] == "Kosong") {
            cout << "Kamar " << setw(2) << i << " - Tipe " << setw(7) << tipe[i] 
                 << " - Rp " << setw(7) << harga[i] << "/bulan" << endl;
            adaKosong = true;
        }
    }
    
    if (!adaKosong) {
        cout << "Maaf, semua kamar sudah terisi!" << endl;
    }
}

void inisialisasiKamar(string status[], int harga[], string tipe[]) {
    for (int i = 1; i <= 15; i++) {
        status[i] = "Kosong";
        
        if (i <= 5) {
            tipe[i] = "Reguler";
            harga[i] = 500000;
        } else if (i <= 10) {
            tipe[i] = "VIP";
            harga[i] = 800000;
        } else {
            tipe[i] = "Premium";
            harga[i] = 1200000;
        }
    }
}

void tampilTipeKamar() {
    cout << "\n======== INFORMASI TIPE KAMAR ========" << endl;
    cout << "TIPE REGULER (Kamar 1-5)  : Rp 500.000/bulan" << endl;
    cout << "TIPE VIP     (Kamar 6-10) : Rp 800.000/bulan" << endl;
    cout << "TIPE PREMIUM (Kamar 11-15): Rp 1.200.000/bulan" << endl;
    cout << "=======================================" << endl;
}

void tampilStatistik(string status[], string bayar[], int total) {
    int kamarTerisi = 0;
    int sudahLunas = 0;
    int belumLunas = 0;
    
    for (int i = 1; i <= 15; i++) {
        if (status[i] == "Terisi") {
            kamarTerisi++;
        }
    }
    
    for (int i = 0; i < total; i++) {
        if (bayar[i] == "Lunas") {
            sudahLunas++;
        } else {
            belumLunas++;
        }
    }
    
    cout << "\n========== STATISTIK KOS ==========" << endl;
    cout << "Total Kamar        : 15 kamar" << endl;
    cout << "Kamar Terisi       : " << kamarTerisi << " kamar" << endl;
    cout << "Kamar Kosong       : " << (15 - kamarTerisi) << " kamar" << endl;
    cout << "Pembayaran Lunas   : " << sudahLunas << " penyewa" << endl;
    cout << "Pembayaran Belum   : " << belumLunas << " penyewa" << endl;
    cout << "===================================" << endl;
}

int main() {
    string nama[25];
    int kamar[25];
    int durasi[25];
    string bayar[25];
    string telepon[25];
    
    string statusKamar[16];
    int hargaKamar[16];
    string tipeKamar[16];
    
    inisialisasiKamar(statusKamar, hargaKamar, tipeKamar);
    
    int totalPenyewa = muatDataDariFile(nama, kamar, durasi, bayar, telepon, statusKamar);
    int pilihan;
    
    bersihLayar();
    header();
    
    cout << "\nSelamat datang di Sistem Pengelolaan Kos!" << endl;
    cout << "Sistem ini mengelola 15 kamar dengan 3 tipe kualitas." << endl;
    
    tampilTipeKamar();
    pause();
    
    do {
        bersihLayar();
        header();
        tampilStatistik(statusKamar, bayar, totalPenyewa);
        menu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                bersihLayar();
                header();
                cout << "\n========== TAMBAH PENYEWA BARU ==========" << endl;
                
                if (totalPenyewa >= 25) {
                    cout << "Maaf! Kapasitas maksimal 25 penyewa sudah penuh." << endl;
                    pause();
                    break;
                }
                
                tampilKamarKosong(statusKamar, hargaKamar, tipeKamar);
                
                bool adaKosong = false;
                for (int i = 1; i <= 15; i++) {
                    if (statusKamar[i] == "Kosong") {
                        adaKosong = true;
                        break;
                    }
                }
                
                if (!adaKosong) {
                    pause();
                    break;
                }
                
                cout << "\n--- INPUT DATA PENYEWA ---" << endl;
                cout << "Nama penyewa: ";
                cin >> nama[totalPenyewa];
                
                cout << "Nomor telepon: ";
                cin >> telepon[totalPenyewa];
                
                do {
                    cout << "Nomor kamar (1-15): ";
                    cin >> kamar[totalPenyewa];
                    
                    if (kamar[totalPenyewa] < 1 || kamar[totalPenyewa] > 15) {
                        cout << "Error: Nomor kamar harus antara 1-15!" << endl;
                        continue;
                    }
                    
                    if (statusKamar[kamar[totalPenyewa]] == "Terisi") {
                        cout << "Error: Kamar sudah terisi! Pilih kamar lain." << endl;
                        continue;
                    }
                    
                    break;
                } while (true);
                
                cout << "Durasi sewa (bulan): ";
                cin >> durasi[totalPenyewa];
                
                cout << "Status pembayaran (Lunas/Belum): ";
                cin >> bayar[totalPenyewa];
                
                statusKamar[kamar[totalPenyewa]] = "Terisi";
                totalPenyewa++;
                
                simpanDataKeFile(nama, kamar, durasi, bayar, telepon, totalPenyewa);
                
                cout << "\nBERHASIL! Penyewa baru telah ditambahkan." << endl;
                cout << "Tipe kamar: " << tipeKamar[kamar[totalPenyewa-1]] << endl;
                cout << "Biaya per bulan: Rp " << hargaKamar[kamar[totalPenyewa-1]] << endl;
                cout << "Total biaya: Rp " << (hargaKamar[kamar[totalPenyewa-1]] * durasi[totalPenyewa-1]) << endl;
                
                pause();
                break;
            }
            
            case 2: {
                bersihLayar();
                header();
                tampilStatusKamar(statusKamar, hargaKamar, tipeKamar);
                pause();
                break;
            }
            
            case 3: {
                bersihLayar();
                header();
                tampilDataPenyewa(nama, kamar, durasi, bayar, tipeKamar, hargaKamar, totalPenyewa);
                
                if (totalPenyewa > 0) {
                    cout << "\nDetail lengkap penyewa:" << endl;
                    garis();
                    
                    for (int i = 0; i < totalPenyewa; i++) {
                        cout << "\nPenyewa #" << (i+1) << endl;
                        cout << "Nama           : " << nama[i] << endl;
                        cout << "Telepon        : " << telepon[i] << endl;
                        cout << "Kamar          : " << kamar[i] << " (Tipe " << tipeKamar[kamar[i]] << ")" << endl;
                        cout << "Durasi         : " << durasi[i] << " bulan" << endl;
                        cout << "Status Bayar   : " << bayar[i] << endl;
                        cout << "Total Biaya    : Rp " << (hargaKamar[kamar[i]] * durasi[i]) << endl;
                        garis();
                    }
                }
                
                pause();
                break;
            }
            
            case 4: {
                bersihLayar();
                header();
                cout << "\n========== UPDATE STATUS BAYAR ==========" << endl;
                
                if (totalPenyewa == 0) {
                    cout << "Belum ada data penyewa untuk diupdate." << endl;
                    pause();
                    break;
                }
                
                cout << "\nDaftar semua penyewa:" << endl;
                garis();
                
                for (int i = 0; i < totalPenyewa; i++) {
                    cout << (i+1) << ". " << nama[i] << " - Kamar " << kamar[i] 
                         << " - Status: " << bayar[i] << endl;
                }
                
                int nomorPenyewa;
                cout << "\nPilih nomor penyewa yang akan diupdate: ";
                cin >> nomorPenyewa;
                
                if (nomorPenyewa >= 1 && nomorPenyewa <= totalPenyewa) {
                    if (bayar[nomorPenyewa-1] == "Belum") {
                        bayar[nomorPenyewa-1] = "Lunas";
                        simpanDataKeFile(nama, kamar, durasi, bayar, telepon, totalPenyewa);
                        cout << "\nBERHASIL! Status pembayaran " << nama[nomorPenyewa-1] 
                             << " telah diubah menjadi LUNAS." << endl;
                        cout << "Total yang dibayar: Rp " 
                             << (hargaKamar[kamar[nomorPenyewa-1]] * durasi[nomorPenyewa-1]) << endl;
                    } else {
                        cout << "Pembayaran penyewa ini sudah lunas sebelumnya." << endl;
                    }
                } else {
                    cout << "Error: Nomor penyewa tidak valid!" << endl;
                }
                
                pause();
                break;
            }
            
            case 5: {
                bersihLayar();
                header();
                cout << "\n========== HAPUS DATA PENYEWA ==========" << endl;
                
                if (totalPenyewa == 0) {
                    cout << "Belum ada data penyewa untuk dihapus." << endl;
                    pause();
                    break;
                }
                
                tampilDataPenyewa(nama, kamar, durasi, bayar, tipeKamar, hargaKamar, totalPenyewa);
                
                int nomorHapus;
                cout << "\nPilih nomor penyewa yang akan dihapus: ";
                cin >> nomorHapus;
                
                if (nomorHapus >= 1 && nomorHapus <= totalPenyewa) {
                    cout << "\nAnda yakin ingin menghapus data penyewa: " 
                         << nama[nomorHapus-1] << "? (y/n): ";
                    char konfirmasi;
                    cin >> konfirmasi;
                    
                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        statusKamar[kamar[nomorHapus-1]] = "Kosong";
                        
                        for (int i = nomorHapus-1; i < totalPenyewa-1; i++) {
                            nama[i] = nama[i+1];
                            kamar[i] = kamar[i+1];
                            durasi[i] = durasi[i+1];
                            bayar[i] = bayar[i+1];
                            telepon[i] = telepon[i+1];
                        }
                        
                        totalPenyewa--;
                        simpanDataKeFile(nama, kamar, durasi, bayar, telepon, totalPenyewa);
                        cout << "\nBERHASIL! Data penyewa telah dihapus." << endl;
                    } else {
                        cout << "Penghapusan dibatalkan." << endl;
                    }
                } else {
                    cout << "Error: Nomor penyewa tidak valid!" << endl;
                }
                
                pause();
                break;
            }
            
            case 6: {
                bersihLayar();
                header();
                cout << "\n========== BACKUP DATA ==========" << endl;
                
                if (totalPenyewa == 0) {
                    cout << "Tidak ada data untuk di-backup." << endl;
                } else {
                    backupData(nama, kamar, durasi, bayar, telepon, totalPenyewa, tipeKamar, hargaKamar);
                }
                
                pause();
                break;
            }
            
            case 0: {
                bersihLayar();
                header();
                cout << "\n========== TERIMA KASIH ==========" << endl;
                cout << "Program Sistem Pengelolaan Kos telah selesai." << endl;
                cout << "Data tersimpan otomatis di file 'data_penyewa.txt'" << endl;
                cout << "Sampai jumpa kembali!" << endl;
                cout << "==================================" << endl;
                break;
            }
            
            default: {
                cout << "\nERROR! Pilihan tidak valid." << endl;
                cout << "Silakan pilih menu 0-6 saja." << endl;
                pause();
                break;
            }
        }
        
    } while (pilihan != 0);
    
    return 0;
}



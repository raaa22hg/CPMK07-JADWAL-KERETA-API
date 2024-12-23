#include <iostream> // Library untuk input dan output
#include <vector>   // Library untuk penggunaan vector
#include <fstream>  // Library untuk file handling
#include <string>   // Library untuk penggunaan string
using namespace std;

// ADT (Abstract Data Type) Jadwal Kereta
struct JadwalKereta
{
    string namaKereta;           // Nama kereta
    string stasiunKeberangkatan; // Stasiun keberangkatan
    string stasiunTujuan;        // Stasiun tujuan
    string jamBerangkat;         // Jam keberangkatan
    string jamTiba;              // Jam tiba
    string status;               // Status kereta (misalnya: on time, delayed)
};

// Fungsi untuk input data jadwal kereta
void inputJadwal(JadwalKereta &jadwal)
{
    cout << "Masukkan Nama Kereta: ";
    cin.ignore();                    // Mengabaikan karakter newline yang tersisa di buffer
    getline(cin, jadwal.namaKereta); // Mengambil input string dengan spasi
    cout << "Masukkan Stasiun Keberangkatan: ";
    getline(cin, jadwal.stasiunKeberangkatan);
    cout << "Masukkan Stasiun Tujuan: ";
    getline(cin, jadwal.stasiunTujuan);
    cout << "Masukkan Jam Berangkat (HH:MM): ";
    getline(cin, jadwal.jamBerangkat);
    cout << "Masukkan Jam Tiba (HH:MM): ";
    getline(cin, jadwal.jamTiba);
    cout << "Masukkan Status (misal: on time, delayed): ";
    getline(cin, jadwal.status);
}

// Fungsi untuk menyimpan data ke file CSV
void simpanKeCSV(const string &filename, const vector<JadwalKereta> &jadwalList)
{
    ofstream file(filename); // Membuka file dengan nama yang diberikan
    file << "Nama Kereta,Stasiun Keberangkatan,Stasiun Tujuan,Jam Berangkat,Jam Tiba,Status\n";
    // Menulis header ke file CSV
    for (const auto &jadwal : jadwalList)
    { // Loop melalui setiap elemen dalam daftar jadwal
        file << jadwal.namaKereta << ","
             << jadwal.stasiunKeberangkatan << ","
             << jadwal.stasiunTujuan << ","
             << jadwal.jamBerangkat << ","
             << jadwal.jamTiba << ","
             << jadwal.status << "\n"; // Menulis data jadwal ke file CSV
    }
    file.close(); // Menutup file
}

// Fungsi untuk mencari jadwal berdasarkan nama kereta
vector<JadwalKereta> cariJadwal(const vector<JadwalKereta> &jadwalList, const string &namaKereta)
{
    vector<JadwalKereta> hasil; // Vektor untuk menyimpan hasil pencarian
    for (const auto &jadwal : jadwalList)
    { // Loop melalui setiap elemen dalam daftar jadwal
        if (jadwal.namaKereta == namaKereta)
        {                            // Memeriksa apakah nama kereta sesuai
            hasil.push_back(jadwal); // Menambahkan jadwal ke hasil jika sesuai
        }
    }
    return hasil; // Mengembalikan hasil pencarian
}

// Fungsi untuk menampilkan jadwal
void tampilkanJadwal(const vector<JadwalKereta> &jadwalList)
{
    for (const auto &jadwal : jadwalList)
    { // Loop melalui setiap elemen dalam daftar jadwal
        cout << "Nama Kereta: " << jadwal.namaKereta
             << ", Stasiun Keberangkatan: " << jadwal.stasiunKeberangkatan
             << ", Stasiun Tujuan: " << jadwal.stasiunTujuan
             << ", Jam Berangkat: " << jadwal.jamBerangkat
             << ", Jam Tiba: " << jadwal.jamTiba
             << ", Status: " << jadwal.status << endl; // Menampilkan data jadwal ke layar
    }
}

int main()
{
    vector<JadwalKereta> jadwalList;      // Vektor untuk menyimpan daftar jadwal kereta
    string filename = "jadwalKereta.csv"; // Nama file CSV untuk menyimpan data
    int pilihan;                          // Variabel untuk menyimpan pilihan menu

    // Simpan header ke file CSV
    ofstream file(filename); // Membuka file dengan nama yang diberikan
    file << "Nama Kereta,Stasiun Keberangkatan,Stasiun Tujuan,Jam Berangkat,Jam Tiba,Status\n";
    // Menulis header ke file CSV
    file.close(); // Menutup file

    do
    {
        // Menampilkan menu dan meminta input dari pengguna
        cout << "Menu:\n"
             << "1. Input Jadwal Kereta\n"
             << "2. Cari Jadwal Kereta\n"
             << "3. Tampilkan Semua Jadwal\n"
             << "4. Keluar\n"
             << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1)
        {
            JadwalKereta jadwal;               // Membuat objek JadwalKereta baru
            inputJadwal(jadwal);               // Meminta input dari pengguna untuk jadwal baru
            jadwalList.push_back(jadwal);      // Menambahkan jadwal ke daftar
            simpanKeCSV(filename, jadwalList); // Menyimpan daftar jadwal ke file CSV
        }
        else if (pilihan == 2)
        {
            string namaKereta; // Variabel untuk menyimpan nama kereta yang dicari
            cout << "Masukkan Nama Kereta untuk Dicari: ";
            cin.ignore();             // Mengabaikan karakter newline yang tersisa di buffer
            getline(cin, namaKereta); // Mengambil input nama kereta
            vector<JadwalKereta> hasil = cariJadwal(jadwalList, namaKereta);
            // Mencari jadwal berdasarkan nama kereta
            tampilkanJadwal(hasil); // Menampilkan hasil pencarian
        }
        else if (pilihan == 3)
        {
            tampilkanJadwal(jadwalList); // Menampilkan semua jadwal dalam daftar
        }
        else if (pilihan == 4)
        {
            cout << "Keluar dari program." << endl; // Menampilkan pesan keluar
        }
    } while (pilihan != 4);

    return 0; // Mengakhiri program
}
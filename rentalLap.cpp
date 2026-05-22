#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Booking {
    int id;
    string nama, lapangan;
    int tanggal, jam;
    Booking *next;
};

Booking *head = NULL;
Booking *tail = NULL;

bool cekID(int id){
    Booking *bantu = head;
    while(bantu != NULL){
        if(bantu->id == id) return true;
        bantu = bantu->next;
    }
    return false;
}

int inputAngka(string pesan){
    int x;
    while(true){
        cout << pesan;
        cin >> x;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input harus angka!\n";
        } else break;
    }
    cin.ignore();
    return x;
}

string inputString(string pesan){
    string x;
    do{
        cout << pesan;
        getline(cin, x);
        if(x == "") cout << "Tidak boleh kosong!\n";
    }while(x == "");
    return x;
}

void tambahBooking(int id, string nama, string lapangan, int tanggal, int jam){
    Booking *baru = new Booking;
    baru->id = id;
    baru->nama = nama;
    baru->lapangan = lapangan;
    baru->tanggal = tanggal;
    baru->jam = jam;
    baru->next = NULL;

    if(head == NULL) head = tail = baru;
    else {
        tail->next = baru;
        tail = baru;
    }

    cout << "Booking berhasil ditambahkan!\n";
}

void tambahBookingFile(int id, string nama, string lapangan, int tanggal, int jam){
    Booking *baru = new Booking;
    baru->id = id;
    baru->nama = nama;
    baru->lapangan = lapangan;
    baru->tanggal = tanggal;
    baru->jam = jam;
    baru->next = NULL;

    if(head == NULL) head = tail = baru;
    else {
        tail->next = baru;
        tail = baru;
    }
}

int main(){
    int pilih;

    do{
        cout << "\n=================================\n";
        cout << "      BOOKING LAPANGAN\n";
        cout << "=================================\n";
        cout << "1. Tambah Booking\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Data\n";
        cout << "4. Sorting Tanggal & Jam\n";
        cout << "5. Simpan ke File\n";
        cout << "6. Baca dari File\n";
        cout << "7. Hapus Data\n";
        cout << "8. Edit Data\n";
        cout << "0. Keluar\n";
        cout << "=================================\n";

        pilih = inputAngka("Pilih menu: ");

        if(pilih == 1){
            int id;
            do{
                id = inputAngka("ID: ");
                if(cekID(id)) cout << "ID sudah ada!\n";
            }while(cekID(id));

            string nama = inputString("Nama: ");
            string lapangan = inputString("Lapangan: ");
            int tanggal = inputAngka("Tanggal: ");
            int jam = inputAngka("Jam: ");

            tambahBooking(id, nama, lapangan, tanggal, jam);
        }
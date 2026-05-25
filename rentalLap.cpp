#include <iostream>
#include <iomanip>
#include <cstdio>
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
}

void tampil(){
    if(head == NULL){
        cout << "\nData kosong!\n";
        return;
    }

    cout << "\n===========================================================\n";
    cout << left << setw(5) << "No"
         << setw(5) << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Lapangan"
         << setw(10) << "Tanggal"
         << setw(5) << "Jam" << endl;
    cout << "===========================================================\n";

    void simpanFile(){
    FILE *file = fopen("booking.txt", "w");

    if(file == NULL){
        cout << "Gagal membuka file untuk menulis!\n";
        return;
    }

    Booking *bantu = head;

    while(bantu != NULL){
        fprintf(file, "%d,%s,%s,%d,%d\n",
                bantu->id,
                bantu->nama.c_str(),
                bantu->lapangan.c_str(),
                bantu->tanggal,
                bantu->jam);

        bantu = bantu->next;
    }

    fclose(file);
    cout << "Data berhasil disimpan ke booking.txt\n";
}

void bacaFile(){
    FILE *file = fopen("booking.txt", "r");

    if(file == NULL){
        cout << "File belum ada atau gagal dibuka!\n";
        return;
    }

    while(head != NULL){
        Booking *hapus = head;
        head = head->next;
        delete hapus;
    }

    tail = NULL;

    int id, tanggal, jam;
    char nama[100], lapangan[100];

    while(fscanf(file, "%d,%[^,],%[^,],%d,%d\n",
                 &id,
                 nama,
                 lapangan,
                 &tanggal,
                 &jam) != EOF){

        tambahBooking(id,
                       string(nama),
                       string(lapangan),
                       tanggal,
                       jam);
    }

    fclose(file);
    cout << "Data berhasil dibaca dari booking.txt\n";
}

    Booking *bantu = head;
    int no = 1;

    while(bantu != NULL){
        cout << left << setw(5) << no++
             << setw(5) << bantu->id
             << setw(20) << bantu->nama
             << setw(15) << bantu->lapangan
             << setw(10) << bantu->tanggal
             << setw(5) << bantu->jam << endl;
        bantu = bantu->next;
    }
    cout << "===========================================================\n";
}

int main(){
    int pilih;
    do{
        cout << "\n=================================\n";
        cout << "       BOOKING LAPANGAN\n";
        cout << "=================================\n";
        cout << "1. Tambah Booking\n";
        cout << "2. Tampilkan Data\n";
        cout << "5. Simpan ke File\n";
        cout << "6. Baca dari File\n";
        cout << "0. Keluar\n";
        cout << "=================================\n";

        pilih = inputAngka("Pilih menu: ");

        switch(pilih){
            case 1: {
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
                cout << "Booking berhasil ditambahkan!\n";
                break;
            }
            case 2:
                tampil();
                break;
            case 5:
                simpanFile();
                break;           
            case 6:
                bacaFile();
                break;
            case 0:
                break;
            default:
                cout << "Pilihan menu tidak valid!\n";
                break;
        }
    }while(pilih != 0);

    while(head != NULL){
        Booking *hapus = head;
        head = head->next;
        delete hapus;
    }
    return 0;
}
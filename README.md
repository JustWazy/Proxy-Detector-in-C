# Proxy-Detector-in-C
[![language](https://img.shields.io/badge/language-C-239120)](/)
[![OS](https://img.shields.io/badge/OS-linux-0078D4)](/)

## How to use
```shell
git clone https://github.com/JustWazy/Proxy-Detector-in-C.git
apt update
apt install libcurl4-openssl-dev
gcc proxyscanner.c -o proxyscanner -lcurl
./proxyscanner
```

## About Script
Script C ini dirancang untuk memeriksa apakah sebuah alamat IP adalah proxy dengan menggunakan API dari `ipinfo.app`, setelah pengguna memasukkan alamat IP yang ingin diperiksa, program membuat permintaan HTTP menggunakan pustaka `libcurl` ke API tersebut, Data respons kemudian diproses melalui fungsi callback untuk menyimpan hasilnya dalam struktur data, jika respons dari API adalah "Y" program menyimpulkan bahwa ip tersebut adalah proxy dan menampilkan pesan kepada pengguna, jika bukan "Y" maka ip dianggap bukan proxy, script ini menggabungkan teknik HTTP request dengan manipulasi data dinamis menjadikannya contoh aplikasi jaringan sederhana dalam bahasa C yang saya gunakan untuk pembelajaran.

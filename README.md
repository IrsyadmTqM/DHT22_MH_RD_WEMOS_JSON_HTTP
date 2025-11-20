# 📡 DHT22 & Rain Sensor JSON Sender via ESP8266 + Node.js HTTP Server

Project ini menggunakan **ESP8266 (Wemos D1 Mini)** untuk membaca sensor **DHT22 (temperature & humidity)** dan **sensor hujan MH-RD**, kemudian mengirimkan data dalam bentuk **JSON via HTTP POST** ke **server Node.js**.

Server Node.js menerima data tersebut, menyimpannya sebagai *data terakhir*, dan menyediakan endpoint untuk mengambil data melalui:

➡️ **GET `/ambil_data`**

---

## 🔧 Hardware yang Digunakan

| Komponen      | Keterangan |
|---------------|------------|
| Wemos D1 Mini | ESP8266 board |
| DHT22         | Sensor temperatur & kelembaban |
| MH-RD         | Sensor hujan analog |
| Kabel jumper  | Penghubung |
| Breadboard    | Opsional |

---

## 🔌 Wiring

| Sensor | Pin ESP8266 |
|--------|-------------|
| DHT22  | D4          |
| MH-RD  | A0          |
| VCC    | 3.3V        |
| GND    | GND         |

---

## 💻 Cara Penggunaan

### 📱 1. Upload Kode ke ESP8266

Pastikan library berikut sudah terinstal:

```cpp
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <DHTesp.h>
```
Lalu isi konfigurasi WiFi dan IP server di file .ino.

🖥️ 2. Jalankan Server Node.js

cd server

npm init -y

npm install express

node server.js


Server akan berjalan pada:

http://localhost:3000

🔁 Endpoint API
Method	Endpoint	Fungsi
POST	/kirim_data	ESP8266 mengirim data
GET	/ambil_data	Mengambil data terakhir
📦 Contoh Data JSON dari ESP8266
{
  "temperature": 28.5,
  "humidity": 65,
  "rain": 1
}


📌 rain = 1 → Tidak hujan
📌 rain = 0 → Hujan

🚀 Contoh Response dari Server (GET /ambil_data)
{
  "status": "success",
  "data": {
    "temperature": 28.5,
    "humidity": 65,
    "rain": 1,
    "timestamp": "2025-11-20T14:30:00.000Z"
  }
}

⚙️ Konfigurasi WiFi & Server di ESP8266
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
const char* serverUrl = "http://192.168.1.10:3000/kirim_data";

🔍 Troubleshooting
Masalah	Solusi
Tidak konek WiFi	Cek SSID & Password
Server error	Pastikan Node.js sudah berjalan
Data tidak muncul	Cek IP server & endpoint
Sensor tidak terbaca	Periksa wiring & library Arduino
📃 License

Proyek ini bersifat open-source. Bebas digunakan dan dimodifikasi.

✨ Jika project ini membantu, jangan lupa ⭐ di GitHub!


const express = require('express');
const app = express();
const port = 3000;

// Supaya Express bisa membaca JSON
app.use(express.json());

// Variabel untuk menyimpan data terakhir
let lastData = {
    temperature: null,
    humidity: null,
    rain_value: null,
    rain_status: null,
    timestamp: null
};

// Endpoint untuk menerima data dari ESP
app.post('/simpan_data', (req, res) => {
    const { temperature, humidity, rain_value, rain_status } = req.body;

    // Simpan data terakhir
    lastData = {
        temperature,
        humidity,
        rain_value,
        rain_status,
        timestamp: new Date().toISOString()
    };

    console.log("📥 Data diterima dari ESP:");
    console.log(lastData);

    res.json({
        message: "Data diterima!",
        received: lastData
    });
});

// Endpoint untuk mengambil data terbaru (GET)
app.get('/ambil_data', (req, res) => {
    if (lastData.temperature === null) {
        res.json({ message: "Belum ada data dari ESP!" });
    } else {
        res.json(lastData);
    }
});

// Jalankan server
app.listen(port, () => {
    console.log(`🚀 Server berjalan di http://localhost:${port}`);
});

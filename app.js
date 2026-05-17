const SerialPort = require('serialport');
const ReadlineParser = require('@serialport/parser-readline');
const mysql = require('mysql2');

const connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '',
    database: 'ArduinoTraffic'
});

const port = new SerialPort.SerialPort({
    path: 'COM3',
    baudRate: 9600
});

const parser = port.pipe(
    new ReadlineParser.ReadlineParser({
        delimiter: '\n'
    })
);

parser.on('data', (data) => {

    console.log("Arduino Verisi:", data);

    const values = data.split(',');

    const vehicleCount = parseInt(values[0]);

    const greenTime = parseInt(values[1]);

    connection.query(
        `INSERT INTO Trafik_Verisi
        (arac_sayisi, yesil_isik_suresi, sensor_id)
        VALUES (?, ?, ?)`,
        [vehicleCount, greenTime, 1],
        (err, result) => {

            if(err)
            {
                console.log(err);
            }
            else
            {
                console.log("Veri Kaydedildi");
            }
        }
    );
});
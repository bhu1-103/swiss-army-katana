const express = require('express');
const bodyParser = require('body-parser');
const { exec } = require('child_process');
const app = express();
const PORT = 8080;
const HOST = '192.168.0.7';

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static('public'));

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/public/index.html');
});

app.post('/shutdown', (req, res) => {
  console.log('Shutdown triggered');
  res.send('<h1>Shutting down…</h1>');
  exec('shutdown now', (error, stdout, stderr) => {
    if (error) {
      console.error(`Error: ${error}`);
      return;
    }
    console.log(`Shutdown stdout: ${stdout}`);
    console.error(`Shutdown stderr: ${stderr}`);
  });
});

app.listen(PORT, HOST, () => {
  console.log(`⚡ Listening on http://${HOST}:${PORT}`);
});

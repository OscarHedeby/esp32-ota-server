const {Storage} = require('@google-cloud/storage');
const {app} = require('../../lib/server_setup/server_setup');
const admin = require('firebase-admin');
// Instantiate a storage client
const storage = new Storage();

admin.initializeApp();
const db = admin.firestore();


/*
  We want an easy way to controle the software running on the esp32 device
  Goals:
    - The ESP should be able to ask which version it should run
    - The ESP should be able to download the .bin from google cloud storage
    - We should be able to roll out newer software versions
    - We should be able to push updates to individual devices

  Endpoints (/spf/ota/):
    (ESP):
      - GET: version: Returns the version a given ESP device should be running
      - GET: update: Should return the version a given device should update to
    (Admin):
      - GET: versions: Should return every available software version
      - POST: version: Should set the recommended version for all devices
      - POST: version?deid: Should set the recommended version for a given device
*/


/*
  (ESP) - version: Returns the version a given ESP device should be running
*/
app.get('/version', (req, res) => {
  // We get the recommended software version from the default settings

  res.status(400).send('0.0.1');
});


/*
  (EPS) - update: Should return the version a given device should update to
*/
app.get('/update', async (req, res) => {
  // Set the headers
  res.setHeader('Content-Type', 'application/octet-stream');

  // This should send the asked for version
  const version = req.query.version;

  let downloadedFile;

  try {
    downloadedFile = storage
        .bucket(process.env.GCLOUD_STORAGE_BUCKET_OTA_UPDATE)
        .file(`${version}.bin`)
        .createReadStream();
  } catch (e) {
    console.error(e);
    res.status(400);
    res.send(e);
    return;
  }

  res.status(200);
  downloadedFile.pipe(res);
});


// Listen to the App Engine-specified port, or 8080 otherwise
const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}...`);
});

module.exports = app;

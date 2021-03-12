const {app} = require('../../lib/server_setup/server_setup');


app.get('/', (req, res) => {
  res.send('Hello world');
});

// Listen to the App Engine-specified port, or 8080 otherwise
const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
  console.log(`Server listening on port ${PORT}...`);
});

module.exports = app;

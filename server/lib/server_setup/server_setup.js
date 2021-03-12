const express = require('express');
const {json, raw, text, urlencoded} = require('body-parser');
const helmet = require('helmet');
const app = express();


app.use(helmet());
app.use(json());
app.use(raw());
app.use(text());
app.use(urlencoded());

exports.app = app;

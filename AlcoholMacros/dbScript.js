var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var session = require('express-session');
var request = require('request');
var mysql = require('mysql');

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);
var mysql = require('./dbcon.js');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static('public'));
app.use(session({ 
    secret: 'password',
    saveUninitialized: true,
    resave: true
}));

app.get('/', function (req, res) {
    res.render('start');
});

app.get('/addItem', function (req, res) {
    res.render('addItem');
});

app.get('/addBrand', function (req, res) {
    res.render('addBrand');
});

app.get('/addGlass', function (req, res) {
    res.render('addGlass');
});

app.get('/insertBrand', function (req, res) {
    res.render('addItem');
});

app.get('/insertGlass', function (req, res) {
    res.render('addItem');
});

app.get('/insertEst', function (req, res) {
    res.render('addItem');
});

app.get('/insert', function (req, res) {
    res.render('start');
});

//check for 404 error
app.use(function (req, res) {
    res.status(404);
    res.render('404');
});

//check for 500 error
app.use(function (err, req, res, next) {
    console.error(err.stack);
    res.type('plain/text');
    res.status(500);
    res.render('500');
});

//output affirmative to node console
app.listen(app.get('port'), function () {
    console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});

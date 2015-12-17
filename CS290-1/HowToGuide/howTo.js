var request = require('request');
var express = require('express');
var ua = require('universal-analytics');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout: 'main'});
var session = require('express-session');
var bodyParser = require('body-parser');
//get google apis
var google = require('googleapis');
//get key info
var key = require('VisVires-fba55597adbe.json');
var uaKey = require('universalAnalytics.json');
//view id
const VIEW_ID = 'ga:112638844';
app.use(ua.middleware(uaKey.tid));


var vistor = ua(uaKey.tid,{https:true}).debug();

vistor.pageview("/","https://52.33.123.15:3000").pageview("/core", "https://52.33.123.15:3000", function(err){
    if(!err){
        console.log(arguments);
    }
});

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static('public'));
app.use(session({
    secret: 'SuperDuperSecret',
    saveUninitialized: true,
    resave: true
}));

app.get('/', function (req, res) {
    res.render('home');
});

app.get('/setup', function (req, res) {
    res.render('setup');
});

app.get('/node', function (req, res) {
    res.render('node');
});

app.get('/universal', function (req, res) {
    res.render('universal');
});

var jwtClient = new google.auth.JWT(key.client_email, null, key.private_key, ['https://www.googleapis.com/auth/analytics.readonly'], null);
app.get('/core', function (req, res, next) {  
    jwtClient.authorize(function (err, tokens) {
        var context = {};
        if (err) {
          next(err);
          return;
        }
        var analytics = google.analytics('v3');
        analytics.data.ga.get({
            'auth': jwtClient,
            'ids': VIEW_ID,
            'metrics': 'ga:pageViews, ga:newUsers', 
            'dimensions': 'ga:country, ga:cityId',
            'start-date': '30daysAgo',
            'end-date': 'yesterday',
            'sort': '-ga:country',
            'max-results': 10,
            'output' : 'dataTable',
            'filters': 'ga:pagePath=~/ch_[-a-z0-9]+[.]html$',
        }, function (err, response) {
              if (err) {
              next(err);
              return;
            }
            console.log(response);
            context.datatable = response.dataTable;
            console.log(response.dataTable);
            context.columnHeaders = response.columnHeaders;
            res.render('core', context);
      });
  });
});


//check for 404 error
app.use(function (req,res) {
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



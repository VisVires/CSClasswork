var request = require('request');
var express = require('express');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout: 'main'});
var session = require('express-session');
var bodyParser = require('body-parser');

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
//get google apis
var google = require('googleapis');
//get key info
var key = require('VisVires-fba55597adbe.json');
//view id
const VIEW_ID = 'ga:112638844';

//JSON Web Token Authorization
var jwtClient = new google.auth.JWT(key.client_email, null, key.private_key, ['https://www.googleapis.com/auth/analytics.readonly'], null);
app.get('/results', function (req, res, next) {  
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
            'filters': 'ga:pagePath=~/ch_[-a-z0-9]+[.]html$',
        }, function (err, response) {
              if (err) {
              next(err);
              return;
            }
            context.response = JSON.stringify(response, null, 4);
            console.log(context.response);
          res.send(context);
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


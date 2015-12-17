var request = require('request');
var express = require('express');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout: 'main'});
var session = require('express-session');
var bodyParser = require('body-parser');
var credentials = require('./credentials.js');

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

function renderPage(res, req, context) {
    context.name = req.session.name;
    context.cityCount = req.session.todo.length || 0;
    context.todo = req.session.todo || [];
    console.log(context.todo);
    res.render('todo', context);
}

app.get('/', function (req, res, next) {
    var context = {};
    //If there is no session, go to the main page.
    if (!req.session.name) {
        res.render('start', context);
        return;
    }
    res.render(res, req, context);
});

app.post('/', function (req, res, next) {
    var context = {};
    if (req.body['New List']) {
        req.session.name = req.body.name;
        req.session.todo = [];
        req.session.curId = 0;
        renderPage(res, req, context);
    }

    //If there is no session, go to the main page.
    if (!req.session.name) {
        res.render('start', context);
        return;
    }

    if (req.body['Done']) {
        req.session.todo = req.session.todo.filter(function (e) {
            return e.id != req.body.id;
        });
        renderPage(res, req, context);
    }

    //Add Cities to List
    if (req.body['Add Item']) {
        request('http://api.openweathermap.org/data/2.5/weather?q=' + req.body.city + '&units=Imperial' + '&APPID=' + credentials.owmKey, function (err, response, body) {
            if (!err && response.statusCode < 400) {
                console.log(body);
                var weather = JSON.parse(body);
                req.session.todo.push({"name": req.body.name, "id": req.session.curId, "city": req.body.city, "temp": weather.main.temp_max});
                req.session.curId++;
                renderPage(res, req, context);
            } else {
                console.log(err);
                if (response) {
                    console.log(response.statusCode);
                }
                next(err);
            }
        });
    }
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

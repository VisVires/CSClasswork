var express = require('express');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout: 'main'});
var session = require('express-session');
var request = require('request');
var bodyparser = require('body-parser');
var mysql = require('./dbcon.js');

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);

app.use(bodyparser.urlencoded({ extended: false }));
app.use(express.static('public'));
app.use(session({
    secret: 'SuperDuperSecret',
    saveUninitialized: true,
    resave: true
}));

app.get('/reset-table', function (req, res, next) {
    var context = {};
    mysql.pool.query("DROP TABLE IF EXISTS workouts", function (err) {
        var createString = "CREATE TABLE workouts(" +
                "id INT PRIMARY KEY AUTO_INCREMENT," +
                "name VARCHAR(255) NOT NULL," +
                "reps INT," +
                "weight INT," +
                "date DATE," +
                "lbs BOOLEAN)";
        mysql.pool.query(createString, function (err) {
            context.results = "Table reset";
            res.render('exercise',context);
        });
    });
});

//start
app.get('/exercise', function (req, res) {
    var context = {};
    res.render('exercise', context);
});

//load table
app.get('/load', function (req, res, next) {
    var context = {};
    mysql.pool.query('SELECT * FROM workouts', function (err, rows, fields) {
        if (err) {
            next(err);
            return;
        }
        var results = JSON.stringify(rows);
        res.send(results);
    });
});

//add row to table
app.get('/insert', function (req, res, next) {
    var context = {};
    mysql.pool.query("INSERT INTO workouts (`name`,`reps`,`weight`,`date`,`lbs`) VALUES (?,?,?,?,?)", [req.query.name, req.query.reps, req.query.weight, req.query.date, req.query.lbs], function (err, result) {
        if (err) {
            next(err);
            return;
        }
        mysql.pool.query('SELECT * FROM workouts', function (err, rows, fields) {
            if (err) {
                next(err);
                return;
            }
            var results = JSON.stringify(rows);
            res.send(results);
        });
    });
});

//return new deleted rows
app.get('/delete', function (req, res, next) {
    var context = {};
    mysql.pool.query("DELETE FROM workouts WHERE id = ?", [req.query.id], function (err, result) {
        if (err) {
            next(err);
            return;
        }
        mysql.pool.query('SELECT * FROM workouts', function (err, rows, fields) {
            if (err) {
                next(err);
                return;
            }
            var results = JSON.stringify(rows);
            res.send(results);
        });
    });
});

//output form for updating
app.get('/update', function (req, res, next) {
    var context = {};
    mysql.pool.query("SELECT * FROM workouts WHERE id=?",[req.query.id], function (err, rows) {
        if (err) {
            next(err);
            return;
        }
        context.edit = rows;
        //send result
        console.log(rows);
        res.render('update', context);
    });
});

//update row
app.get('/simpleUpdate', function (req, res, next) {
    var context = {};
    mysql.pool.query("UPDATE workouts SET name=?, reps=?, weight=?, date=?, lbs=? WHERE id=? ",
        [req.query.name, req.query.reps, req.query.weight, req.query.date, req.query.lbs, req.query.id],
        function (err, result) {
            if (err) {
                next(err);
                return;
            }
            context.results = "Updated " + result.changedRows + " rows.";
            res.render('exercise', context);
        });
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
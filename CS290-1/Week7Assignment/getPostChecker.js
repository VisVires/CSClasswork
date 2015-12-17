/*
URL for site: 52.27.62.191:3000
*/

var express = require('express');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout: 'main'});
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);

//get
app.get('/', function (req, res) {
    var qParams = [];
    //add reqtype to context object
    var context = {};
    context = {"reqType": 'GET'};
    //add qParams array of parameters to context object as datalist
    context.dataList = qParams;
    if (Object.keys(req.query).length === 0)
    	context.reqType = 'NO CONTENT GET';
    //break up map into items and values and output to qParam
    for (var item in req.query){
    	qParams.push({'name':item,'value':req.query[item]})
  	}
  	//move context object to getPost.handlebars
	res.render('getPost', context);
});

//post 
app.post('/', function (req, res) {
	var qParams = [];
	for (var item in req.body){
    		qParams.push({'name':item,'value':req.body[item]})
  	}
	var context = {};
    	context = {"reqType": 'POST'};
	context.dataList = qParams;
	res.render('getPost', context);
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

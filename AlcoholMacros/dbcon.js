var mysql = require('mysql');
var pool = mysql.createPool({
    connectionLimit : 10,
    host            : 'oniddb.cws.oregonstate.edu',
    user            : 'georgew-db',
    password        : 'bCCYYhX7UVXshOjb',
    database        : 'georgew-db'
});

module.exports.pool = pool;
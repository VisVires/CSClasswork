document.addEventListener('DOMContentLoaded', getDrink);
//make ajax request to ajax.php
function getDrink() {
    'use strict';
    document.getElementById('search').addEventListener('click', function (event) {
        //set variables
        var brand = document.getElementById('brand').value;
        var drink = document.getElementById('drink').value;
        var servings = document.getElementById('servings').value;
        //make request
        var req  = new XMLHttpRequest();
        req.open("GET", "ajax.php?brand=" + brand + "&drink=" + drink + "&servings=" + servings, true);
        req.addEventListener('load', function () {
            if (req.status >= 200 && req.status < 400) {
                console.log(req.responseText);
                //add inner html to table
                document.getElementById("drinkTable").innerHTML = req.responseText;
            } else {
                console.log("Error in network request: " + req.statusText);
            }
        });
        req.send(null);
        event.preventDefault();
    });
}


function deleteRow(rowId){
    var req = new XMLHttpRequest();
        req.open("GET", 'http://52.11.111.118:3000/delete?id=' + rowId, true);
        req.addEventListener('load', function () {
            if (req.status >= 200 && req.status < 400) {
                var response = JSON.parse(req.responseText);
                console.log(req.responseText);
                document.getElementById("tbody").innerHTML = "";
                for (var i = 0; i <= response.length - 1; i++) {
                   document.getElementById("tbody").innerHTML += "<tr id='row"+response[i].id+"'><td>"+response[i].name+"</td><td>"+response[i].reps+"</td><td>"+response[i].weight+"</td><td>"+response[i].date+"</td><td>"+isTrue(response[i].lbs)+"</td><td><form action='/update' method='get'><input type='hidden' name= 'id' value='"+response[i].id+"'><input type='submit' name='update' value='Edit'></form></td><td><form action='/delete' onsubmit='deleteRow("+response[i].id+")' method='get'><input type='hidden' name='id' value='"+response[i].id+"'><input type='submit' name='delete' value='Delete'></form></td></tr>";         
                };
               
            } else {
                console.log("Error in network request: " + req.statusText);
            }
        });
        req.send(null);
        event.preventDefault();
}
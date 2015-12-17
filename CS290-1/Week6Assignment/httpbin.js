document.addEventListener("DOMContentLoaded", activateSubmit);
function activateSubmit() {
	document.getElementById('submit').addEventListener('click', function (event) {
	var string = document.getElementById('myText').value;
	var req = new XMLHttpRequest();

	req.open('POST', 'http://httpbin.org/post', true);
	req.setRequestHeader('Content-Type', 'application/json');
	req.addEventListener('load', function () {
		var response = JSON.parse(req.responseText);
		console.log(response.data);
		//alert(response.data);
		document.getElementById('responseData').textContent = response.data;
	});
	req.send(string);
	event.preventDefault();
	});
}
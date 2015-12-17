/*CREATE 4x4 TABLE*/
var newTable = document.createElement("table");
//create rows
for (var i = 0; i < 4; ++i){
	var tr = document.createElement("tr");
	//create data
	for (var j = 1; j < 5; ++j){
		//create headers
		if(i == 0){
			var th = document.createElement("th");
			th.textContent = "Header " + j ;
			styleTable(th);
			tr.appendChild(th);
		}
		//create data cells 
		else {
			var td = document.createElement("td");
			td.textContent= i + "," + j;
			styleTable(td);
			tr.appendChild(td);	
		}
	}
	//append rows
	newTable.appendChild(tr);
}
newTable.id = "userTable";
styleTable(newTable);
document.body.appendChild(newTable);


/*CREATE 4 DIRECTIONAL BUTTONS*/
var directionButtons = document.createElement("div");
for(var i = 0; i < 4; ++i){
	var newButton = document.createElement("button");
	styleButton(newButton);
	switch(i){
		case 0: newButton.textContent = "UP";
				newButton.id = "upButton";
				directionButtons.appendChild(newButton);
				break;
		case 1: newButton.textContent = "DOWN";
				newButton.id = "downButton";
				directionButtons.appendChild(newButton);
				break;
		case 2: newButton.textContent = "LEFT";
				newButton.id = "leftButton";
				directionButtons.appendChild(newButton);
				break;
		case 3: newButton.textContent = "RIGHT";
				newButton.id = "rightButton";
				directionButtons.appendChild(newButton);
				break;
	}	
}
document.body.appendChild(directionButtons);

/*ADD MARK BUTTON*/
var newButton = document.createElement("button");
newButton.textContent = "MARK CELL";
newButton.id = "markButton";
styleButton(newButton);
document.body.appendChild(newButton);

//create cell "array"
var cells = document.getElementById("userTable").getElementsByTagName("td");
 
/*SET UP ELEMENTS STYLE*/
function styleButton(nb){
	nb.style.border = "1px solid black";
	nb.style.marginLeft = "10px";
	nb.style.marginTop = "20px";
	nb.style.backgroundColor = "red";
	nb.style.color = "white";
}

function styleTable(el){
	el.style.border = "1px solid black";
	el.style.textAlign = "center";
	el.style.marginLeft = "10px";
}


/*Button Click Functions*/
//set current
var current = 0;
//set upper left cell as current on load
document.addEventListener("DOMContentLoaded", selectCell);

document.getElementById("upButton").addEventListener("click", function selectUp(){
	if(current > 3){
		deselectCell();
		current = current - 4;
		selectCell(); 
	} //else {console.log("Too Far");}
});

document.getElementById("downButton").addEventListener("click", function selectDown(){
	if (current < 8){
		deselectCell();
		current = current + 4;
		selectCell(); 
	} //else {console.log("Too Far");}
});

document.getElementById("leftButton").addEventListener("click", function selectLeft(){
	if((current%4 != 0)){
		deselectCell();
		current = current - 1;
		selectCell();
	} //else {console.log("Too Far");} 
});

document.getElementById("rightButton").addEventListener("click", function selectRight(){
	if((current+1)%4 != 0){ 
		deselectCell();
		current = current + 1;
		selectCell();				
	} //else {console.log("Too Far");}
});

document.getElementById("markButton").addEventListener("click", function markCell(){
	cells[current].style.backgroundColor = "yellow"; 
});

/*Helper Functions*/
function selectCell(){
	cells[current].style.outlineStyle = "solid";
	cells[current].style.outlineWidth = "4px";
}

function deselectCell(){
	cells[current].style.outlineStyle = "none";
}	


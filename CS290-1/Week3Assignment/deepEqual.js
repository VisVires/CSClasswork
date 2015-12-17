function deepEqual(item_1, item_2){
	//make sure types are the same
	if(typeof item_1 != typeof item_2){
		return false;
	}
	//base case
	if(item_1 === item_2){
		return true;
	}

	//if item_1 or item_2 are not objects or they are null
	if (typeof item_1 != "object" || typeof item_2 != "object"){
		//console.log("One not an object")
		return false;
	}
	//if either item 1 or item 2 are false but not both return f	
	if(item_1 == null || item_2 == null){
		return false;
	}

	var count1 = countProperties(item_1);

	if (count1 != countProperties(item_2)){
		//console.log("Length unequal")
		return false;
	}
	else
		//console.log("Equal Length");
	//call recursive 
	for(var item in item_2){
		if(!(item in item_1) || !deepEqual(item_1[item], item_2[item]))
			return false
	}
	return true;
}

function countProperties(obj){
	count = 0;
	//console.log("Counting object");
	//count number of items in 
	for(var x in obj)
			{
				if (obj.hasOwnProperty(x))
					count++;
			}
	return count;
}


var string1 = "the first";
var string2 = "the second";
var obj1 = {here: {is: "an"}, object: 2, object2: 3};
var obj2 = {here: 1, object: 2};
var obj3 = {here: 1, object: 2};
//book test cases
console.log("Book Tests");
var obj = {here: {is: "an"}, object: 2};

console.log(deepEqual(obj, obj));
// → true
console.log(deepEqual(obj, {here: 1, object: 2}));
// → false
console.log(deepEqual(obj, {here: {is: "an"}, object: 2}));
// → true

//my test cases
console.log("My Tests");
console.log(deepEqual(3,3));
//true
console.log(deepEqual(5,4));
//false
console.log(deepEqual(null, 5));
//false
console.log(deepEqual(null, null));
//true
console.log(deepEqual(obj1, null));
//false
console.log(deepEqual(string1, string1));
//true
console.log(deepEqual(string1, string2));
//false
console.log(deepEqual(obj2, obj2));
//true
console.log(deepEqual(obj1, obj2));
//false
console.log(deepEqual(obj2, obj3));
//true
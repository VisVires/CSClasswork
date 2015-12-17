/*
//Part 1 of JS Functions Assignment
console.log("Part 1")
fizzBuzz(20);

function fizzBuzz(x)
{
    for (var i = 1; i <= x; i++){
        if (i % 3 == 0 && i % 5 == 0){
            console.log("FizzBuzz");
        } else if(i % 3 == 0){
            console.log("Fizz");
        } else if(i % 5 == 0){
            console.log("Buzz");
        } else {
            console.log(i);
        }
    }
}

//Part 2 of JS Functions Assignment
console.log("Part 2")
var word = "abcdefghijklmnopqrtuvwxyz";

console.log(word);
//console.log(reverseString(word));

var reverseString = function (input)
{
    var o = "";
    for(var i = input.length - 1; i >= 0; --i)
        o += input[i];
    return o;
}

console.log(word);
console.log(reverseString(word));

//Looping a Triangle
var stair = '#';
var stairs = stair;
while (stairs.length <= 7)
{
    console.log(stairs)
    stairs = stairs + stair;
}
*/
//Example 5

function buildList(list) {
    var result = [];
    for (var i = 0; i < list.length; i++){
    	result[i] = function(x){
    		return function(){
        		var item = 'item' + list[x];
        		result.push(function() {alert(item + ' ' + list[x])} );
    		};
    	}(i);
	}
    return result;
}
 
function testList() {
    var fnlist = buildList([1,2,3]);
    // using j only to help prevent confusion - could use i
    for (var j = 0; j < fnlist.length; j++) {
        fnlist[j]();
    }
}

testList();
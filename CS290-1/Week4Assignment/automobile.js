function Automobile(year, make, model, type) {
    this.year = year; //integer (ex. 2001, 1995)
    this.make = make; //string (ex. Honda, Ford)
    this.model = model; //string (ex. Accord, Focus)
    this.type = type; //string (ex. Pickup, SUV)
}

var automobiles = [
    new Automobile(1995, "Honda", "Accord", "Sedan"),
    new Automobile(1990, "Ford", "F-150", "Pickup"),
    new Automobile(2000, "GMC", "Tahoe", "SUV"),
    new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
    new Automobile(2005, "Lotus", "Elise", "Roadster"),
    new Automobile(2008, "Subaru", "Outback", "Wagon")
];

/*TEST SORT
var arr = [5, 7, 98, 2, 5, 8, 2, 84, 33, 12];
console.log(arr);
console.log(sortArr(exComparator, arr));
*/

/*This function sorts arrays using an arbitrary 
comparator. You pass it a comparator and an array 
of objects appropriate for that comparator and it 
will return a new array which is sorted with the 
largest object in index 0 and the smallest in the 
last index*/
function sortArr(comparator, array) {
    //get size
    var size = array.length;
    //make shallow copy of array
    var arr2 = array.slice(0, size);
    //set max
    var max = 0;
    for (var i = 0; i < size; ++i){
        max = i;
        //find a larger item in array
        for(var j = i+1; j < size; ++j)
        {
            if (comparator(arr2[j], arr2[max]))
                max = j;
        }
        //if not i swap with max
        if(i != max)
        {
            swapItems(arr2, i, max);
        }
    }
    return arr2;
}

function swapItems(array, i, j)
{
    var temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

/*A comparator takes two arguments and uses some 
algorithm to compare them. If the first argument is 
larger or greater than the 2nd it returns true, 
otherwise it returns false. Here is an example that 
works on integers*/
function exComparator(int1, int2) {
    if (int1 > int2) {
        return true;
    } else {
        return false;
    }
}

/*For all comparators if cars are 'tied' 
according to the comparison rules then the 
order of those 'tied' cars is not specified 
and either can come first*/

/*This compares two automobiles based on their year. 
Newer cars are "greater" than older cars.*/

function yearComparator(auto1, auto2) {
    /* your code here*/
    if (auto1.year > auto2.year){
        return true;
    } else {
        return false;
    }
}

/*This compares two automobiles based on their make. 
It should be case insensitive and makes which are 
alphabetically earlier in the alphabet are "greater" 
than ones that come later.*/

function makeComparator(auto1, auto2) {
    auto1 = auto1.make.toUpperCase();
    auto2 = auto2.make.toUpperCase();
    if(auto1 < auto2) {
        return true;
    } else {
        return false;
    }
}

/*This compares two automobiles based on their type. 
The ordering from "greatest" to "least" is as follows: 
roadster, pickup, suv, wagon, (types not otherwise listed). 
It should be case insensitive. If two cars are of equal type 
then the newest one by model year should be considered "greater".*/

function typeComparator(auto1, auto2) {
    //correct for differences in case
    auto1type = auto1.type.toLowerCase();
    auto2type = auto2.type.toLowerCase();
    var carType1, carType2;
    //assign car types to a number starting with auto1
    switch(auto1type){
        case "wagon":
                carType1 = 1;
                break;
        case "suv":
                carType1 = 2;
                break;
        case "pickup":
                carType1 = 3;
                break;
        case "roadster":
                carType1 = 4;
                break;
        //if not listed
        default:
                carType2 = 0;
                break;
    }
    switch(auto2type){
        case "wagon":
                carType2 = 1;
                break;
        case "suv":
                carType2 = 2;
                break;
        case "pickup":
                carType2 = 3;
                break;
        case "roadster":
                carType2 = 4;
                break;
        //if not listed
        default:
                carType2 = 0;
                break;
    }
    //compare car types if equal types compare by year
    if (carType1 > carType2){
        return true;
    } else if (carType1 == carType2) {
        if(yearComparator(auto1, auto2)) {
            return true;
        } else {
            return false;
        } 
    } else {
        return false;
    }
}

/*Your program should output the following to 
the console.log, including the opening and closing 
5 stars. All values in parenthesis should be replaced 
with appropriate values. Each line is a seperate call to console.log.

Each line representing a car should be produced via a 
logMe function. This function should be added to the Automobile 
class and accept a single boolean argument. If the argument is 
'true' then it prints "year make model type" with the year, make, 
model and type being the values appropriate for the automobile. 
If the argument is 'false' then the type is ommited and just the "year make model" is logged.


*****
The cars sorted by year are:
(year make model of the 'greatest' car)
(...)
(year make model of the 'least' car)

The cars sorted by make are:
(year make model of the 'greatest' car)
(...)
(year make model of the 'least' car)

The cars sorted by type are:
(year make model type of the 'greatest' car)
(...)
(year make model type of the 'least' car)
*****

As an example of the content in the parenthesis:
1990 Ford F-150 */

//logMe function
Automobile.prototype.logMe = function (bool) {
    if (bool) {
        console.log(this.year + ' ' + this.make + ' ' + this.model + ' ' + this.type);
    } else {
        console.log(this.year + ' ' + this.make + ' ' + this.model);
    }
};

//set stars variable
var stars = "*****"

//make automobiles object into a map
var carMap = automobiles.map(function (car) {
    return car;
});

//get sorted arrays
var byYear = sortArr(yearComparator, carMap);
var byMake = sortArr(makeComparator, carMap);
var byType = sortArr(typeComparator, carMap);

//output stars
console.log(stars);

//output sorted arrays
console.log("The cars sorted by year are: ");
byYear.forEach(function (car){
    car.logMe(false);
});

console.log("\nThe cars sorted by make are: ");
byMake.forEach(function (car){
    car.logMe(false);
});

console.log("\nThe cars sorted by type are: ")
byType.forEach(function (car){
    car.logMe(true);
});

//output stars
console.log(stars);
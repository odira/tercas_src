.pragma library

/* Translate month number to month name
 * */
function getMonthName (num) {
    if (num === 1) return qsTr("Январь");
    else if (num === 2) return qsTr("Февраль");
    else if (num === 3) return qsTr("Март");
    else if (num === 4) return qsTr("Апрель");
    else if (num === 5) return qsTr("Май");
    else if (num === 6) return qsTr("Июнь");
    else if (num === 7) return qsTr("Июль");
    else if (num === 8) return qsTr("Август");
    else if (num === 9) return qsTr("Сентябрь");
    else if (num === 10) return qsTr("Октябрь");
    else if (num === 11) return qsTr("Ноябрь");
    else if (num === 12) return qsTr("Декабрь");
}

function getMonthName0 (num) {
    return getMonthName(num + 1)
}

function getDayOfWeekNameAbbr (num) {
    var weekdays = new Array(7);
    weekdays[0] = "пн";  // "Sunday"
    weekdays[1] = "вт";  // "Monday"
    weekdays[2] = "ср";  // "Tuesday"
    weekdays[3] = "чт";  // "Wednesday"
    weekdays[4] = "пт";  // "Thursday"
    weekdays[5] = "сб";  // "Friday"
    weekdays[6] = "вс";  // "Saturday"

    var DayOfWeekNameAbbr = weekdays[num];
    return DayOfWeekNameAbbr;
}

function getShiftNum (date) {
    var jDate = new Date(1, 0, 1);
    var shiftNum = 4;

    var dif = (date - jDate) / 1000 / 60 / 60 / 24 % 6;
    if (dif === 0 || dif === 1 || dif === 2 || dif === 3)
        return 4;

    return 0;
}

function getShiftColor (date) {
    var jDate = new Date(1, 0, 0);  // 0-0-1 A.C
    var shiftNum = 4;
    var theColor;

    var dif = (date - jDate) /1000 /60 /60 /24 %6;
    if (dif === 0 || dif === 1 || dif === 2 || dif === 3) {
        theColor = "#f9eeda";
    } else {
        theColor = "white";
    }

    return theColor;
}

function addDay (date) {
    date.setDate(date.getDate() + 1);
    return date;
}
function subtrackDay (date) {
    date.setDate(date.getDate() - 1);
    return date;
}
function addMonth(date) {
    date.setMonth(date.getMonth() + 1);
    return date;
}
function subtrackMonth(date) {
    date.setMonth(date.getMonth() - 1);
    return date;
}
function addYear(date) {
    date.setFullYear(date.getFullYear() + 1);
    return date;
}
function subtrackYear(date) {
    date.setFullYear(date.getFullYear() - 1);
    return date;
}

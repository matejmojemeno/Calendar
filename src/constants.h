#pragma once

//different time units in minutes
const long long YEAR = 525600;
const long long WEEK = 10080;
const long long DAY = 1440;
const long long HOUR = 60;
const long long LEAP_YEAR_DAYS = 366;
const long long MAX_YEAR = 2000000000;

const int ONE_DAY = 1;
const int DAYS_IN_WEEK = 7;
const int DAYS_IN_TWOWEEKS = 14;

//"sun" + space
const int DAY_SIZE = 4;
//dont want your days right on the edge, do ya?
const int OFFSET = 3;

//first item in main menu
const int DISPLAY = 0;
//second item in main menu
const int EVENT = 1;
//last item in main menu
const int EXIT = 2;

//first item in event menu
const int ADD = 0;
//second item in event menu
const int IMPORT = 1;
//third item in event menu
const int FIND_NAME = 2;
//third item in event menu
const int FIND_PLACE = 3;
//last item in event menu, also ctrl+d on keyboard to go back in program
const int BACK = 4;
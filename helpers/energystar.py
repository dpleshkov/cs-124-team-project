import csv

file = open("../data/EnergyStar.csv", "r", encoding="utf8")
reader = csv.reader(file)


def get_sleep_mode(row):
    for index in [20, 35, 50, 65, 80, 95, 110, 152]:
        if row[index]:
            return row[index]
    return "-1"


def get_long_idle(row):
    for index in [21, 36, 51, 66, 81, 96, 111, 153]:
        if row[index]:
            return row[index]
    return "-1"


def get_short_idle(row):
    for index in [22, 37, 52, 67, 82, 97, 112, 154]:
        if row[index]:
            return row[index]
    return "-1"


def get_tec(row):
    for index in [25, 40, 55, 70, 85, 100, 115, 155]:
        if row[index]:
            return row[index]
    return "-1"


for r in reader:
    print(r[2] + "|" + r[3] + "|" + r[4] + "|" + r[7] + "|" + get_sleep_mode(r) + "|" + get_long_idle(r) + "|" + get_short_idle(r) + "|" + get_tec(r))

from bs4 import BeautifulSoup
from requests import get

computers = []

for x in range(1, 15):
    page = get("http://www.tpcdb.com/list.php?page=%s&type=13" % x).text
    soup = BeautifulSoup(page, "html.parser")
    row_count = 0
    for Row in soup.find_all("tr"):
        for child in Row.children:
            row = ""
            i = 0
            for r in child.children:
                if i == 2:
                    #print("Brand:", r.a.text)
                    row += r.a.text + "|"
                if i == 3:
                    #print("Model:", r.a.text)
                    row += r.a.text + "|"
                if i == 4:
                    #print("Normal:", r.text)
                    if len(r.text):
                        row += r.text.split()[0] + "|"
                if i == 5:
                    #print("Standby:", r.text)
                    if len(r.text):
                        row += r.text.split()[0] + "|"
                if i == 6:
                    #print("Max:", r.text)
                    if len(r.text):
                        row += r.text.split()[0]
                i += 1
            if len(row):
                computers.append(row)
        row_count += 1

for r in computers:
    print(r)
import csv
import sys

teams = []
# TODO: Read teams into memory from file
with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        teams.append(row)

print(teams)

"""counts = {
    "Paris": 0,
    "Marsillia": 2,
    "Lille": 6
}

if "Paris" in counts:
    counts["Paris"] += 1

print(counts["Paris"]) """